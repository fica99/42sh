/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/05/25 11:28:33 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING
# define LINE_EDITING

void			print_read(char *c);
void			print_read_other(char *c);
void			go_left(short i);
void			go_right(short i);
void			prev_word(char *buf, short len);
void			next_word(char *buf);
void			del_symb(char *buf, short len);
void			print_symb(char *c, char *buf, short len);

#endif