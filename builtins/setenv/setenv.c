/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:13:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/23 18:40:51 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t ft_setenv(int argc, char **argv, char **environ)
{
    int	j;
	int	i;
    
    if (argc == 1)
        print_environ(environ);
    else
    {
        j = 0;
        i = 0;
        while (environ[i])
            i++;
        while (argv[++j])
        {
            if (!(ft_strchr(argv[j], '=')))
                continue ;
            else
				environ[i++] = argv[j];
		}
    }
    return (0);
}

int     main(int argc, char **argv, char **environ)
{
    ft_setenv(argc, argv, environ);
    return (0);
}