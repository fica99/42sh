/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filip <filip@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:19:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/27 15:37:05 by filip            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *arr)
{
	if (get_count_var(arr) == -1)
		return (NULL);
	else
		return (g_term.env_cp[get_count_var(arr)] + ft_strlen(arr) + 1);
}

short	get_count_var(char *arr)
{
	uint8_t	i;

	i = 0;
	while (g_term.env_cp[i])
	{
		if (ft_strncmp(g_term.env_cp[i], arr, ft_strlen(arr)) == 0
				&& g_term.env_cp[i][ft_strlen(arr)] == '=')
			return (i);
		i++;
	}
	return (-1);
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

char			*strnew_realloc_buf(char *str, short len)
{
	char	*arr;

	arr = str;
	if (!(str = ft_strnew(len)))
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		reset_input_mode();
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	}
	str = ft_strcat(str, arr);
	ft_memdel((void**)&arr);
	return (str);
}

void	reset_input_mode (void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(g_term.savetty)) < 0)
		print_error("minishell", "tcsetattr() error", NULL, 0);
}
