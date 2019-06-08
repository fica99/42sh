/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:54:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/08 15:13:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>

# define HISTORY_SIZE 100

t_history	*make_history_buff(void);
void		go_history(char *c, t_history *history, t_cord *cord, t_buff *buffer);
void		history_up(t_history *history, t_cord *cord, t_buff *buffer);
void		history_down(t_history *history, t_cord *cord, short len, t_buff *buffer);
void    	add_to_historybuf(t_term *term);
char		check_print_arr(char *arr);
void		write_history(t_term *term);
void	    rewrite_file(short len, t_history *history);
void	    add_to_file(short len, t_history *history);
void		free_history(t_history **history);
void	    find_history(char **buffer, t_cord *cord, t_history *history);
#endif
