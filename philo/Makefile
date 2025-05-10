NAME = philo


SRC =	philo_main.c \
		philo_utils.c \
		philo_check_input.c \
		philo_store.c

OBJ_DIR = obj
OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

CC = cc
HEADER = -I.
CFLAGS = -Wall -Wextra -Werror -pthread -g
RM = rm -f
RM_DIR = rm -rf

all: $(NAME)
	@echo "$(NAME) successfully created."

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

 $(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ)
	$(RM_DIR) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re