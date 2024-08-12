/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 20:31:13 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/12 13:06:24 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	do_order(char **do_it, char **envp)
{
	if (execve(do_it[0], do_it, envp) == -1)
		return (write(2, "Error, execve in do_order failed\n", 33)
			, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

pid_t	child_pipe(char **do_it, char **envp, int fileno, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "Error, pid fork in child_pipe failed\n", 37);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (fileno == 0)
			dup2(fd[0], STDIN_FILENO);
		else if (fileno == 1)
			dup2(fd[1], STDOUT_FILENO);
		else if (fileno == 2)
			dup2(fd[2], STDERR_FILENO);
		close(fd[0]);
		close(fd[1]);
		exit(do_order(do_it, envp));
	}
	return (pid);
}

/// @brief Hand
/// @param do1 
/// @param do2 
/// @param envp 
void	pipex(char **do1, char **do2, char **envp)
{
	int		fd[2];
	pid_t	p1;
	pid_t	p2;

	if (pipe(fd) == -1)
	{
		write(2, "Error, pipe in pipex failed\n", 28);
		exit(EXIT_FAILURE);
	}
	p1 = child_pipe(do1, envp, 1, fd);
	p2 = child_pipe(do2, envp, 0, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(p1, NULL, 0);
	waitpid(p2, NULL, 0);
}

/// @brief lists all files in the current directory with details
/// and then searches for all files with the ending .c and shows
/// only those files (short test for pipex)
/// @param argc argument count
/// @param argv argument vector
/// @param envp enviroment variables
/// @return exit status
// int	main(int argc, char **argv, char **envp)
// {
// 	char *to_do1[] = {"/bin/ls", "-l", NULL};
// 	char *to_do2[] = {"/usr/bin/grep", ".c", NULL};

// 	if (argc > 1)
// 	{
// 		printf("Usage: %s\n", argv[0]);
// 		return (EXIT_FAILURE);
// 	}
// 	pipex(to_do1, to_do2, envp);
// 	return (EXIT_SUCCESS);
// }
