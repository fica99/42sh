/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara- <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 13:42:45 by olegmulko         #+#    #+#             */
/*   Updated: 2019/12/21 18:21:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char		**ac_parse_cmd_line(char *line, t_autocom *ac)
{
	char	*position;
	short	is_prog;

	if (!(position = ft_strrchr(line, ';')))
		position = line;
	else
		position++;
	is_prog = (ft_get_cnt_words(position, " ") > 1) ? 0 : 1;
	position = ft_last_word_pos(position, " ");
	return (ac_get_options(position, is_prog, ac));
}

char		*ac_parse_path(char *dirpath)
{
	char	*newpath;
	char	*slesh_pos;

	if (!dirpath)
		return (NULL);
	if (!(slesh_pos = ft_strrchr(dirpath, '/')))
	{
		if (!(newpath = ft_strdup("./")))
			return (NULL);
	}
	else
	{
		*(slesh_pos + 1) = '\0';
		if (!(newpath = ft_strdup(dirpath)))
			return (NULL);
	}
	ft_memdel((void **)&dirpath);
	return (newpath);
}

char		*ac_parse_arg(char *dirpath)
{
	char	*arg;
	char	*end_path;
	char	*line;

	if (!(line = ft_strdup(dirpath)))
		return (NULL);
	if ((end_path = ft_strrchr(line, '/')))
	{
		arg = (*(end_path + 1) == '\0') ? ft_strdup("*") :
		ft_strdup(end_path + 1);
		if (!arg)
			return (NULL);
	}
	else if (!(arg = (*line == '~') ? ft_strdup("*") :
	ft_strdup(dirpath)))
		return (NULL);
	ft_memdel((void **)&line);
	return (arg);
}

char		*ac_tilda(char *dirpath)
{
	char	*newpath;
	char	*home;
	size_t	i;

	if (!dirpath)
		return (NULL);
	i = 0;
	while (dirpath[i] && (dirpath[i] == '~'
		|| dirpath[i] == '/'))
		i++;
	if (!(home = get_env("HOME", ENV)))
		return (NULL);
	if (!(home = ft_strjoin(home, "/")))
		return (NULL);
	if (!(newpath = ft_strjoin(home, dirpath + i)))
		return (NULL);
	ft_memdel((void **)&home);
	return (newpath);
}
