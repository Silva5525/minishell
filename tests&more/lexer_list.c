/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:56:44 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/12 12:56:33 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
// carefull as long the #include is here its probably not ok for
// the norminette, becouse of the used illegal functions.

/// @brief This function creates a new token in form of a linked list
/// @param str The string that will be stored in the token
/// @param typ The type of the token (w = word, | = pipe, > <= redirect)
/// @param next The next token in the linked list
typedef struct s_tokens
{
	char	*str;
	int		typ;
	struct s_tokens	*next;
}	t_to;

t_to	*list_token(char *val, int typ)
{
	t_to	*ken = malloc(sizeof(t_to));
	if (!ken)
		return (NULL);
	ken->str = strdup(val);
	if (!ken->str)
	{
		free(ken);
		return (NULL);
	}
	ken->typ = typ;
	ken->next = NULL;
	return (ken);
}

void	catch_token(t_to **ken, t_to *new)
{
	t_to *hold;
	
	if (!*ken)
		*ken = new;
	else
	{
		hold = *ken;
		while (hold->next)
			hold = hold->next;
		hold->next = new;
	}
}

/// @brief This function creates a linked list of tokens
/// first it skips all whitespaces, then it checks if the current
/// character is a pipe, redirect or word. If it is a pipe or redirect
/// it creates a token with the current character and adds it to the list.
/// @param read is the string that will be tokenized
/// @return ken is the linked list of tokens
t_to	*to_ken_producer(const char *read)
{
	t_to 	*ken;
	char	buf[1024];
	int		i;

	i = 0;
	ken = NULL;
	while (*read)
	{
		if (isspace(*read))
		{
			read++;
			continue ;
		}
		if (strchr("|><", *read))
		{
			buf[0] = *read;
			buf[1] = '\0';
			catch_token(&ken, list_token(buf, *read));
			read++;
			continue;
		}
		while (*read && !isspace(*read) && !strchr("|><", *read))
			buf[i++] = *read++;
		buf[i] = '\0';
		catch_token(&ken, list_token(buf, 'w'));
		i = 0;
	}
	return (ken);
}

void	free_kens(t_to *ken)
{
	t_to	*hold;

	while (ken)
	{
		hold = ken;
		ken = ken->next;
		free(hold->str);
		free(hold);
	}
}

// int	main(void)
// {
// 	const char	*read = "echo \"Ducks \"are cool | grep Ducks > output.txt";
// 	t_to		*ken = to_ken_producer(read);

// 	t_to *arr = ken;
// 	while (arr)
// 	{
// 		printf("Token: %s, Type: %c\n", arr->str, arr->typ);
// 		arr = arr->next;
// 	}
// 	free_kens(arr);
// 	return (EXIT_SUCCESS);
// }
