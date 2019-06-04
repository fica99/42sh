/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:54:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/02 15:15:25 by filip            ###   ########.fr       */
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

typedef struct	s_history
{
	char		**history_buff;
	short		history_index;
	char			*history_path;
}				t_history;

t_history	*make_history_buff(void);
void		go_history(char *c, t_history *history, t_cord *cord, char *buffer);
void		history_up(t_history *history, t_cord *cord);
void		history_down(t_history *history, t_cord *cord, short len, char *buffer);
void		change_buf(t_history *history, char **buffer);
void    	add_to_historybuf(void);
char		check_print_arr(char *arr);
void		write_history(void);
void		rewrite_file(short len);
void		add_to_file(short len);
void    	free_history(void);
void		find_history(void);
#endif
