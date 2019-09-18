/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 21:12:36 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/18 21:13:08 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	check_malloc_len_buffer(t_buff *buffer, char *c)
{
	while (ft_strlen(buffer->buffer) + ft_strlen(c) >=
			(unsigned)buffer->malloc_len)
	buffer->buffer = ft_strdup_realloc(buffer->buffer,
	buffer->malloc_len += NORMAL_LINE);
}
