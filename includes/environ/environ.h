/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:01:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/21 20:00:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# define DEFAULT_ENV_MALLOC_SIZE 500

typedef struct	s_environ
{
	short	cur_size;
	short	malloc_size;
	char	**env;
}				t_environ;
/*
**	init_environ.c
*/
void		init_global_env(t_environ *env, char **arr);
void		set_env_struct(t_environ *env, char **arr, short malloc_size);
void		unset_env_struct(t_environ **env);
/*
**	get_env.c
*/
char		*ft_getenv(char *arr, char **env);
short		get_count_env(char *arr, char **env);
t_environ		g_env;
#endif
