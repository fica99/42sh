/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrimes <ggrimes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:20:18 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/18 21:19:42 by ggrimes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdar.h"

void		ft_free_dar(char **arr)
{
	short	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		ft_memdel((void**)&(arr[i]));
	free(arr);
	arr = NULL;
}
