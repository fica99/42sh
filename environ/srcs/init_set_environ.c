#include "ft_shell.h"

char	**init_set_values(char **values)
{
	values = (char **)malloc(sizeof(char *) * 11);
	values[0] = ft_strdup("HISTFILE=");
	values[1] = ft_strdup("HISTFILESIZE=");
	values[2] = ft_strdup("HISTSIZE=");
	values[3] = ft_strdup("HOSTNAME=");
	values[4] = ft_strdup("IFS=");
	values[5] = ft_strdup("LINES=");
	values[6] = ft_strdup("MACHTYPE=");
	values[7] = ft_strdup("PS1=");
	values[8] = ft_strdup("PS2=");
	values[9] = ft_strdup("PS4=");
	values[10] = NULL;
	return (values);
}
