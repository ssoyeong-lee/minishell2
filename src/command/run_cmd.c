/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:19 by seheo             #+#    #+#             */
/*   Updated: 2023/01/10 19:04:29 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_builtin(char **cmds)
{
	if (!ft_strncmp(cmds[0], "cd", ft_strlen(cmds[0]) + 1))
		ft_cd(cmds);
	if (!ft_strncmp(cmds[0], "echo", ft_strlen(cmds[0]) + 1))
		ft_echo(cmds);
	if (!ft_strncmp(cmds[0], "pwd", ft_strlen(cmds[0]) + 1))
		ft_pwd(cmds);
	if (!ft_strncmp(cmds[0], "env", ft_strlen(cmds[0]) + 1))
		ft_env(cmds);
	if (!ft_strncmp(cmds[0], "export", ft_strlen(cmds[0]) + 1))
		ft_export(cmds);
	if (!ft_strncmp(cmds[0], "unset", ft_strlen(cmds[0]) + 1))
		ft_unset(cmds);
	if (!ft_strncmp(cmds[0], "exit", ft_strlen(cmds[0]) + 1))
		ft_exit(cmds);
}

void run_cmdline(t_token *t, int *prev_pipe, int *cur_pipe)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		minish_exit("minish: fork", 1);
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (!t->next)
			g_system_var.last_pid = pid;
		run_parent(t, prev_pipe, cur_pipe);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		run_child(t, prev_pipe, cur_pipe);
	}
}

void no_pipe_builtin(t_token *t)
{
	if (t->redir->count != 0)
	{
		if (set_in_out(t->redir->front))
			return;
	}
	run_builtin(t->cmdline);
	reset_in_out();
}

void run_token(t_token *t)
{
	int cur_pipe[2];
	int prev_pipe[2];

	if (!t->next && is_builtin(t->cmdline[0]))
	{
		no_pipe_builtin(t);
		return;
	}
	cur_pipe[0] = -1;
	while (t)
	{
		prev_pipe[0] = cur_pipe[0];
		prev_pipe[1] = cur_pipe[1];
		if (t->next)
		{
			if (pipe(cur_pipe) == -1)
				minish_exit("pipe", 1);
		}
		run_cmdline(t, prev_pipe, cur_pipe);
		t = t->next;
	}
	wait_children();
}
