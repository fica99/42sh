/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_emacs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:13:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/14 22:14:06 by aashara-         ###   ########.fr       */
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

void	rl_k_ctrl_k(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer + rl->cord.pos);
	ft_strcpy(rl->copy_buff.buffer, rl->line.buffer + rl->cord.pos);
	ft_strclr(rl->line.buffer + rl->cord.pos);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_set_end_cord(&rl->cord);
}

void	rl_k_ctrl_u(t_readline *rl)
{
	char	*copy;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (!(copy = ft_strdup(rl->line.buffer + rl->cord.pos)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl->line.buffer[rl->cord.pos] = '\0';
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer);
	ft_strcpy(rl->copy_buff.buffer, rl->line.buffer);
	rl_check_str_mem(&rl->line, copy);
	ft_strcpy(rl->line.buffer, copy);
	ft_strdel(&copy);
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_set_end_cord(&rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line.buffer, &rl->cord);
	rl_go_left(rl->cord.pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}

void	rl_k_alt_d(t_readline *rl)
{
	short	pos;
	char	*copy;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	pos = rl_next_word(rl->line.buffer, rl->cord.pos);
	if (!(copy = ft_strdup(rl->line.buffer + pos)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl->line.buffer[pos] = '\0';
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer + rl->cord.pos);
	ft_strcpy(rl->copy_buff.buffer, rl->line.buffer + rl->cord.pos);
	rl_check_str_mem(&rl->line, copy);
	ft_strcpy(rl->line.buffer + rl->cord.pos, copy);
	ft_strdel(&copy);
	pos = rl->cord.pos;
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_set_end_cord(&rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line.buffer, &rl->cord);
	rl_go_left(rl->cord.pos - pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}

void	rl_k_ctrl_w(t_readline *rl)
{
	short	pos;
	char	*copy;

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	pos = rl_prev_word(rl->line.buffer, rl->cord.pos);
	if (!(copy = ft_strdup(rl->line.buffer + rl->cord.pos)))
		rl_err("42sh", "malloc() error", ENOMEM);
	rl->line.buffer[rl->cord.pos] = '\0';
	rl_check_str_mem(&rl->copy_buff, rl->line.buffer + pos);
	ft_strcpy(rl->copy_buff.buffer, rl->line.buffer + pos);
	ft_strcpy(rl->line.buffer + pos, copy);
	ft_strdel(&copy);
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_set_end_cord(&rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line.buffer, &rl->cord);
	rl_go_left(rl->cord.pos - pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}
