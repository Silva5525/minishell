/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:06:40 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/17 11:49:21 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void b_echo(t_arr *arr)
{
	bool 	minus_nl;
	size_t		i;

	minus_nl = false;
	i = 1;
	if (arr->ken[1] && ft_strncmp(arr->ken[1]->str, "-n", 2) == 0)
	{
		minus_nl = true;
		i++;
	}
	while (i < arr->size)
	{
		printf("%s", arr->ken[i]->str);
		if (i < arr->size - 1)
			printf(" ");
	}
	if (minus_nl == false)
		printf("\n");
}