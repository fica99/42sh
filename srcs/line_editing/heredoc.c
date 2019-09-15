/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:32:47 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/15 20:17:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"


char	*check_heredoc(t_buff buffer, t_buff *stop_buff, t_cord *cord)
{
	short	j;
	short	i;

	if ((j = find_heredoc(buffer.buffer)) == -1)
		return (NULL);
	i = 0;
	while (buffer.buffer[j] && buffer.buffer[j] == ' ')
		j++;
	while (buffer.buffer[j] && ft_isalnum(buffer.buffer[j]))
		stop_buff->buffer[i++] = buffer.buffer[j++];
	if (*(stop_buff->buffer) == '\0')
	{
		g_line_flags |= BREAK_FLAG;
		g_line_flags |= HEREDOC_ERROR_FLAG;
		g_line_flags &= ~HEREDOC_FLAG;
		return (NULL);
	}
	print_heredoc(buffer.buffer, cord);
	return (SOMETHING);
}

short	find_heredoc(char *buffer)
{
	short	i;

	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '<' && (buffer[i + 1] && buffer[i + 1] == '<'))
		{
			g_line_flags |= HEREDOC_FLAG;
			return (i + 2);
		}
	}
	return (-1);
}

void	print_heredoc(char *buffer, t_cord *cord)
{
	go_right(ft_strlen(buffer) - cord->pos, cord);
	ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
	ft_putstr_fd("\nheredoc> ", STDIN_FILENO);
	get_cur_cord(cord);
	set_start_cord(cord);
}

void	check_heredoc_end(char *buffer, char *stop_buff, t_cord *cord)
{
	char	*last_line;

	if (!(last_line = ft_strrchr(buffer, NEW_LINE) + 1))
		return ;
	if (last_line && !ft_strcmp(last_line, stop_buff))
		g_line_flags |= BREAK_FLAG;
	else
		print_heredoc(buffer, cord);
}

void	write_hered(char **buf)
{
	char	*her;
	int		fd;

	if (!buf || !*buf || !(**buf))
		return ;
	if (g_line_flags & HEREDOC_ERROR_FLAG)
	{
		err("42sh", "heredoc error", NULL, NOERROR);
		ft_memdel((void**)buf);
	}
	else if (g_line_flags & HEREDOC_FLAG)
	{
		her = ft_strdup(ft_strchr(*buf, '\n') + 1);
		ft_strclr(ft_strchr(*buf, '\n'));
		if (!(g_line_flags & HEREDOC_CTRL_D))
		{
			(ft_strrchr(her, '\n')) ? ft_strclr(ft_strrchr(her, '\n') + 1)
			: ft_memdel((void**)&her);
		}
		if ((fd = open(HEREDOC_FILE, RRED_OPEN, PERM_MODE)) == -1)
			err_exit("42sh", "open() error", NULL, NOERROR);
		ft_putstr_fd(her, fd);
		close(fd);
		ft_memdel((void**)&her);
	}
}
