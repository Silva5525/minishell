/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:26:13 by wdegraf           #+#    #+#             */
/*   Updated: 2024/09/02 19:09:51 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief reallocates the envp array if the variable is not found.
/// @param first_time 
/// @param envp 
/// @param  
/// @param i 
/// @return 
static char	**realloc_envp(bool first_time, char **envp, char *new, int i)
{
	if (!first_time)
	{
		envp = ft_realloc(envp, sizeof(char *)
				* (i + 1), sizeof(char *) * (i + 2));
		if (!envp)
			return (free(new), NULL);
	}
	envp[i + 1] = NULL;
	return (envp);
}

/// @brief loops through the envp array and checks if the variable
/// is already set. If it is, it frees the old variable.
/// @param envp environment array
/// @param first_time true if the function is called for the first time
/// @param str the variable to search for
/// @return index of the variable in the envp array
static int	envp_loop(char **envp, bool first_time, const char *str)
{
	int		i;
	int		len;

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
	return (i);
}

/// @brief own implementation of setenv from stdlib.c
/// Checks if *str is valid then searches for the *v variable in the envp array.
/// If the variable is found, it changes the value of the variable.
/// If the variable is not found, it adds the variable to the array.
/// @param str the name of the environment variable to set.
/// @param v value of the environment variable to set.
/// @param envp the enviroment array.
/// @param first_time if true, the function will not free the old envp.
/// @return the new envp array or NULL if an error occurred.
char	**ft_arr_setenv(const char *str, const char *v
			, char **envp, bool first_time)
{
	char	*new;
	char	*hold;
	int		i;

	if (!str || !v || ft_strchr(str, '=') != NULL || *str == '\0')
		return (NULL);
	i = envp_loop(envp, first_time, str);
	hold = ft_strjoin(str, "=");
	if (!hold)
		return (NULL);
	new = ft_strjoin(hold, v);
	free(hold);
	if (!new)
		return (NULL);
	if (!envp[i])
		realloc_envp(first_time, envp, new, i);
	envp[i] = new;
	return (envp);
}

/// @brief executes the command
/// @param arr holds all data
void	ex_order(t_arr *arr)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid < 0)
	{
		free_tokens(arr);
		write(2, "Error, fork failed in ex_order\n", 31);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(arr->ken[0]->str[0], arr->ken[0]->str, arr->envp) == -1)
		{
			free_tokens(arr);
			write(2, "Error, execve failed in ex_order\n", 33);
			exit(EXIT_FAILURE);
		}
	}
	else /// not sure if this is needed
	{
		waitpid(pid, &stat, 0);
		if (WIFEXITED(stat))
			arr->stat = WEXITSTATUS(stat);
		else if (WIFSIGNALED(stat))
			arr->sig = WTERMSIG(stat);
	}
}

/// @brief checks if the command is a built-in command and executes it
/// @param arr is the struct that holds all data
void	builtin(t_arr *arr)
{
	size_t	i;
	t_b		built[8];

	built[0] = (t_b){"echo", b_echo};
	built[1] = (t_b){"cd", b_cd};
	built[2] = (t_b){"pwd", b_pwd};
	built[3] = (t_b){"export", b_export};
	built[4] = (t_b){"unset", b_unset};
	built[5] = (t_b){"env", b_env};
	built[6] = (t_b){"exit", b_exit};
	built[7] = (t_b){NULL, NULL};
	i = 0;
	while (built[i].name)
	{
		if (ft_strcmp(arr->ken[0]->str[0], built[i].name) == 0)
		{
			built[i].fun(arr);
			return ;
		}
		i++;
	}
	ex_order(arr);
}
