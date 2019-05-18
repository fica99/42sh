/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:37:26 by filip             #+#    #+#             */
/*   Updated: 2019/05/18 17:15:51 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

pid_t	make_process(void)
{
	pid_t	p;

	p = fork();
	if (p < 0)
		print_error("minishell", "fork() error", NULL, 0);
	return (p);
}
