/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_vi3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:52:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 21:56:06 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_x_upper(t_readline *rl)
{
	char	symb[2];

	symb[1] = '\0';
	symb[0] = rl->line.buffer[rl->cord.pos];
	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	rl_del_symb(rl->line.buffer, &rl->cord);
}

void	rl_k_v(t_readline *rl)
{
	int		fd;
	char	*buff;

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	if ((fd = open(RL_VIFILE, RL_OPEN_VIFILE, RL_PERM_VIFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	ft_putstr_fd(rl->line.buffer, fd);
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	rl_open_editor(rl->env);
	ft_strclr(rl->line.buffer);
	if ((fd = open(RL_VIFILE, RL_READ_VIFILE)) == -1)
		rl_err("42sh", "open() error", UNDEFERR);
	while (get_next_line(fd, &buff) > 0)
	{
		rl_check_str_mem(&rl->line, buff);
		ft_strcat(rl->line.buffer, buff);
		ft_strdel(&buff);
	}
	if (close(fd) == -1)
		rl_err("42sh", "close() error", UNDEFERR);
	rl_k_enter(rl);
}

void	rl_open_editor(char **env)
{
	char	**argv;
	char	*command;

	if (!(argv = ft_darnew(2)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if (!(command = ft_getenv("VISUAL", env)))
		if (!(command = ft_getenv("EDITOR", env)))
			command = "vi";
	if (!(argv[1] = ft_strdup(RL_VIFILE)))
		rl_err("42sh", "malloc() error", ENOMEM);
	if (!(argv[0] = ft_strdup(command)))
		rl_err("42sh", "malloc() error", ENOMEM);
	find_command(argv);
	ft_free_dar(argv);
}

void	rl_k_f_lower(t_readline *rl)
{
	char	*pos;
	char	c[RL_MAX_BUFF + 1];

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_read_handler(c, STDOUT_FILENO);
	if (ft_isprint(*c))
	{
		if ((pos = ft_strchr(rl->line.buffer + rl->cord.pos, *c)))
			rl_go_right(pos - (rl->line.buffer + rl->cord.pos), &rl->cord);
	}
}

void	rl_k_f_upper(t_readline *rl)
{
	short	new_pos;
	char	c[RL_MAX_BUFF + 1];

	if ((g_rl_flags & RL_HISTORY_SEARCH_FLAG) ||
	(g_rl_flags & RL_HIGHLIGHT_FLAG))
		rl_disable_line(rl);
	rl_read_handler(c, STDOUT_FILENO);
	if (ft_isprint(*c))
	{
		new_pos = rl->cord.pos;
		while (new_pos >= 0)
		{
			if (rl->line.buffer[new_pos] == *c)
			{
				rl_go_left(rl->cord.pos - new_pos, &rl->cord);
				break ;
			}
			--new_pos;
		}
	}
}
