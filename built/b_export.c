/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:07:54 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/18 19:15:59 by wdegraf          ###   ########.fr       */
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
		tmp = ft_strchr(arr->ken[i]->str, '=');
		if (tmp)
		{
			tmp++;
			if (ft_setenv(str, tmp, arr->envp, 0) == -1)
			{
				write(2, "Error, ft_setenv in b_export\n", 30);
				free(str);
				free_tokens(arr);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (ft_setenv(str, "", arr->envp, 1) == -1)
			{
				write(2, "Error, ft_setenv in b_export\n", 30);
				free(str);
				free_tokens(arr);
				exit(EXIT_FAILURE);
			}
		}
		free(str);
		i++;
	}	
}