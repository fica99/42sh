/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:52:19 by aashara-          #+#    #+#             */
/*   Updated: 2019/12/06 13:36:19 by lcrawn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

/*void	synch_signal(int sig)
{
	if (sig == SIGINT) {
		chld_interrupt = 1;
	}
	if (sig == SIGTSTP) {
		chld_interrupt = 2;
	}
	if (sig == SIGQUIT) {
		chld_interrupt = 3;
	}
	if (sig == SIGWINCH) {
		chld_interrupt = 4;
	}
}

void	sigaction_set(void (*f)(int sig), struct sigaction *usr_action)
{
	sigset_t set;

	sigfillset(&set);
  	usr_action->sa_handler = f;
  	usr_action->sa_mask = set;
 	usr_action->sa_flags = 0;
  	sigaction(SIGINT, usr_action, NULL);
	sigaction(SIGQUIT, usr_action, NULL);
	sigaction(SIGTSTP, usr_action, NULL);
	sigaction(SIGTTIN, usr_action, NULL);
	sigaction(SIGTTOU, usr_action, NULL);
	sigaction(SIGCHLD, usr_action, NULL);
	sigaction(SIGWINCH, usr_action, NULL);
}*/

void	set_sig_def(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

void 	sighandler_chld(int sign)
{
	write(STDOUT_FILENO, "\nIM THE CHILD\n", 15);
	//tcsetpgrp(STDIN_FILENO, g_cur_process);
    //tcsetpgrp(STDOUT_FILENO, g_cur_process);
	if (sign == SIGTSTP) {
		/*write(STDOUT_FILENO, "background\n", 11);
		kill(getpid(), SIGKILL);
		while (true) {
			printf("chld received SIGTSTP\n");
			sleep(1);
		}*/
		pause();
		//kill(g_cur_process, SIGTSTP);
	}
}

void	signalling_chld(void)
{
	signal(SIGTSTP, sighandler_chld);
	//signal(SIGINT, sighandler_chld);
}

void	break_handler(int sign)
{
	if (sign == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (sign == SIGQUIT)
		ft_putstr_fd("\nquit (core dumped)\n", STDERR_FILENO);
}

void	signalling(void)
{
	signal(SIGINT, break_handler);
	signal(SIGQUIT, break_handler);
	signal(SIGWINCH, break_handler);
}

//void	win_handler(int sign)
//{
//	t_cord	*cord;
//	short	pos;
//
//	if (sign == SIGWINCH)
//	{
//		cord = g_line.cord;
//		pos = cord->pos;
//		cord->pos -= (cord->x_cur - cord->x_start + ((cord->y_cur - cord->y_start) *
//		cord->ws_col));
//		set_attr(&g_orig_mode);
//		get_win_size(g_line.cord);
//		go_to_cord(0, g_line.cord->y_start, STDIN_FILENO);
//		ft_putstr_fd(CLEAR_END_SCREEN, STDIN_FILENO);
//		write_prompt(g_prompt);
//		set_input_mode(&g_raw_mode);
//		get_cur_cord(cord);
//		set_start_cord(cord);
//		set_end_cord(cord);
//		ft_putstr_cord(g_line.buffer.buffer + cord->pos, cord);
//		go_left(cord->pos - pos, cord);
//	}
//}
