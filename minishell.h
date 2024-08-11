/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:52:57 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/11 16:25:51 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"

/// @brief struct for the tokens
/// @param str the token
/// @param typ the type of the tokens
typedef struct s_tokens
{
	char	**str;
	int		typ;
}	t_to;

/// @brief struct for the minishell
/// @param ken array of tokens
/// @param envp environment variables
/// @param direktory current working directory
/// @param size number of tokens
/// @param max_size maximum number of tokens before resizing arr
/// @param in_fd file descriptor for input
/// @param out_fd file descriptor for output
/// @param first_time if true envp will be set to the envp (leak handling)
typedef struct s_arr
{
	t_to	**ken;
	char	**envp;
	char	*direktory;
	size_t	size;
	size_t	max_size;
	int		in_fd;
	int		out_fd;
	bool	first_time;
}	t_arr;

// typedef struct s_ast
// {
// 	int				typ;
// 	char			*str;
// 	struct s_ast	*right;
// 	struct s_ast	*left;
// }	t_ast;

typedef void (*built_f)(t_arr *arr);
typedef struct s_builtin
{
	char	*name;
	built_f	fun;
}	t_b;

/// ########################################## @brief./built #################################################
/// 

void	builtin(t_arr *arr);
void	b_echo(t_arr *arr);
void	b_cd(t_arr *arr);
void	b_pwd(t_arr *arr);
void	b_export(t_arr *arr);
void	b_unset(t_arr *arr);
void	b_env(t_arr *arr);
void	b_exit(t_arr *arr);

/// @param built/a_builtins.c

char	**ft_arr_setenv(const char *str, const char *v, char **envp, bool first_time);

/// ########################################## @brief Sources ################################################

/// @param lexer.c

t_arr	*to_ken_producer(const char *read);
void	free_tokens(t_arr *arr);

/// @param expand.c

char	*expanding_env(char *read, char **envp);

#endif