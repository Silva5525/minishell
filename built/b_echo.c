/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:06:40 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/12 14:09:29 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void b_echo(char **args)
{
	bool 	minus_nl;
	size_t		i;

	minus_nl = false;
	i = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
	{
		minus_nl = true;
		args++;
	}
	while (args[i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", args[i]);
	}
	if (minus_nl == false)
		printf("\n");
}