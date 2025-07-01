/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:12:49 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:12:51 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char **cmds)
{
	int i;
	int tag;

	if (cmds[1] && ft_strncmp("-n", cmds[1], 3) == 0) {
		tag = 0;
		i = 2;
	} else {
		tag = 1;
		i = 1;
	}
	while (cmds[i])
	{
		ft_putstr_fd(cmds[i], STDOUT_FILENO);
		if (cmds[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (tag)
		ft_putendl_fd("", STDOUT_FILENO);
	g_system_var.status = 0;
}
