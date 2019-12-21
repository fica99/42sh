/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara- <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:27:38 by ggrimes           #+#    #+#             */
/*   Updated: 2019/12/21 18:21:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

char	**ac_get_options(char *start, short is_prog, t_autocom *ac)
{
	char	**options;
	char	*arg;

	if (!start)
		return (NULL);
	ac->start = start;
	ac->prog = is_prog;
	if (is_prog)
	{
		if (!(arg = ft_strdup(start)))
			return (NULL);
		options = ac_prog_options();
	}
	else
	{
		arg = ac_parse_arg(start);
		options = ac_dir_options(start, ac);
	}
	return (ac_options_selection(arg, options));
}

char	**ac_newselection(char **options, char *search_arg)
{
	char	**selection;
	size_t	size;

	if (!options && !search_arg)
		return (NULL);
	if (!(size = ft_num_match(options, search_arg)))
		return (NULL);
	if (!(selection = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	return (selection);
}

char	**ac_options_selection(char *arg, char **options)
{
	int		i;
	int		j;
	char	**selection;
	char	*search_arg;

	if (!options || !arg)
		return (NULL);
	if (!(search_arg = ft_strjoin(arg, "*")))
		return (NULL);
	if (!(selection = ac_newselection(options, search_arg)))
	{
		clear_opts_args(arg, search_arg, options);
		return (NULL);
	}
	i = -1;
	j = -1;
	while (options[++i])
		if (ft_match(options[i], search_arg))
			selection[++j] = ft_strdup(options[i]);
	selection[++j] = NULL;
	clear_opts_args(arg, search_arg, options);
	return (selection);
}

char	**ac_dir_options(char *dirpath, t_autocom *ac)
{
	char	*path;
	char	**options;

	if (!dirpath)
		return (NULL);
	path = (*dirpath == '~') ? ac_tilda(dirpath) : ft_strdup(dirpath);
	if (!path)
		return (NULL);
	path = ac_parse_path(path);
	ac->path = path;
	options = ft_dir_content(path, 0);
	return (options);
}

char	**ac_prog_options(void)
{
	char	**paths;
	char	**options;
	int		i;

	if (!(paths = ft_strsplit(get_env("PATH", ENV), ':')))
		return (NULL);
	i = -1;
	options = NULL;
	while (paths[++i])
		options = ac_add_options(paths[i], options);
	ft_free_dar(paths);
	return (options);
}
