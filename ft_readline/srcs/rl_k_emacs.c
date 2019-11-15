/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_emacs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:13:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/15 22:45:10 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	rl_k_ctrl_l(t_readline *rl)
{
	short	pos;

	if (g_rl_flags)
		rl_disable_line(rl);
	pos = rl->cord.pos;
	ft_putstr(RL_CUR_INVIS);
	ft_putstr(RL_CLEAR_SCREEN);
	rl_write_prompt(rl->prompt, rl->env, rl->history);
	rl_start_cord_data(&rl->cord);
	rl_print(rl->line.buffer, &rl->cord);
	rl_go_left(rl->cord.pos - pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}

void	rl_k_alt_d(t_readline *rl)
{
	short	pos;
	char	*copy;

	if (rl_is_end_pos(rl->cord))
		return ;
	pos = rl->cord.pos;
	if (ft_isspace(rl->line.buffer[pos]))
		pos = rl_next_word(rl->line.buffer, pos);
	while (ft_isalnum(rl->line.buffer[pos]))
		++pos;
	if (!(copy = ft_strdup(rl->line.buffer + pos)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer + rl->cord.pos);
	ft_strncpy(rl->copy_buff.buffer, rl->line.buffer + rl->cord.pos,
	pos - rl->cord.pos);
	rl_check_str_mem(&rl->line, copy);
	ft_strcpy(rl->line.buffer + rl->cord.pos, copy);
	ft_strdel(&copy);
	pos = rl->cord.pos;
	rl_disable_line(rl);
}

void	rl_k_ctrl_w(t_readline *rl)
{
	short	pos;
	char	*copy;

	if (rl_is_start_pos(rl->cord))
		return ;
	pos = rl->cord.pos;
	while (pos >= 0 && ft_isspace(rl->line.buffer[pos]))
		--pos;
	if (pos == -1)
		return ;
	while (pos >= 0 && ft_isalnum(rl->line.buffer[pos]))
		--pos;
	++pos;
	if (!(copy = ft_strdup(rl->line.buffer + rl->cord.pos)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer + pos);
	ft_strncpy(rl->copy_buff.buffer, rl->line.buffer + pos,
	rl->cord.pos - pos);
	ft_strcpy(rl->line.buffer + pos, copy);
	ft_strdel(&copy);
	rl->cord.pos = pos;
	rl_disable_line(rl);
}

void	rl_k_alt_r(t_readline *rl)
{
	ft_strclr(rl->line.buffer);
	rl_disable_line(rl);
}

void	rl_k_alt_t(t_readline *rl)
{
	char	copy[10000];
	char	rl_cur_word[10000];
	char	w[10000];
	short	i;
	short	pos;

	i = rl->cord.pos;
	(ft_isspace(rl->line.buffer[i]) || !rl->line.buffer[i]) ? (i =
	rl_next_word(rl->line.buffer, i)) : (i = rl_prev_word(rl->line.buffer, i));
	if (!i || !rl->line.buffer[i])
		return ;
	(ft_strchr(rl->line.buffer + i, ' ')) ? (pos = ft_strchr(rl->line.buffer
	+ i, ' ') - (rl->line.buffer + i)) : (pos = ft_strchr(rl->line.buffer
	+ i, '\0') - (rl->line.buffer + i));
	ft_strncpy(rl_cur_word, rl->line.buffer + i, pos);
	ft_strcpy(copy, rl->line.buffer + pos + i);
	rl->cord.pos = pos + i;
	pos = rl_prev_word(rl->line.buffer, --i);
	ft_strcpy(w, rl->line.buffer + pos);
	ft_strcpy(rl->line.buffer + pos, rl_cur_word);
	i = rl_count_spaces(ft_strchr(w, ' '));
	while (i--)
		ft_strcat(rl->line.buffer, " ");
	ft_strcat(ft_strncat(rl->line.buffer, w, ft_strchr(w, ' ') - w), copy);
	rl_disable_line(rl);
}
