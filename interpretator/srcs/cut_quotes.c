/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:48:13 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/16 00:29:10 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char	*del_bs(char *str, size_t pos)
{
	char	*new_str;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (!(new_str = ft_strnew(len)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_memcpy(new_str, str, pos);
	ft_memcpy(new_str + pos, str + pos + 1, len - pos - 1);
	free(str);
	return (new_str);
}

static char	*del_quote(char *str, size_t pos, t_qt *qt)
{
	char	*new_str;
	size_t	len;

	*qt = check_quotes_type(str, pos, *qt);
	len = ft_strlen(str);
	if (!(new_str = ft_strnew(len)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_memcpy(new_str, str, pos);
	ft_memcpy(new_str + pos, str + pos + 1, len - pos - 1);
	free(str);
	return (new_str);
}

static char	*check_bs(char *str, size_t *pos)
{
	char	*tmp;

	tmp = del_bs(str, *pos);
	(*pos)++;
	return (tmp);
}

static int	cut(char **str, size_t *pos, t_qt *qt)
{
	if ((*str)[*pos] == '\\' && *qt != QT_SQ)
	{
		*str = check_bs(*str, pos);
		return (1);
	}
	else if ((*str)[*pos] == '"' || (*str)[*pos] == '\'')
	{
		if (((*str)[*pos] == '"' && *qt == QT_SQ)
		|| ((*str)[*pos] == '\'' && *qt == QT_DQ))
			return (0);
		*str = del_quote(*str, *pos, qt);
		return (1);
	}
	return (0);
}

char		**cut_quotes(char **args)
{
	size_t		i;
	size_t		j;
	t_qt		qt;

	i = 0;
	while (args[i])
	{
		j = 0;
		qt = QT_NQ;
		while (args[i][j])
		{
			if (cut(&args[i], &j, &qt))
				continue ;
			j++;
		}
		i++;
	}
	return (args);
}
