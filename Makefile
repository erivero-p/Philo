NAME = philosophers
FLAGS = -Wall -Werror -Wextra
SRC_DIR = src/
SRC = args.c init.c main.c routine.c states.c
OBJ_DIR = objs/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@cc $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(FLAGS) -o $(NAME) $(OBJ)
	@ echo "philosophers compiled"
clean:
	@rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
