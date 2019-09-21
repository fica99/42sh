/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:49:40 by filip             #+#    #+#             */
/*   Updated: 2019/09/21 21:25:21 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H

# include <unistd.h>

typedef struct		s_temp
{
	char			*template;
	char			(*handler)(t_line *line);
	struct s_temp	*next;
}					t_temp;
/*
**	templates.c
*/
t_temp				*init_templates(void);
t_temp				*init_temp_struct(char *template, void (*handler)());
void				free_templates(t_temp **head);
/*
**	set_templates.c
*/
t_temp				*set_templates(void);
t_temp				*set_esc_templates(void);
t_temp				*set_other_templates(char *str);
/*
**	free_line.c
*/
void				free_line(t_line *line);
void				free_cord(t_cord **cord);
void				free_buffer(t_buff *buffer);
/*
**	init_line.c
*/
void				init_line(t_line *line, t_term *term);
void				init_buff(t_buff *buffer);
t_cord				*init_cord(void);
/*
**	canon_mode.c
*/
void	set_attr(struct termios *savetty);
void	set_input_mode(struct termios *tty);
void	save_attr(struct termios *savetty);
void	is_stdin_term(void);
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

struct termios	g_orig_mode;
struct termios	g_raw_mode;
struct s_line	g_line;
#endif
