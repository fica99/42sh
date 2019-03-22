/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 14:51:21 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/22 15:56:01 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint8_t env(int argc, char **argv, char **environ);

int main(int argc, char **argv, char **environ)
{
    env(argc, argv, environ);
    return (0);
}