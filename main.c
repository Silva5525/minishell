/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:45 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/06 12:34:26 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 
/// @param argc Argument Count
/// @param argv Argument Vector
/// @param envp Environment Pointer (each string is a enviroment variable)
/// @return 
int	main(int argc, char **argv, char **envp)
{
	int i;
	
	i = 0;
	printf("argc: %d\n", argc);
	while (argv[i])
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
	i = 0;
	while (envp[i])
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		i++;
	}
	return(0);
}
