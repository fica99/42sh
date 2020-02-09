/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:19:28 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/09 14:58:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <termios.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <time.h>
# include "libft.h"
# include "libhash.h"
# include "libdar.h"
# include "libstr.h"
# include "libdir.h"
# include "rl_templates.h"
# include "variables.h"

# define LINE_SIZE 10000
# define DONT_FREE_HASH_DATA 0
# define RL_HISTORY_FILE "/.42sh_history"
# define RL_BUILTINS_LIST "builtins/builtins_list/builtins_list"
# define RL_HISTSIZE "500"
# define RL_HISTFILESIZE "500"
# define RL_INIT_FLAGS 0
# define FT_HOST_NAME_MAX 255
# define READING 1
# define RL_MAX_BUFF 1000
# define RL_PROMPT_TIME_BRACKETS 2
# define RL_BREAK_FLAG 2
# define RL_VI_COMMAND_MODE 16
# define RL_VI_INPUT_MODE 32
# define RL_HIGHLIGHT_FLAG 4
# define RL_HISTORY_SEARCH_FLAG 8
# define STANDART "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define HIGHLIGHT "\033[35;4m"
# define RL_BUILTINS_COUNT 17

typedef enum		e_rl_mode
{
	VI = 1,
	EMACS = 2,
}					t_rl_mode;
typedef struct		s_rl_cord
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
}					t_rl_cord;

typedef struct		s_buff
{
	char			*buffer;
	size_t			malloc_len;
	size_t			cur_len;
}					t_buff;

typedef struct		s_rl_history
{
	char			**history_buff;
	t_buff			save_line;
	t_buff			search;
	int				hist_len;
	int				hist_index;
	int				histsize;
	int				histfilesize;
	int				cur_command_nb;
}					t_rl_history;

typedef struct		s_readline
{
	struct termios	start_mode;
	struct termios	non_canon_mode;
	t_buff			line;
	t_buff			copy_buff;
	t_buff			save_line;
	size_t			save_index;
	t_rl_cord		cord;
	t_hash			**emacs_temp;
	t_hash			**vi_temp;
	char			*prompt;
	t_rl_history	history;
	t_rl_mode		mode;
}					t_readline;

typedef struct		s_rl_autocom_print
{
	short			rows;
	short			cols;
	short			max_word;
	short			arr_len;
	char			**arr;
}					t_rl_autocom_print;

typedef struct		s_rl_autocom_parse
{
	char			*to_find;
	char			**res;
	short			pos;
	uint8_t			is_env;
	uint8_t			is_path;
	uint8_t			is_bin;
}					t_rl_autocom_parse;
/*
**	init_readline.c
*/
void				init_readline(void);
/*
**	rl_term_mode.c
*/
void				rl_save_mode(struct termios *savetty);
void				rl_set_mode(struct termios *savetty);
void				rl_set_non_canon_mode(struct termios *tty);
/*
**	rl_err.c
*/
void				rl_err(char *name, char *str, char *err);
/*
**	rl_init_structs.c
*/
void				rl_init_buff(t_buff *buffer);
void				rl_init_cord(t_rl_cord *cord);
/*
**	rl_init_emacs_temp.c
*/
t_hash				**init_emacs_temp(int hash_size);
/*
**	rl_init_temp.c
*/
t_hash				**init_temp(int hash_size);
/*
**	rl_init_vi_temp.c
*/
t_hash				**init_vi_temp(int hash_size);
/*
**	rl_init_history.c
*/
void				rl_init_history(t_rl_history *history);
/*
**	free_readline.c
*/
void				rl_clr_data(t_readline *rl);
void				rl_clr_buff(t_buff *buff);
void				free_readline(void);
/*
**	rl_free_history.c
*/
void				rl_free_history(t_rl_history *history);
/*
**	add_to_history_buff.c
*/
void				rl_get_hist_size(t_rl_history *history);
void				rl_check_history_size(t_rl_history *history);
void				add_to_history_buff(char *line);
/*
**	history_exp.c
*/
char				*get_hist_expansions(char *line);
size_t				get_hist_size(void);
/*
**	ft_readline.c
*/
char				*ft_readline(char *prompt);
void				rl_read_handler(char *c, int fd);
/*
**	rl_prompt.c
*/
void				rl_write_prompt(char *str, t_rl_history history);
/*
**	rl_prompt_time.c
*/
short				rl_prompt_time(char *str, short i);
/*
**	rl_cord.c
*/
void				rl_start_cord_data(t_rl_cord *cord);
void				rl_set_end_cord(t_rl_cord *cord);
void				rl_set_start_cord(t_rl_cord *cord);
void				rl_get_win_size(t_rl_cord *cord);
void				rl_get_cur_cord(t_rl_cord *cord);
/*
**	rl_print.c
*/
void				rl_print(char *str, t_rl_cord *cord);
void				rl_disable_line(t_readline *rl);
void				rl_print_highlight(char *str, short start, short end,
															t_rl_cord *cord);
