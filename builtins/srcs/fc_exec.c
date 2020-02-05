/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:40:55 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/05 16:51:27 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "main.h"

static char		**fc_get_list(int first, int last)
{
	char	**res;
	int		i;
	char	*copy;
	char	*elem;

	if (!(res = ft_darnew(abs(last - first) + 1)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	i = -1;
	while (first != last)
	{
		(first > last) ? (copy = ft_itoa(first--)) :
		(copy = ft_itoa(first++));
		if ((elem = get_hist_expansions(copy)))
			res[++i] = elem;
		ft_strdel(&copy);
	}
	copy = ft_itoa(first);
	if ((elem = get_hist_expansions(copy)))
		res[++i] = elem;
	ft_strdel(&copy);
	return (res);
}

static void		fc_write_commands(int first, int last, char *path)
{
	char	**line;
	char	*new_line;

	if ((line = fc_get_list(first, last)))
	{
		if (!(new_line = ft_dar2str(line, "\n")))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		ft_free_dar(line);
		ft_write_to_file(path, O_RDWR | O_CREAT | O_TRUNC,
								S_IRUSR | S_IWUSR, new_line);
		ft_strdel(&new_line);
	}
}

static void		fc_print_list(t_fc *fc)
{
	char	**line;
	int		i;
	int		first;
	int		last;

	if (fc->flag_r)
		ft_swap(&fc->first_i, &fc->last_i);
	line = fc_get_list(fc->first_i, fc->last_i);
	i = -1;
	first = fc->first_i;
	last = fc->last_i;
	while (line[++i])
	{
		if (fc->flag_n)
			ft_putstr("\t");
		else
			ft_putnbr((first > last) ? first-- : first++);
		ft_putstr("\t");
		ft_putendl(line[i]);
	}
	ft_free_dar(line);
}

void			fc_exec(t_fc *fc)
{
	char	*path;
	char	*line;
	char	*random;

	if (fc->flag_l)
		fc_print_list(fc);
	else
	{
		if (!(path = get_var("TMPDIR", ALL_VARS)))
			path = "/tmp/";
		random = ft_itoa(rand());
		path = ft_strjoin(path, random);
		ft_strdel(&random);
		fc_write_commands(fc->first_i, fc->last_i, path);
		if (!(line = ft_strnew(ft_strlen(path) + ft_strlen(fc->editor) + 1)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		ft_strcat(ft_strcat(ft_strcpy(line, fc->editor), " "), path);
		ft_system(&line);
		ft_strdel(&line);
		line = ft_read_file(path);
		ft_strdel(&path);
		if (g_last_exit_status == 0)
			ft_system(&line);
		ft_strdel(&line);
	}
}
