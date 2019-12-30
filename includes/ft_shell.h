/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:12:11 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 16:12:13 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H
# include <unistd.h>
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
# include "../lex/includes/lex.h"
# include "../jobs/includes/jobs.h"
# include "../term/includes/term.h"
# include "../environ/includes/environ.h"
# include "../hash_table/includes/hash_table.h"
# include "../error/includes/error.h"
# include "../ft_readline/includes/ft_readline.h"
# include "../interpretator/includes/interpretator.h"
# include "../builtins/includes/builtins.h"
# include "../signal/includes/signals.h"
#endif
