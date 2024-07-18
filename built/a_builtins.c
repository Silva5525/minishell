/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:26:13 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/18 21:36:36 by wdegraf          ###   ########.fr       */
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
int	ft_arr_setenv(const char *str, const char *v, char **envp, t_arr *arr)
{
	char	*new;
	char 	*hold;
	int 	i;
	int 	len;

	if (!str || !v || ft_strchr(str, '=') != NULL || *str == '\0')
		return (-1);
	len = ft_strlen(str);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, len) == 0 && envp[i][len] == '=')
		{
			if (!arr->first_time)
				free(envp[i]);
			break ;
		}
		i++;
	}
	hold = ft_strjoin(str, "=");
	if (!hold)
		return (-1);
	new = ft_strjoin(hold, v);
	free(hold);
	if (!new)
		return (-1);
	envp[i] = new;
	return (0);
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
