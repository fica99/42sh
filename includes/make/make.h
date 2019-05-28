/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:07:13 by filip             #+#    #+#             */
/*   Updated: 2019/05/28 19:42:44 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_H
# define MAKE_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <termios.h>

char			**copy_double_arr(char **arr);
char			*strnew_realloc_buf(char *str, short len);
char			*ft_strdel_el(char	*buf, size_t i);
char			*ft_stradd(char	*buf, char *s, size_t i);
char			*ft_getenv(char *arr);
short			get_count_var(char *arr);
void			ft_setenv(char *name, char *new_value);
char			*join_env(char *name, char *new_value);
void			print_environ(void);
char			*check_path(void);
void			get_win_size(void);
void			init_term();
void			get_cur_cord(void);
void			set_input_mode(void);
void			reset_input_mode (void);
void			ft_putstr_cord(char *str);
void			reset_term(void);
pid_t			make_process(void);
#endif
