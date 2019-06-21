/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/06/22 00:17:09 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <stdlib.h>

char			*print_move(char *c, t_buff *buffer, t_cord *cord);
char			*print_symbols(char *c, t_buff *buffer, t_cord *cord,
t_history *history);
char			*print_read(char *c, char *buffer, t_cord *cord);
void			go_left(short i, t_cord *cord);
void			go_right(short i, t_cord *cord);
void			prev_word(char *buf, t_cord *cord);
void			next_word(char *buf, t_cord *cord);
void			del_symb(char *buf, short len);
void			print_symb(char *c, char *buf, t_cord *cord);
void			go_to_cord(short x, short y, int fd);
void			ft_putstr_cord(char *str, t_cord *cord);
char	        *cut_copy_paste(char *c, t_buff *buffer, t_cord *cord);
void		    ft_putstr_highlight(char *str, short start, short end, t_cord *cord);
void			highlight_left(t_buff *buffer, t_cord *cord, short pos);
void			highlight_right(t_buff *buffer, t_cord *cord, short pos);
void			disable_highlight(t_cord *cord, t_buff *buffer, short len);
void			copy_highlight(t_buff *buffer, t_cord *cord);
void		    paste_highlight(t_buff *buffer, t_cord *cord);
void    		cut_highlight(t_buff *buffer, t_cord *cord);
char		    *copy_from_buff(char *buffer, char *new_buffer,
short start, short end);
#endif
