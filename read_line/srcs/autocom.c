/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 17:03:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/21 19:34:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	autocom(t_line *line)
{
	char	*word;
	char	is_command;

	word = ac_get_word(&is_command, line->buffer.buffer, line->cord->pos);
	//ac_bins(command, line->cord);
	ft_strdel(&word);
}

char	*ac_get_word(char *is_command, char *line, short pos)
{
	char	*command;
	short	start;

	start = pos;
	while (--start > 0)
		if (ft_strchr(" \t\n;|", line[start]))
			break ;
	command = NULL;
	if (++start != pos)
		if (!(command = ft_strsub(line, start, pos)))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	*is_command = TRUE;
	while (start > 0 && !ft_strchr(";|", line[start]))
	{
		if (ft_strchr(" \t\n", line[start]))
		{
			*is_command = FALSE;
			break ;
		}
		--start;
	}
	return (command);
}

// void	ac_bins(char *command, t_cord *cord)
// {
// 	char	*bin;

// 	if (!command)
// 		return ;
// 	ft_putstr_fd(SAVE_CUR, STDIN_FILENO);
// 	go_to_cord(cord->x_end, cord->y_end, STDIN_FILENO);
// 	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
// 	ft_putchar_fd(NEW_LINE, STDIN_FILENO);
// 	while ((bin = get_bin(command)))
// 	{
// 		ft_putstr_fd(bin, STDIN_FILENO);
// 		ft_putchar_fd(' ', STDIN_FILENO);
// 	}
// 	go_to_cord(cord->x_cur, cord->y_cur, STDIN_FILENO);
// 	ft_putstr_fd(RESTORE_CUR, STDIN_FILENO);
// }

// char	*get_bin(char *command)
// {
// 	static size_t	i;
// 	t_hash			*hash;
// 	int				len;
// 	char			*data;

// 	len = ft_strlen(command);
// 	while (i < g_bin_table.size)
// 	{
// 		hash = g_bin_table.table[i];
// 		while (hash)
// 		{
// 			data = ft_strrchr((char*)hash->data, '/');
// 			if (!ft_strncmp(command, ++data, len))
// 			{
// 				++i;
// 				return (data);
// 			}
// 			hash = hash->next;
// 		}
// 		++i;
// 	}
// 	return (NULL);
// }
