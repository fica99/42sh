/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_substitutions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 02:23:31 by aashara           #+#    #+#             */
/*   Updated: 2020/02/20 03:05:27 by aashara-         ###   ########.fr       */
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
	if (line[pos] == '$' || line[pos] == '?')
		var[i++] = line[pos++];
	else if (!isvalidparameter(line[pos]))
	{
		ft_strdel(&var);
		return (NULL);
	}
	else
	{
		while (line[pos] && isvalidparameter(line[pos]))
			var[i++] = line[pos++];
	}
	replace = get_var(var, ALL_VARS);
	ft_memdel((void**)&var);
	return (strcutcopy(line, replace, pos_save, i));
}

static char	*var_substitution(char *line, int *pos)
{
	char	*for_return;

	for_return = NULL;
	if (line[*pos + 1] == '{')
		for_return = expansions(line, *pos);
	else if (!ft_strncmp(line + *pos, "$((", 3))
		(*pos) += 3;
	else
		for_return = dollar_expr(line, *pos);
	if (for_return)
	{
		ft_strdel(&line);
		--(*pos);
	}
	else
		for_return = line;
	if (!*for_return)
		ft_strdel(&for_return);
	return (for_return);
}

static char	**delete_element(char **args, int *i)
{
	size_t	len;

	len = ft_darlen(args + *i + 1);
	ft_memcpy(args + *i, args + *i + 1, sizeof(char *) * len);
	args[*i + len] = NULL;
	--(*i);
	if (!*args)
	{
		ft_free_dar(args);
		args = NULL;
	}
	return (args);
}

char		**vars_substitutions(char **args)
{
	int		i;
	int		j;
	t_qt	qt;

	i = -1;
	while (args && args[++i])
	{
		j = -1;
		qt = QT_NQ;
		while (args[i][++j])
		{
			if (check_bs_int(args[i], &j))
				continue ;
			qt = check_quotes_type(args[i], j, qt);
			if (qt != QT_SQ && args[i][j] == '$')
			{
				if (!(args[i] = var_substitution(args[i], &j)))
				{
					args = delete_element(args, &i);
					break ;
				}
			}
		}
	}
	return (args);
}
