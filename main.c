/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:45 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/19 17:31:42 by wdegraf          ###   ########.fr       */
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


void alloc_envp(t_arr *arr, char **envp)
{
	size_t i;
	size_t j;
	size_t k;

	if (arr->first_time)
	{
		arr->envp = envp;
		return ;
	}
	i = 0;
	while (envp[i])
		i++;
	arr->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!arr->envp)
	{
		write(2, "Error, malloc failed in alloc_envp\n", 35);
		free_tokens(arr);
		exit(EXIT_FAILURE);
	}
	j = 0;
	k = 0;
	while (j < i)
	{
		arr->envp[j] = ft_strdup(envp[j]);
		if (!arr->envp[j])
		{
			write(2, "Error, malloc failed in alloc_envp\n", 35);
			while (k < j)
			{
				free(arr->envp[k]);
				arr->envp[k] = NULL;
				k++;
			}
			free(arr->envp);
			free_tokens(arr);
			exit(EXIT_FAILURE);
		}
		j++;
	}
	arr->envp[i] = NULL;
}

void main_process(char *read, char **envp, bool first_time)
{
	t_arr	*arr;
	char	*expand_r;

	add_history(read);
	expand_r = expanding_env(read, envp);
	printf("Out: %s\n", expand_r);
	arr = to_ken_producer(expand_r);
	free(expand_r);
	if (!arr)
	{
		free(read);
		write(2, "Error, to_ken_producer\n", 24);
		return ;
	}
	arr->first_time = first_time;
	alloc_envp(arr, envp);
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

char	*direktory_minishell(void)
{
	char	*pwd;
	const char	*ms;
	char 	*out;
	int		i;
	int		j;
	
	out = (char *)malloc(sizeof(char) * (PATH_MAX + 11));
	if (!out)
	{
		write(2, "Error, malloc failed in main\n", 30);
		return (NULL);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		write(2, "Error, getcwd failed in main\n", 30);
		return (NULL);
	}
	i = 0;
	while (pwd[i] && i < PATH_MAX)
	{
		out[i] = pwd[i];
		i++;
	}
	free(pwd);	
	ms = " minishell$ ";
	j = 0;
	while (ms[j] && i < PATH_MAX + 11 - 1)
	{
		out[i] = ms[j];
		i++;
		j++;
	}
	out[i] = '\0';
	return (out);	
}

/// @brief 
/// @param argc Argument Count
/// @param argv Argument Vector
/// @param envp Environment Pointer (each string is a enviroment variable)
/// @return 
int	main(int argc, char **argv, char **envp)
{
	char	*read;
	char	*pwd;
	bool	first_time;
	(void)argc;
	(void)argv;

	signal(SIGINT, read_signal);
	signal(SIGQUIT, SIG_IGN);
	first_time = true;
	while (1)
	{
		pwd = direktory_minishell();
		if (!pwd)
		{
			write(2, "Error, direktory_minishell in main\n", 35);
			free(pwd);
		}
		read = readline(pwd);
		free(pwd);
		if (read)
			main_process(read, envp, first_time);
		else
		{
			write(1, "exit\n", 5);
			break ;
		}
		first_time = false;
	}
	return (0);
}
