/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cnt_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:18:32 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/15 21:20:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

size_t	ft_get_cnt_words(const char *str, char *spr)
{
	size_t	i;
	size_t	count;
	short	in_word;

	count = 0;
	if (!str || !spr)
		return (count);
	i = -1;
	in_word = 0;
	while (str[++i])
	{
		if (!ft_is_str_contain(spr, str[i]) && !in_word)
		{
			in_word = !in_word;
			count++;
		}
		if (ft_is_str_contain(spr, str[i]) && in_word)
			in_word = !in_word;
	}
	return (count);
}
