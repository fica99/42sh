/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:29:29 by filip             #+#    #+#             */
/*   Updated: 2019/04/28 00:12:06 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "term.h"

void			print_symb(char *c, char *buf, short len)
{
	short	i;

	buf = ft_stradd(buf, c, len);
	CLEAN_SCREEN(STDIN_FILENO);
	ft_putstr_cord(buf + len);
	i = ft_strlen(buf + len);
	go_left(i - 1);
}
