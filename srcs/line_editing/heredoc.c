/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:32:47 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/01 16:52:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_shell.h"


char	*check_heredoc(t_buff buffer, t_buff *stop_buff, t_cord *cord)
{
	short	j;
	short	i;

	if ((j = find_heredoc(buffer.buffer)) == -1)
		return (NULL);
	i = 0;
	while(buffer.buffer[++j])
	{
		while (ft_strlen(stop_buff->buffer) + 1 >=
		(unsigned)stop_buff->malloc_len)
			stop_buff->buffer = ft_strdup_realloc(stop_buff->buffer,
			stop_buff->malloc_len += NORMAL_LINE);
		stop_buff->buffer[i++] = buffer.buffer[j];
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
			return (i++);
		}
	}
	return (-1);
}

void	print_heredoc(char *buffer, t_cord *cord)
{
		go_right(ft_strlen(buffer) - cord->pos, cord);
		ft_putstr_fd(tigetstr("ed"), STDIN_FILENO);
		ft_putstr_fd("\nheredoc> ", STDIN_FILENO);
		get_cur_cord(cord);
		set_start_cord(cord);
}

void	check_heredoc_end(char *buffer, char *stop_buff, t_cord *cord)
{
	char	*last_line;

	if (!(last_line = ft_strrchr(buffer, '\n')))
		return ;
	if (!ft_strcmp(last_line, stop_buff))
		g_line_flags |= BREAK_FLAG;
	else
		print_heredoc(buffer, cord);
}
