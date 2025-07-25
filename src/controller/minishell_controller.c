/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:29 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:13:30 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cmd_run(char *line)
{
	t_deque p_token;
	t_token buf_token;
	char **lexer_line;

	lexer_line = lexer(line);
	p_token = make_tokens(lexer_line);
	if (g_system_var.hd_flag == 0)
	{
		if (!is_empty(p_token))
			run_token(p_token.front);
	}
	heredoc_unlink();
	while (!is_empty(p_token))
	{
		buf_token = output_front(&p_token);
		free_redir(buf_token.redir);
		ft_free_strs(buf_token.cmdline);
	}
	ft_free_strs(lexer_line);
}

void sig_readline(int signo)
{
	g_system_var.status = 128 + signo;
	if (signo == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == (-1))
		{
			ft_putendl_fd("", STDOUT_FILENO);
			if (rl_on_new_line() == -1)
				exit(1);
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else
			ft_putendl_fd("", STDOUT_FILENO);
	}
	return;
}

static char *set_read_line(void)
{
	char *line;

	signal(SIGINT, sig_readline);
	signal(SIGQUIT, SIG_IGN);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_system_var.nodisplay_set);
	line = readline("🎃 minishell 🎃 ");
	if (!line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(g_system_var.status);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_system_var.display_set);
	return (line);
}

void minishell_start(void)
{
	char *cmd_line;

	while (1)
	{
		g_system_var.hd_flag = 0;
		g_system_var.hd_cnt = 0;
		cmd_line = set_read_line();
		if (cmd_line[0] == 0)
		{
			free(cmd_line);
			continue;
		}
		if (!cmd_line)
			exit(0);
		if (*cmd_line != 0)
			add_history(cmd_line);
		cmd_run(cmd_line);
		free(cmd_line);
	}
}
