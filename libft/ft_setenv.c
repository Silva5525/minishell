/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:34:14 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/18 19:16:58 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief free the memory of the string, variable or environment array.
/// depending on the free_flag.
/// @param str string to free.
/// @param v variable to free.
/// @param envp environment array to free.
/// @param free_flag flag to determine what to free.
static void ask_free( const char *str, const char *v, char **envp, int free_flag)
{
	if (free_flag == 1)
		free((char *)str);
	else if (free_flag == 2)
		free((char *)v);
	else if (free_flag == 3)
	{
		while (*envp)
		{
			free(*envp);
			envp++;
		}
		free(envp);
	}
}

/// @brief own implementation of setenv from stdlib.c
/// Checks if *str is valid then searches for the *v variable in the envp array.
/// If the variable is found, it changes the value of the variable.
/// If the variable is not found, it adds the variable to the array.
/// @param str the name of the environment variable to set.
/// @param v value of the environment variable to set.
/// @param envp the enviroment array.
/// @return 0 on success, -1 on error.
int	ft_setenv(const char *str, const char *v, char **envp, int free_flag)
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
			break;
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
	envp[i + 1] = NULL;
	ask_free(str, v, envp, free_flag);
	return (0);
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
// 	return (0);
// }