/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:37:40 by lcrawn            #+#    #+#             */
/*   Updated: 2020/02/04 21:40:19 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpretator.h"

void		put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp(g_shell_terminal, j->pgid);
	if (cont)
	{
		tcsetattr(g_shell_terminal, TCSADRAIN, j->tmodes);
		kill(-j->pgid, SIGCONT);
	}
	wait_for_job(j);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
	tcgetattr(g_shell_terminal, j->tmodes);
	tcsetattr(g_shell_terminal, TCSADRAIN, &g_shell_tmodes);
}

void		put_job_in_background(t_job *j, int cont)
{
	if (cont)
		kill(-j->pgid, SIGCONT);
}
