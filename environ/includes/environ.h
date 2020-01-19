/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:01:08 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/19 13:32:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "libdar.h"
# include "libft.h"
# include "../../error/includes/error.h"

# define DEFAULT_ENV_MALLOC_SIZE 500

typedef struct	s_environ
{
	short		cur_size;
	short		malloc_size;
	char		**env;
}				t_environ;

typedef enum		e_env
{
	ENV = 1,
	SET_ENV = 2,
	ALL_ENV = 3
}					t_env;
/*
**	init_environ.c
*/
void			init_global_env(t_environ *env, char **arr);
void			unset_env_struct(t_environ *env);
char			*get_env(char *arr, t_env mode);
void			set_env(char *name, char *new_value, t_env mode);
/*
**	get_env.c
*/
void			ft_setenv(char *name, char *new_value, t_environ *env);
void			ft_unsetenv(char *arr, t_environ *env);
void			unset_env(char *name, t_env mode);
/*
**	get_env_dar.c
*/
char			**get_env_names_dar(char *name, t_env mode);
t_environ		g_set_env;
t_environ		g_env;
#endif
