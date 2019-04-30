/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_make.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 23:18:04 by filip             #+#    #+#             */
/*   Updated: 2019/04/30 16:02:43 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "42sh.h"

void	get_win_size(void)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) < 0)
		print_error("minishell", "ioctl() error", NULL, 0);
	g_term.ws_col = size.ws_col;
	g_term.ws_row = size.ws_row;
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

void    ft_putstr_cord(char *str)
{
	while (str && *str)
	{
		ft_putchar_fd(*str, STDIN_FILENO);
		(g_term.x_cur)++;
		str++;
		if (g_term.x_cur > g_term.ws_col)
		{
			ft_putchar_fd('\n', STDIN_FILENO);
			g_term.x_cur = 1;
			if (g_term.y_cur >= g_term.ws_row)
				(g_term.y_start)--;
			else
				(g_term.y_cur)++;
		}
	}
}