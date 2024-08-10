/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:34:14 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/10 20:42:45 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief own implementation of setenv from stdlib.c
/// Checks if *str is valid then searches for the *v variable in the envp array.
/// If the variable is found, it changes the value of the variable.
/// If the variable is not found, it adds the variable to the array.
/// @param str the name of the environment variable to set.
/// @param v value of the environment variable to set.
/// @param envp the enviroment array.
/// @return 0 on success, -1 on error.
int	ft_setenv(const char *str, const char *v, char **envp)
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
			if (envp[i])
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
	return (EXIT_SUCCESS);
}

// /// ########################################### test main###################

// #include <stdio.h>

// void print_env(char **envp)
// {
// 	while (*envp)
// 	{
// 		printf("%s\n", *envp);
// 		envp++;
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
	
// 	printf("Before setenv:\n");
// 	print_env(envp);
// 	ft_setenv("TEST_VAR", "test", envp);
// 	printf("After setenv:\n");
// 	print_env(envp);
// 	return (EXIT_SUCCESS);
// }