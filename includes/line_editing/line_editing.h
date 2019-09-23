/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/09/23 22:39:13 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# define CTRL_UP "\033[1;5A"
# define CTRL_DOWN "\033[1;5B"
# define CTRL_RIGHT "\033[1;5C"
# define CTRL_LEFT "\033[1;5D"
# define CTRL_R 18
# define BCSP 127
# define CTRL_H 8
# define CTRL_V 22
# define CTRL_X 24
# define CTRL_D 4
# define CTRL_C 3
# define TAB 9
# define SHIFT_LFT tigetstr("kLFT")
# define SHIFT_RGHT tigetstr("kRIT")
# define K_LFT tigetstr("kcub1")
# define K_RGHT tigetstr("kcuf1")
# define K_HOME tigetstr("khome")
# define K_END tigetstr("kend")
# define K_UP tigetstr("kcuu1")
# define K_DOWN tigetstr("kcud1")
# define K_DEL tigetstr("kdch1")
# define NEW_LINE '\n'
# define TRANSMIT_MODE tigetstr("smkx")
# define STOP_TRANSMIT_MODE tigetstr("rmkx")
# define SET_CUR tigetstr("cup")
# define SAVE_CUR tigetstr("sc")
# define RESTORE_CUR tigetstr("rc")
# define CLEAR_END_SCREEN tigetstr("ed")
# define CLEAR_SCREEN tigetstr("clear")
# define CUR_CORD tigetstr("u7")

# define HEREDOC_FLAG (1 << 1)
# define HISTORY_SEARCH (1 << 2)
# define TERM_HIGHLIGHT (1 << 3)
# define START_POS (1 << 4)
# define TERM_QUOTES (1 << 5)
# define TERM_NL (1 << 6)
# define BREAK_FLAG (1 << 7)
# define HEREDOC_ERROR_FLAG (1 << 8)
# define HEREDOC_CTRL_D (1 << 9)

# define NORMAL_LINE 1000

typedef struct		s_cord
{
	short			x_start;
	short			y_start;
	short			x_cur;
	short			y_cur;
	short			ws_col;
	short			ws_row;
	short			highlight_pos;
	short			pos;
	struct s_cord	*nl;
}					t_cord;

typedef struct		s_buff
{
	char			*buffer;
	short			malloc_len;
}					t_buff;

typedef struct		s_line
{
	t_buff			buffer;
	t_buff			history_search;
	t_buff			save_buff;
	t_buff			copy_buff;
	t_buff			her_buff;
	t_cord			*cord;
	struct s_temp	*templates;
}					t_line;

typedef struct		s_temp
{
	char			*template;
	char			(*handler)(t_line *line);
	struct s_temp	*next;
}					t_temp;
/*
**	init_line.c
*/
void	init_line(t_line *line);
void	init_buff(t_buff *buffer);
t_cord	*init_cord(void);
t_temp	*init_templates(void);
/*
**	free_line.c
*/
void	free_line(t_line *line);
void	free_cord(t_cord **cord);
void	free_buffer(t_buff *buffer);
void	free_templates(t_temp **head);
/*
**	templates.c
*/
t_temp	*set_templates(void);
t_temp	*set_esc_templates(void);
t_temp	*set_other_templates(char *str);
/*
**	global_cord.c
*/
void	get_cur_cord(t_cord *cord);
void	get_win_size(t_cord *cord);
void	unset_cord(t_cord *cord);
/*
**	data.c
*/
void	set_data(t_line *line);
void	unset_data(t_line *line);
/*
**	heredoc.c
*/
void	write_hered(char **buf);
char	check_heredoc(t_buff buffer, t_buff *her_buff, t_cord *cord);
short	find_heredoc(char *buffer);
void	print_heredoc(char *buffer, t_cord *cord);
void	check_heredoc_end(char *buffer, char *stop_buff, t_cord *cord);
/*
**	buff_edit.c
*/
void	check_malloc_len_buffer(t_buff *buffer, char *c);
/*
**	new_line.c
*/
void	check_new_line(t_line *line, char *c);
/*
**	quotes.c
*/
void	check_quotes(t_line *line);
char	quotes_dquotes_brackets(short q, short dq, short br, t_line *line);
void	print_quotes(short q, short dq, short br, t_line *line);
unsigned short	g_line_flags;
struct s_line	g_line;
#endif
