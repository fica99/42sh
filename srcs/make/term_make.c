/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_make.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:18:04 by filip             #+#    #+#             */
/*   Updated: 2019/05/28 22:58:45 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		get_win_size(void)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) < 0)
		print_error("42sh", "ioctl() error", NULL, 0);
	g_term.ws_col = size.ws_col;
	g_term.ws_row = size.ws_row;
}

void		init_term(void)
{
	char	*term;
	int		err;
	char	*smkx_mode;

	if ((term = ft_getenv("TERM")) == NULL ||
	(setupterm(term, STDIN_FILENO, &err) == ERR))
		print_error("42sh", "setupterm() error", NULL, 0);
	if ((smkx_mode = tigetstr("smkx")) != (char*)-1
		&& tigetstr("u7") != (char*)-1
	&& tigetstr("kcub1") != (char*)-1 && tigetstr("khome") != (char*)-1
	&& tigetstr("kcuf1") != (char*)-1 && tigetstr("kend") != (char*)-1
	&& tigetstr("cup") != (char*)-1 && tigetstr("sc") != (char*)-1
	&& tigetstr("rc") != (char*)-1 && tigetstr("ed") != (char*)-1
	&& tigetstr("clear") != (char*)-1 && tigetstr("kdch1") != (char*)-1
	&& tigetstr("kcuu1") != (char*)-1 && tigetstr("kcud1") != (char*)-1)
		ft_putstr_fd(smkx_mode, STDIN_FILENO);
	else
		print_error("42sh", "no correct capabilities", NULL, 0);
}

void		get_cur_cord(void)
{
	char	cur_cord[NORMAL_LINE];
	char	*pos;
	short	num;

	num = 0;
	set_input_mode();
	ft_putstr_fd(tigetstr("u7"), STDIN_FILENO);
	read_handler(cur_cord, STDOUT_FILENO);
	reset_input_mode();
	if (!(pos = ft_strchr(cur_cord, (int)'[')))
		return ;
	while (ft_isdigit(*(++pos)))
		num = num * 10 + (int)*pos - 48;
	g_term.y_cur = num - 1;
	num = 0;
	if (!(pos = ft_strchr(cur_cord, (int)';')))
		return ;
	while (ft_isdigit(*(++pos)))
		num = num * 10 + (int)*pos - 48;
	g_term.x_cur = num - 1;
}

void		set_input_mode(void)
{
	struct termios	tty;

	if (!isatty(0))
		print_error("42sh", "stdin not terminal\n", NULL, 0);
	if (tcgetattr(STDIN_FILENO, &(g_term.savetty)) < 0)
		print_error("42sh", "tcgetattr() error", NULL, 0);
	tty = g_term.savetty;
	tty.c_lflag &= ~(ICANON | ECHO | ISIG);
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN] = 1;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) < 0)
		print_error("42sh", "tcsetattr() error", NULL, 0);
}

void		reset_input_mode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(g_term.savetty)) < 0)
		print_error("42sh", "tcsetattr() error", NULL, 0);
}
