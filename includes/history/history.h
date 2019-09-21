/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:54:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/21 20:50:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>

# define HISTSIZE 500
# define HISTFILESIZE 500
# define HISTORY_FILE "/.history"
# define PERM_HISTFILE S_IRUSR | S_IWUSR
# define OPEN_HISTFILE O_RDONLY | O_CREAT

typedef struct		s_history
{
	char			**history_buff;
	short			history_index;
	char			*history_path;
	short			hist_fd;
	short			hist_len;
	short			histsize;
	short			histfilesize;
}					t_history;

/*
**	make_history.c
*/
void		make_history_buff(t_history *history);
void		free_history(t_history *history);
char		*get_history_file_path(void);
/*
**	write_history.c
*/
void		add_to_history(char *buffer, t_history *history);
void		write_history(char *buffer, t_history *history);
void		rewrite_file(short len, t_history *history);
void		add_to_file(short len, t_history *history);

t_history	g_history;
#endif
