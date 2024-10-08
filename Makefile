NAME = minishell

CC = cc

LIBFT = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRC = main.c lexer/main_lexer.c lexer/check_slpit.c lexer/count_word.c lexer/utils.c lexer/utils2.c lexer/utils3.c lexer/delimiters/qoutes.c lexer/delimiters/quotes_utils.c lexer/delimiters/parentheses.c lexer/delimiters/input_output.c \
	lexer/delimiters/string.c lexer/delimiters/pipe.c lexer/delimiters/env.c\
	lexer/delimiters/white_spaces.c free_functions/ft_malloc.c free_functions/ft_malloc_utils.c\
	expand/expand.c expand/utils.c\
	parce/check_quotes.c parce/parcing.c parce/helpers.c parce/helpers_2.c parce/utils.c parce/utils2.c parce/utils3.c parce/utils4.c\
	execution/execution.c execution/preparing_execution.c execution/access_errors.c execution/execution_errors.c execution/builtin1_echo.c execution/builtin2_cd.c \
	execution/builtin2_cd_utils.c syntax/syntax.c syntax/utils.c quotes/d_quotes.c \
	execution/builtin3_env.c execution/builtin4_pwd.c execution/builtin5_unset.c execution/heredoc/heredoc.c \
	execution/builtin6_export.c execution/builtin6_export_utils4.c execution/builtin6_export_utils.c execution/builtin6_export_utils2.c execution/builtin6_export_utils3.c \
	execution/heredoc/utils.c execution/utils_malloc.c execution/utils_malloc_1.c execution/builtin7_exit.c execution/builtin7_exit_utils.c execution/execution_utils.c \
	execution/redirection_append.c execution/redirections_utils.c execution/redirection_append_parent.c \
	execution/execution_utils1.c execution/execution_utils2.c execution/execution_utils3.c execution/execution_utils4.c execution/single_cmd.c execution/multi_utils.c execution/multi_utils3.c execution/multi_cmd.c \
	execution/heredoc/ex_node.c execution/heredoc/ex.c execution/heredoc/utils_2.c execution/heredoc/utils_3.c execution/heredoc/utils_4.c execution/shlvl.c signals.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	make all -C ./libft
	$(CC) $(CFLAGS) $(OBJ) ./libft/libft.a -lreadline -o $(NAME)

all : $(NAME)

clean :
	make clean -C ./libft
	rm -f $(OBJ)

fclean :
	make fclean -C ./libft
	rm -f $(OBJ) $(NAME)

re : fclean all

.SECONDRY : $(OBJ)

