/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:14:33 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:14:34 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void dictionary_show(t_dictionary dic)
{
	t_dictionary_node *temp;

	temp = dic.head;
	while (temp != NULL)
	{
		ft_putendl_fd(ft_strjoin(temp->key, temp->value), 2);
		temp = temp->link;
	}
}

int dictionary_add(t_dictionary *head, char *key, char *value)
{
	t_dictionary_node *temp;

	temp = head->head;
	while (1)
	{
		if (head->count == 0)
		{
			head->head = dic_add_util(temp, key, value);
			break;
		}
		else if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
			return (false);
		else if (temp->link == NULL)
		{
			dic_add_util2(temp, key, value);
			break;
		}
		else
			temp = temp->link;
	}
	head->count++;
	return (true);
}

int dictionary_delete(t_dictionary *head, char *key)
{
	t_dictionary_node *ptr;

	ptr = head->head;
	while (true)
	{
		if (ptr == NULL)
			return (false);
		else if (ft_strncmp(ptr->key, key, ft_strlen(key) + 1) == 0)
			break;
		ptr = ptr->link;
	}
	dic_del_util(ptr, head);
	head->count--;
	return (true);
}

t_dictionary_node *dictionary_search(t_dictionary head, char *key)
{
	t_dictionary_node *temp;

	temp = head.head;
	while (1)
	{
		if (temp == NULL)
			return (NULL);
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
			return (temp);
		temp = temp->link;
	}
}

void dictionary_init(t_dictionary *head)
{
	head->count = 0;
	head->head = NULL;
}
