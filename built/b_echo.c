/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:06:40 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/17 15:50:58 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void b_echo(t_arr *arr)
{
	bool 	minus_nl;
	size_t		i;
	size_t		j;

	minus_nl = false;
	i = 1;
	while (arr->ken[i] && ft_strncmp(arr->ken[i]->str, "-n", 2) == 0)
	{
		j = 2;
		while (arr->ken[i]->str[j] == 'n')
			j++;
		if (arr->ken[i]->str[j] != '\0')
			break;
		minus_nl = true;
		i++;
	}
	while (i < arr->size)
	{
		printf("%s", arr->ken[i]->str);
		if (i + 1 < arr->size)
			printf(" ");
		i++;
	}
	if (minus_nl == false)
		printf("\n");
}