/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:54:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/07/01 16:23:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>

# define HISTORY_SIZE 1000

void		make_history_buff(t_history *history);
void		add_to_historybuf(char *buffer, t_history *history);
void		write_history(char *buffer, t_history *history);
void		rewrite_file(short len, t_history *history);
void		add_to_file(short len, t_history *history);
void		free_history(t_history *history);
char		*get_history_file_path(void);
#endif
