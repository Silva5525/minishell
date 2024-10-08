/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:29:51 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/10 20:43:17 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief The isalnum() function tests for any character for which isalpha(3)
/// or isdigit(3) is true.  The value of the argument must be representable
/// as an unsigned char or the value of EOF.
/// @param c zu testende char
/// @return The isalnum() function returns zero if the character tests false
/// and returns non-zero if the character tests true.
int	ft_isalnum(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	c = '@';
// 	int	out = ft_isalnum(c);

// 	printf("%i", out);
// 	return (EXIT_SUCCESS);
// }
