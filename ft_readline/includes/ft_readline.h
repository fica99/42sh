/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara- <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/12/21 18:18:30 by aashara-         ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>
# include <time.h>
# include "libft.h"
# include "libhash.h"
# include "libstr.h"
# include "libdar.h"
# include "libdir.h"
# include "rl_errors.h"
# include "rl_colours.h"
# include "rl_templates.h"
# include "../../term/includes/term.h"
# include "../../environ/includes/environ.h"


# define MAX_LINE_SIZE 10000
# define DONT_FREE_HASH_DATA 0
# define FT_HOST_NAME_MAX 255
# define READING 1
# define RL_PATH_MAX 2048
# define RL_MAX_BUFF 1000
# define RL_INIT_FLAGS 0
# define RL_BREAK_FLAG (1 << 1)
# define RL_HIGHLIGHT_FLAG (1 << 2)
# define RL_HISTORY_SEARCH_FLAG (1 << 3)
# define RL_VI_COMMAND_MODE (1 << 4)
# define RL_VI_INPUT_MODE (1 << 5)
# define RL_HISTSIZE "500"
# define RL_HISTFILESIZE "500"
# define RL_HISTORY_FILE "/.42sh_history"
# define RL_PERM_HISTFILE S_IRUSR | S_IWUSR
# define RL_OPEN_HISTFILE O_RDWR | O_CREAT
# define RL_REWRITE_HISTFILE O_RDWR | O_APPEND | O_CREAT
# define RL_VIFILE ".42sh_vimode"
# define RL_OPEN_VIFILE O_RDWR | O_CREAT | O_TRUNC
# define RL_PERM_VIFILE S_IRUSR | S_IWUSR
# define RL_READ_VIFILE O_RDONLY
# define RL_PROMPT_TIME_BRACKETS 2
# define RL_MIN(a, b) ((a > b) ? b : a)
# define RL_MAX(a, b) ((a > b) ? a : b)
# define SUCCESS 1
# define FUILURE 0
# define CHECK(val) if (!val) return (0)
# define CHECKV(val) if (!val) return

typedef struct	s_autocom
{
	int			max_len;
	int			opts_size;
	int			cols;
	int			rows;
	int			index;
	int			index_print;
	char		*start;
	char		*path;
	int			prog;
	int			first;
	int			scrolling;
	int			delta_y;
	int			opts_print;
	int			fixed_opts_print;
	char		**options;
}				t_autocom;
typedef struct		s_buff
{
	char			*buffer;
	short			malloc_len;
	short			max_len;
}					t_buff;

typedef struct		s_rl_history
{
	char			**history_buff;
	t_buff			save_line;
	t_buff			search;
	size_t			hist_len;
	size_t			hist_index;
	size_t			histsize;
	size_t			histfilesize;
	size_t			cur_command_nb;
}					t_rl_history;

