/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:26:13 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/13 15:24:58 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef void (*built_f)(t_arr *arr, char **envp);
typedef struct s_builtin
{
	char	*name;
	built_f	fun;
}	t_b;

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

void	builtin(t_arr *arr, char **envp)
{
	size_t	i;

	i = 0;
	while (built[i].name)
	{
		if (ft_strcmp(arr->ken[0]->str, built[i].name) == 0)
		{
			built[i].fun(arr, envp);
			return ;
		}
		i++;
	}
	/// maybe some execution handling for non builtins ? exit maybe too xD
}
