/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_one_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 23:47:29 by jijerde           #+#    #+#             */
/*   Updated: 2020/01/26 14:59:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		echo_one_escape(char **argv, int i, int j)
{
	if (argv[i][j] == '0')
		return (j = ft_octal(argv, i, j));
	else
		return (j = ft_hexout(argv, i, j));
}

void	echo_slashes(char **argv, int i, int j)
{
	if (argv[i][j - 3] != '\\')
		ft_putchar_fd('\\', STDOUT_FILENO);
	ft_putchar_fd(argv[i][j], STDOUT_FILENO);
}

void	echo_text(char **argv, int i, int j)
{
	if (argv[i][j] == '\\')
		;
	else
		ft_putchar_fd(argv[i][j], STDOUT_FILENO);
}
