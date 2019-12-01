/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara- <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 22:01:15 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/01 23:58:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

static void	open_editor(char **env)
{
	char	*editor;
	char	path[1000];
	char	*command;

	if (!(editor = ft_getenv("VISUAL", env)))
		if (!(editor = ft_getenv("EDITOR", env)))
			editor = "vi";
	ft_strcat(ft_strcpy(path, ft_getenv("TMPDIR", env)), RL_VIFILE);
	ft_write_to_file(path, RL_OPEN_VIFILE, RL_PERM_VIFILE,
	get_hist_expansions("!"));
	if (!(command = ft_strnew(1000)))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	ft_strcat(ft_strcat(ft_strcpy(command, editor), " "), path);
	check_valid_string(command);
	ft_strdel(&command);
	if (!(command = ft_read_file(path)))
		err_exit("42sh", "reading error", path, NOERROR);
	ft_putendl(command);
	check_valid_string(command);
	ft_strdel(&command);
}

void	fc(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc == 1)
		open_editor(env);
}
