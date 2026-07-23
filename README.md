*This project has been created as part of the 42 curriculum by lgirard.*

## Description

### Project Goal

Codexion is a concurrent C program that simulates a set of coders competing for a limited number of dongles in order to compile, debug, and refactor.

The project focuses on:

- thread creation and coordination with `pthread`
- shared-resource management with mutexes and condition variables
- fair dongle allocation using FIFO or EDF scheduling
- burnout detection through a monitoring thread
- log serialization in a multi-threaded environment

### Overview

The simulation is built around three main actors:

- Coders: worker threads that alternate between compiling, debugging, and refactoring
- Dongles: shared resources that must be acquired before a coder can compile
- Monitor: a dedicated thread (the main one) that starts the simulation and checks for burnout or completion

Each coder must acquire two dongles before compiling. After each compile, the coder may continue until it reaches the required number of compilations or until a burnout occurs.

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

Available targets:

- `make clean` to remove object files
- `make fclean` to remove object files and the executable
- `make re` to rebuild everything

Compilation flags used by the project:

- `-Wall -Wextra -Werror` for strict warning handling
- `-std=c89` for C89 compatibility
- `-pthread` for POSIX threads
- `-D_XOPEN_SOURCE=500` to expose the POSIX prototype of `usleep`

### Execution

Run the simulation with:

```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

Parameters:

- `number_of_coders` (`int`): number of coder threads
- `time_to_burnout` (`int`): milliseconds before a coder burns out if it does not compile
- `time_to_compile` (`int`): compilation duration in milliseconds
- `time_to_debug` (`int`): debugging duration in milliseconds
- `time_to_refactor` (`int`): refactoring duration in milliseconds
- `number_of_compiles_required` (`int`): number of successful compiles required per coder
- `dongle_cooldown` (`int`): cooldown time in milliseconds before a dongle can be reused
- `scheduler` (`string`): `fifo` or `edf`

Example:

```bash
./codexion 5 800 200 100 50 3 100 edf
```

### Output Format

The program prints timestamped log lines in the following format:

```text
<timestamp> <coder_id> <action>
```

Common actions:

- `has taken a dongle`
- `is compiling`
- `is debugging`
- `is refactoring`
- `has burned out`

## Resources

### Documentation & References

- POSIX Threads:
	- `man pthread_create`
	- `man pthread_join`
	- `man pthread_mutex_init`
	- `man pthread_mutex_lock`
	- `man pthread_mutex_unlock`
	- `man pthread_cond_wait`
	- `man pthread_cond_broadcast`
- Standard C Library:
	- `man malloc`
	- `man free`
	- `man usleep`
	- `man gettimeofday`
- Concurrency concepts:
	- mutual exclusion
	- condition variables
	- starvation prevention
	- resource scheduling with FIFO and EDF

### AI Usage

AI assistance was used to help structure the documentation, clarify concurrency concepts, and polish the README presentation.

## Blocking Cases Handled

### 1. Deadlock Prevention

Issue addressed: coders could otherwise wait forever while trying to acquire the two dongles they need.

Solution implemented:

- Each coder acquires a consistent pair of dongles
- The scheduler can reorder dongle checks to reduce unfair waiting
- Mutex-protected acquisition keeps the resource state coherent

### 2. Starvation Prevention

Issue addressed: a coder with a tighter burnout deadline could be delayed too long.

Solution implemented:

- EDF scheduling prioritizes coders closer to burnout
- The monitor thread keeps checking the simulation regularly
- `pthread_cond_broadcast` wakes waiting coders when the simulation state changes

### 3. Cooldown Handling

Issue addressed: dongles must not be reused immediately after release.

Solution implemented:

- Each dongle stores the timestamp of the last time it was taken
- Reuse is blocked until the cooldown expires
- The cooldown check is done under the dongle mutex

### 4. Precise Burnout Detection

Issue addressed: a coder may burn out while another thread is still updating shared state.

Solution implemented:

- Burnout checks read coder state under the coder mutex
- The monitor compares the last compile time against the burnout threshold
- When a burnout is detected, the simulation is stopped immediately

### 5. Log Serialization

Issue addressed: concurrent writes to stdout can produce unreadable output.

Solution implemented:

- A dedicated print mutex protects all logs
- Each log line is written atomically
- The burnout message also stops the simulation cleanly

## Thread Synchronization Mechanisms

### Synchronization Primitives Used

#### 1. `pthread_mutex_t` - Mutual Exclusion Locks

Global mutexes:

- `stop_mutex`: protects the global stop flag
- `print_mutex`: serializes logging output
- `start_mutex`: protects the simulation start barrier

Per-object mutexes:

- `dongle->mutex`: protects the state of a single dongle
- `coder->mutex`: protects the compile count and last compile timestamp of a coder

#### 2. `pthread_cond_t` - Condition Variables

The global condition variable is used as a start barrier:

- coder threads wait until the monitor starts the simulation
- once the monitor is ready, it broadcasts to all coders

This avoids coders acting before the shared state is initialized.

### Thread-Safe Communication Patterns

#### Pattern 1: Atomic Dongle Acquisition

Dongle acquisition is guarded by the dongle mutex so the check and the state change happen in the same critical section.

This prevents:

- double allocation
- inconsistent dongle state
- race conditions during release and reuse

#### Pattern 2: Burnout Detection with the Monitor

The monitor thread iterates over all coders and checks whether a coder has exceeded its burnout time.

This ensures:

- regular supervision of the simulation
- immediate shutdown when a burnout occurs
- consistent reads of coder state

#### Pattern 3: Log Serialization

All log output is protected by a single mutex so each line is printed completely before another thread can write.

This prevents:

- interleaved output
- mixed timestamps
- unreadable logs

### Race Condition Examples and Prevention

Race Condition 1: double dongle allocation

- Without protection, two coders could observe the same dongle as available and both take it
- With a mutex, only one thread can update the dongle state at a time

Race Condition 2: corrupted compile timestamps

- Without protection, one thread could read a coder timestamp while another updates it
- With the coder mutex, reads and writes remain coherent

Race Condition 3: garbled console output

- Without protection, logs from different threads can overlap
- With the print mutex, each message remains intact

### Scheduling Implementation

#### FIFO Scheduling

- coders are handled in arrival order
- behavior remains simple and deterministic
- fair enough when all coders have similar deadlines

#### EDF Scheduling

- coders closest to burnout are prioritized
- better suited for deadline-sensitive simulations
- helps reduce starvation for urgent coders

## Technical Architecture

### Module Organization

- `src/coder/`: coder thread routine, dongle acquisition, coder creation
- `src/dongle/`: dongle creation, lookup, and release helpers
- `src/monitoring/`: monitor loop and burnout checks
- `src/utils/`: initialization, logging, timestamps, argument validation, stop state helpers
- `src/includes/`: shared project headers and structure definitions

### Key Design Decisions

1. Per-object mutexes reduce contention compared to a single global lock
2. A monitor thread centralizes burnout detection and startup coordination
3. A condition variable avoids busy waiting at startup
4. FIFO and EDF provide two different allocation strategies with the same core code
5. Timestamped logging makes simulation behavior easy to inspect

## Conclusion

Codexion is a compact concurrency project that demonstrates shared-resource management, mutex-protected state, thread coordination, and scheduling under constraints.

The codebase focuses on practical POSIX threading patterns rather than higher-level abstractions, which makes it a good exercise in synchronization and race-condition prevention.
