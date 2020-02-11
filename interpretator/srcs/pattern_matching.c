/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 00:14:37 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/12 01:21:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char	is_glob(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == ']')
			return (TRUE);
	}
	return (FALSE);
}

static char	**result_pattern(char *line)
{
	char	**res;
	glob_t	globbuf;
	int		j;

	glob(line, 0, NULL, &globbuf);
	if (!(res = ft_darnew(globbuf.gl_pathc)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	j = -1;
	while (++j < (int)globbuf.gl_pathc)
		if (!(res[j] = ft_strdup(globbuf.gl_pathv[j])))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
	globfree(&globbuf);
	return (res);
}

static int	count_pattern(char **args)
{
	int		i;
	int		counter;
	glob_t	globbuf;

	i = -1;
	counter = 0;
	while (args[++i])
	{
		if (is_glob(args[i]))
		{
			glob(args[i], 0, NULL, &globbuf);
			counter += globbuf.gl_pathc;
			globfree(&globbuf);
		}
		else
			++counter;
	}
	return (counter);
}

char		**pattern_matching(char **args)
{
	char	**tmp;
	char	**res;
	int		i;
	int		k;

	i = -1;
	if (!(res = ft_darnew(count_pattern(args))))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	while (args[++i])
	{
		if (is_glob(args[i]))
		{
			tmp = result_pattern(args[i]);
			k = -1;
			while (tmp[++k])
				if (!(res[i + k] = ft_strdup(tmp[k])))
					err_exit("42sh", "malloc() error", NULL, ENOMEM);
			ft_free_dar(tmp);
		}
		else
			res[i] = ft_strdup(args[i]);
	}
	return (res);
}
