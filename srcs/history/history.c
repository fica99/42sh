/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/30 18:11:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		make_history_buff(t_history *history)
{
	int		fd;
	char	**buff;
	short	len;
	int		histsize;
	int		histfilesize;

	history->hisfile_path = get_history_file_path();
	if ((fd = open(history->hisfile_path, OPEN_HISTFILE, PERM_HISTFILE)) == -1)
		err_exit(g_argv[0], "open() error", NULL, NOERROR);
	if (!(histsize = ft_atoi(ft_getenv("HISTSIZE"))))
		histsize = HISTSIZE;
	if (!(histfilesize = ft_atoi(ft_getenv("HISTFILESIZE"))))
		histfilesize = HISTFILESIZE;
	history->histsize = histsize;
	history->histfilesize = histfilesize;
	if (!(buff = ft_darnew(histsize)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	len = 0;
	while (len != histsize && (get_next_line(fd, &buff[len]) > 0))
		len++;
	history->hist_len = len;
	history->history_buff = buff;
	if (close(fd) == -1)
		err_exit(g_argv[0], "close() error", NULL, NOERROR);
}

void	free_history(t_history *history)
{
	char	**buf;

	rewrite_file(history);
	buf = history->history_buff;
	ft_free_dar(buf);
	ft_strdel(&history->hisfile_path);
	history->history_buff = NULL;
	history->hist_len = 0;
}

void		add_to_history_buff(char *buffer, t_history *history)
{
	short	len;
	short	i;
	char	*nl;

	while ((nl = ft_strchr(buffer, '\n')))
	{
		*nl = '\0';
		add_to_history_buff(buffer, history);
		buffer = nl + 1;
	}
	len = history->hist_len;
	if (len >= history->histsize)
	{
		ft_memdel((void**)&(history->history_buff[0]));
		i = -1;
		while (++i < len - 1)
			history->history_buff[i] = history->history_buff[i + 1];
		if (!(history->history_buff[i] = ft_strdup(buffer)))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	}
	else
	{
		if (!(history->history_buff[history->hist_len++] = ft_strdup(buffer)))
			err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	}
}

void		rewrite_file(t_history *history)
{
	int		fd;
	short	i;

	if ((fd = open(history->hisfile_path,
	REWRITE_HISTFILE, PERM_HISTFILE)) == -1)
		err_exit(g_argv[0], "open() error", NULL, NOERROR);
	i = -1;
	if (history->histfilesize < history->hist_len)
		i += history->hist_len - history->histfilesize;
	while (++i < history->histsize)
	{
		ft_putstr_fd(history->history_buff[i], fd);
		ft_putchar_fd('\n', fd);
	}
	if (close(fd) == -1)
		err_exit(g_argv[0], "close() error", NULL, NOERROR);
}

char	*get_history_file_path(void)
{
	if (ft_getenv("PWD"))
		return (ft_strjoin(ft_getenv("PWD"), HISTORY_FILE));
	return (NULL);
}
