/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_colour.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 14:34:35 by aashara-          #+#    #+#             */
/*   Updated: 2019/08/02 01:31:11 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_shell.h"

short	prompt_colour(char *str, short i)
{
	char	colour[20];
	short	j;

	j = 0;
	if (*(str + i) == '\\' && *(str + i + 1) == 'e')
	{
		colour[0] = '\033';
		j = 1;
		while (*(str + i + j + 1) != 'm')
		{
			colour[j] = *(str + i + j + 1);
			j++;
		}
		colour[j] = '\0';
		ft_putstr_fd(colour, STDIN_FILENO);
	}
	return (i + j);
}
