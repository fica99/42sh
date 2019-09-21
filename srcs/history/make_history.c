/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:57:09 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/21 22:37:57 by aashara-         ###   ########.fr       */
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

	if (!(history->history_path = get_history_file_path()))
		return ;
	if ((fd = open(history->history_path, OPEN_HISTFILE,
	PERM_HISTFILE)) == -1)
		err_exit("open() error", NULL, NOERROR);
	history->hist_fd = fd;
	if (!(histsize = ft_atoi(ft_getenv("HISTSIZE", g_env.env))))
		histsize = HISTSIZE;
	if (!(histfilesize = ft_atoi(ft_getenv("HISTFILESIZE", g_env.env))))
		histfilesize = HISTFILESIZE;
	history->histsize = histsize;
	history->histfilesize = histfilesize;
	if (!(buff = ft_darnew(histsize)))
		err_exit("malloc() error", NULL, ENOMEM);
		len = 0;
	while (len != histsize && (get_next_line(fd, &buff[len]) > 0))
		len++;
	history->hist_len = len;
	history->history_buff = buff;
}

void	free_history(t_history *history)
{
	char	**buf;

	buf = history->history_buff;
	history->history_index = -1;
	ft_memdel((void**)&(history->history_path));
	if (close(history->hist_fd) == -1)
		err_exit("close() error", NULL, NOERROR);
	ft_free_dar(buf);
	history->hist_len = 0;
}

char	*get_history_file_path(void)
{
	char	*pwd;

	if ((pwd = ft_getenv("PWD", g_env.env)))
		return (ft_strjoin(pwd, HISTORY_FILE));
	return (NULL);
}
