/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:26:13 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/16 20:12:40 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin(t_arr *arr)
{
	size_t	i;
	t_b built[] =
	{
		// {"echo", b_echo},
		{"cd", b_cd},
		// {"pwd", b_pwd},
		// {"export", b_export},
		// {"unset", b_unset},
		// {"env", b_env},
		{"exit", b_exit},
		{NULL, NULL}
	};
	i = 0;
	while (built[i].name)
	{
		if (ft_strcmp(arr->ken[0]->str, built[i].name) == 0)
		{
			built[i].fun(arr);
			return ;
		}
		i++;
	}
	/// maybe some execution handling for non builtins ? exit maybe too xD
}
