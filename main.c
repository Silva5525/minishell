/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:45 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/06 13:21:17 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

/// @brief 
/// @param argc Argument Count
/// @param argv Argument Vector
/// @param envp Environment Pointer (each string is a enviroment variable)
/// @return 
int	main(int argc, char **argv, char **envp)
{
	char *read;
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		read = readline("minishell$ ");
		if (read)
		{
			add_history(read);
			if (ft_strncmp(read, "exit", 6) == 0)
			{
				free(read);
				break;
			}
			printf("Out: %s\n", read);
			free(read);
		}
		else
			break;
	}
	return(0);
}
