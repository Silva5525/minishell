/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:07:05 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/14 20:59:46 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	ft_pwd(void)
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
	if (setenv("OLDPWD", oldpwd, 1) == -1)
		return (free(pwd),
			write(2, "Error, setenv failed in set_pwd\n", 33), false);
	if (setenv("PWD", pwd, 1) == -1)
		return (free(pwd),
			write(2, "Error, setenv failed in set_pwd\n", 33), false);
	free(pwd);
	return (true);
}

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
	size_t		argc;
	size_t		i;

	argc = arr->size;
	i = 0;
	argv = (char **)malloc((argc + 1) * sizeof(char *));
	if (!argv)
	{
		write(2, "Error, malloc failed in b_cd\n", 29);
		free_tokens(arr);
		return ;
	}
	while (i < argc)
	{
		argv[i] = arr->ken[i]->str;
		i++;
	}
	argv[argc] = NULL;
	if (!ft_cd(argv))
		write(2, "Error, ft_cd in b_cd failed\n", 28);
	else if (!ft_pwd())
		write(2, "Error, ft_pwd in b_cd failed\n", 29);
	free(argv);
}

// void b_cd(t_arr *arr)
// {
// ///	(void)envp; needs a way biger implementation for pwd
// 	if (!arr->ken[1]->str || chdir(arr->ken[1]->str) == -1)
// 		write(2 ,"cd: No such file or directory\n", 30);
// }
