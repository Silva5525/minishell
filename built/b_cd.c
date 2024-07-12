/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:07:05 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/12 16:45:48 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void b_cd(t_arr *arr, char **envp)
{
	(void)envp; ///needs a way biger implementation for pwd
	if (!arr->ken[1]->str || chdir(arr->ken[1]->str) == -1)
		write(2 ,"cd: No such file or directory\n", 30);
}
