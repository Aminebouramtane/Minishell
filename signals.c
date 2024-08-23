#include "minishell.h"

void    ft_handler()
{
   write(1, "\n",1);
   rl_replace_line("", 0);
   rl_on_new_line();
   rl_redisplay();
}
void    ft_handler2()
{
   write(1, "\n",1);
}
void    ft_handler3()
{
    exit(0);
    write(1, "exit\n",1);
}