/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:39:26 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/15 21:23:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

short	rl_prev_word(char *buff, short pos)
{
	++pos;
	while (--pos > 0)
		if (ft_isspace(buff[pos - 1]) && ft_isalnum(buff[pos]))
			return (pos);
	return (0);
}

short	rl_next_word(char *buff, short pos)
{
	--pos;
	while (buff[++pos])
		if (ft_isspace(buff[pos]) && ft_isalnum(buff[pos + 1]))
			return (pos + 1);
	return (pos);
}

short	rl_count_spaces(char *buff)
{
	short	i;

	i = 0;
	while (ft_isspace(buff[i]))
		++i;
	return (i);
}
