/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:07:05 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/18 22:40:47 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/// @brief ft_pwd sets the PWD and OLDPWD environment variables with:
/// getcwd to get the current working directory
/// getenv to get the value of the environment variable PWD
/// ft_etenv to set the value of the environment variable PWD
/// @return true if successful, false otherwise
static bool	ft_pwd(t_arr *arr)
{
	char		*pwd;
	char		*oldpwd;

	pwd = getcwd(NULL, 0);
	oldpwd = getenv("PWD");
	if (!pwd)
		return (write(2, "Error, getcwd failed in set_pwd\n", 32), false);
	if (!oldpwd)
		return (free(pwd),
			write(2, "Error, getenv failed in set_pwd\n", 32), false);
	if (ft_arr_setenv("OLDPWD", oldpwd, arr->envp, arr) == -1) 
		return (free(pwd),
			write(2, "Error, setenv failed in set_pwd\n", 33), false);
	if (ft_arr_setenv("PWD", pwd, arr->envp, arr) == -1)
		return (free(pwd),
			write(2, "Error, setenv failed in set_pwd\n", 33), false);
	free(pwd);
	return (true);
}

/// @brief ft cd changes the current working directory to the directory
/// specified in the argument. If no argument is given, it changes the
/// current working directory to the value of the HOME environment variable.
/// @param argv specifies the directory to change to
/// @return true if successful, false otherwise
static bool	ft_cd(char **argv)
{
	if (!argv[1])
	{
		if (chdir(getenv("HOME")) == -1)
			return (write(2, "Error, chdir failed in ft_cd\n", 29),
				false);
	}
	else if (chdir(argv[1]) == -1)
		return (perror("cd"), false);
	return (true);
}

void b_cd(t_arr *arr)
{
	char		**argv;
	char 		*new_direktory;
	size_t		argc;
	size_t		i;

	argc = arr->size;
	i = 0;
	argv = (char **)malloc((argc + 1) * sizeof(char *));
	if (!argv)
	{
		write(2, "Error, malloc failed in b_cd\n", 29);
		free_tokens(arr);
		return;
	}
	while (i < argc)
	{
		argv[i] = arr->ken[i]->str;
		i++;
	}
	argv[argc] = NULL;

	if (!ft_cd(argv))
		write(2, "Error, ft_cd in b_cd failed\n", 28);
	else if (!ft_pwd(arr))
		write(2, "Error, ft_pwd in b_cd failed\n", 29);
	else
	{
		new_direktory = getcwd(NULL, 0);
		if (new_direktory)
		{
			printf("new directory: %s\n", new_direktory);
			free(arr->direktory);
			arr->direktory = new_direktory;
		}
		else
			write(2, "Error, getcwd failed in b_cd\n", 30);
	}
	free(argv);
}
