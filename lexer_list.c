/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:56:44 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/10 19:45:03 by wdegraf          ###   ########.fr       */
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

typedef struct s_tokens
{
	char	*str;
	int		typ;
	struct s_tokens	*next;
}	t_to;

t_to	*list_token(char *val, int typ)
{
	t_to	*ken = malloc(sizeof(t_to)); // this needs a free...
	if (!ken)
		return (NULL);
	ken->str = strdup(val);
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
	t_to *hold;

	while (ken)
	{
		hold = ken;
		ken = ken->next;
		free(hold->str);
		free(hold);
	}
}

int main(void)
{
	const char	*read = "echo Ducks are cool | grep Ducks > output.txt";
	t_to		*ken = to_ken_producer(read);
	
	t_to *arr = ken;
	while (arr)
	{
		printf("Token: %s, Type: %c\n", arr->str, arr->typ);
		arr = arr->next;
	}
	free_kens(arr);
	return (0);
}