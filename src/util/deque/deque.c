/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:14:27 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:14:28 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_deque(t_deque *deque)
{
	deque->front = NULL;
	deque->back = NULL;
}

void input_front(t_deque *deque, t_token token)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->cmdline = token.cmdline;
	new_token->redir = token.redir;
	if (deque->front == NULL)
	{
		deque->front = new_token;
		deque->back = new_token;
		new_token->next = NULL;
		return;
	}
	new_token->next = deque->front;
	deque->front = new_token;
}

void input_back(t_deque *deque, t_token token)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->cmdline = token.cmdline;
	new_token->redir = token.redir;
	if (deque->front == NULL)
	{
		deque->front = new_token;
		deque->back = new_token;
		new_token->next = NULL;
		return;
	}
	deque->back->next = new_token;
	deque->back = new_token;
	new_token->next = NULL;
}

t_token output_front(t_deque *deque)
{
	t_token result;
	t_token *temp;

	if (deque->front == NULL)
	{
		result.redir = NULL;
		result.cmdline = NULL;
		return (result);
	}
	result.redir = deque->front->redir;
	result.cmdline = deque->front->cmdline;
	result.next = deque->front->next;
	temp = deque->front;
	if (deque->front == deque->back)
	{
		deque->front = NULL;
		free(temp);
		deque->back = NULL;
		return (result);
	}
	deque->front = deque->front->next;
	free(temp);
	return (result);
}

t_token output_back(t_deque *deque)
{
	t_token result;
	t_token *temp;

	if (deque->back == NULL)
	{
		result.redir = NULL;
		result.cmdline = NULL;
		return (result);
	}
	result.redir = deque->back->redir;
	result.cmdline = deque->back->cmdline;
	result.cmdline = deque->back->cmdline;
	temp = deque->back;
	if (deque->front == deque->back)
	{
		deque->front = NULL;
		deque->back = NULL;
		free(temp);
		return (result);
	}
	deque->back->next = NULL;
	free(temp);
	return (result);
}
