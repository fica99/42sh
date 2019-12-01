#include "ft_shell.h"

static void	init_set_values(void)
{
	ft_strcpy(g_set_env.env[0], "HISTFILE=");
	ft_strcpy(g_set_env.env[1], "HISTFILESIZE=");
	ft_strcpy(g_set_env.env[2], "HISTSIZE=");
	ft_strcpy(g_set_env.env[3], "HOSTNAME=");
	ft_strcpy(g_set_env.env[4], "IFS=");
	ft_strcpy(g_set_env.env[5], "LINES=");
	ft_strcpy(g_set_env.env[6], "MACHTYPE=");
	ft_strcpy(g_set_env.env[7], "PS1=");
	ft_strcpy(g_set_env.env[8], "PS2=");
	ft_strcpy(g_set_env.env[9], "PS4=");
}

void	change_set_value(short index, const char *value)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < g_set_env.str_size && g_set_env.env[index][i] != '=')
		i++;
	if (i < g_set_env.str_size)
		i++;
	while (i < g_set_env.str_size && value[j])
	{
		g_set_env.env[index][i] = value[j];
		j++;
		i++;
	}
	while (i < g_set_env.str_size)
	{
		g_set_env.env[index][i] = 0;
		i++;
	}
}

void	init_global_set_env(void)
{
	int i;

	g_set_env.ar_size = 10;
	g_set_env.str_size = 128;
	i = g_set_env.ar_size;
	while (i--)
		ft_memset(g_set_env.env[i], 0, g_set_env.str_size);
	init_set_values();
}
