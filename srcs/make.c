/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 14:19:14 by aashara-          #+#    #+#             */
/*   Updated: 2019/04/22 15:46:18 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_double_arr(char **arr)
{
	short	i;
	char	**arr1;

	if (!(arr1 = (char**)malloc(sizeof(char*) * (double_arr_len(arr) + 1))))
		print_error("minishell", "malloc() error", NULL, ENOMEM);
	i = -1;
	while (arr[++i])
		if (!(arr1[i] = ft_strdup(arr[i])))
			print_error("minishell", "malloc() error", NULL, ENOMEM);
	arr1[i] = NULL;
	return (arr1);
}

void	get_cord(void)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) < 0)
		print_error("minishell", "ioctl() error", NULL, 0);
	cord.ws_col = size.ws_col;
}

char	*ft_getenv(char *arr)
{
	if (get_count_var(arr) == -1)
		return (NULL);
	else
		return (&(env_cp[get_count_var(arr)][ft_strlen(arr) + 1]));
}

short	get_count_var(char *arr)
{
	uint8_t	i;

	i = 0;
	while (env_cp[i])
	{
		if (ft_strncmp(env_cp[i], arr, ft_strlen(arr)) == 0
				&& env_cp[i][ft_strlen(arr)] == '=')
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
	if (tcgetattr(STDIN_FILENO, &savetty) < 0)
		print_error("minishell", "tcgetattr() error", NULL, 0);
	tty = savetty;
	tty.c_lflag &= ~(ICANON | ECHO);
	tty.c_cc[VTIME] = 0;
	tty.c_cc[VMIN] = 1;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) < 0)
		print_error("minishell", "tcsetattr() error", NULL, 0);
}
