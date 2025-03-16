//header

#include "libft.h"

char    *ft_strcat(char *dest, char *src)
{
    int i;
    int j;

    if (!dest || !src)
        return (NULL);
    i = 0;
    while (dest[i])
        i++;
    j = 0;
    while (src[j])
    {
        dest[i] = src[j];
        j++;
        i++;
    }
    dest[i] = '\0';
    return (dest);
}