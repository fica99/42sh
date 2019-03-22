/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:10:41 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/22 20:08:24 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t ft_setenv(int argc, char **argv, char **environ);

int     main(int argc, char **argv, char **environ)
{
    ft_setenv(argc, argv, environ);
    return (0);
}