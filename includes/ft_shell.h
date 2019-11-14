/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 17:28:23 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/21 15:45:51 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include <termios.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <time.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include "libft.h"
# include "libstr.h"
# include "libdir.h"
# include "libdar.h"
# include "libfifo.h"
# include "libstack.h"
# include "libhash.h"
# include "../jobs/includes/jobs.h"
# include "../signal/includes/signals.h"
# include "../term/includes/term.h"
# include "../environ/includes/environ.h"
# include "../bin_table/includes/bin_table.h"
# include "../history/includes/history.h"
# include "../prompt/includes/prompt.h"
# include "../error/includes/error.h"
# include "colour.h"
# include "../read_line/includes/read_line.h"
# include "../lexer/includes/lexer.h"
# include "../parser/includes/parser.h"
# include "../interpretator/includes/interpretator.h"
# include "../builtins/includes/builtins.h"
#endif
