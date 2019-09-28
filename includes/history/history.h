/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:54:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/28 15:03:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define HISTSIZE 500
# define HISTFILESIZE 500
# define HISTORY_FILE "/.history"
# define PERM_HISTFILE S_IRUSR | S_IWUSR
# define OPEN_HISTFILE O_RDWR | O_CREAT
# define REWRITE_HISTFILE O_RDWR | O_TRUNC

typedef struct		s_history
{
	char			**history_buff;
	char			*hisfile_path;
	short			hist_len;
	short			histsize;
	short			histfilesize;
}					t_history;

/*
**	history.c
*/
void		make_history_buff(t_history *history);
void		free_history(t_history *history);
void		add_to_history_buff(char *buffer, t_history *history);
void		rewrite_file(t_history *history);
char		*get_history_file_path(void);
t_history	g_history;
#endif
