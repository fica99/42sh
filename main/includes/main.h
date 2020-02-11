/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:45:35 by aashara-          #+#    #+#             */
/*   Updated: 2020/02/11 15:43:23 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include "variables.h"
# include "hash_tables.h"
# include "ft_readline.h"
# include "lex.h"
# include "parser.h"
# include "interpretator.h"
# include "builtins.h"

/*
**			main.c
*/
void		ft_system(char **line);
#endif
