/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reaalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:14:38 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/13 16:28:42 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;
	size_t copy_size;
	
	copy_size = 0;
	new_ptr = NULL;
	if (new_size == 0)
	{
		free(ptr);
		write (2, "Error, ft_realloc new_size is 0\n", 32);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		free(ptr);
		write(2, "Error, ft_realloc new_ptr malloc\n", 33);
		return (NULL);
	}
	if (!ptr)
		return (new_ptr);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}