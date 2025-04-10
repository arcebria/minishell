/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:10:54 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/09 19:13:45 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"  // Asumiendo que tienes tus propias funciones

void    *ft_realloc(void *ptr, size_t old_size, size_t new_size) {
    void    *new_ptr;
    size_t  copy_size;

    if (new_size == 0) {
        free(ptr);
        return (NULL);
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return (NULL);
    if (ptr) {
        copy_size = old_size < new_size ? old_size : new_size;
        ft_memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }
    return (new_ptr);
}