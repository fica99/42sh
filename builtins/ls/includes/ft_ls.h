/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 13:00:16 by aashara-          #+#    #+#             */
/*   Updated: 2019/03/15 14:41:04 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>

# define NAME_SATTR 300
# define SIZE_VATTR 300
# define BUFFOUT 100000
# define SIZELINE 300

typedef struct	s_dir
{
	char			*name;
	char			*path;
	struct s_dir	*f_names;
	struct s_dir	*next;
	struct s_dir	*pre;
	short int		total;
	uint16_t		len;
	uint8_t			level;
	ushort			flags;
	off_t			size;
	time_t			time_mod;
	time_t			a_time;
	nlink_t			nlink;
	mode_t			mode;
	uid_t			uid;
	gid_t			gid;
	dev_t			st_rdev;
}				t_dir;

typedef struct	s_prt_cols
{
	uint8_t	max;
	ushort	cnt_elems;
	ushort	cols;
	ushort	rows;
	ushort	cur_row;
	ushort	cur_col;
}				t_prt_cols;

typedef struct	s_prt_rows
{
	unsigned int	total;
	u_int8_t		max_nlink;
	u_int8_t		max_size;
	ushort			max_uid;
	ushort			max_gid;
	ushort			max_minor;
	ushort			max_major;
	time_t			cur_time;
}				t_prt_rows;

typedef struct	s_attr
{
	char		list[NAME_SATTR];
	ssize_t		size_list;
}				t_attr;

t_dir			*opening(int argc, char **argv);
ushort			read_flags(char **argv, uint8_t *i);
ushort			add_flag(ushort flags, char flag);
ushort			add_flag2(ushort flags, char flag);
void			print_usage(char c);
char			**check_dir(int argc, char **argv, uint8_t i);
uint8_t			double_arr_len(char **d_names);
t_dir			*make_list(char **arr, uint8_t *i, ushort flags);
t_dir			*check_exist(t_dir *dir, t_dir **head, ushort flags);
t_dir			*ft_list(ushort flags);
char			*check_name(char *name);
t_dir			*get_data(t_dir **request);
void			check_err(char *name, char *path);
void			delete_from_list(t_dir **dir, t_dir **head);
void			free_list(t_dir **request);
char			get_type(mode_t mode);
t_dir			*make_file_list(t_dir *dir, t_dir **head_files, t_dir **head);
t_dir			*make_dir_list(t_dir **head, t_dir *dir);
t_dir			*print_files(t_dir *head, t_dir *head_files);
void			print(t_dir *request);
t_dir			*sorting(t_dir *request, ushort flags);
ushort			is_flags(ushort flags, char flag);
ushort			is_flags2(ushort flags, char flag);
t_dir			*sort_one_list(t_dir *list, uint8_t (fun)(t_dir*));
t_dir			*swap_list(t_dir *cur, t_dir *next);
uint8_t			list_sort(t_dir *list);
uint8_t			list_f_d(t_dir *list);
uint8_t			list_rev(t_dir *list);
uint8_t			list_time_mod(t_dir *list);
uint8_t			list_time_a(t_dir *list);
uint8_t			list_size(t_dir *list);
void			print_cols(t_dir *request, ushort ws_col, ushort flags,
				uint8_t j);
t_prt_cols		get_print_prm_c(t_dir *request, ushort ws_col);
void			get_cols_rows(t_prt_cols *pprm, ushort ws_col);
void			print_line(t_dir *request, t_prt_cols pprm, char *buf,
				u_int16_t *i);
u_int8_t		check_buf(char *buf, u_int8_t i);
t_dir			*next_elem(t_dir *request, t_prt_cols pprm);
void			print_rows(t_dir *request, ushort ws_cols, ushort flags,
				uint8_t g);
t_prt_rows		get_print_prm_r(t_dir *request);
void			get_data_max(t_prt_rows *pprm, t_dir *request);
uint8_t			get_bit(int nlink);
int				print_line_rows(t_dir *request, ushort flags, t_prt_rows pprm,
				char *buf);
int				print_mode_bits(mode_t mode, char *buf);
void			cheak_usr(mode_t mode, char *str);
void			cheak_grp(mode_t mode, char *str);
void			cheak_oth(mode_t mode, char *str);
int				print_label_attr(t_dir *request, char *buf, t_attr *attr);
int				print_number(long int num, long int max, char *buf, uint8_t j);
void			putnum(long int n, int i, char *buf);
int				print_gu_ids(t_dir *request, t_prt_rows pprm, ushort flags,
				char *buf);
int				putuid(char *uid, ushort max, char *buf);
int				putgid(char *gid, ushort max, char *buf);
int				print_time(time_t time, time_t cur_time, char *buf);
int				print_name(t_dir *request, char *buf);
int				print_link(t_dir *request, char *buf);
int				print_attr_full(t_dir *request, ushort flags, char *buf,
				t_attr attr);
void			print_all_rek(t_dir *request, ushort size,
				void (f)(t_dir *, ushort, ushort, uint8_t), ushort flags);
t_dir			*reading(t_dir *list);
DIR				*check_open(char *path, char *name);
void			data_init(struct dirent *file, t_dir *list, t_dir **d,
				t_dir **head);
char			*check_path(char *path, char *name);
void			check_close(int nb);
void			print_path(t_dir *request, ushort flags);
void			free_all_list(t_dir *request);

#endif
