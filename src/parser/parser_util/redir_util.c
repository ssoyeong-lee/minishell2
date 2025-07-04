/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:51 by seheo             #+#    #+#             */
/*   Updated: 2023/01/09 17:09:19 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_redir(t_redir_queue *r_que, t_redir buf_redir)
{
	t_redir *new_node;

	new_node = (t_redir *)malloc(sizeof(t_redir));
	new_node->file_name = buf_redir.file_name;
	new_node->type = buf_redir.type;
	new_node->hd_number = buf_redir.hd_number;
	new_node->next = NULL;
	if (r_que->count == 0)
		r_que->front = new_node;
	else
		r_que->rear->next = new_node;
	r_que->rear = new_node;
	r_que->count++;
}

t_redir dequeue_redir(t_redir_queue *queue)
{
	t_redir data;
	t_redir *ptr;

	if (queue->count == 0)
	{
		data.hd_number = -1;
		return (data);
	}
	ptr = queue->front;
	data.file_name = ptr->file_name;
	data.hd_number = ptr->hd_number;
	data.type = ptr->type;
	queue->front = ptr->next;
	free(ptr->file_name);
	free(ptr);
	queue->count--;
	return (data);
}

void free_redir(t_redir_queue *que)
{
	while (que->count != 0)
	{
		dequeue_redir(que);
	}
	free(que);
}
