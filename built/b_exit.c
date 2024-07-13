/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:05:15 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/13 15:11:15 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void b_exit(t_arr *arr, char **envp)
{
	(void)envp;
	(void)arr;
	free_tokens(arr);
	write(1, "exit\n", 5);
	exit(0);
}