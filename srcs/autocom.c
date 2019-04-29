//
// Created by Guy Grimes on 2019-03-30.
//

#include "minishell.h"

/*
 * Обработать malloc ft_strdup;
 * */

int autocom(char **buf, short len)
{
	char	*start;
	int		prog;
	char	**arr_mat;
	char	*rest_add;
	int		len_am;

	len = len + 1;
	start = get_start_com(*buf, &prog);
	arr_mat = get_arr_matches(&start, prog);
	rest_add = get_autocom_part(arr_mat, start);
	len_am = ft_strarr_len(arr_mat);
	CLEAN_SCREEN(STDIN_FILENO);
	if (rest_add)
		print_read(rest_add);
	if (len_am)
	{
		//get_autocom_params(get_max_len(arr_mat), len_am);
		//ft_putnbr(g_term.autocom_cols);
		//ft_putchar('\n');
		//ft_putnbr(g_term.autocom_rows);
		//ft_putchar('\n');
	}
	if (rest_add)
		free(rest_add);
	if (arr_mat)
		free_double_arr(arr_mat);
	return (1);
}

int		get_max_len(char **arr_mat)
{
	int	max_len;
	int	len;

	max_len = 0;
	if (!arr_mat)
		return (0);
	while (arr_mat)
	{
		if ((len = ft_strlen(*(arr_mat++))) > max_len)
			max_len = len;
	}
	return (max_len);
}

void	get_autocom_params(int max_len, int cnt_arr_mat)
{
	int cnt;
	int	cols;
	int delta_cols;
	int rows;
	int delta_rows;

	cnt = cnt_arr_mat;
	while ((cnt * (max_len + 1)) > g_term.ws_col)
		cnt /= 2;
	cols = g_term.ws_col / (cnt * (max_len + 1));
	delta_cols = (g_term.ws_col % (cnt * (max_len + 1)) == 0) ? 0 : 1;
	cols += delta_cols;
	g_term.autocom_cols = cols;
	rows = cnt_arr_mat / cols;
	delta_rows = (cnt_arr_mat % cols == 0) ? 0 : 1;
	rows += delta_rows;
	g_term.autocom_rows = rows;
}

char *get_start_com(char *buf, int *prog)
{
	char *start;
	char *end;

	start = ft_strrchr(buf, ';');
	start = (!start) ? buf : start + 1;
	while (*start == ' ')
		start++;
	*prog = (!(end = ft_strrchr(start, ' '))) ? 1 : 0;
	start = (*prog) ? start : end + 1;
	return (start);
}

char **get_arr_matches(char **start, int prog)
{
	char **arr;
	char *path_end;

	if (prog)
		arr = get_prog_arr(*start);
	else
	{
		if ((path_end = ft_strrchr(*start, '/')))
		{
			*path_end = '\0';
			arr = get_dirs_arr(*start, 0);
			*path_end = '/';
			*start = path_end + 1;
		}
		else
			arr = get_dirs_arr("./", 0);
	}
	return (match_selection(*start, arr));
}

char **match_selection(char *arg, char **arr_mat)
{
	int i;
	int j;
	int count;
	char **buf;

	if (!arr_mat)
		return (NULL);
	if (!arg)
		return (arr_mat);
	i = -1;
	count = 0;
	while (arr_mat[++i])
		if (ft_strcmp_mod(arg, arr_mat[i], 0))
			count++;
	if (!count)
		return (NULL);
	buf = (char **)malloc(sizeof(char *) * count + 1);
	i = -1;
	j = -1;
	while (arr_mat[++i])
		if (ft_strcmp_mod(arg, arr_mat[i], 0))
			buf[++j] = ft_strdup(arr_mat[i]);
	buf[++j] = NULL;
	return (buf);
}

char **get_dirs_arr(char *path, int flag)
{
	int i;
	DIR *dir;
	struct dirent *d;
	char **buf_dir;
	int count;

	count = 0;
	if (!(dir = opendir(path)))
		return (NULL);
	while (readdir(dir))
		count++;
	rewinddir(dir);
	if (!(buf_dir = (char **)malloc(sizeof(char *) * count + 1)))
		return (NULL);
	i = 0;
	while ((d = readdir(dir)))
		if (!flag || (flag == 1 && d->d_type != 4)
		|| (flag == 2 && d->d_type == 4))
		buf_dir[i++] = ft_strdup(d->d_name);
	buf_dir[i] = NULL;
	closedir(dir);
	return (buf_dir);
}

char  *get_autocom_part(char **com_arr, char *arg)
{
	int i;
	int min;
	int count;
	int arg_len;
	char *com_str;

	if (!com_arr || !arg)
		return (NULL);
	i = 0;
	arg_len = ft_strlen(arg);
	min = ft_strlen(com_arr[0]);
	while (com_arr[++i])
	{
		count = ft_strcmp_mod(com_arr[0] + arg_len, com_arr[i] + arg_len, 1);
		min = (min > count) ? count : min;
	}
	if (!min)
		return (NULL);
	com_str = ft_strnew((size_t)min);
	i = -1;
	while (++i < min)
		com_str[i] = com_arr[0][arg_len + i];
	com_str[++i] = '\0';
	return (com_str);
}

char **get_prog_arr(char *arg)
{
	char **path_arr;
	char **prog_arr;
	char **temp;
	char **dirs;
	char *exc[] = {".", "..", NULL};
	int i;

	(void)arg;
	if (!(path_arr = ft_strsplit(ft_getenv("PATH"), ':')))
		return (NULL);
	i = -1;
	prog_arr = NULL;
	while (path_arr[++i])
	{
		dirs = get_dirs_arr(path_arr[i], 0);
		temp = ft_strarr_add(prog_arr, dirs, exc);
		if (prog_arr)
			free(prog_arr);
		prog_arr = temp;
		free(dirs);
	}
	return (prog_arr);
}

char **ft_strarr_add(char **dest, char **src, char **exc)
{
	int i;
	int j;
	char **str_arr;
	int len;

	if (!src || !*src)
		return (NULL);
	len = ft_strarr_len(dest);
	len += ft_strarr_len(src);
	if (!(str_arr = (char **)malloc(sizeof(char *) * len + 1)))
		return (NULL);
	i = -1;
	if (dest)
		while (dest[++i])
			str_arr[i] = dest[i];
	j = -1;
	while (src[++j])
		if (!ft_cheak_exc(src[j], exc))
			str_arr[i++] = src[j];
	str_arr[i] = NULL;
	return (str_arr);
}

int ft_strarr_len(char **str_arr)
{
	int len;

	len = 0;
	if (!str_arr)
		return (len);
	while (str_arr[len])
		len++;
	return (len);
}

int ft_cheak_exc(char *str, char **exc)
{
	int i;

	if (!str || !exc || !*exc)
		return (0);
	i = -1;
	while (exc[++i])
		if (!ft_strcmp(exc[i], str))
			return (1);
	return (0);
}

int			ft_strcmp_mod(const char *str1, const char *str2, int flag)
{
	size_t	i;

	i = 0;
	while ((unsigned char)str1[i] == (unsigned char)str2[i]
		   && (unsigned char)str1[i])
		i++;
	if (!flag)
		return ((!str1[i]) ? 1 : 0);
	else
		return (i);
}

char			get_type(mode_t mode)
{
	if (S_ISLNK(mode))
		return ('l');
	else if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('?');
}

void print_arr(char **arr)
{
	int i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
		{
			ft_putstr(arr[i]);
			ft_putchar('\n');
		}
	}
}