void				rl_del_symb(char *buf, t_rl_cord *cord);
void				rl_print_hist_search(t_readline *rl);
/*
**	rl_check.c
*/
char				rl_is_start_pos(t_rl_cord cord);
char				rl_is_end_pos(t_rl_cord cord);
void				rl_check_str_mem(t_buff *buffer, char *c);
/*
**	rl_cur_mov.c
*/
void				rl_go_to_cord(short x, short y);
void				rl_go_left(short i, t_rl_cord *cord);
void				rl_go_right(short i, t_rl_cord *cord);
/*
**	rl_str.c
*/
short				rl_prev_word(char *buff, short pos);
short				rl_next_word(char *buff, short pos);
short				rl_count_spaces(char *buff);
char				rl_isupperchar(char c);
char				rl_islowerchar(char c);
/*
**	rl_k_cur_left.c
*/
void				rl_k_left(t_readline *rl);
void				rl_k_home(t_readline *rl);
void				rl_k_ctrl_up(t_readline *rl);
void				rl_k_ctrl_left(t_readline *rl);
void				rl_k_shift_left(t_readline *rl);

/*
**	rl_k_cur_right.c
*/
void				rl_k_right(t_readline *rl);
void				rl_k_end(t_readline *rl);
void				rl_k_ctrl_down(t_readline *rl);
void				rl_k_ctrl_right(t_readline *rl);
void				rl_k_shift_right(t_readline *rl);

/*
**	rl_k_cut_copy_paste.c
*/
void				rl_k_ctrl_c(t_readline *rl);
void				rl_k_ctrl_x(t_readline *rl);
void				rl_k_ctrl_v(t_readline *rl);
void				rl_k_ctrl_k(t_readline *rl);
void				rl_k_ctrl_u(t_readline *rl);
/*
**	rl_k_emacs.c
*/
void				rl_k_ctrl_l(t_readline *rl);
void				rl_k_alt_d(t_readline *rl);
void				rl_k_ctrl_w(t_readline *rl);
void				rl_k_alt_r(t_readline *rl);
void				rl_k_alt_t(t_readline *rl);
/*
**	rl_k_emacs2.c
*/
void				rl_k_ctrl_t(t_readline *rl);
void				rl_k_alt_u(t_readline *rl);
void				rl_k_alt_l(t_readline *rl);
void				rl_k_alt_c(t_readline *rl);
/*
**	rl_k_history_search.c
*/
void				rl_k_ctrl_r(t_readline *rl);
void				rl_k_ctrl_j(t_readline *rl);
void				rl_k_esc(t_readline *rl);
void				rl_k_ctrl_g(t_readline *rl);
void				rl_find_history(t_readline *rl, short i);
/*
**	rl_k_history.c
*/
void				rl_k_up(t_readline *rl);
void				rl_k_down(t_readline *rl);
void				rl_k_alt_right(t_readline *rl);
void				rl_k_alt_left(t_readline *rl);
/*
**	rl_k_other.c
*/
void				rl_k_enter(t_readline *rl);
void				rl_k_ctrl_d(t_readline *rl);
void				rl_print_symb(char *c, t_readline *rl);
void				rl_k_del(t_readline *rl);
void				rl_k_bcsp(t_readline *rl);
/*
**	rl_k_vi.c
*/
void				rl_k_i_lower(t_readline *rl);
void				rl_k_i_upper(t_readline *rl);
void				rl_k_a_lower(t_readline *rl);
void				rl_k_a_upper(t_readline *rl);
void				rl_k_sharp(t_readline *rl);
/*
**	rl_k_vi2.c
*/
void				rl_k_e(t_readline *rl);
void				rl_k_carat(t_readline *rl);
void				rl_k_s_upper(t_readline *rl);
void				rl_k_s_lower(t_readline *rl);
void				rl_k_x_lower(t_readline *rl);
/*
**	rl_k_vi3.c
*/
void				rl_k_x_upper(t_readline *rl);
void				rl_k_v(t_readline *rl);
void				rl_k_f_lower(t_readline *rl);
void				rl_k_f_upper(t_readline *rl);
/*
**	rl_k_vi4.c
*/
void				rl_k_semicolon(t_readline *rl);
void				rl_k_comma(t_readline *rl);
void				rl_k_r_upper(t_readline *rl);
void				rl_k_r_lower(t_readline *rl);
void				rl_k_p_lower(t_readline *rl);
/*
**	rl_k_vi5.c
*/
void				rl_k_p_upper(t_readline *rl);
void				rl_k_y_upper(t_readline *rl);
void				rl_k_d_upper(t_readline *rl);
/*
**	rl_k_tab.c
*/
void				rl_k_tab(t_readline *rl);
/*
**	rl_autocom_print.c
*/
void				rl_autocom_print(t_rl_autocom_parse *parse, t_readline *rl);
/*
**	rl_autocom_parse.c
*/
void				rl_autocom_parse(t_rl_autocom_parse *autocom,
															t_readline *rl);
/*
**	rl_autocom_path.c
*/
char				**rl_autocom_path(char *word);
/*
**	rl_autocom_bin.c
*/
char				**rl_autocom_bin(char *word);
/*
**	check_hist_expansions.c
*/
char				check_hist_expansions(char **buffer);
t_readline			g_rl;
unsigned char		g_rl_flags;
#endif
