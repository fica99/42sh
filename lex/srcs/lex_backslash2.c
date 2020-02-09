/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_backslash2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 14:47:02 by ggrimes           #+#    #+#             */
/*   Updated: 2020/02/09 15:17:39 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

char	*lex_del_backslash(char *str, size_t pos)
{
	char *new_str;

	if (!str)
		return (NULL);
	str[pos] = '\0';
	if (!(new_str = ft_strjoin(str, str + pos + 1)))
		return (NULL);
	free(str);
	return (new_str);
}
