/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdegraf <wdegraf@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:07:29 by wdegraf           #+#    #+#             */
/*   Updated: 2024/07/12 14:11:55 by wdegraf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void b_pwd(void)
{
	char working_directory[PATH_MAX];
	
	if (getcwd(working_directory, sizeof(working_directory)) != NULL)
		printf("%s\n", working_directory);
	else
		write(2, "Error, b_pwd failed\n", 20);
}