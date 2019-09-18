/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:49:40 by filip             #+#    #+#             */
/*   Updated: 2019/09/18 21:10:39 by aashara-         ###   ########.fr       */
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
void	transmit_mode(void);
void	reset_transmit_mode(void);
/*
**	set_data.c
*/
void	set_data(t_line *line);
void	get_cur_cord(t_cord *cord);
void	get_win_size(t_cord *cord);
void	unset_cord(t_cord *cord);
void	unset_data(t_line *line);
/*
**	new_line.c
*/
void	check_new_line(t_line *line, char *c);
/*
**	quotes.c
*/
void	check_quotes(t_line *line);
char	*quotes_dquotes_brackets(short q, short dq, short br, t_line *line);
void	print_quotes(short q, short dq, short br, t_line *line);
/*
**	heredoc.c
*/
char	*check_heredoc(t_buff buffer, t_buff *stop_buff, t_cord *cord);
short	find_heredoc(char *buffer);
void	print_heredoc(char *buffer, t_cord *cord);
void	check_heredoc_end(char *buffer, char *stop_buff, t_cord *cord);
void	write_hered(char **buf);
#endif
