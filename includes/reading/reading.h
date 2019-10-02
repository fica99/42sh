/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:49:40 by filip             #+#    #+#             */
/*   Updated: 2019/10/02 15:25:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H

# define READING 1
# define BREAK_FLAG (1 << 1)

/*
**	read_mode.c
*/
void	set_attr(struct termios *savetty);
void	set_input_mode(struct termios *tty);
void	save_attr(struct termios *savetty);
void	is_stdin_term(void);
void	init_terminfo(void);
/*
**	reading.c
*/
char	*read_prompt(void);
void	reading(t_line *line);
void	read_handler(char *c, int fd);

struct termios	g_orig_mode;
struct termios	g_raw_mode;
#endif
