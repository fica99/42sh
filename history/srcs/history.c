/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/05 20:07:38 by aashara-         ###   ########.fr       */
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

	if (!(histsize = ft_atoi(sh_getenv("HISTSIZE"))))
		histsize = HISTSIZE;
	if (!(histfilesize = ft_atoi(sh_getenv("HISTFILESIZE"))))
		histfilesize = HISTFILESIZE;
	history->histsize = histsize;
	history->histfilesize = histfilesize;
	if (!(buff = ft_darnew(histsize)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
	history->hisfile_path = get_history_file_path();
	if ((fd = open(history->hisfile_path, OPEN_HISTFILE, PERM_HISTFILE)) == -1)
		err_exit(g_argv[0], "open() error", NULL, NOERROR);
	len = 0;
	while (len != histsize && (get_next_line(fd, &buff[len]) > 0))
		++len;
	if (close(fd) == -1)
		err_exit(g_argv[0], "close() error", NULL, NOERROR);
	history->hist_len = len;
	history->history_buff = buff;
}

void		free_history(t_history *history)
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
	if (!*buffer)
		return ;
	len = history->hist_len;
	if (len >= history->histsize)
	{
		ft_memdel((void**)&(history->history_buff[0]));
		i = -1;
		while (++i < len - 1)
			history->history_buff[i] = history->history_buff[i + 1];
	}
	else
		i = ++history->hist_len;
	if (!(history->history_buff[i] = ft_strdup(buffer)))
		err_exit(g_argv[0], "malloc() error", NULL, ENOMEM);
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
		ft_putendl_fd(history->history_buff[i], fd);
	if (close(fd) == -1)
		err_exit(g_argv[0], "close() error", NULL, NOERROR);
}

char		*get_history_file_path(void)
{
	char	*home;

	if ((home = sh_getenv("HOME")))
		return (ft_strjoin(home, HISTORY_FILE));
	return (NULL);
}
