/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:12:45 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:12:53 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *find_real_path(char *path)
{
	t_dictionary_node *env;
	char *real_path;

	if (!path || ft_strncmp(path, "~", 2) == 0)
	{
		env = dictionary_search(g_system_var.env, "HOME");
		if (!env)
			return (NULL);
		real_path = ft_strdup(env->value);
	}
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		env = dictionary_search(g_system_var.env, "OLDPWD");
		if (!env)
			return (NULL);
		real_path = ft_strdup(env->value);
	}
	else
		real_path = ft_strdup(path);
	if (real_path == 0)
	{
		minish_exit("minish: ft_strdup", 1);
	}
	return (real_path);
}

static void set_cd_env(void)
{
	t_dictionary_node *oldpwd;
	t_dictionary_node *pwd;
	char *real_path;

	oldpwd = dictionary_search(g_system_var.env, "OLDPWD");
	pwd = dictionary_search(g_system_var.env, "PWD");
	if (oldpwd)
		dictionary_delete(&g_system_var.env, "OLDPWD");
	dictionary_add(&g_system_var.env, ft_strdup("OLDPWD"),
								 ft_strdup(pwd->value));
	if (pwd)
		dictionary_delete(&g_system_var.env, "PWD");
	real_path = getcwd(NULL, 0);
	if (!real_path)
	{
		perror("minishell: cd: ");
		g_system_var.status = 2;
		return;
	}
	dictionary_add(&g_system_var.env, ft_strdup("PWD"), real_path);
}

static void print_err(char *cmd)
{
	if (!cmd || *cmd == '~')
	{
		ft_putendl_fd("minish: cd: HOME not set", STDERR_FILENO);
		g_system_var.status = 1;
	}
	else if (*cmd == '-')
	{
		ft_putendl_fd("minish: cd: OLDPWD not set", STDERR_FILENO);
		g_system_var.status = 1;
	}
}

void ft_cd(char **cmds)
{
	int ret;
	char *real_path;

	real_path = find_real_path(cmds[1]);
	if (!cmds[1] || !ft_strncmp(cmds[1], "-", 2) || !ft_strncmp(cmds[1], "~", 2))
	{
		if (real_path)
			ft_putendl_fd(real_path, STDOUT_FILENO);
		else
		{
			print_err(cmds[1]);
			return;
		}
	}
	ret = chdir(real_path);
	free(real_path);
	if (ret == -1)
	{
		perror("minishell: cd");
		g_system_var.status = 1;
		return;
	}
	set_cd_env();
	g_system_var.status = 0;
}
