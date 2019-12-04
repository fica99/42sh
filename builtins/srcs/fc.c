/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:01:57 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/03 20:01:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	fc_print_usage(void)
{
	ft_putendl(FC_USAGE);
}

void	fc_open_editor(char *editor, char *first, char *last, char *path)
{
	char	*line;

	(void)last;
	if (!first)
		first = "!";
	line = get_hist_expansions(first);
	ft_write_to_file(path, FC_FILE_FLAGS, FC_FILE_PERM, line);
	ft_strdel(&line);
	if (!(line = ft_strnew(ft_strlen(path) + ft_strlen(editor) + 1)))
		err_exit("42sh", "malloc() error", NULL, ENOMEM);
	ft_strcat(ft_strcat(ft_strcpy(line, editor), " "), path);
	check_valid_string(line);
	ft_strdel(&line);
}

void	fc_check_flags(int flags, char *editor, char *first, char *last)
{
	char	*line;
	char	*path;

	(void)editor;
	if (flags & FC_FLAG_L)
		fc_flag_l(flags, first, last);
	else if (!(flags & FC_FLAG_S))
	{
		if (!(path = ft_strjoin(get_env("TMPDIR", ENV), FC_FILE_EDITOR)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		fc_open_editor(editor, first, last, path);
		if (!(line = ft_read_file(path)))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		ft_strdel(&path);
		ft_putendl(line);
		check_valid_string(line);
		add_to_history_buff(line);
		ft_strdel(&line);
	}
}

void	fc_check_error(int flags, char *editor, int argc, char **argv)
{
	char	*first;
	char	*last;

	first = NULL;
	last = NULL;
	if (flags & FC_FLAG_ERROR)
	{
		fc_print_usage();
		return ;
	}
	if (!editor && !(editor = get_env("FCEDIT", ENV))
	&& !(editor = get_env("EDITOR", ENV)))
		editor = "vi";
	if (optind < argc)
		first = argv[optind++];
	if (optind < argc)
		last = argv[optind];
	fc_check_flags(flags, editor, first, last);
}

void	fc(int argc, char **argv)
{
	int 	opt;
	int		flags;
	char	*editor;

	editor = NULL;
	flags = 0;
	while((opt = getopt(argc, argv, "e:lnr")) != -1)
	{
		if (opt == 'e')
			editor = optarg;
		else if (opt == 'n')
			flags |= FC_FLAG_N;
		else if (opt == 'l')
			flags |= FC_FLAG_L;
		else if (opt == 'r')
			flags |= FC_FLAG_R;
			else if (opt == 's')
			flags |= FC_FLAG_S;
		else
			flags |= FC_FLAG_ERROR;
	}
	fc_check_error(flags, editor, argc, argv);
	optind = 1;
}
