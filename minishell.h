/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:52:57 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/13 15:10:48 by wdegraf          ###   ########.fr       */
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

typedef struct s_tokens
{
	char	*str;
	int		typ;
}	t_to;

typedef struct s_arr
{
	t_to	**ken;
	size_t	size;
	size_t	max_size;
}	t_arr;

typedef struct s_ast
{
	int				typ;
	char			*str;
	struct s_ast	*right;
	struct s_ast	*left;
}	t_ast;

/// @brief ./built 
void builtin(t_arr *arr, char **envp);
// void b_echo(t_arr *arr);
void b_cd(t_arr *arr, char **envp);
// void b_pwd(void);
// void b_export(t_arr *arr, char **envp);
// void b_unset(t_arr *arr, char **envp);
// void b_env(char **envp);
void b_exit(t_arr *arr, char **envp);

/// @param lexer.c

t_arr	*to_ken_producer(const char *read);
void	free_tokens(t_arr *arr);

#endif