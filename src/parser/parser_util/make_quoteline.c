/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_quoteline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:13:44 by seheo             #+#    #+#             */
/*   Updated: 2023/01/11 00:55:06 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *remove_quote(char *s, char c)
{
	char *result;
	int i;
	int j;
	int cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == c)
			cnt++;
		i++;
	}
	result = (char *)malloc((ft_strlen(s) - cnt + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			result[j++] = s[i];
		i++;
	}
	result[j] = 0;
	return (result);
}

int find_env(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && !(s[i + 1] == 0 || s[i + 1] == ' ' || s[i + 1] == '\'' || s[i + 1] == '\"'))
			return (1);
		i++;
	}
	return (0);
}

char *loop_convert(char *s)
{
	char *env_convert;
	char *temp;

	env_convert = convert_env(s);
	while (find_env(env_convert))
	{
		temp = env_convert;
		env_convert = convert_env(env_convert);
		free(temp);
	}
	return (env_convert);
}

static char* get_quote_line(char *s, unsigned int *start_idx, char c) {
	int		idx;
	int		cnt;
	int		len;
	char* ret;

	idx = *start_idx;
	cnt = 0;
	len = 0;
	while (s[idx] && cnt != 2) {
		if (s[idx] == c) {
			cnt ++;
		}
		idx ++;
		len ++;
	}
	ret = ft_substr(s, *start_idx + 1, len - 2);
	*start_idx = idx;
	return ret;
}

static char* make_single_quote(char *s, unsigned int *start_idx)
{
	return get_quote_line(s, start_idx, '\'');
}

static char* make_double_quote(char *s, unsigned int *start_idx)
{
	char* tmp;
	char*	ret;

	tmp = get_quote_line(s, start_idx, '\"');
	ret = loop_convert(tmp);
	free(tmp);
	return ret;
}

char *remove_quote_and_convert_env(char *s) {
	unsigned int	idx;
	char					*ret;
	char					*tmp;
	char					*convert_ret;

	idx = 0;
	ret = ft_strdup("");
	while (s[idx]) {
		if (s[idx] == '\'') {
			convert_ret = make_single_quote(s, &idx);
		} else if (s[idx] == '\"') {
			convert_ret = make_double_quote(s, &idx);
		} else {
			convert_ret = ft_calloc(2, sizeof(char));
			*convert_ret = s[idx++];
		}
		tmp = ft_strjoin(ret, convert_ret);
		free(ret);
		ret = tmp;
		
		free(convert_ret);
	}
	return ret;
}

void make_quoteline(t_lst *list, char *s)
{
	char *res;

	res = remove_quote_and_convert_env(s);
	insert_node(list, l_size(list), res);
	free(res);
}
