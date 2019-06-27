/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 10:52:38 by filip             #+#    #+#             */
/*   Updated: 2019/06/27 23:43:35 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

void	parse_string(char *buf, t_hash **hash_table, short hash_table_size,
t_history *history);
void	make_command(char *buf, t_hash **hash_table, short hash_table_size,
t_history *history);
char	*spec_symbols(char *args);
#endif
