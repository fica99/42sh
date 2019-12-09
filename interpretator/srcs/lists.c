/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 07:51:16 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/28 07:51:17 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

t_job *job_new(void)
{
	t_job *new;
	t_job *tmp;

	if (!(new = (t_job *)ft_memalloc(sizeof(t_job))))
		err_exit("42sh", "malloc() error", NULL, NOERROR);
	new->pgid = getpgrp();
	new->tmodes = &g_shell_tmodes;
	if (!g_first_job)
		g_first_job = new;
	else
	{
		tmp = g_first_job;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}
