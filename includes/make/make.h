/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:07:13 by filip             #+#    #+#             */
/*   Updated: 2019/06/13 15:47:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_H
# define MAKE_H

# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <termios.h>
# include <sys/types.h>

char			**copy_double_arr(char **arr);
void			init_term(void);
t_cord			*init_cord(void);
char			*ft_getenv(char *arr);
void			get_win_size(t_cord *cord);
char			*strnew_realloc_buf(char *str, short len);
char			*ft_strdel_el(char	*buf, size_t i);
char			*ft_stradd(char	*buf, char *s, size_t i);
short			get_count_var(char *arr);
void			ft_setenv(char *name, char *new_value);
char			*join_env(char *name, char *new_value);
void			print_environ(void);
char			*check_path(void);
void			get_cur_cord(t_cord *cord);
void			set_input_mode(struct termios *savetty);
void			reset_input_mode(struct termios *savetty);
void			reset_term(void);
pid_t			make_process(void);
char			*get_history_file_path(void);
t_buff			*init_buff(void);
void			set_start_cord(t_cord *cord);
#endif
