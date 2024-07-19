/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:26:13 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/19 14:39:59 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/// @brief own implementation of setenv from stdlib.c
/// Checks if *str is valid then searches for the *v variable in the envp array.
/// If the variable is found, it changes the value of the variable.
/// If the variable is not found, it adds the variable to the array.
/// @param str the name of the environment variable to set.
/// @param v value of the environment variable to set.
/// @param envp the enviroment array.
/// @return 0 on success, -1 on error.
char	**ft_arr_setenv(const char *str, const char *v, char **envp, bool first_time)
{
	char	*new;
	char 	*hold;
	int 	i;
	int 	len;

	if (!str || !v || ft_strchr(str, '=') != NULL || *str == '\0')
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, len) == 0 && envp[i][len] == '=')
		{
			if (!first_time)
				free(envp[i]);
			break ;
		}
		i++;
	}
	hold = ft_strjoin(str, "=");
	if (!hold)
		return (NULL);
	new = ft_strjoin(hold, v);
	free(hold);
	if (!new)
		return (NULL);
	if (!envp[i])
	{
		if (!first_time)
		{
			envp = ft_realloc(envp, sizeof(char *) * (i + 1) ,sizeof(char *) * (i + 2));
			if (!envp)
				return (free(new), NULL);
		}
		envp[i + 1] = NULL;
	}
	envp[i] = new;
	return (envp);
}

void	builtin(t_arr *arr)
{
	size_t	i;
	t_b built[] =
	{
		{"echo", b_echo},
		{"cd", b_cd},
		{"pwd", b_pwd},
		{"export", b_export},
		{"unset", b_unset},
		{"env", b_env},
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
