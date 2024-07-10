/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:45 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/07 19:02:07 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief When user press Ctrl+C the input will be canceled
/// and the shell will present a new prompt on a new line.
/// @param sig if sig number is SIGINT it means you pressed Ctrl+C
/// @rl_on_new_line() Prepare Readline to read the next input
/// @rl_replace_line("", 0) clears the current line
/// @rl_redisplay() redisplays the prompt on a cleared line
void read_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/// @brief 
/// @param argc Argument Count
/// @param argv Argument Vector
/// @param envp Environment Pointer (each string is a enviroment variable)
/// @return 
int	main(int argc, char **argv, char **envp)
{
	char *read;
	t_to *ken;
	(void)argc;
	(void)argv;
	(void)envp;

	signal(SIGINT, read_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		read = readline("minishell$ ");
		if (read)
		{
			add_history(read);
			if (ft_strcmp(read, "exit") == 0)
			{
				write(1, "exit\n", 5);
				free(read);
				break;
			}
			printf("Out: %s\n", read);
			free(read);
		}
		else
		{
			write(1, "exit\n", 5);
			break;
		}
		ken = to_ken_ize(read);
	}
	return (0);
}
