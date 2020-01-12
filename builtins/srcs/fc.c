/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:01:57 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/12 20:23:54 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		**fc_get_list(int first, int last)
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

static void	fc_check_flags(int flags, char *editor, int first, int last)
{
	char	*line;
	char	*path;

	if (flags & FC_FLAG_L)
		fc_print_command(flags, first, last);
	else
	{
		if (!(path = ft_strjoin(get_env("TMPDIR", ENV), FC_FILE_EDITOR)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		if (!(line = ft_strnew(ft_strlen(path) + ft_strlen(editor) + 1)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		fc_write_commands(first, last, path);
		ft_strcat(ft_strcat(ft_strcpy(line, editor), " "), path);
		ft_system(line);
		ft_strdel(&line);
		if (!(line = ft_read_file(path)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		ft_strdel(&path);
		ft_putendl(line);
		ft_system(line);
		ft_strdel(&line);
	}
}

static void	fc_check_data(int flags, char *editor, int argc, char **argv)
{
	char	*first;
	char	*last;
	int		first_i;
	int		last_i;
	int		size;

	first = NULL;
	last = NULL;
	if (!editor && !(editor = get_env("FCEDIT", ENV))
	&& !(editor = get_env("EDITOR", ENV)))
		editor = "vi";
	if (optind < argc)
		first = argv[optind++];
	if (optind < argc)
		last = argv[optind];
	size = get_hist_size();
	if ((first_i = ft_atoi((!first) ? "-16" : first)) <= 0)
		first_i += size;
	if ((last_i = ft_atoi((!last) ? "-1" : last)) <= 0)
		last_i += size;
	if (first_i > size)
		first_i = size - 1;
	if (last_i > size)
		last_i = size - 1;
	fc_check_flags(flags, editor, first_i, last_i);
}

static void	fc_find_flags(int opt, int *flags)
{
	if (opt == 'n')
		*flags |= FC_FLAG_N;
	else if (opt == 'l')
		*flags |= FC_FLAG_L;
	else if (opt == 'r')
		*flags |= FC_FLAG_R;
	else if (ft_isdigit(opt))
		*flags |= FC_DIGIT;
	else
		*flags |= FC_FLAG_ERROR;
}

int			fc(int argc, char **argv)
{
	int		opt;
	int		flags;
	int		res;
	char	*editor;

	editor = NULL;
	flags = 0;
	res = EXIT_SUCCESS;
	while ((opt = getopt(argc, argv, "e:lnr1234567890")) != -1)
	{
		if (opt == 'e')
			editor = optarg;
		fc_find_flags(opt, &flags);
		if (flags & FC_DIGIT)
			break ;
	}
	if (!(flags & FC_FLAG_ERROR))
		fc_check_data(flags, editor, argc, argv);
	else
	{
		ft_putendl(FC_USAGE);
		res = EXIT_FAILURE;
	}
	optind = 1;
	return (res);
}
