/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:26:24 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/15 15:09:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char	*ft_stradd(char *buf, char *s, size_t i)
{
	char	*str;

	if (!s || !buf)
		return (buf);
	if (i >= ft_strlen(buf))
		return (ft_strcat(buf, s));
	if (!(str = ft_strdup(buf + i)))
		return (NULL);
	ft_strcpy(buf + i, s);
	buf = ft_strcat(buf, str);
	ft_strdel(&str);
	return (buf);
}
