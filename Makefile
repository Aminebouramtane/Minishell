# gcc main.c lexer/main_lexer.c lexer/check_slpit.c - libft/libft.a
NAME = minishell

CC = CC

CFLAGS = -Wall -Wextra -Werror

SRC = lexer/main_lexer.c lexer/check_slpit.c

OBJ = $(SRC=.c:.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean :
	rm -f $(OBJ) $(NAME)

re : fclean all