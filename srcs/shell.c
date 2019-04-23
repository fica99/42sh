/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/23 22:02:32 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	while (RUNNING)
	{
		signalling();
		term_prompt();
		read_prompt();
		if (!(g_flags & TERM_SIGINT))
				parse_string();
		else
			g_flags &= ~TERM_SIGINT;
		ft_memdel((void**)&(g_term.buffer));
	}
}
