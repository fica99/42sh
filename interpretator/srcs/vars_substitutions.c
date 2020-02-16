/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_substitutions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jijerde <jijerde@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 02:23:31 by aashara           #+#    #+#             */
/*   Updated: 2020/02/16 02:56:11 by jijerde          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

char		*strcutcopy(char *dest, char *copy, int i, int n)
{
	char	*new;
	int		copylen;

	if (!copy)
		copy = "";
	copylen = ft_strlen(copy);
	if (!(new = (char *)malloc(ft_strlen(dest) + copylen + 1 - n)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_memcpy(new, dest, i);
	ft_memcpy(new + i, copy, copylen);
	ft_memcpy(new + i + copylen, dest + i + n + 1,
											ft_strlen(dest + i + n));
	return (new);
}

static char	*dollar_expr(char *line, int pos)
{
	char	*var;
	int		i;
	char	*replace;
	int		pos_save;

	i = 0;
	pos_save = pos;
	if (!(var = ft_strnew(LINE_MAX)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	pos++;
	while (line[pos] && isvalidparameter(line[pos]))
		var[i++] = line[pos++];
	replace = get_var(var, ALL_VARS);
	ft_memdel((void**)&var);
	return (strcutcopy(line, replace, pos_save, i));
}

static char	*var_substitution(char *line, size_t pos)
{
	char	*for_return;

	for_return = NULL;
	if (line[pos + 1] == '{')
		for_return = expansions(line, pos);
	else
		for_return = dollar_expr(line, pos);
	if (for_return)
		ft_strdel(&line);
	else
		return (line);
	return (for_return);
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
			if (qt != QT_SQ && args[i][j] == '$')
			{
				args[i] = var_substitution(args[i], j);
				continue ;
			}
			++j;
		}
		++i;
	}
	return (args);
}
