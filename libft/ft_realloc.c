/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:14:38 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/19 14:19:03 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "libft.h"

/// @brief ft_realloc reallocates memory for a pointer to a new size and frees
/// the old pointer. If the new size is 0 the old pointer will be freed and
/// NULL will be returned.
/// @param ptr the old pointer
/// @param old_size the old size of the pointer
/// @param new_size the new size of the pointer
/// @return the new pointer with the old information and the new size, or NULL
/// if malloc fails or new_size is 0.
void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;

    if (new_size == 0)
    {
        free(ptr);
        write(2, "Error, ft_realloc new_size is 0\n", 32);
        return (NULL);
    }

    new_ptr = malloc(new_size);
    if (!new_ptr)
    {
        write(2, "Error, ft_realloc new_ptr malloc\n", 33);
        return (NULL);
    }

    if (ptr)
    {
        ft_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
        free(ptr);
    }

    return (new_ptr);
}