typedef enum		e_rl_mode
{
	VI = 1,
	EMACS = 2,
	NOEDIT = 3
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

typedef struct		s_readline
{
	t_hash			**vi_hash;
	t_hash			**rl_hash;
	t_hash			**noedit_hash;
	t_rl_cord		cord;
	t_buff			line;
	t_buff			copy_buff;
	t_buff			save_line;
	short			save_index;
	struct termios	canon_mode;
	struct termios	non_canon_mode;
	char			*prompt;
	t_rl_history	history;
	t_rl_mode		mode;
}					t_readline;

/*
**	rl_main.c
*/
char				*ft_readline(char *prompt, t_rl_mode mode);
void				init_readline(void);
void				free_readline(void);
void				add_to_history_buff(char *line);
char				*get_hist_expansions(char *line);
/*
**	rl_read_mode.c
*/
void				rl_save_attr(struct termios *savetty);
void				rl_set_non_canon_mode(struct termios *tty);
void				rl_set_attr(struct termios *savetty);
/*
**	rl_init.c
*/
void				rl_init_terminfo(void);
void				rl_init_rl_struct(t_readline *rl);
void				rl_init_cord(t_rl_cord *cord);
void				rl_init_buff(t_buff *buffer);
/*
**	rl_free.c
*/
void				rl_free_rl_struct(t_readline *rl);
void				rl_clr_data(t_readline *rl);
void				rl_clr_buff(t_buff *buff);
/*
**	rl_prompt.c
*/
void				rl_write_prompt(char *str, t_rl_history history);
short				rl_prompt_user_host(char *str, short i);
short				rl_prompt_dir_history(char *str, short i,
t_rl_history history);
short				rl_prompt_colour_name(char *str, short i);
/*
**	rl_init_hash.c
*/
t_hash				**init_vi_hash(int hash_size);
t_hash				**init_standart_templates(int hash_size);
t_hash				**init_emacs_hash(int hash_size);
t_hash				**init_noedit_hash(int hash_size);
/*
**	rl_reading.c
*/
char				*rl_reading(t_readline *rl);
void				rl_read_handler(char *c, int fd);
void				rl_find_template(t_readline *rl, char *c);
/*
**	rl_cord.c
*/
void				rl_get_cur_cord(t_rl_cord *cord);
void				rl_get_win_size(t_rl_cord *cord);
void				rl_set_start_cord(t_rl_cord *cord);
void				rl_set_end_cord(t_rl_cord *cord);
void				rl_start_cord_data(t_rl_cord *cord);
/*
**	rl_print.c
*/
void				rl_print(char *str, t_rl_cord *cord);
void				rl_del_symb(char *buf, t_rl_cord *cord);
void				rl_print_highlight(char *str, short start,
short end, t_rl_cord *cord);
void				rl_disable_line(t_readline *rl);
void				rl_print_hist_search(t_readline *rl);
/*
**	rl_check.c
*/
char				rl_is_start_pos(t_rl_cord cord);
char				rl_is_end_pos(t_rl_cord cord);
char				rl_check_empty_line(char *line);
void				rl_check_str_mem(t_buff *buffer, char *c);
/*
**	rl_cur_movements.c
*/
void				rl_go_to_cord(short x, short y);
void				rl_go_left(short i, t_rl_cord *cord);
void				rl_go_right(short i, t_rl_cord *cord);
/*
**	rl_k_cur_left.c
*/
void				rl_k_left(t_readline *line);
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
**	rl_k_other.c
*/
void				rl_k_enter(t_readline *rl);
void				rl_k_ctrl_d(t_readline *rl);
void				rl_print_symb(char *c, t_readline *rl);
void				rl_k_del(t_readline *rl);
void				rl_k_bcsp(t_readline *rl);
/*
**	rl_history.c
*/
void				rl_free_history(t_rl_history *history);
void				rl_get_hist_size(t_rl_history *history);
void				rl_check_history_size(t_rl_history *history);
/*
**	rl_k_history.c
*/
void				rl_k_up(t_readline *rl);
void				rl_k_down(t_readline *rl);
void				rl_k_alt_right(t_readline *rl);
void				rl_k_alt_left(t_readline *rl);
/*
**	rl_signal.c
*/
void				rl_win_handler(int sign);
/*
**	rl_prompt_time.c
*/
short				rl_prompt_time(char *str, short i);
short				rl_check_time_flags(char *str, short i, struct tm *info);
short				rl_time_format_flag(char *str, short i, struct tm *info);
/*
**	rl_k_history_search.c
*/
void				rl_k_ctrl_r(t_readline *rl);
void				rl_k_ctrl_j(t_readline *rl);
void				rl_k_esc(t_readline *rl);
void				rl_k_ctrl_g(t_readline *rl);
void				rl_find_history(t_readline *rl, short i);
/*
**	rl_k_emacs.c
*/
void				rl_k_ctrl_l(t_readline *rl);
void				rl_k_alt_d(t_readline *rl);
void				rl_k_ctrl_w(t_readline *rl);
void				rl_k_alt_r(t_readline *rl);
void				rl_k_alt_t(t_readline *rl);
/*
**	rl_str.c
*/
short				rl_prev_word(char *buff, short pos);
short				rl_next_word(char *buff, short pos);
short				rl_count_spaces(char *buff);
char				rl_isupperchar(char c);
char				rl_islowerchar(char c);
/*
**	rl_k_cut_copy_paste.c
*/
void				rl_k_ctrl_c(t_readline *rl);
void				rl_k_ctrl_x(t_readline *rl);
void				rl_k_ctrl_v(t_readline *rl);
void				rl_k_ctrl_k(t_readline *rl);
void				rl_k_ctrl_u(t_readline *rl);
/*
**	rl_k_emacs2.c
*/
void				rl_k_ctrl_t(t_readline *rl);
void				rl_k_alt_u(t_readline *rl);
void				rl_k_alt_l(t_readline *rl);
void				rl_k_alt_c(t_readline *rl);
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
**	rl_init_hash2.c
*/
t_hash				**init_standart_templates_other(t_hash **table,
int hash_size);
t_hash				**init_emacs_hash_other(t_hash **table, int hash_size);
t_hash				**init_vi_hash_other(t_hash **table, int hash_size);
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
**	rl_init_history.c
*/
void				rl_init_history(t_rl_history *history);
size_t				rl_find_hist_len(char *path);
void				rl_set_hist_buff(char *path, t_rl_history *history,
size_t hist_len);
/*
**	rl_hist_expansions.c
*/
char				*rl_search_exp(char *line, t_rl_history history);
char				*rl_digit_exp(int i, t_rl_history history);
char				*rl_hist_copy(short index, char **hist_buff);
/*
**	rl_err.c
*/
void				rl_err(char *name, char *str, char *err);
/*
**	rl_main2.c
*/
int					get_hist_size(void);

/*
**	ac_autocom.c
*/
void				autocomplite(t_buff *buff, t_rl_cord *cord);
void				ac_complement_line(t_buff *buffer, t_rl_cord *cord, t_autocom *ac);
int					ac_rewrite_str(char *dest, char *src);
/*
**	ac_move_cursor.c
*/
void				move_cursor_pos(short x, short y);
void				move_cursor_down(short count);
void				move_cursor_left(short count);
void				move_cursor_right(short count);
void				move_cursor_up(short count);
/*
**	ac_options.c
*/
char				**ac_get_options(char *start, short is_prog, t_autocom *ac);
char				**ac_newselection(char **options, char *search_arg);
char				**ac_options_selection(char *arg, char **options);
char				**ac_dir_options(char *dirpath, t_autocom *ac);
char				**ac_prog_options(void);
/*
**	ac_options2.c
*/
char				**ac_add_options(char *path, char **options);
void				clear_opts_args(char *arg, char *search_arg,
char **options);
/*
**	ac_parse.c
*/
char				**ac_parse_cmd_line(char *line, t_autocom *ac);
char				*ac_parse_path(char *buffer);
char				*ac_parse_arg(char *dirpath);
char				*ac_tilda(char *dirpath);
/*
**	ac_print_paramas.c
*/
void				ac_conversion_scrolling(int opt_rows, t_rl_cord *cord,
t_autocom *ac);
void				ac_get_rows_cols_count(char **options, t_rl_cord *cord,
t_autocom *ac);
int					ac_get_max_word_len(char **list);
int					ac_get_rows(int count_options, int cols);
void				ac_set_null_params(t_autocom *ac);
/*
**	ac_print.c
*/
void				ac_print_options(t_autocom *ac, t_rl_cord *cord);
void				ac_print_coll(t_autocom *ac, int *index);
void				ac_select_option(char *option);
void				ac_clear_options(void);
void				ac_return_carriage(short count);
/*
**	ac_recalc_index.c
*/
void				ac_index_tracking(t_autocom *ac);
void				ac_opts_tracking(t_autocom *ac);

t_readline			g_rl;
unsigned char		g_rl_flags;
#endif
