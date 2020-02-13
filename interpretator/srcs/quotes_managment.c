/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 19:47:42 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/14 00:21:48 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static int	check_quote_type(char *str, short quote_type)
{
	if (*str == '"' && quote_type == 0)
		return (1);
	else if (*str == '"' && quote_type == 1)
		return (0);
	else if (*str == '\'' && quote_type == 0)
		return (2);
	else if (*str == '\'' && quote_type == 2)
		return (0);
	else
		return (0);
}

static int	del_quote(char **str, size_t pos, short *quote_type)
{
	char	*new_str;
	size_t	len;

	if (pos > 0 && (*str)[pos - 1] == '\\')
		return (pos);
	*quote_type = check_quote_type(*str, *quote_type);
	len = ft_strlen(*str);
	if (!(new_str = ft_strnew(len)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_memcpy(new_str, *str, pos++);
	ft_memcpy(new_str + pos - 1, (*str) + pos, len - pos);
	free(*str);
	*str = new_str;
	return ((pos > 1) ? pos - 2 : pos);
}

static char	*check_sub(char *str, size_t pos)
{
	char	*result;
	char	*start;
	char	*tmp;

	if (pos == 0 && str[pos] == '~')
		result = tilda_substitution(str + pos);
	else if (str[pos] == '$')
		result = var_substitution(str + pos);
	else
		return (str);
	if (!(start = ft_strsub(str, 0, pos)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	if (!(tmp = ft_strjoin(start, result)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_strdel(&result);
	ft_strdel(&start);
	free(str);
	return (tmp);
}

static char	is_glob(char c)
{
	if (c == '*' || c == '?' || c == '[' || c == ']')
		return (TRUE);
	return (FALSE);
}

char		**quotes_managment(char **args)
{
	int		i;
	int		j;
	short	quote_type;
	short	patterns;

	i = -1;
	while (args[++i])
	{
		j = -1;
		quote_type = 0;
		patterns = 0;
		args[i] = check_sub(args[i], j);
		while (args[i][++j])
		{
			if (args[i][j] == '"' || args[i][j] == '\'')
				j = del_quote(&args[i], j, &quote_type);
			if (quote_type == 2)
				continue ;
			args[i] = check_sub(args[i], j);
			if (!quote_type && is_glob(args[i][j]))
				patterns = 1;
		}
		args = check_patterns(args, i, patterns);
	}
	return (args);
}
