/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:54:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/31 00:55:15 by filip            ###   ########.fr       */
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
}				t_history;

void	make_history_buff(void);
void	go_history(char *c);
void	history_up(void);
void	history_down(short len);
void	change_buf(void);
void    add_to_historybuf(void);
char	check_print_arr(char *arr);
void	write_history(void);
void	rewrite_file(short len);
void	add_to_file(short len);
void    free_history(void);
#endif
