/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_templates.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:30:15 by aashara-          #+#    #+#             */
/*   Updated: 2019/11/02 19:13:42 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RL_TEMPLATES_H
# define RL_TEMPLATES_H

# define RL_TRANSMIT_MODE tigetstr("smkx")
# define RL_STOP_TRANSMIT_MODE tigetstr("rmkx")
# define RL_CUR_CORD tigetstr("u7")
# define RL_SET_CUR tigetstr("cup")
# define RL_K_LFT tigetstr("kcub1")
# define RL_K_RGHT tigetstr("kcuf1")
# define RL_K_HOME tigetstr("khome")
# define RL_K_END tigetstr("kend")
# define RL_SHIFT_LEFT tigetstr("kLFT")
# define RL_SHIFT_RIGHT tigetstr("kRIT")
// # define RL_SAVE_CUR tigetstr("sc")
// # define RL_RESTORE_CUR tigetstr("rc")
# define RL_CUR_INVIS tigetstr("civis")
# define RL_CUR_VIS tigetstr("cvvis")
# define RL_CLEAR_END_SCREEN tigetstr("ed")
# define RL_K_DEL tigetstr("kdch1")
# define RL_K_UP tigetstr("kcuu1")
# define RL_K_DOWN tigetstr("kcud1")
# define RL_CTRL_UP "\033[1;5A"
# define RL_CTRL_DOWN "\033[1;5B"
# define RL_CTRL_RIGHT "\033[1;5C"
# define RL_CTRL_LEFT "\033[1;5D"
# define RL_CTRL_V 22
# define RL_CTRL_X 24
# define RL_CTRL_C 3
# define RL_NEW_LINE 10
# define RL_BCSP 127
# define RL_CTRL_H 8
# define RL_CTRL_D 4

#endif