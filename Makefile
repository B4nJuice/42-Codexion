NAME			= codexion

CODEXION_CODER_DIR	= src/coder/
CODEXION_CODER		= create_coders.c \
					release_dongles.c \
					take_dongles.c

CODEXION_DONGLE_DIR	= src/dongle/
CODEXION_DONGLE		= create_dongles.c \
					destroy_dongles.c \
					get_dongle.c

CODEXION_UTILS_DIR	= src/utils/
CODEXION_UTILS		= log.c \
					timestamp.c \
					fill_params.c

CODEXION_MONITORING_DIR	= src/monitoring/
CODEXION_MONITORING		= monitoring_routine.c

SRCS				= codexion.c \
					$(addprefix $(CODEXION_CODER_DIR), $(CODEXION_CODER)) \
					$(addprefix $(CODEXION_DONGLE_DIR), $(CODEXION_DONGLE)) \
					$(addprefix $(CODEXION_UTILS_DIR), $(CODEXION_UTILS)) \
					$(addprefix $(CODEXION_MONITORING_DIR), $(CODEXION_MONITORING))

OBJS_DIR			= .objects
OBJS				= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

INCLUDES_DIR		= src/includes

CC					= cc
CFLAGS				= -Wall -Wextra -Werror
IFLAGS				= -I $(INCLUDES_DIR)
LFLAGS				= -pthread

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)/src/coder $(OBJS_DIR)/src/dongle $(OBJS_DIR)/src/utils $(OBJS_DIR)/src/monitoring

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re