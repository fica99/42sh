/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:39:26 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/15 00:26:36 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

short	rl_prev_word(char *buff, short pos)
{
	while (--pos > 0)
		if (ft_isspace(buff[pos - 1]) && ft_isalnum(buff[pos]))
			return (pos);
	return (0);
}

short	rl_next_word(char *buff, short pos)
{
	--pos;
	while (buff[++pos])
		if (ft_isalnum(buff[pos]) && ft_isspace(buff[pos + 1]))
			return (pos + 1);
	return (pos);
}

void	rl_clr_buff(t_buff *buff)
{
	ft_strclr(buff->buffer);
	buff->max_len = 0;
}
