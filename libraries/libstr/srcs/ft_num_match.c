/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_match.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 00:21:38 by ggrimes           #+#    #+#             */
/*   Updated: 2019/09/15 21:19:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"

size_t	ft_num_match(char **str, char *arg)
{
	int		i;
	size_t	count;

	i = -1;
	count = 0;
	if (!str || !arg)
		return (count);
	while (str[++i])
		if (ft_match(str[i], arg))
			count++;
	return (count);
}
