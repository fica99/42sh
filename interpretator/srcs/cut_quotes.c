/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:48:13 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/15 18:49:45 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char	*del_bs(char *str, size_t pos)
{
	char *new_str;

	if (!str)
		return (NULL);
	str[pos] = '\0';
	if (!(new_str = ft_strjoin(str, str + pos + 1)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	free(str);
	return (new_str);
}

static char	*del_quote(char *str, size_t pos, t_qt *qt, short *is_cut)
{
	char	*new_str;
	size_t	len;

	*is_cut = 1;
	*qt = check_quotes_type(str, pos, *qt);
	len = ft_strlen(str);
	if (!(new_str = ft_strnew(len)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_memcpy(new_str, str, pos);
	ft_memcpy(new_str + pos, str + pos + 1, len - pos - 1);
	free(str);
	return (new_str);
}

static char	*check_bs(char *str, size_t *pos, t_qt qt)
{
	char	*tmp;

	if (!((str[(*pos) + 1] == '"' && qt == QT_DQ)
		|| (str[(*pos) + 1] == '\'' && qt == QT_SQ)))
		return (str);
	tmp = del_bs(str, *pos);
	(*pos)++;
	return (tmp);
}

char		**cut_quotes(char **args)
{
	size_t		i;
	size_t		j;
	t_qt		qt;
	short		is_cut;

	i = 0;
	while (args[i])
	{
		j = 0;
		qt = QT_NQ;
		while (args[i][j])
		{
			is_cut = 0;
			if (args[i][j] == '\\')
				args[i] = check_bs(args[i], &j, qt);
			if (args[i][j] == '"' || args[i][j] == '\'')
				args[i] = del_quote(args[i], j, &qt, &is_cut);
			if (is_cut)
				continue ;
			j++;
		}
		i++;
	}
	return (args);
}
