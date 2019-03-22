/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:53:37 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/22 20:08:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t ft_unsetenv(int argc, char **argv, char **environ);

int main(int argc, char **argv, char **environ)
{
    ft_unsetenv(argc, argv, environ);
    return (0);
}