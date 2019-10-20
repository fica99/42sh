/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:03:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/20 17:59:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	autocom(t_line *line)
{
	char	*command;

	command = ac_parse_line(line->buffer.buffer, line->cord->pos);
	ac_bins(command, line->cord);
	ft_strdel(&command);
}

char	*ac_parse_line(char *buff, short pos)
{
	char	*command;
	short	start;

	start = pos - 1;
	while (start && ft_isalnum(buff[start]))
		--start;
	command = NULL;
	if (start != pos)
		if (!(command = ft_strsub(buff, start, pos)))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	return (command);
}

void	ac_bins(char *command, t_cord *cord)
{
	char	*bin;

	if (!command)
		return ;
	ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
	go_to_cord(cord->x_end, cord->y_end, STDIN_FILENO);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	while ((bin = get_bin(command)))
	{
		ft_putchar_fd(NEW_LINE, STDIN_FILENO);
		check_end_window(cord);
		ft_putstr_fd(bin, STDIN_FILENO);
	}
	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
	ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
}

char	*get_bin(char *command)
{
	static size_t	i;
	t_hash			*hash;
	int				len;
	char			*data;

	len = ft_strlen(command);
	while (i < g_bin_table.size)
	{
		hash = g_bin_table.table[i];
		while (hash)
		{
			data = ft_strrchr((char*)hash->data, '/');
			if (!ft_strncmp(command, ++data, len))
			{
				++i;
				return (data);
			}
			hash = hash->next;
		}
		++i;
	}
	return (NULL);
}
