/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:05:15 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/14 19:46:50 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void b_exit(t_arr *arr)
{
	free_tokens(arr);
	write(1, "exit\n", 5);
	/// the exit code if something more then exit is writen should be something
	/// like: The terminal process "/usr/bin/bash" terminated with exit code: 2.
	exit(0);
}