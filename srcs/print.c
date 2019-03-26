/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:53:08 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/26 11:02:41 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_message(void)
{
	ft_putstr(get_var("PWD", env_cp));
	ft_putchar(':');
}

void	print_environ(char **environ)
{
	short	i;

	i = -1;
	while (environ[++i])
	{
		ft_putstr(environ[i]);
		ft_putchar('\n');
	}
}