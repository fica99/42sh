/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/15 19:30:03 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include <termios.h>
# include "libft.h"
# include "libstr.h"
# include "libdir.h"
# include "libdar.h"
# include "libfifo.h"
# include "libstack.h"
# include "hash_table/hash_table.h"
# include "history/history.h"
# include "term/term.h"
# include "prompt/prompt.h"
# include "make/make.h"
# include "error/error.h"
# include "macro/colour.h"
# include "line_editing/line_editing.h"
# include "signal/signal.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "interpretator/interpretator.h"
# include "reading/reading.h"
# include "autocom/autocom.h"
# include "builtins/cd.h"
# include "builtins/env.h"
# include "builtins/echo.h"
# include "builtins/setenv.h"
# include "builtins/unsetenv.h"
# include "builtins/hash.h"
# include "builtins/his.h"

# define RUNNING 1
# define NORMAL_LINE 1000
# define FT_HOST_NAME_MAX 255
# define LINE_MAX 2048
# define SOMETHING "1"
# define READING 1
# define INIT_FLAGS 0
# define TERM_SIGINT (1 << 1)
# define TERM_EXIT (1 << 2)
# define TERM_INIT_HASH (1 << 3)
# define TERM_FREE_HASH (1 << 4)

unsigned char	g_flags;
struct termios	g_orig_mode;
struct termios	g_raw_mode;
struct s_lexer  *g_lexer;
char			**g_env;
char			**g_argv;
#endif
