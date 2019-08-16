/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:03:32 by lubenard          #+#    #+#             */
/*   Updated: 2019/08/16 12:39:50 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "struc.h"
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <signal.h>
/*
** Termcaps structs
*/
typedef	struct		s_coord
{
	int				*coord;
	int				i;
	int				j;
	int				k;
	char			*tmpy;
	char			*tmpx;
}					t_coord;

typedef	struct		s_get_prompt_pos
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

/*
** Line edition
*/
void				left_arrow(int *prompt, int i);
void				move_toword(char *line, char *buf, int *prompt);
int					get_row(int r, int i, int pc);
void				clean(int i, int *prompt, int r);
char				*delete_c(int r, int *prompt, char *line, int *sizel);
int					go_last_row(int tmp, int maxc, int r);
void				go_first_char(int *prompt, int i, int r);
void				right_arrow(int i, int *prompt);
void				go_last_char(int i, int *prompt);
void				move_with_arrows(char *buf, int i, int *prompt, int r);
char				*get_cursor_position();
int					*get_coord(char *buf);
int					set_none_canon_mode(int fd);
int					reset_shell_attr(int fd);
void				manage_tab(char *buf);
char				*ft_copy_paste(char *line, char *buf, int **prompt, int *i);
/*
** History
*/
char				*move_hist(char *buf, char *line, int **prompt,
	t_hustru *big_struc);
void				save_command(t_hustru *big_struc, char *command, int save);
char				*get_quotes(char *line, t_hustru *big_struc);
/*
** Weird function
*/
char				*test1(int index, char *buf, char *line, int **prompt);
#endif
