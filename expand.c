/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:42:54 by wdegraf           #+#    #+#             */
/*   Updated: 2024/08/28 17:22:35 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief searches for the variable in the environment array
/// if the variable is found, the value of the variable is returned
/// @param envp the environment array
/// @param str string to search
/// @return variable value or NULL if the variable is not found
static char	*ft_getenv_val(char **envp, char *str)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = ft_strlen(str);
	while (envp[i])
	{
		if ((envp[i][j] == '=') && (ft_strncmp(envp[i], str, j) == 0))
			return (envp[i] + j + 1);
		i++;
	}
	return (NULL);
}

/// @brief replaces the variable with its environment value
/// for example: $HOME will be replaced with the environment value of the
/// HOME=Example which is Example.
/// @param doller Pointer to the $ in the string
/// @param hold current string holds the expanded string
/// @param envp the environment array
/// @param out output string to result after joining
/// @return Pointer of position in the string after the processed variable
/// or NULL if an error occurred
static char	*split_doller_search(
			char *doller, char *hold, char **envp, char *out)
{
	char	*search;
	char	*env;
	char	safe;

	search = doller + 1;
	while ((*search && ft_isalnum(*search)) || *search == '_')
		search++;
	safe = *search;
	*search = '\0';
	env = ft_getenv_val(envp, doller + 1);
	*search = safe;
	if (env)
	{
		out = ft_strjoin(hold, env);
		if (!out)
			return (NULL);
		free(hold);
		hold = out;
	}
	return (search);
}

/// @brief search for $ in the string and replaces the variable with its value.
/// If the variable is not found, the variable will be replaced with an empty
/// string and the search will continue.
/// @param str string to search
/// @param hold hold the string
/// @param envp environment array
/// @param out the expanded string
/// @return hold or NULL if an error occurred
static char	*doller_search(char *str, char *hold, char **envp, char *out)
{
	char	*doller;

	doller = ft_strchr(str, '$');
	while (doller)
	{
		*doller = '\0';
		out = ft_strjoin(hold, str);
		free(hold);
		if (!out)
			return (NULL);
		hold = out;
		str = split_doller_search(doller, hold, envp, out);
		doller = ft_strchr(str, '$');
	}
	return (hold);
}

/// @brief expands the environment variables in the read string
/// if the string contains a $ followed by a valid variable name
/// the variable will be replaced with its value.
/// @param read the string to expand
/// @param envp environment array
/// @return the expanded string out, or NULL if an error occurred
char	*expanding_env(char *read, char **envp)
{
	char	*hold;
	char	*out;
	char	*str;

	if (!read)
		return (NULL);
	str = read;
	hold = ft_strdup("");
	if (!hold)
		return (NULL);
	out = doller_search(str, hold, envp, NULL);
	if (!out)
		return (free(hold), NULL);
	out = ft_strjoin(hold, str);
	free(hold);
	if (!out)
		return (NULL);
	return (out);
}
