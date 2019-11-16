/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_emacs_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:48:20 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/16 20:09:48 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_hash	**init_emacs_hash(int hash_size)
{
	t_hash	**table;
	char	symb[2];

	symb[1] = '\0';
	table = init_standart_templates(hash_size);
	table = init_emacs_hash_symb(table, hash_size);
	symb[0] = RL_K_CTRL_W;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_w, hash_size);
	symb[0] = RL_K_CTRL_T;
	table = push_hash(table, symb, (void*)&rl_k_ctrl_t, hash_size);
	table = push_hash(table, RL_K_ALT_B, (void*)&rl_k_ctrl_left, hash_size);
	table = push_hash(table, RL_K_ALT_F, (void*)&rl_k_ctrl_right, hash_size);
	table = push_hash(table, RL_K_ALT_D, (void*)&rl_k_alt_d, hash_size);
	table = push_hash(table, RL_K_ALT_R, (void*)&rl_k_alt_r, hash_size);
	table = push_hash(table, RL_K_ALT_RIGHT, (void*)&rl_k_alt_right,
	hash_size);
	table = push_hash(table, RL_K_ALT_T, (void*)&rl_k_alt_t, hash_size);
	table = push_hash(table, RL_K_ALT_U, (void*)&rl_k_alt_u, hash_size);
	table = push_hash(table, RL_K_ALT_L, (void*)&rl_k_alt_l, hash_size);
	table = push_hash(table, RL_K_ALT_C, (void*)&rl_k_alt_c, hash_size);
	table = push_hash(table, RL_K_ALT_LEFT, (void*)&rl_k_alt_left,
	hash_size);
	return (table);
}

t_hash	**init_emacs_hash_symb(t_hash **table, int hash_size)
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
