/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_init_vi_temp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 16:40:42 by aashara-          #+#    #+#             */
/*   Updated: 2020/01/22 16:57:50 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

static t_hash	**init_vi_temp2(t_hash **table, int hash_size)
{
	table = push_hash(table, RL_K_X_UPPER, (void*)&rl_k_x_upper, hash_size);
	table = push_hash(table, RL_K_X_LOWER, (void*)&rl_k_x_lower, hash_size);
	table = push_hash(table, RL_K_V, (void*)&rl_k_v, hash_size);
	table = push_hash(table, RL_K_F_LOWER, (void*)&rl_k_f_lower, hash_size);
	table = push_hash(table, RL_K_F_UPPER, (void*)&rl_k_f_upper, hash_size);
	table = push_hash(table, RL_K_SEMICOLON, (void*)&rl_k_semicolon, hash_size);
	table = push_hash(table, RL_K_COMMA, (void*)&rl_k_comma, hash_size);
	table = push_hash(table, RL_K_R_LOWER, (void*)&rl_k_r_lower, hash_size);
	table = push_hash(table, RL_K_R_UPPER, (void*)&rl_k_r_upper, hash_size);
	table = push_hash(table, RL_K_P_LOWER, (void*)&rl_k_p_lower, hash_size);
	table = push_hash(table, RL_K_P_UPPER, (void*)&rl_k_ctrl_v, hash_size);
	table = push_hash(table, RL_K_Y_UPPER, (void*)&rl_k_y_upper, hash_size);
	table = push_hash(table, RL_K_D_UPPER, (void*)&rl_k_d_upper, hash_size);
	table = push_hash(table, RL_K_C_UPPER, (void*)&rl_k_d_upper, hash_size);
	return (table);
}

t_hash			**init_vi_temp(int hash_size)
{
	t_hash	**table;

	table = init_temp(hash_size);
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
	return (init_vi_temp2(table, hash_size));
}
