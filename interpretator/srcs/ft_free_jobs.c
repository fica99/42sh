/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:32:40 by mmarti            #+#    #+#             */
/*   Updated: 2020/01/26 17:57:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

void	ft_free_redir(int **red)
{
	int i;

	if (!red)
		return ;
	i = -1;
	while (red[++i])
		free(red[i]);
	free(red);
}

void	ft_free_r(t_redir_list *r)
{
	if (!r)
		return ;
	ft_free_r(r->next);
	free(r);
}

void	ft_free_proc(t_process *p)
{
	if (!p)
		return ;
	ft_free_proc(p->next);
	ft_free_r(p->r);
	cls_redir(p->fd_list);
	if (p->args)
		ft_free_dar(p->args);
	if (p->environment)
		ft_free_dar(p->environment);
	ft_free_redir(p->fd_list);
	free(p);
}

void	ft_free_jobs(t_job *j)
{
	if (!j)
		return ;
	ft_free_jobs(j->next);
	ft_free_proc(j->first_process);
	if (j->command)
		ft_free_dar(j->command);
	free(j);
}
