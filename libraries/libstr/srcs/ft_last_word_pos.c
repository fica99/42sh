/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_word_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:17:54 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/15 21:20:17 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char	*ft_last_word_pos(const char *str, char *seps)
{
	size_t	len;
	short	in_word;

	if (!str || !seps)
		return (NULL);
	if (!(len = ft_strlen(str)))
		return (NULL);
	in_word = 0;
	while ((int)--len != -1)
	{
		if (ft_is_str_contain(seps, str[len]) && in_word)
			return ((char *)str + (len + 1));
		if (!ft_is_str_contain(seps, str[len]) && !in_word)
			in_word = !in_word;
	}
	return ((in_word) ? (char *)str : NULL);
}
