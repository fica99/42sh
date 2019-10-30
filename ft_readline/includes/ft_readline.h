/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/10/30 18:51:16 by aashara-         ###   ########.fr       */
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
# include "libft.h"
# include "libhash.h"
# include "libstr.h"
# include "rl_errors.h"
# include "rl_colours.h"
# include "rl_terminfo.h"

# define MAX_LINE_SIZE 1000
# define VI_HASH_SIZE 4
# define RL_HASH_SIZE 4
# define DONT_FREE_HASH_DATA 0
# define FT_HOST_NAME_MAX 255
# define READING 1
# define LINE_MAX 2048
# define RL_INIT_FLAGS 0
# define RL_BREAK_FLAG (1 << 1)

typedef enum		e_rl_mode
{
					VI = 1,
					READLINE = 2
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

typedef struct		s_rl_buff
{
	char			*buffer;
	short			malloc_len;
}					t_rl_buff;

typedef struct		s_readline
{
	t_hash			**vi_hash;
	t_hash			**rl_hash;
	t_rl_cord		cord;
	t_rl_buff		line;
	t_rl_buff		save_line;
	t_rl_buff		copy_buff;
	struct termios	canon_mode;
	struct termios	non_canon_mode;
	char			prompt[MAX_LINE_SIZE];
	char			**env;
	t_rl_mode		mode;
}					t_readline;

/*
**	rl_main.c
*/
/*
**	Before usage of this function you need to make initialization(init_readline()).
**	After usage of this function you need to free memory(free_readline()).
**	Enum (t_rl_mode) is responsible for the editing mode(VI == 1, READLINE == 2).
**	Environ is an array of environment variables.
** 	History is an array of commands history.
*/
char				*ft_readline(char *prompt, t_rl_mode mode,
char **environ, char **history);
void				init_readline(void);
void				free_readline(void);
void				rl_err(char *name, char *str, char *err);
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
void				rl_init_buff(t_rl_buff *buffer);
void				rl_init_cord(t_rl_cord *cord);
/*
**	rl_free.c
*/
void				rl_free_rl_struct(t_readline *rl);
void				rl_free_buff(t_rl_buff *buffer);
void				rl_clr_data(t_readline *rl);
/*
**	rl_prompt.c
*/
void				rl_standart_prompt(char *prompt, char **env);
/*
**	rl_env.c
*/
char				*ft_getenv(char *arr, char **env);
short				get_count_env(char *arr, char **env);
/*
**	rl_init_hash.c
*/
t_hash				**init_vi_hash(void);
t_hash				**init_rl_hash(void);
t_hash				**init_standart_templates(int hash_size);
/*
**	rl_reading.c
*/
char				*rl_reading(t_readline *rl);
void				read_handler(char *c, int fd);
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
/*
**	rl_check.c
*/
char				rl_is_start_pos(t_rl_cord *cord);
char				rl_is_end_pos(t_rl_cord *cord);
void				rl_malloc_len(t_rl_buff *buffer, char *c);
void				rl_is_end_window(t_rl_cord *cord);
/*
**	rl_cur_movements.c
*/
void				rl_go_to_cord(short x, short y);
void				rl_go_left(short i, t_rl_cord *cord);
void				rl_go_right(short i, t_rl_cord *cord);
/*
**	rl_k_cur_movements.c
*/
void				rl_k_left(t_readline *line);
void				rl_k_right(t_readline *rl);
void				rl_k_home(t_readline *rl);
void				rl_k_end(t_readline *rl);
t_readline			g_rl;
unsigned char		g_rl_flags;
#endif
