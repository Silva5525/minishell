/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:31:13 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/11 12:51:34 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief executing the command given as do_it in the new process
/// given.. it preperes the argument for execve in correct form..
/// execve replaces the current process image with a new process img
/// specified by the path and the arguments passed to it..
/// if it fails it will print an error message and exits..
/// on success it will exit the process without returning anything
/// @param do_it the command to be executed
/// @param envp environment variables for the new process
void	do_command(char *do_it,char **args, char **envp)
{
	char	*args[] = {"/bin/sh", "-c", do_it, NULL};
	execve("/bin/sh", args, envp);
	write(2, "Error, execve failed in pipex do_command\n", 41);
	exit(EXIT_FAILURE);
}

void	pipex(char *do1, char *do2, char **envp)
{
	int		fd[2];
	pid_t	p1;
	pid_t	p2;

	if (pipe(fd) == -1)
	{
		write(2, "Error, pipe failed\n", 20);
		exit(EXIT_FAILURE);
	}
	p1 = fork();
	if (p1 == -1)
	{
		write(2, "Error, fork failed\n", 20);
		exit(EXIT_FAILURE);
	}
	if (p1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		do_command(do1, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 3)
	{
		write(2, "Error, wrong number of arguments\n", 33);
		return (EXIT_FAILURE);
	}
	pipex(argv[1], argv[2], envp);
	return (EXIT_SUCCESS);
}
