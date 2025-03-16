//poner header

#include "libft.h"

char    *ft_strcpy(char *dest, char *src)
{
    int i;

    if (!dest || !src)
        return (NULL);
    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}