/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_templates.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:30:15 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/18 15:12:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RL_TEMPLATES_H
# define RL_TEMPLATES_H

# define VI_HASH_SIZE 47
# define EMACS_HASH_SIZE 46
# define RL_TRANSMIT_MODE tigetstr("smkx")
# define RL_STOP_TRANSMIT_MODE tigetstr("rmkx")
# define RL_CUR_CORD tigetstr("u7")
# define RL_SET_CUR tigetstr("cup")
# define RL_CUR_INVIS tigetstr("civis")
# define RL_CUR_VIS tigetstr("cvvis")
# define RL_CLEAR_END_SCREEN tigetstr("ed")
# define RL_CLEAR_SCREEN tigetstr("clear")
/*
**	VI
*/
# define RL_K_I_LOWER "i"
# define RL_K_I_UPPER "I"
# define RL_K_A_LOWER "a"
# define RL_K_A_UPPER "A"
# define RL_K_SHARP "#"
# define RL_K_J "j"
# define RL_K_K "k"
# define RL_K_L "l"
# define RL_K_H "h"
# define RL_K_W_LOWER "w"
# define RL_K_W_UPPER "W"
# define RL_K_B_LOWER "b"
# define RL_K_B_UPPER "B"
# define RL_K_ZERO "0"
# define RL_K_DOLLAR "$"
# define RL_K_SPACE " "
# define RL_K_E_LOWER "e"
# define RL_K_E_UPPER "E"
# define RL_K_S_UPPER "S"
# define RL_K_S_LOWER "s"
# define RL_K_X_UPPER "X"
# define RL_K_X_LOWER "x"
# define RL_K_CARAT "^"
# define RL_K_V "v"
/*
**	EMACS
*/
# define RL_K_ALT_B "\033b"
# define RL_K_ALT_F "\033f"
# define RL_K_ALT_D "\033d"
# define RL_K_ALT_R "\033r"
# define RL_K_ALT_RIGHT "\033\033[C"
# define RL_K_ALT_LEFT "\033\033[D"
# define RL_K_ALT_T "\033t"
# define RL_K_ALT_U "\033u"
# define RL_K_ALT_L "\033l"
# define RL_K_ALT_C "\033c"
# define RL_K_CTRL_B 2
# define RL_K_CTRL_F 6
# define RL_K_CTRL_A 1
# define RL_K_CTRL_E 5
# define RL_K_CTRL_P 16
# define RL_K_CTRL_N 14
# define RL_K_CTRL_L 12
# define RL_K_CTRL_U 21
# define RL_K_CTRL_K 11
# define RL_K_CTRL_Y 25
# define RL_K_CTRL_W 23
# define RL_K_CTRL_T 20
/*
**	STANDART
*/
# define RL_K_LFT tigetstr("kcub1")
# define RL_K_RGHT tigetstr("kcuf1")
# define RL_K_HOME tigetstr("khome")
# define RL_K_END tigetstr("kend")
# define RL_SHIFT_LEFT tigetstr("kLFT")
# define RL_SHIFT_RIGHT tigetstr("kRIT")
# define RL_K_DEL tigetstr("kdch1")
# define RL_K_UP tigetstr("kcuu1")
# define RL_K_DOWN tigetstr("kcud1")
# define RL_K_CTRL_UP "\033[1;5A"
# define RL_K_CTRL_DOWN "\033[1;5B"
# define RL_K_CTRL_RIGHT "\033[1;5C"
# define RL_K_CTRL_LEFT "\033[1;5D"
# define RL_K_BCSP 127
# define RL_K_CTRL_V 22
# define RL_K_CTRL_X 24
# define RL_K_CTRL_C 3
# define RL_K_ENTER 13
# define RL_K_CTRL_J 10
# define RL_K_CTRL_G 7
# define RL_K_ESC 27
# define RL_K_CTRL_H 8
# define RL_K_CTRL_D 4
# define RL_K_CTRL_R 18
#endif
