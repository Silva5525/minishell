/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:07:29 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/17 12:52:27 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void b_pwd(t_arr *arr)
{
	(void)arr;
	
	if (getcwd(arr->direktory, sizeof(PATH_MAX)) != NULL)
		printf("%s\n", arr->direktory);
	else
		write(2, "Error, b_pwd failed\n", 20);
}