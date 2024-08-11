/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:06:40 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/11 17:05:40 by wdegraf          ###   ########.fr       */
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
	while (arr->ken[0]->str[i] && arr->ken[0]->str[i][0] == '-'
			&& arr->ken[0]->str[i][1] == 'n')
	{
		j = 2;
		while (arr->ken[0]->str[i][j] == 'n')
			j++;
		if (arr->ken[0]->str[i][j] != '\0')
			break;
		minus_nl = true;
		i++;
	}
	while (i < arr->size)
	{
		printf("%s", arr->ken[0]->str[i]);
		if (i + 1 < arr->size)
			printf(" ");
		i++;
	}
	if (minus_nl == false)
		printf("\n");
}