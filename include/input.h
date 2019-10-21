/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:03:32 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/21 15:04:30 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "sh21.h"
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <sys/ioctl.h>

/*
** Termcaps structs
*/
typedef	struct		s_coord
{
	int				*coord;
	int				q_state;
	int				i;
	int				j;
	int				k;
	int				r;
	int				t;
	int				x;
	int				y;
	int				c;
	int				cmax;
	int				*prompt;
	int				*pos;
	int				ret;
	char			*buf;
	char			*tmpy;
	char			*tmpx;
	char			*line;
	char			*tmp;
	char			**tmp1;
	char			**tmp2;
	int				mainindex;
}					t_coord;

typedef	struct		s_getprompt_pos
{
	int				y;
	int				x;
	int				c;
	int				r;
	int				tmp;
	int				p;
	int				*coord;
	int				cmax;
}					t_getprompt_pos;

typedef	struct		s_w
{
	int				ws_col;
	int				ws_row;
}					t_w;

struct s_w			w;
char				*g_mainline;

/*
** Line edition
*/

void				freefornorme(int i, t_coord *c, char **arg_tab);
int					*tab_malloc(int *pos, int i);
void				move_hist(t_coord *c, t_hustru *big_struc);
int					i_is(int *prompt, int *coord);
void				clean_for_quotes(int *mainindex, int *prompt, int *pos);
char				*suppr_lastchar(char *line);
char				*do_i_have_to_do_it_quote(char *line, int *i,
					t_hustru *big_struc, char **tmp);
char				*get_inline(char *line, t_hustru *big_struc);
int					init(int *mainindex, int **prompt, t_coord *c);
char				*read_quit(int **prompt, int **pos, char d);
int					entry(int r, t_hustru *big_struc, int *coord, int *prompt);
char				*heredoc(t_hustru *big_struc, char **tab_line);
int					*ft_print_line(char *tmp, int **pos, int *mainindex,
	int **prompt);
int					*last_line_col(int *coord, int **prompt, char c);
int					singleton(int comp);
void				signalhandler(int signal);
void				ft_copy_paste(char *buf, int **prompt,
	int *mainindex, int **pos);
char				*copy_until(char *str, int i);
int					get_nb_line_quote(char *str);
void				left_arrow(int *mainindex, int *pos);
void				move_toword(char *buf, int *prompt, int *mainindex,
	int *pos);
int					get_row(int r, int i, int pc);
void				clean(int *prompt, int *mainindex, int *pos);
void				delete_c(int **pos, int *prompt, int *mainindex, int w);
int					go_last_row(int tmp, int maxc, int r);
void				go_first_char(int *mainindex, int *prompt, int *pos);
void				right_arrow(int *mainindex, int i, int *prompt);
void				go_last_char(int *mainindex, int i, int *prompt);
void				move_with_arrows(char *buf, int *prompt,
	int *mainindex, int *pos);
void				print_char(int *mainindex, char *buf,
	int **prompt, int **pos);
int					control_c(char *buf, int *prompt, int *coord, int r);
int					main_core(char *buf, int **prompt,
	int **pos, int *mainindex);
int					ft_read_1(t_hustru *big_struc);
int					*get_coord(char *buf);
char				*get_cursor_position();
int					set_none_canon_mode(int fd);
int					reset_shell_attr(int fd);
#endif
