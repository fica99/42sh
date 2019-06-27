/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:20:50 by filip             #+#    #+#             */
/*   Updated: 2019/06/28 00:33:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include <stdlib.h>

t_cord	*init_cord(void);
void	get_win_size(t_cord *cord);
void	get_cur_cord(t_cord *cord);
void	set_start_cord(t_cord *cord);
t_buff	init_buff(t_buff buffer);
char	*check_quotes(t_line line);
char	*quotes_dquotes_brackets(short q, short dq, short br, t_line line);
void	go_left(short i, t_cord *cord);
short	check_nl_left(t_cord *cord, short i);
void	go_to_cord(short x, short y, int fd);
void	go_right(short i, t_cord *cord);
short	check_nl_right(t_cord *cord, short i);
char	*print_symbols(char *c, t_line line, t_history *history);
char	*cut_copy_paste(char *c, t_line line);
void	highlight_left(char *buffer, t_cord *cord);
void	ft_putstr_highlight(char *str, short start, short end, t_cord *cord);
void	highlight_right(char *buffer, t_cord *cord);
short	is_start_pos(t_cord *cord);
void	unset_start_pos(t_cord	*cord);
void	free_cord(t_cord **cord);
void	copy_highlight(t_buff copy_buff, t_buff buffer, t_cord *cord);
void    cut_highlight(t_buff buffer, t_cord *cord);
void	ft_putstr_cord(char *str, t_cord *cord);
void	check_end_window(t_cord *cord);
void	paste_highlight(t_buff buffer, t_buff copy_buff, t_cord *cord);
#endif
