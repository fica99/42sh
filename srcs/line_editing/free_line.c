/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:22:12 by aashara-          #+#    #+#             */
/*   Updated: 2019/09/23 21:12:38 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_line(t_line *line)
{
	free_buffer(&line->buffer);
	free_buffer(&line->history_search);
	free_buffer(&line->save_buff);
	free_buffer(&line->copy_buff);
	free_buffer(&line->her_buff);
	free_cord(&line->cord);
	free_templates(&line->templates);
}

void	free_cord(t_cord **cord)
{
	t_cord	*copy;
	t_cord	*nl;

	if (!*cord)
		return ;
	nl = *cord;
	while (nl)
	{
		copy = nl;
		nl = nl->nl;
		ft_memdel((void**)&copy);
	}
	*cord = NULL;
}

void	free_buffer(t_buff *buffer)
{
	if (buffer)
	{
		ft_memdel((void**)&buffer->buffer);
		buffer->malloc_len = 0;
	}
}

void	free_templates(t_temp **head)
{
	t_temp	*copy;
	t_temp	*temp;

	temp = *head;
	while (temp)
	{
		copy = temp;
		ft_memdel((void**)&copy->template);
		temp = temp->next;
		ft_memdel((void**)&copy);
	}
	*head = NULL;
}
