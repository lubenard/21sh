/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 21:17:15 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 18:02:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		get_nb_line_quote(char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	while (str[i++])
	{
		if (str[i] == '\n')
			nb++;
	}
	if (nb == 0)
		return (nb);
	return (nb);
}

void	clean_for_quotes(int *mainindex, int *prompt, int *pos)
{
	int i;
	int gnbl;

	i = 0;
	gnbl = get_nb_line_quote(g_mainline) +
		get_row(0, ft_strlenu(g_mainline), prompt[1]);
	go_first_char(mainindex, prompt, pos);
	ft_putstr_fd("\e[0K", 0);
	while (i < gnbl)
	{
		ft_putstr_fd("\e[B", 0);
		ft_putstr_fd("\e[2K", 0);
		i++;
	}
	while (i-- > 0)
		ft_putstr_fd("\e[A", 0);
}
