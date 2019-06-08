/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/06/08 14:45:39 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <stdlib.h>

void	        print_read(char *c, t_buff *buffer, t_cord *cord, t_history *history);
void	        print_read_two(char *c, t_buff *buffer, t_cord *cord, t_history *history);
void	        print_read_three(char *c, char *buffer, short len, t_cord *cord);
void			go_left(short i, t_cord *cord);
void			go_right(short i, t_cord *cord);
void			prev_word(char *buf, short len, t_cord *cord);
void			next_word(char *buf, t_cord *cord);
void			del_symb(char *buf, short len);
void			print_symb(char *c, char *buf, short len, t_cord * cord);
void			go_to_cord(short x, short y);
//void            cut_copy_paste(char *c, short len);
#endif
