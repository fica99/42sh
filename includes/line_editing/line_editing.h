/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/09/26 23:35:25 by aashara-         ###   ########.fr       */
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
# define CUR_LFT tigetstr("cub1")
# define CUR_RIGHT tigetstr("cuf1")
# define ENTER_INSERT_MODE tigetstr("smir")
# define EXIT_INSERT_MODE tigetstr("rmir")
# define ENTER_AM_MODE tigetstr("smam")


# define HEREDOC_FLAG (1 << 1)
# define HISTORY_SEARCH (1 << 2)
# define TERM_HIGHLIGHT (1 << 3)
# define START_POS (1 << 4)
# define TERM_QUOTES (1 << 5)
# define TERM_NL (1 << 6)

# define NORMAL_LINE 1000
# define TEMPL_TABLE_SIZE 2

typedef struct		s_cord
{
	short			x_start;
	short			y_start;
	short			x_end;
	short			y_end;
	short			x_cur;
	short			y_cur;
	short			ws_col;
	short			ws_row;
	short			highlight_pos;
	short			pos;
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
	t_hash			**templates;
	int				her_fd;
}					t_line;

/*
**	init_line.c
*/
void	init_line(t_line *line);
void	init_buff(t_buff *buffer);
t_cord	*init_cord(void);
t_hash	**init_templates(void);
/*
**	free_line.c
*/
void	free_line(t_line *line);
void	free_buffer(t_buff *buffer);
/*
**	templates.c
*/
t_hash	**set_templ_table(void);
t_hash	**set_templ_table_symb(t_hash **table);
void	find_templ(char *c, t_line *line);
/*
**	data.c
*/
void	set_data(t_line *line);
void	unset_data(t_line *line);
/*
**	cord.c
*/
void	get_cur_cord(t_cord *cord);
void	unset_cord(t_cord *cord);
void	get_win_size(t_cord *cord);
void	set_start_cord(t_cord *cord);
void	set_end_cord(t_cord *cord);
/*
**	check.c
*/
char	is_start_pos(t_cord *cord);
char	is_end_pos(t_cord *cord);
void	check_malloc_len_buffer(t_buff *buffer, char *c);
/*
**	keys.c
*/
void	k_left(t_line *line);
void	k_right(t_line *line);
/*
**	print_symb.c
*/
void	print_symb(char *c, t_line *line);

unsigned short	g_line_flags;
struct s_line	g_line;
#endif
