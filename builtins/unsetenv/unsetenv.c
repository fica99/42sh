/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:55:51 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/22 20:12:58 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t ft_unsetenv(int argc, char **argv, char **environ)
{
    short  i;

    if (argc == 2)
    {
        if ((i = get_count_var(argv[1], environ)) >= 0)
        {
            while (environ[i + 1])
            {
                environ[i] = environ[i + 1];
                i++;
            }
            environ[i] = NULL;
			i = -1;
			while (environ[++i])
			{
				ft_putstr(environ[i]);
				ft_putchar('\n');
			}
        }
    }
    return (0);
}