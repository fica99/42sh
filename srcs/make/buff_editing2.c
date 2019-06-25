/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_editing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 21:35:22 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/25 17:20:22 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		check_print_arr(char *arr)
{
	short	i;

	i = -1;
	while (arr[++i])
	{
		if (ft_isprint(arr[i]) && arr[i] != ' ')
			return (1);
	}
	return (0);
}
