/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/17 15:23:06 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include "libft.h"
# include <termios.h>
# include "term/term.h"
# include "make/make.h"
# include "error/error.h"
# include "hash_table/hash_table.h"
# include "history/history.h"
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
# define HISTORY_SEARCH (1 << 3)
# define TERM_HIGHLIGHT (1 << 4)
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
