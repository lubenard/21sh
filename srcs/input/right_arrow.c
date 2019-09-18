/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:16:24 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 17:58:53 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	right_arrow(int *mainindex, int i, int *prompt)
{
	t_getprompt_pos gpp;

	if (!(gpp.coord = get_coord(get_cursor_position()))
		|| *mainindex > ft_strlenu(g_mainline))
		return ;
	gpp.r = get_row(0, i, prompt[1]);
	gpp.r += get_nb_line_quote(g_mainline);
	if (g_mainline[*mainindex] == '\n' ||
		(g_mainline[*mainindex] && gpp.coord[1] == w.ws_col))
	{
		ft_putstr_fd("\e[E", 0);
		*mainindex += 1;
	}
	else if (g_mainline[*mainindex])
	{
		ft_putstr_fd("\e[C", 0);
		*mainindex += 1;
	}
	free(gpp.coord);
}
