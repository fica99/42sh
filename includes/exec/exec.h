/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 23:14:23 by filip             #+#    #+#             */
/*   Updated: 2019/06/27 23:45:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

void	find_command(char **args, t_hash **hash_table, short hash_table_size,
t_history *history);
char	*check_command(char **args);
char	*exec_command(char **args, t_hash **hash_table, short hash_table_size);
#endif
