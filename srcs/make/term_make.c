/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_make.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:18:04 by filip             #+#    #+#             */
/*   Updated: 2019/05/08 19:21:07 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "42sh.h"

void	get_win_size(void)
{
	if ((g_term.ws_col = tigetnum("cols")) == -2 ||
	(g_term.ws_row = tigetnum("lines")) == -2)
	print_error("minishell", "tigetnum() error", "no correct defenitions", 0);
}

void	init_term()
{
	char	*smkx_mode;

	setupterm(ft_getenv("TERM"), STDIN_FILENO, (int*)0);
	if ((smkx_mode = tigetstr("smkx")) != (char*)-1)
		tputs(smkx_mode, 1, putchar);
//	if (tigetflag("bw") == -1 || tigetflag("am") == -1
//	|| tigetflag("da") == -1 || tigetflag("db") == -1 || tigetflag("msgr") == -1)
//		print_error("minishell", "tigetflag() error", "no correct defenitions", 0);
}

void		get_cur_cord(void)
{
	char	cur_cord[NORMAL_LINE];
	char	*pos;
	short	num;

	num = 0;
	set_input_mode();
	ft_putstr_fd(CUR_CORD, STDIN_FILENO);
	read_handler(cur_cord, STDOUT_FILENO);
	reset_input_mode();
	if (!(pos = ft_strchr(cur_cord, (int)'[')))
		return ; // обработать!
	while (ft_isdigit(*(++pos)))
		num = num * 10 + (int)*pos - 48;
	g_term.y_cur = num;
	num = 0;
	if (!(pos = ft_strchr(cur_cord, (int)';')))
		return ; // обработать!i
	while (ft_isdigit(*(++pos)))
		num = num * 10 + (int)*pos - 48;
	g_term.x_cur = num;
}

void	set_input_mode(void)
{
	struct termios	tty;

	if (!isatty(0))
		print_error("minishell", "stdin not terminal\n", NULL, 0);
	if (tcgetattr(STDIN_FILENO, &(g_term.savetty)) < 0)
		print_error("minishell", "tcgetattr() error", NULL, 0);
	if (tcgetattr(STDIN_FILENO, &tty) < 0)
		print_error("minishell", "tcgetattr() error", NULL, 0);
	tty.c_lflag &= ~(ICANON | ECHO | ISIG);
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN] = 1;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) < 0)
		print_error("minishell", "tcsetattr() error", NULL, 0);
}

void	reset_input_mode (void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(g_term.savetty)) < 0)
		print_error("minishell", "tcsetattr() error", NULL, 0);
}

