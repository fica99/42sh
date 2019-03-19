/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:54:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/19 20:07:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t	cd(int argc, char **argv, char **env)
{
	char	buf[MAXDIR];

	check_ch_dir(argc, argv, env);
	getcwd(buf, MAXDIR);
	env[get_count_var("PWD", env)] = ft_strjoin("PWD=", buf);
	ft_putstr(env[6]);
	return (0);
}
