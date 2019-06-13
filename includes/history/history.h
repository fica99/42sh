/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:54:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/13 15:46:57 by aashara-         ###   ########.fr       */
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

t_history	*make_history_buff(void);
void		go_history(char *c, t_history *history, t_cord *cord,
t_buff *buffer);
void		history_up(t_history *history, t_cord *cord, short len,
t_buff *buffer);
void		history_down(t_history *history, t_cord *cord, short len,
t_buff *buffer);
void		add_to_historybuf(t_term *term);
char		check_print_arr(char *arr);
void		write_history(t_term *term);
void		rewrite_file(short len, t_history *history);
void		add_to_file(short len, t_history *history);
void		free_history(t_history **history);
void		find_history(char *symbol, t_buff *buffer, t_cord *cord,
t_history *history);
char		*check_history(t_history *history, t_buff *buffer);
#endif
