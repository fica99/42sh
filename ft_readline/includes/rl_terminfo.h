/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_terminfo.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:30:15 by aashara-          #+#    #+#             */
/*   Updated: 2019/10/30 18:50:44 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RL_TERMINFO_H
# define RL_TERMINFO_H

# define TRANSMIT_MODE tigetstr("smkx")
# define STOP_TRANSMIT_MODE tigetstr("rmkx")
# define CUR_CORD tigetstr("u7")
# define SET_CUR tigetstr("cup")
# define RL_K_LFT tigetstr("kcub1")
# define RL_K_RGHT tigetstr("kcuf1")
# define RL_K_HOME tigetstr("khome")
# define RL_K_END tigetstr("kend")
#endif
