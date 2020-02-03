/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel_el.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 18:24:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/15 23:39:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

char		*ft_strdel_el(char *buf, int i)
{
	if (i < 0)
		return (buf);
	if (i >= (int)ft_strlen(buf))
		return (buf);
	ft_strcpy(buf + i, buf + i + 1);
	return (buf);
}
