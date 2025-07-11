/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:14:18 by seheo             #+#    #+#             */
/*   Updated: 2023/01/10 19:03:37 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_option(char *line)
{
	if (line && *line == '-' && line + 1)
		return (1);
	return (0);
}

char abstract_opt(char *line)
{
	line++;
	while (*line && *(line + 1))
	{
		if (*line != *(line + 1))
			return (0);
		line++;
	}
	return (*line);
}

int check_valid_opt(char **cmds, char opt, char *usage)
{
	int i;
	char ab_opt;

	i = 1;
	while (cmds[i])
	{
		ab_opt = abstract_opt(cmds[i]);
		if (is_option(cmds[i]) && ab_opt != opt)
		{
			perror_opt(cmds[0], ab_opt, usage);
			return (0);
		}
		i++;
	}
	return (1);
}

void perror_opt(char *cmd, char opt, char *usage)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": -", STDERR_FILENO);
	ft_putchar_fd(opt, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": usage: ", STDERR_FILENO);
	ft_putendl_fd(usage, STDERR_FILENO);
	g_system_var.status = 2;
}

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd) + 1) \
		|| !ft_strncmp(cmd, "echo", ft_strlen(cmd) + 1) \
		|| !ft_strncmp(cmd, "pwd", ft_strlen(cmd) + 1) \
		|| !ft_strncmp(cmd, "env", ft_strlen(cmd) + 1) \
		|| !ft_strncmp(cmd, "export", ft_strlen(cmd) + 1) \
		|| !ft_strncmp(cmd, "unset", ft_strlen(cmd) + 1) \
		|| !ft_strncmp(cmd, "exit", ft_strlen(cmd) + 1))
		return (1);
	return (0);
}
