# gcc main.c lexer/main_lexer.c lexer/check_slpit.c - libft/libft.a
NAME = minishell

CC = cc

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3


SRC = main.c lexer/main_lexer.c lexer/check_slpit.c lexer/utils.c lexer/utils2.c lexer/delimiters/qoutes.c lexer/delimiters/quotes_utils.c lexer/delimiters/parentheses.c lexer/delimiters/input_output.c \
	lexer/delimiters/string.c lexer/delimiters/pipe.c lexer/delimiters/env.c\
	lexer/delimiters/white_spaces.c free_functions/ft_malloc.c expand/expand.c expand/utils.c parce/check_quotes.c parce/helpers.c parce/helpers_2.c parce/parcing.c \
	parce/utils.c parce/utils2.c parce/utils3.c parce/utils4.c execution/execution.c execution/builtin1_echo.c execution/builtin2_cd.c syntax/syntax.c syntax/utils.c quotes/d_quotes.c \
	execution/builtin3_env.c execution/builtin4_pwd.c execution/builtin5_unset.c execution/heredoc/heredoc.c  execution/builtin6_export.c \
	execution/heredoc/utils.c execution/utils_malloc.c execution/builtin7_exit.c execution/execution_utils.c execution/single_cmd.c execution/multi_cmd.c execution/redirection_append.c \
	execution/heredoc/ex_node.c execution/heredoc/ex.c 

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -lreadline -o $(NAME)
# $(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -lreadline -o $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean :
	rm -f $(OBJ) $(NAME)

re : fclean all

run : re
	./minishell

a : all clean

.SECONDRY : $(OBJ)
