

#include "../../minishell.h"

int ft_here_isalnum(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
        return 1;
    return 0;
}

size_t ft_here_strlen(const char *s)
{
    size_t len = 0;
    while (s[len] != '\0')
    {
        len++;
    }
    return len;
}

char *ft_here_strncat(char *dest, const char *src, size_t n)
{
    char *d = dest;

    while (*d != '\0')
        d++;
    while (n-- && *src != '\0')
        *d++ = *src++;
    *d = '\0';
    return dest;
}


char *ft_here_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

char *ft_here_strchr(const char *s, int c)
{
    while (*s != '\0')
    {
        if (*s == (char)c)
        {
            return (char *)s;
        }
        s++;
    }
    if (c == '\0')
    {
        return (char *)s;
    }
    return NULL;
}

char *ft_here_strcat(char *dest, const char *src)
{
    char *d = dest;
    while (*d != '\0')
        d++;
    while (*src != '\0')
        *d++ = *src++;
    return dest;
}