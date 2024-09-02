/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:06:40 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/28 20:34:07 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief Outputs the string array with a space between each element.
/// If minus_nl is false, a newline is added at the end.
/// @param arr all information about the shell
/// @param i index of the string array
/// @param minus_nl boolean to add a newline at the end
static void	split_b_echo(t_arr *arr, size_t i, bool minus_nl)
{
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

/// @brief Handles the echo command.
/// The echo command writes any specified operands,
/// separated by a single space and followed by a newline.
/// If the -n option is specified, the trailing newline
/// is suppressed.
/// @param arr all information about the shell
void	b_echo(t_arr *arr)
{
	bool		minus_nl;
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
			break ;
		minus_nl = true;
		i++;
	}
	split_b_echo(arr, i, minus_nl);
}
