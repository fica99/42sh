/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:21:50 by mmarti            #+#    #+#             */
/*   Updated: 2019/12/21 13:21:51 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	cls_redir(int **red)
{
	int *tmp;

	while (*red)
	{
		tmp = *red;
		if (*tmp > 2)
			close(*tmp);
		if (*++tmp > 2)
			close(*tmp);
		red++;
	}
}
