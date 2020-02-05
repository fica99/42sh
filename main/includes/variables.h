/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:49:09 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/05 15:58:07 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# include <unistd.h>
# include <limits.h>
# include "libft.h"
# include "libdar.h"
# include "error.h"
# define VAR_DEF_MALLOC_SIZE 500

typedef struct	s_vars
{
	short		cur_size;
	short		malloc_size;
	char		**vars;
}				t_vars;

typedef enum		e_vars_type
{
	ENV = 1,
	VARS = 2,
	ALL_VARS = 3
}					t_vars_type;

/*
**				init_variables.c
*/
void			init_cwd(void);
void			init_variables(char **data, t_vars_type type);
/*
**				get_variable.c
*/
char			**get_vars_names_dar(char *name, t_vars_type type);
char			*get_var(char *arr, t_vars_type mode);
/*
**				set_variable.c
*/
short			get_index_var(char *arr, char **vars);
void			set_var(char *name, char *value, t_vars_type type);
/*
**				unset_variable.c
*/
void			unset_var(char *name, t_vars_type type);
t_vars			g_environ;
t_vars			g_vars;
char			*g_cur_wd;
#endif
