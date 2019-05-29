/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:54:54 by aashara-          #+#    #+#             */
/*   Updated: 2019/05/29 20:53:23 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>

# define HISTORY_SIZE 300
# define DEL_HISTORY_INDEX 0
# define INIT_HISTORY_INDEX 0

void	make_history_buff(void);
void	go_history(char *c);
void	history_up(void);
void	history_down(short len);
void	change_buf(void);
void    add_to_historybuf(void);
char	check_print_arr(char *arr);
#endif
