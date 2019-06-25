/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:07:13 by filip             #+#    #+#             */
/*   Updated: 2019/06/25 17:24:02 by aashara-         ###   ########.fr       */
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
char			*ft_getenv(char *arr);
char			*strnew_realloc_buf(char *str, short len);
char			*ft_strdel_el(char	*buf, size_t i);
char			*ft_stradd(char	*buf, char *s, size_t i);
short			get_count_var(char *arr);
void			ft_setenv(char *name, char *new_value);
char			*join_env(char *name, char *new_value);
void			print_environ(void);
char			*check_path(void);
pid_t			make_process(void);
char			check_print_arr(char *arr);
#endif
