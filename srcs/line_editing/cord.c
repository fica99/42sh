/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cord.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 17:31:46 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/20 17:32:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		go_to_cord(short x, short y, int fd)
{
	char	*cursor;

	cursor = SET_CUR;
	ft_putstr_fd(tparm(cursor, y, x), fd);
}
