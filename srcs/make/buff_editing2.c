/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_editing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 21:35:22 by aashara-          #+#    #+#             */
/*   Updated: 2019/06/18 21:35:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char		*copy_from_buff(char *buffer, char *new_buffer, short start, short end)
{
	short	j;

	j = 0;
	while (start <= end)
		new_buffer[j++] = buffer[start++];
	return (new_buffer);
}
