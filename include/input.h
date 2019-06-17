/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:03:32 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/14 16:34:43 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "sh21.h"
# include <termios.h>
# include <term.h>
# include <curses.h>

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

typedef	struct		get_prompt_pos
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
int					ft_strlenu(char *str);
int					go_last_row(int tmp, int maxc, int r);
void				go_first_char(int *prompt, int i, int r);
void				right_arrow(int i, int *prompt);
void				go_last_char(int i, int *prompt);
void				move_with_arrows(char *buf, int i, int *prompt, int r);
char				*get_cursor_position();
int					*get_coord(char *buf);
int					set_none_canon_mode(int fd);
int					reset_shell_attr(int fd);
int					ft_read_1(const int fd, char **line);

#endif