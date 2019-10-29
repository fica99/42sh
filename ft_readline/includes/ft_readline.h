/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/10/29 23:42:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <termios.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "libhash.h"
# include "rl_errors.h"
# include "rl_colours.h"

# define MAX_LINE_SIZE 1000
# define VI_HASH_SIZE 5
# define RL_HASH_SIZE 5
# define DONT_FREE_HASH_DATA 0
# define FT_HOST_NAME_MAX 255

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
}					t_readline;

/*
**	rl_main.c
*/
/*
**	Before usage of this function you need to make initialization(init_readline()).
**	After usage of this function you need to free memory(free_readline()).
**	Enum (t_rl_mode) is responsible for the editing mode(VI == 1, READLINE == 2).
*/
char				*ft_readline(char *prompt, t_rl_mode mode);
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
/*
**	rl_prompt.c
*/
void				rl_standart_prompt(char *prompt);
char				*rl_get_path(void);
t_readline			g_rl;
unsigned char		g_rl_flags;
#endif
