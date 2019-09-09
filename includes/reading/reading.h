/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:49:40 by filip             #+#    #+#             */
/*   Updated: 2019/09/09 22:45:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H

# include <unistd.h>

/*
**	canon_mode.c
*/
void	set_attr(struct termios *savetty);
void	set_input_mode(struct termios *tty);
void	save_attr(struct termios *savetty);
/*
**	reading.c
*/
void	read_prompt(t_term *term);
void	reading(t_line *line);
void	read_handler(char *c, int fd);
void	init_terminfo(void);
void	reset_terminfo(void);
#endif
