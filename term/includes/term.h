/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:03:47 by filip             #+#    #+#             */
/*   Updated: 2020/01/08 19:46:59 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# define RUNNING 1
# define INIT_FLAGS 0
# define LINE_MAX 2048
# define FREE_TABLE_DATA 1
# define DONT_FREE_TABLE_DATA 0
# define RULES_NUM 14

/*
**	ft_term.c
*/
void				term_start(void);
void				check_valid_string(char *buffer);
/*
**	global_var.c
*/
void				init_global_var(char **environ);
void				free_globar_var(void);

#endif
