/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 12:13:17 by lubenard          #+#    #+#             */
/*   Updated: 2019/06/17 12:13:19 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	get_quotes(char *line)
{
	int i;
	int	sq;
	int	dq;
	char buf[9];
	int		ret;

	(void)ret;
	(void)buf;
	i = 0;
	sq = 0;
	dq = 1;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			while (line[i])
			{
				if (line[i] == '\'')
					sq = 1;
			}
			if (sq == 0)
			{
				ft_putstr("\n\r");
				ft_putstr("quotes>");
				//if ((ret = read
			}
		}
	}
}
