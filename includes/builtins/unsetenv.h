/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 00:04:46 by filip             #+#    #+#             */
/*   Updated: 2019/04/28 00:40:59 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSETENV_H
# define UNSETENV_H

# include "libft.h"

void			ft_unsetenv(int argc, char **argv, char **env_cp);
char			**copy_new_arr(short i);
#endif