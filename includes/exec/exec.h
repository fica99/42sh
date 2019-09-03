/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 23:14:23 by filip             #+#    #+#             */
/*   Updated: 2019/08/30 20:33:09 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

void	make_command(char *buff, t_term *term);
char	*spec_symbols(char *args);
void	find_command(char **args, t_term *term);
char	*check_command(char **args);
char	*check_bin(char **args, t_hash **hash_table, short hash_table_size);
#endif
