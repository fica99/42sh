/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_k_emacs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:13:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/13 20:55:31 by aashara-         ###   ########.fr       */
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
	rl_print(rl->line, &rl->cord);
	rl_go_left(rl->cord.pos - pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}

void	rl_k_ctrl_k(t_readline *rl)
{
	if (g_rl_flags)
		rl_disable_line(rl);
	ft_strcpy(rl->copy_buff, rl->line + rl->cord.pos);
	ft_strclr(rl->line + rl->cord.pos);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_set_end_cord(&rl->cord);
}

void	rl_k_ctrl_u(t_readline *rl)
{
	char	copy[MAX_LINE_SIZE];

	if (g_rl_flags)
		rl_disable_line(rl);
	ft_strcpy(copy, rl->line + rl->cord.pos);
	ft_strncpy(rl->copy_buff, rl->line, rl->cord.pos);
	ft_strcpy(rl->line, copy);
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_set_end_cord(&rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line, &rl->cord);
	rl_go_left(rl->cord.pos, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}

void	rl_k_alt_d(t_readline *rl)
{
	short	i;
	char	copy[MAX_LINE_SIZE];

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_end_pos(rl->cord))
		return ;
	i = rl->cord.pos - 1;
	while (rl->line[++i])
	{
		if (ft_isalnum(rl->line[i]) && ft_isspace(rl->line[i + 1]))
		{
			++i;
			break ;
		}
	}
	ft_strncpy(rl->copy_buff, rl->line + rl->cord.pos, i - rl->cord.pos);
	ft_strcpy(copy, rl->line + i);
	ft_strcpy(rl->line + rl->cord.pos, copy);
	i = rl->cord.pos;
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_set_end_cord(&rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line, &rl->cord);
	rl_go_left(rl->cord.pos - i, &rl->cord);
}

void	rl_k_ctrl_w(t_readline *rl)
{
	short	i;
	char	copy[MAX_LINE_SIZE];

	if (g_rl_flags)
		rl_disable_line(rl);
	if (rl_is_start_pos(rl->cord))
		return ;
	i = rl->cord.pos;
	while (--i > 0)
		if (ft_isspace(rl->line[i - 1]) && ft_isalnum(rl->line[i]))
			break ;
	ft_strncpy(rl->copy_buff, rl->line + i, rl->cord.pos - i);
	ft_strcpy(copy, rl->line + rl->cord.pos);
	ft_strcpy(rl->line + i, copy);
	ft_putstr(RL_CUR_INVIS);
	rl_go_left(rl->cord.pos, &rl->cord);
	rl_set_end_cord(&rl->cord);
	ft_putstr(RL_CLEAR_END_SCREEN);
	rl_print(rl->line, &rl->cord);
	rl_go_left(rl->cord.pos - i, &rl->cord);
	ft_putstr(RL_CUR_VIS);
}
