/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:55:13 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/17 17:31:27 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_start(void)
{
	char		*arr;

	while (RUNNING)
	{
		signalling();
		if (g_flags & SHELL_SIGINT)
			g_flags &= ~SHELL_SIGINT;
		else
			shell_prompt();
		arr = read_prompt();
		parse_string(arr);
		ft_memdel((void**)&arr);
	}
}
