/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/10/23 20:12:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_H
# define READ_LINE_H

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
# define HIGHLIGHT(fd) ft_putstr_fd("\033[35;4m", fd)
# define NORMAL_LINE 1000
# define TEMPL_TABLE_SIZE 22
# define READING 1
# define HISTORY_SEARCH (1 << 1)
# define HIGHLIGHT_TEXT (1 << 2)
# define AUTOCOM (1 << 3)
# define BREAK_FLAG (1 << 4)
# define QUOTES (1 << 5)

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
	t_cord			*cord;
	t_hash			**templates;
	short			history_index;
	int				her_fd;
}					t_line;

/*
**	init_line.c
*/
void				init_line(t_line *line);
void				init_buff(t_buff *buffer);
t_cord				*init_cord(void);
t_hash				**init_templates(void);
void				clr_buffs(t_line *line);
/*
**	free_line.c
*/
void				free_line(t_line *line);
void				free_buffer(t_buff *buffer);
/*
**	templates.c
*/
t_hash				**set_templ_table(void);
t_hash				**set_templ_table_symb(t_hash **table);
void				find_templ(char *c, t_line *line);
/*
**	cord.c
*/
void				get_cur_cord(t_cord *cord);
void				unset_cord(t_cord *cord);
void				get_win_size(t_cord *cord);
void				set_start_cord(t_cord *cord);
void				set_end_cord(t_cord *cord);
/*
**	cord2.c
*/
void				set_start_params(void);
/*
**	check.c
*/
char				is_start_pos(t_cord *cord);
char				is_end_pos(t_cord *cord);
void				check_malloc_len_buffer(t_buff *buffer, char *c);
void				check_end_window(t_cord *cord);
void				check_quotes(char *c);
/*
**	k_cur_movements.c
*/
void				k_left(t_line *line);
void				k_right(t_line *line);
void				k_home(t_line *line);
void				k_end(t_line *line);
/*
**	k_cur_movements2.c
*/
void				k_ctrl_up(t_line *line);
void				k_ctrl_down(t_line *line);
void				k_ctrl_left(t_line *line);
void				k_ctrl_right(t_line *line);
/*
**	k_highlight.c
*/
void				k_ctrl_c(t_line *line);
void				k_shift_left(t_line *line);
void				k_shift_right(t_line *line);
void				k_ctrl_x(t_line *line);
void				k_ctrl_v(t_line *line);
/*
**	k_history.c
*/
void				k_up(t_line *line);
void				k_down(t_line *line);
void				k_ctrl_r(t_line *line);
/*
**	k_print.c
*/
void				k_ctrl_d(t_line *line);
void				k_enter(t_line *line);
void				k_bcsp(t_line *line);
void				k_del(t_line *line);
void				k_tab(t_line *line);
/*
**	print.c
*/
void				ft_putstr_cord(char *str, t_cord *cord);
void				ft_putstr_highlight(char *str, short start, short end,
t_cord *cord);
void				disable_highlight(char *buffer, t_cord *cord);
void				disable_history(t_line *line);
void				find_history(t_line *line);
/*
**	symb.c
*/
void				print_symb(char *c, t_line *line);
void				del_symb(char *buf, t_cord *cord);
/*
**	cur_movements.c
*/
void				go_to_cord(short x, short y, int fd);
void				go_left(short i, t_cord *cord);
void				go_right(short i, t_cord *cord);
/*
**	autocom.c
*/
char				*ac_get_word(char *is_command, char *line, short pos);
void				ac_print_params(char **arr, short win_width);
int					ac_max_len(char **arr);
/*
**	ac_bins.c
*/
void				ac_bins(char *command, t_line *line);
char				*ac_get_bin(char *command);
/*
**	ac_path.c
*/
void				ac_path(char *command, t_line *line);
void				ac_print_path(char **content, char *file, t_line *line);
char				*ac_get_path(char *file, char **content);
void				ac_word_split(char *word, char **file);
/*
**	read_mode.c
*/
void				set_attr(struct termios *savetty);
void				set_input_mode(struct termios *tty);
void				save_attr(struct termios *savetty);
void				init_terminfo(void);
/*
**	reading.c
*/
char				*ft_readline(char *prompt);
char				*reading(t_line *line);
void				read_handler(char *c, int fd);

unsigned char		g_line_flags;
struct s_line		g_line;
struct termios		g_orig_mode;
struct termios		g_raw_mode;
#endif
