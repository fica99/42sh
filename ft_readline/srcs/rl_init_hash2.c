/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init_hash2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:34:17 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 15:12:30 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_hash	**init_standart_templates_other(t_hash **table, int hash_size)
{
	char	symb[2];

	symb[1] = '\0';
	symb[0] = RL_K_CTRL_X;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_x, hash_size);
	symb[0] = RL_K_CTRL_V;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_v, hash_size);
	symb[0] = RL_K_CTRL_C;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_c, hash_size);
	symb[0] = RL_K_ENTER;
	table = push_hash(table, symb, (void*)&rl_k_enter, hash_size);
	symb[0] = RL_K_CTRL_H;
	table = push_hash(table, symb, (void*)&rl_k_bcsp, hash_size);
	symb[0] = RL_K_CTRL_R;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_r, hash_size);
	symb[0] = RL_K_BCSP;
	table = push_hash(table, symb, (void*)&rl_k_bcsp, hash_size);
	symb[0] = RL_K_CTRL_D;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_d, hash_size);
	symb[0] = RL_K_CTRL_J;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_j, hash_size);
	symb[0] = RL_K_ESC;
	table = push_hash(table, symb, (void*)&rl_k_esc, hash_size);
	symb[0] = RL_K_CTRL_G;
	return (push_hash(table, symb, (void*)&rl_k_ctrl_g, hash_size));
}

t_hash	**init_emacs_hash_other(t_hash **table, int hash_size)
{
	char	symb[2];

	symb[1] = '\0';
	symb[0] = RL_K_CTRL_B;
	table = push_hash(table, symb, (void*)&rl_k_left, hash_size);
	symb[0] = RL_K_CTRL_F;
	table = push_hash(table, symb, (void*)&rl_k_right, hash_size);
	symb[0] = RL_K_CTRL_A;
	table = push_hash(table, symb, (void*)&rl_k_home, hash_size);
	symb[0] = RL_K_CTRL_E;
	table = push_hash(table, symb, (void*)&rl_k_end, hash_size);
	symb[0] = RL_K_CTRL_P;
	table = push_hash(table, symb, (void*)&rl_k_up, hash_size);
	symb[0] = RL_K_CTRL_N;
	table = push_hash(table, symb, (void*)&rl_k_down, hash_size);
	symb[0] = RL_K_CTRL_L;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_l, hash_size);
	symb[0] = RL_K_CTRL_U;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_u, hash_size);
	symb[0] = RL_K_CTRL_K;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_k, hash_size);
	symb[0] = RL_K_CTRL_Y;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_v, hash_size);
	return (table);
}

t_hash	**init_vi_hash_other(t_hash **table, int hash_size)
{
	table = push_hash(table, RL_K_X_UPPER, (void*)&rl_k_x_upper, hash_size);
	table = push_hash(table, RL_K_X_LOWER, (void*)&rl_k_x_lower, hash_size);
	table = push_hash(table, RL_K_V, (void*)&rl_k_v, hash_size);
	return (table);
}
