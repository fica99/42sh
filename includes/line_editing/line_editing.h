/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/06/24 17:02:16 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <stdlib.h>

char			*print_move(char *c, t_buff *buffer, t_cord *cord);
char			*print_symbols(char *c, t_buff *buffer, t_cord *cord,
t_history *history);
char			*print_printable(char *c, char *buffer, t_cord *cord);
void			go_left(short i, t_cord *cord);
void			go_right(short i, t_cord *cord);
void			prev_word(char *buf, t_cord *cord);
void			next_word(char *buf, t_cord *cord);
void			del_symb(char *buf, t_cord *cord);
void			print_symb(char *c, char *buf, t_cord *cord);
void			go_to_cord(short x, short y, int fd);
void			ft_putstr_cord(char *str, t_cord *cord);
char	        *cut_copy_paste(char *c, t_buff *buffer, t_cord *cord);
void		    ft_putstr_highlight(char *str, short start, short end, t_cord *cord);
void			highlight_left(t_buff *buffer, t_cord *cord);
void			highlight_right(t_buff *buffer, t_cord *cord);
void			disable_highlight(t_cord *cord, t_buff *buffer);
void			copy_highlight(t_buff *buffer, t_cord *cord);
void		    paste_highlight(t_buff *buffer, t_cord *cord);
void    		cut_highlight(t_buff *buffer, t_cord *cord);
char		    *copy_from_buff(char *buffer, char *new_buffer,
short start, short end);
void			go_history(char *c, t_history *history, t_cord *cord,
t_buff *buffer);
void			history_up(t_history *history, t_cord *cord, short len,
t_buff *buffer);
void			history_down(t_history *history, t_cord *cord, short len,
t_buff *buffer);
void			find_history(char *symbol, t_buff *buffer, t_cord *cord,
t_history *history);
char			*check_history(t_history *history, t_buff *buffer);
#endif
