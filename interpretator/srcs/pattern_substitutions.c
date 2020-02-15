/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_substitutions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 16:45:51 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/15 17:18:17 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char		is_glob(char c)
{
	if (c == '*' || c == '?' || c == '[' || c == ']')
		return (TRUE);
	return (FALSE);
}

static char		**pattern_substitution(char **args, size_t i)
{
	char	**res;
	glob_t	globbuf;
	size_t	k;

	res = args;
	if (!glob(args[i], 0, NULL, &globbuf))
	{
		if (!globbuf.gl_pathc)
			return (res);
		if (!(res = ft_darnew(ft_darlen(args) + globbuf.gl_pathc)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		ft_memcpy(res, args, i * sizeof(char *));
		k = 0;
		while (k < globbuf.gl_pathc)
		{
			res[i + k] = ft_strdup(globbuf.gl_pathv[k]);
			++k;
		}
		ft_memcpy(res + i + globbuf.gl_pathc, args + i + 1, sizeof(char *) *
										ft_darlen(args + i + 1));
		ft_memdel((void**)&args[i]);
		free(args);
	}
	globfree(&globbuf);
	return (res);
}

char		**pattern_substitutions(char **args)
{
	size_t	i;
	size_t	j;
	t_qt	qt;
	char	pattern;

	i = 0;
	while (args[i])
	{
		j = 0;
		qt = QT_NQ;
		pattern = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '"')
				qt = check_quotes_type(args[i], j, qt);
			if (qt == QT_NQ)
				if (is_glob(args[i][j]))
					pattern = 1;
			++j;
		}
		if (pattern)
			args = pattern_substitution(args, i);
		++i;
	}
	return (args);
}
