# gcc main.c lexer/main_lexer.c lexer/check_slpit.c - libft/libft.a
NAME = minishell

CC = cc

LIBFT = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

SRC = main.c lexer/main_lexer.c lexer/check_slpit.c lexer/utils.c lexer/delimiters/qoutes.c lexer/delimiters/parentheses.c lexer/delimiters/input_output.c \
	lexer/delimiters/string.c lexer/delimiters/pipe.c lexer/delimiters/env.c lexer/delimiters/white_spaces.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean :
	rm -f $(OBJ) $(NAME)

re : fclean all