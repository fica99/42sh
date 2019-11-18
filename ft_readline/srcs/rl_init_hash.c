/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:30:58 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 14:42:28 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_hash	**init_vi_hash(int hash_size)
{
	t_hash	**table;

	table = init_standart_templates(hash_size);
	table = push_hash(table, RL_K_I_LOWER, (void*)&rl_k_i_lower, hash_size);
	table = push_hash(table, RL_K_I_UPPER, (void*)&rl_k_i_upper, hash_size);
	table = push_hash(table, RL_K_A_LOWER, (void*)&rl_k_a_lower, hash_size);
	table = push_hash(table, RL_K_A_UPPER, (void*)&rl_k_a_upper, hash_size);
	table = push_hash(table, RL_K_SHARP, (void*)&rl_k_sharp, hash_size);
	table = push_hash(table, RL_K_J, (void*)&rl_k_down, hash_size);
	table = push_hash(table, RL_K_K, (void*)&rl_k_up, hash_size);
	table = push_hash(table, RL_K_L, (void*)&rl_k_left, hash_size);
	table = push_hash(table, RL_K_H, (void*)&rl_k_right, hash_size);
	table = push_hash(table, RL_K_W_UPPER, (void*)&rl_k_ctrl_right, hash_size);
	table = push_hash(table, RL_K_W_LOWER, (void*)&rl_k_ctrl_right, hash_size);
	table = push_hash(table, RL_K_B_UPPER, (void*)&rl_k_ctrl_left, hash_size);
	table = push_hash(table, RL_K_B_LOWER, (void*)&rl_k_ctrl_left, hash_size);
	table = push_hash(table, RL_K_ZERO, (void*)&rl_k_home, hash_size);
	table = push_hash(table, RL_K_DOLLAR, (void*)&rl_k_end, hash_size);
	table = push_hash(table, RL_K_SPACE, (void*)&rl_k_right, hash_size);
	table = push_hash(table, RL_K_E_UPPER, (void*)&rl_k_e, hash_size);
	table = push_hash(table, RL_K_E_LOWER, (void*)&rl_k_e, hash_size);
	table = push_hash(table, RL_K_CARAT, (void*)&rl_k_carat, hash_size);
	table = push_hash(table, RL_K_S_UPPER, (void*)&rl_k_s_upper, hash_size);
	table = push_hash(table, RL_K_S_LOWER, (void*)&rl_k_s_lower, hash_size);
	return (init_vi_hash_other(table, hash_size));
}

t_hash	**init_standart_templates(int hash_size)
{
	t_hash	**table;

	if (!(table = init_hash_table(hash_size)))
		rl_err("42sh", "malloc() error", ENOMEM);
	table = push_hash(table, RL_K_LFT, (void*)&rl_k_left, hash_size);
	table = push_hash(table, RL_K_RGHT, (void*)&rl_k_right, hash_size);
	table = push_hash(table, RL_K_HOME, (void*)&rl_k_home, hash_size);
	table = push_hash(table, RL_K_END, (void*)&rl_k_end, hash_size);
	table = push_hash(table, RL_K_CTRL_UP, (void*)&rl_k_ctrl_up, hash_size);
	table = push_hash(table, RL_K_CTRL_DOWN, (void*)&rl_k_ctrl_down,
	hash_size);
	table = push_hash(table, RL_K_CTRL_RIGHT, (void*)&rl_k_ctrl_right,
	hash_size);
	table = push_hash(table, RL_K_CTRL_LEFT, (void*)&rl_k_ctrl_left,
	hash_size);
	table = push_hash(table, RL_SHIFT_RIGHT, (void*)&rl_k_shift_right,
	hash_size);
	table = push_hash(table, RL_SHIFT_LEFT, (void*)&rl_k_shift_left,
	hash_size);
	table = push_hash(table, RL_K_DEL, (void*)&rl_k_del, hash_size);
	table = push_hash(table, RL_K_UP, (void*)&rl_k_up, hash_size);
	table = push_hash(table, RL_K_DOWN, (void*)&rl_k_down, hash_size);
	table = init_standart_templates_other(table, hash_size);
	return (table);
}

t_hash	**init_emacs_hash(int hash_size)
{
	t_hash	**table;
	char	symb[2];

	symb[1] = '\0';
	table = init_standart_templates(hash_size);
	table = init_emacs_hash_other(table, hash_size);
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
