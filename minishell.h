/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:52:57 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/10 20:25:50 by wdegraf          ###   ########.fr       */
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
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"

typedef struct s_tokens
{
	char	*str;
	int		typ;
	struct s_token	*next;
}	t_to;

typedef struct s_ast
{
	int				typ;
	char			*str;
	struct s_ast	*right;
	struct s_ast	*left;
}	t_ast;

/// @param lexer.c

t_to	*to_ken_producer(const char *read);

#endif