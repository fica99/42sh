/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/06/02 15:09:36 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <stdlib.h>

typedef struct		s_cord
{
	short			x_start;
	short			y_start;
	short			x_cur;
	short			y_cur;
	short			ws_col;
	short			ws_row;
}					t_cord;

void			print_read(char *c, char *buffer, t_cord *cord);
void			print_read_other(char *c, char *buffer, short len, t_cord *cord);
void			go_left(short i, t_cord *cord)
void			go_right(short i, t_cord *cord);
void			prev_word(char *buf, short len, t_cord *cord);
void			next_word(char *buf, t_cord *cord);
void			del_symb(char *buf, short len);
void			print_symb(char *c, char *buf, short len, t_cord * cord);
//void            cut_copy_paste(char *c, short len);
#endif
