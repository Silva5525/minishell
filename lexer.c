/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:27:22 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/12 16:21:42 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief 
/// @param arr 
void	free_tokens(t_arr *arr)
{
	size_t	i;
	size_t	j;

	if (!arr)
		return ;
	if (arr->direktory)
	{
		free(arr->direktory);
		arr->direktory = NULL;
	}
	if (!arr->first_time && arr->envp)
	{
		i = 0;
		while (arr->envp[i])
		{
			free(arr->envp[i]);
			arr->envp[i] = NULL;
			i++;
		}
		free(arr->envp);
		arr->envp = NULL;
	}
	i = 0;
	while (i < arr->size)
	{
		if (arr->ken[i])
		{
			if (arr->ken[i]->str)
			{
				j = 0;
				if (arr->ken[i]->str[j])
				{
					while (arr->ken[i]->str[j])
					{
						free(arr->ken[i]->str[j]);
						arr->ken[i]->str[j] = NULL;
						j++;
					}
				}
				free(arr->ken[i]->str);
				arr->ken[i]->str = NULL;
			}
			free(arr->ken[i]);
			arr->ken[i] = NULL;
		}
		i++;
	}
	if (arr->ken)
	{
		free(arr->ken);
		arr->ken = NULL;
	}
	free(arr);
}

void	catch_token(t_arr *arr, t_to *ken)
{
	t_to	**new_ken;

	if (arr->size == arr->max_size)
	{
		arr->max_size *= 2;
		new_ken = ft_realloc(arr->ken, sizeof(t_to *)
				* arr->max_size / 2, sizeof(t_to *) * arr->max_size);
		if (!new_ken)
		{
			free_tokens(arr);
			write(2, "Error, catch_token realloc\n", 27);
			exit(EXIT_FAILURE);
		}
		arr->ken = new_ken;
	}
	arr->ken[arr->size++] = ken;
}

t_arr	*flexible_arr(void)
{
	t_arr	*arr;

	arr = malloc(sizeof(t_arr));
	if (!arr)
		return (write(2, "Error, flexible_arr malloc\n", 27), NULL);
	arr->ken = malloc(sizeof(t_to) * 16);
	if (!arr->ken)
	{
		free_tokens(arr);
		write(2, "Error, flexible_arr malloc\n", 27);
		return (NULL);
	}
	arr->size = 0;
	arr->max_size = 16;
	arr->direktory = NULL;
	arr->envp = NULL;
	arr->in_fd = STDIN_FILENO;
	arr->out_fd = STDOUT_FILENO;
	arr->stat = 0; // needed?
	arr->sig = 0; //needed?
	return (arr);
}

t_to	*list_token(char **val, int typ)
{
	t_to	*ken;

	ken = malloc(sizeof(t_to));
	if (!ken)
		return (NULL);
	ken->str = val;
	ken->typ = typ;
	return (ken);
}

char	**split_str_to_arg(char *str)
{
	int		i;
	int		w_count;
	char	**arg;
	char	*tok;
	char	*save_p;

	w_count = ft_strcwords_isspace(str);
	arg = malloc(sizeof(char *) * (w_count + 1));
	if (!arg)
		return (write(2, "Error, split_str_to_arg malloc\n", 32), NULL);
	i = 0;
	tok = ft_strtok_thread(str, " ", &save_p);
	while (tok)
	{
		arg[i] = ft_strdup(tok);
		if (!arg[i])
		{
			while (i > 0)
			{
				free(arg[i]);
				i--;
			}
			free(arg);
			return (write(2, "Error, split_str_to_arg ft_strdub\n", 35), NULL);
		}
		i++;
		tok = ft_strtok_thread(NULL, " ", &save_p);
	}
	arg[i] = NULL;
	return (arg);
}

t_arr	*to_ken_producer(const char *read)
{
	t_arr	*arr;
	char	**arg;
	char	buf[1024];
	int		i;

	arr = flexible_arr();
	if (!arr)
		return (NULL);
	while (*read)
	{
		if (ft_isspace(*read))
		{
			read++;
			continue ;
		}
		if (ft_strchr(">|<", *read))
		{
			if (*read == '>' && *(read + 1) == '>')
			{
				buf[0] = 'A';
				buf[1] = '\0';
				read += 2;
			}
			else if (*read == '<' && *(read + 1) == '<')
			{
				buf[0] = 'H';
				buf[1] = '\0';
				read += 2;
			}
			else
			{
				buf[0] = *read;
				buf[1] = '\0';
				read++;
			}
			arg = ft_split(buf, ' ');
			catch_token(arr, list_token(arg, *read));
			continue ;
		}
		i = 0;
		while (*read && !ft_isspace(*read) && !ft_strchr(">|<", *read))
			buf[i++] = *read++;
		buf[i] = '\0';
		arg = split_str_to_arg(buf);
		catch_token(arr, list_token(arg, 'w'));
	}
	return (arr);
}

// int main(void)
// {
// 	const char	*read = "echo Ducks are cool | grep Ducks > output.txt";
// 	t_arr		*arr = to_ken_producer(read);
// 	size_t		i;
// 	i = 0;
// 	while (i < arr->size)
// 	{
// 		printf("Token: %s Type: %c\n", arr->ken[i]->str, arr->ken[i]->typ);
// 		i++;
// 	}
// 	free_tokens(arr);
// 	return (EXIT_SUCCESS);
// }
