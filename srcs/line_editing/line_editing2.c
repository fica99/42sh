/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:29:29 by filip             #+#    #+#             */
/*   Updated: 2019/04/30 16:19:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void			print_symb(char *c, char *buf, short len)
{
	short	i;

	buf = ft_stradd(buf, c, len);
	CLEAN_SCREEN(STDIN_FILENO);
	ft_putstr_cord(buf + len);
	i = ft_strlen(buf + len);
	go_left(i - 1);
}
