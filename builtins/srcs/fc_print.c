/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:40:55 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/04 19:40:56 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	fc_print_command(int flags, int first, int last)
{
	char	**line;
	int		i;

	if (flags & FC_FLAG_R)
		ft_swap(&first, &last);
	line = fc_get_list(first, last);
	i = -1;
	while (line[++i])
	{
		if (flags & FC_FLAG_N)
			ft_putstr("\t");
		else
			ft_putnbr((first > last) ? first-- : first++);
		ft_putstr("\t");
		ft_putendl(line[i]);
	}
	ft_free_dar(line);
}

void	fc_write_commands(int first, int last, char *path)
{
	char	**line;
	char	*new_line;

	if ((line = fc_get_list(first, last)))
	{
		if (!(new_line = ft_dar2str(line, "\n")))
			err_exit("42sh", "malloc() error", NULL, ENOMEM);
		ft_free_dar(line);
		ft_write_to_file(path, FC_FILE_FLAGS, FC_FILE_PERM, new_line);
		ft_strdel(&new_line);
	}
}
