/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:14:38 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/13 16:42:04 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief ft_realloc reallocates memory for a pointer to a new size and frees
/// the old pointer. If the new size is 0 the old pointer will be freed and
/// NULL will be returned.
/// @param ptr the old pointer
/// @param old_size the old size of the pointer
/// @param new_size the new size of the pointer
/// @return the new pointer with the old information and the new size, or NULL
/// if malloc fails or new_size is 0.
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

// int	main(void)
// {
// 	char *ptr;
// 	char *new_ptr;
	
// 	ptr = malloc(10);
// 	ptr = ft_memset(ptr, 'a', 10);
// 	new_ptr = ft_realloc(ptr, 10, 20);
// 	if (!new_ptr)
// 		return (1);
// 	new_ptr = ft_memset(new_ptr, 'b', 20);
// 	free(new_ptr);
// 	return (0);
// }