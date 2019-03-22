/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:28:11 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/15 14:29:20 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	cheak_grp(mode_t mode, char *str)
{
	if ((S_IRWXG & mode) != S_IRWXG)
	{
		if ((S_IRGRP & mode) != S_IRGRP)
			str[3] = '-';
		if ((S_IWGRP & mode) != S_IWGRP)
			str[4] = '-';
		if ((S_IXGRP & mode) != S_IXGRP)
			str[5] = '-';
	}
}

void	cheak_oth(mode_t mode, char *str)
{
	if ((S_IRWXO & mode) != S_IRWXO)
	{
		if ((S_IROTH & mode) != S_IROTH)
			str[6] = '-';
		if ((S_IWOTH & mode) != S_IWOTH)
			str[7] = '-';
		if ((S_IXOTH & mode) != S_IXOTH)
			str[8] = '-';
	}
}
