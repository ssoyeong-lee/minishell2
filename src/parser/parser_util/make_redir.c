/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:48 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:16:51 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int get_redir_size(const char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr("><", s[i]))
			i++;
		else
			return (i);
	}
	return (i);
}

static int get_redir_type(char *s, int redir_size)
{
	if (redir_size == 2)
	{
		if (s[0] == '<')
			return (HERE_DOC);
		else
			return (APP_REDIR);
	}
	else if (redir_size == 1)
	{
		if (s[0] == '>')
			return (OUT_REDIR);
		else
			return (IN_REDIR);
	}
	return (IN_REDIR);
}

void is_only_redir(t_redir *buf_redir, char **s, int *idx, int redir_size)
{
	buf_redir->type = get_redir_type(s[*idx], redir_size);
	if (s[*idx + 1] == NULL)
	{
		buf_redir->file_name = ft_strdup("\n");
	}
	else
	{
		buf_redir->file_name = ft_strdup(s[*idx + 1]);
		*idx += 1;
	}
	if (buf_redir->type == HERE_DOC)
	{
		buf_redir->hd_number = ++g_system_var.hd_cnt;
		heredoc_file_maker(buf_redir->file_name, buf_redir->hd_number);
	}
}

void make_redir(t_redir_queue *r_que, char **s, int *idx_ptr)
{
	int redir_size;
	t_redir buf_redir;
	int	idx;

	idx = *idx_ptr;
	buf_redir.hd_number = 0;
	redir_size = get_redir_size(s[idx]);
	is_only_redir(&buf_redir, s, idx_ptr, redir_size);
	add_redir(r_que, buf_redir);

}
