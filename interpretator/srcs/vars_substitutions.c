/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_substitutions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 02:23:31 by aashara           #+#    #+#             */
/*   Updated: 2020/02/15 02:58:59 by aashara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char	*var_substitution(char *line, size_t pos)
{
	size_t	i;
	char	*to_find;
	char	*var;
	char	*res;

	i = pos + 1;
	while (line[i] && !ft_isspace(line[i]) && line[i] != '\''
	&& line[i] != '"' && line[i] != '$')
		++i;
	if (!(to_find = ft_strsub(line, pos + 1, i - (pos + 1))))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	var = get_var(to_find, ALL_VARS);
	ft_strdel(&to_find);
	if (!(res = ft_strnew(ft_strlen(var) + ft_strlen(line))))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	res = ft_strncpy(res, line, pos);
	if (var)
		res = ft_strcat(res, var);
	res = ft_strcat(res, line + i);
	ft_strdel(&line);
	return (res);
}

char		**vars_substitutions(char **args)
{
	size_t	i;
	size_t	j;
	t_qt	qt;

	i = 0;
	while (args[i])
	{
		j = 0;
		qt = QT_NQ;
		while (args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '"')
				qt = check_quotes_type(args[i], j, qt);
			if (qt != QT_SQ)
			{
				if (args[i][j] == '$')
					args[i] = var_substitution(args[i], j);
			}
			++j;
		}
		++i;
	}
	return (args);
}
