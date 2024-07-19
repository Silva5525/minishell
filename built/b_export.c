/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:07:54 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/19 13:10:06 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	b_export(t_arr *arr)
{
	size_t	i;
	char	*str;
	char	*tmp;

	i = 1;
	while (i < arr->size)
	{
		str = ft_strndup(arr->ken[i]->str, ft_strchr(arr->ken[i]->str, '=') - arr->ken[i]->str);
		if (!str)
		{
			write(2, "Error, ft_strndup in b_export\n", 31);
			free_tokens(arr);
			exit(EXIT_FAILURE);
		}
		tmp = ft_strchr(arr->ken[i]->str, '=');
		if (tmp)
		{
			tmp++;
			if (ft_arr_setenv(str, tmp, arr->envp, arr) == -1)
			{
				write(2, "Error, ft_arr_setenv in b_export\n", 33);
				free(str);
				free_tokens(arr);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (ft_arr_setenv(str, "", arr->envp, arr) == -1)
			{
				write(2, "Error, ft_arr_setenv in b_export\n", 33);
				free(str);
				free_tokens(arr);
				exit(EXIT_FAILURE);
			}
		}
		free(str);
		i++;
	}	
}