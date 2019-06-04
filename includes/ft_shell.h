/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/04 21:54:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include <termios.h>

typedef struct		s_cord
{
	short			x_start;
	short			y_start;
	short			x_cur;
	short			y_cur;
	short			ws_col;
	short			ws_row;
}					t_cord;

typedef struct		s_hash
{
	char			*path;
	unsigned short	index;
	char			*name;
	struct s_hash	*next;
}					t_hash;

typedef struct	s_history
{
	char		**history_buff;
	short		history_index;
	char		*history_path;
}				t_history;

typedef struct		s_term
{
	char			*buffer;
	char			**env_cp;
	struct termios	savetty;
	short			malloc_len;
	unsigned short	hash_table_size;
	t_cord			*cord;
	t_hash			**hash_table;
	t_history		*history;
}					t_term;


# include "libft.h"
# include "make/make.h"
# include "error/error.h"
# include "hash_table/hash_table.h"
# include "history/history.h"
# include "term/term.h"
# include "line_editing/line_editing.h"
# include "macro/colour.h"
# include "macro/command.h"
# include "builtins/cd.h"
# include "builtins/env.h"
# include "builtins/echo.h"
# include "builtins/setenv.h"
# include "builtins/unsetenv.h"
# include "exec/exec.h"
# include "reading/reading.h"
# include "parser/parser.h"
# include "signal/signal.h"

# define RUNNING 1
# define TERM_SIGINT (1 << 1)
# define TERM_EXIT (1 << 2)
# define NORMAL_LINE 100
# define FT_HOST_NAME_MAX 255
# define LINE_MAX 2048
# define SOMETHING "1"
# define READING 1
# define INIT_FLAGS 0

struct s_term	g_term;
unsigned short	g_flags;
int				g_errno_f;
#endif
