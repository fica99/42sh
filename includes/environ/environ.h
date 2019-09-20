/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:01:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/20 21:51:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# define DEFAULT_ENV_SIZE 500

typedef struct	s_environ
{
	short	cur_size;
	short	malloc_size;
	char	**env;
}				t_environ;

t_environ	*init_env_struct(char **arr, short malloc_size);
void		free_env_struct(t_environ **env);
#endif
