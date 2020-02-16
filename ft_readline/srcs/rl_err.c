/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara <aashara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 15:36:57 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/16 18:24:06 by aashara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_err(char *name, char *str, char *err)
{
	reset_shell_mode();
	rl_set_mode(&g_rl.start_mode);
	err_exit(name, str, NULL, err);
}
