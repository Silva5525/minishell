/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:27:22 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/10 20:42:45 by wdegraf          ###   ########.fr       */
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

void free_tokens(t_arr *arr)
{
	size_t i;

	i = 0;
	while (i < arr->size)
	{
		free(arr->ken[i]->str);
		free(arr->ken[i]);
		i++;
	}
	free(arr->ken);
	free(arr);
}

void catch_token(t_arr *arr, t_to *ken)
{
	t_to **new_ken;
	if (arr->size == arr->max_size)
	{
		arr->max_size *= 2;
		new_ken = realloc(arr->ken, sizeof(t_to *) * arr->max_size);
		if (!new_ken)
		{
			free_tokens(arr);
			write(1, "Error, catch_token realloc\n", 27);
			exit(EXIT_FAILURE);
		}
		arr->ken = new_ken;
	}
	arr->ken[arr->size++] = ken;
}

t_arr *flexible_arr(void)
{
	t_arr	*arr = malloc(sizeof(t_arr));
	if (!arr)
		return (write(1, "Error, flexible_arr malloc\n", 27), NULL);
	arr->ken = malloc(sizeof(t_to) * 16);
	if (!arr->ken)
	{
		free_tokens(arr);
		write(1, "Error, flexible_arr malloc\n", 27);
		return (NULL);
	}
	arr->size = 0;
	arr->max_size = 16;
	return (arr);
}

t_to	*list_token(char *val, int typ)
{
	t_to	*ken = malloc(sizeof(t_to));
	if (!ken)
		return (NULL);
	ken->str = strdup(val);
	if (!ken->str)
	{
		free(ken);
		write(1, "Error, list_token malloc\n", 25);
		return (NULL);
	}
	ken->typ = typ;
	return (ken);
}

t_arr	*to_ken_producer(const char *read)
{
	t_arr	*arr;
	char	buf[1024];
	int i;

	i = 0;
	arr = flexible_arr();
	if (!arr)
		return (NULL);
	while (*read)
	{
		if (isspace(*read))
		{
			read++;
			continue ;
		}
		if (strchr(">|<", *read))
		{
			buf[0] = *read;
			buf[1] = '\0';
			catch_token(arr, list_token(buf, *read));
			read++;
			continue;
		}
		while (*read && !isspace(*read) && !strchr(">|<", *read))
			buf[i++] = *read++;
		buf[i] = '\0';
		catch_token(arr, list_token(buf, 'w'));
		i = 0;
	}
	return (arr);
}

int main(void)
{
	const char	*read = "echo Ducks are cool | grep Ducks > output.txt";
	t_arr		*arr = to_ken_producer(read);
	size_t		i;
	
	i = 0;
	while (i < arr->size)
	{
		printf("Token: %s Type: %c\n", arr->ken[i]->str, arr->ken[i]->typ);
		i++;
	}
	free_tokens(arr);
	return (EXIT_SUCCESS);
}