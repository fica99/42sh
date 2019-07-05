/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocom.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 20:46:44 by ggrimes           #+#    #+#             */
/*   Updated: 2019/07/05 19:14:40 by aashara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef AUTOCOM_H
# define AUTOCOM_H

# include "libft.h"
# include "ftstr.h"
# include "ftdir.h"
# include "ftdar.h"
# define SUCCESS 1
# define FUILURE 0
# define CHECK(val) if (!val) return (0)
# define CHECKV(val) if (!val) return

typedef struct  s_autocom
{
    int     max_len;
    int     opts_size;
    int     cols;
    int     rows;
    int     index;
    int     index_print;
    char    *start;
    char    *path;
    int     prog;
    int     first;
    int     scrolling;
    int     delta_y;
    int     opts_print;
    int     fixed_opts_print;
    char    **options;
}               t_autocom;

//ac_autocom.c
void    autocomplite(t_buff *buff, t_cord *cord);
void	ac_complement_line(t_buff *buffer, t_cord *cord, t_autocom *ac);
int     ac_rewrite_str(char *dest, char *src);
// ac_parse
char	**ac_parse_cmd_line(char *line, t_autocom *ac);
char    *ac_parse_path(char *buffer);
char    *ac_parse_arg(char *dirpath);
char	*ac_tilda(char *dirpath);
//ac_options
char	**ac_get_options(char *start, short is_prog, t_autocom *ac);
char	**ac_options_selection(char *arg, char **options);
char	**ac_newselection(char **options, char *search_arg);
char	**ac_prog_options(void);
char	**ac_dir_options(char *dirpath, t_autocom *ac);
char	**ac_add_options(char *path, char **options);
//ac_move_cursor
void	move_cursor_left(short count);
void	move_cursor_down(short count);
void	move_cursor_right(short count);
void	move_cursor_up(short count);
void	move_cursor_pos(short x, short y);
//ac_print_params
void    ac_get_rows_cols_count(char **options, t_cord *cord, t_autocom *ac);
void    ac_conversion_scrolling(int opt_rows, t_cord *cord, t_autocom *ac);
int     ac_get_max_word_len(char **list);
int     ac_get_rows(int count_options, int cols);
void	ac_set_null_params(t_autocom *ac);
//ac_print.c
void	ac_print_options(t_autocom *ac, t_cord *cord);
void	ac_select_option(char *option);
void	ac_return_carriage(short count);
void	ac_clear_options(void);
//ac_recalc_index.c
void    ac_index_tracking(t_autocom *ac);
void    ac_opts_tracking(t_autocom *ac);
# endif
