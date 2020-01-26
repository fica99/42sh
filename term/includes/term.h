/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:03:47 by filip             #+#    #+#             */
/*   Updated: 2020/01/26 18:46:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include <unistd.h>
# include "environ.h"
# include "hash_table.h"
# include "error.h"
# include "jobs.h"
# include "ft_readline.h"
# include "lex.h"

# define RUNNING 1
# define INIT_FLAGS 0
# define FREE_TABLE_DATA 1
# define DONT_FREE_TABLE_DATA 0
# define RULES_NUM 15

/*
**	ft_term.c
*/
void				term_start(void);
void				ft_system(char **buffer);
/*
**	global_var.c
*/
void				init_global_var(char **environ);
void				free_globar_var(void);

#endif
