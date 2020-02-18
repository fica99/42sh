/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilda_substitutions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 02:18:08 by aashara           #+#    #+#             */
/*   Updated: 2020/02/18 12:15:19 by aashara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

static char	*tilda_substitution(char *line)
{
	char			*res;
	char			*path;
	char			*slash;
	struct passwd	*data;

	res = NULL;
	if (*(line + 1) == '/' || !*(line + 1))
	{
		if ((path = get_var("HOME", ENV)))
			if (!(res = ft_strjoin(path, line + 1)))
				err_exit("42sh", "malloc() error", NULL, ENOMEM);
	}
	else
	{
		if ((slash = ft_strchr(line, '/')))
			path = ft_strsub(line, 1, slash - (line + 1));
		else
			path = ft_strdup(line + 1);
		if ((data = getpwnam(path)))
			res = ft_strjoin(data->pw_dir, (!slash) ? "" : slash);
		else
			res = ft_strdup(line);
		ft_strdel(&path);
	}
	return (res);
}

char		**tilda_substitutions(char **args)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '~')
		{
			tmp = tilda_substitution(args[i]);
			ft_strdel(&args[i]);
			args[i] = tmp;
		}
		++i;
	}
	return (args);
}
