/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:36:57 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/12 19:14:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_err(char *name, char *str, char *err)
{
	ft_error(name, str, NULL, err);
	reset_shell_mode();
	rl_set_mode(&g_rl.start_mode);
	exit(EXIT_FAILURE);
}
