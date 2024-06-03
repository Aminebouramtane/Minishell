

#include "../../minishell.h"

char *expand_env_vars(const char *input)
{
    size_t input_len = ft_here_strlen(input);
    size_t output_size = input_len + 1;
    char *output = (char *)malloc(output_size);
    if (!output) {
        return NULL;
    }
    output[0] = '\0';

    const char *env_var_start;
    const char *env_var_end;
    size_t len_before_var;

    while ((env_var_start = ft_here_strchr(input, '$')) != NULL)
    {
        len_before_var = env_var_start - input;
        ft_here_strncat(output, input, len_before_var);
        env_var_end = env_var_start + 1;
        while (*env_var_end && (ft_here_isalnum(*env_var_end) || *env_var_end == '_'))
            env_var_end++;
        size_t env_var_len = env_var_end - (env_var_start + 1);
        char env_var_name[env_var_len + 1];
        ft_here_strncpy(env_var_name, env_var_start + 1, env_var_len);
        env_var_name[env_var_len] = '\0';
        char *value = getenv(env_var_name);
        if (value)
        {
            size_t new_output_size = ft_here_strlen(output) + ft_here_strlen(value) + 1;
            if (new_output_size > output_size)
            {
                output_size = new_output_size;
                output = (char *)realloc(output, output_size);
                if (!output)
                    return NULL;
            }
            ft_here_strcat(output, value);
        }
        input = env_var_end;
    }
    ft_here_strcat(output, input);
    return output;
}
