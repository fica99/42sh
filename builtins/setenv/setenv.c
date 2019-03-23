/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:13:34 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/23 15:50:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t ft_setenv(int argc, char **argv, char **environ)
{
    //exec env
    environ = NULL;
    argc = 0;
    argv = NULL;
    return (0);
}

int     main(int argc, char **argv, char **environ)
{
    ft_setenv(argc, argv, environ);
    return (0);
}