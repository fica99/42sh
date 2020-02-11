/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:49:09 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/09 13:33:42 by aashara-         ###   ########.fr       */
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

typedef struct		s_vars
{
	short		cur_size;
	short		malloc_size;
	char		**vars;
}					t_vars;

typedef enum		e_vars_type
{
	ENV = 1,
	VARS = 2,
	ALL_VARS = 3
}					t_vars_type;

typedef struct		s_cycle_list
{
	char				*name;
	struct s_cycle_list *next;
}					t_cycle_list;

/*
**					alias_add_to_cycle.c
*/
void				free_cycle_list(t_cycle_list *l);
void				add_to_cycle_list(char *alias, t_cycle_list **l);
/*
**					init_variables.c
*/
void				set_variables(t_vars *vars, char **data, short malloc_size);
void				init_cwd(void);
void				init_variables(char **data, t_vars_type type);
/*
**					get_variable.c
*/
char				**get_vars_names_dar(char *name, t_vars_type type);
char				*ft_getvar(char *name, char **varlist);
char				*get_var(char *arr, t_vars_type mode);
/*
**					set_variable.c
*/
short				get_index_var(char *arr, char **vars);
void				setvar(char *name, char *value, t_vars *vars);
void				set_var(char *name, char *value, t_vars_type type);
/*
**					unset_variable.c
*/
void				ft_unsetvar(char *arr, t_vars *vars);
void				unset_var(char *name, t_vars_type type);
t_vars				g_environ;
t_vars				g_vars;
char				*g_cur_wd;
t_vars				g_aliases;
#endif
