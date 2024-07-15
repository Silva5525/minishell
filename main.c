/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:45 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/14 20:32:05 by wdegraf          ###   ########.fr       */
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

void main_process(char *read, char **envp)
{
	t_arr *arr;

	add_history(read);

	printf("Out: %s\n", read);
	arr = to_ken_producer(read);
	if (!arr)
	{
		free(read);
		write(2, "Error, to_ken_producer\n", 24);
		return ;
	}
	arr->envp = envp;
	builtin(arr);
	size_t i = 0;
	while ( i < arr->size)
	{
		printf("Token: %s Type: %c\n", arr->ken[i]->str, arr->ken[i]->typ);
		i++;
	}
	free_tokens(arr);
	free(read);
}

/// @brief 
/// @param argc Argument Count
/// @param argv Argument Vector
/// @param envp Environment Pointer (each string is a enviroment variable)
/// @return 
int	main(int argc, char **argv, char **envp)
{
	char	*read;
	(void)argc;
	(void)argv;

	signal(SIGINT, read_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		read = readline("minishell$ ");
		if (read)
			main_process(read, envp);
		else
		{
			write(1, "exit\n", 5);
			break ;
		}
	}
	return (0);
}
