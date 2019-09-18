/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_last_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:12:43 by ymarcill          #+#    #+#             */
/*   Updated: 2019/09/18 17:42:06 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void	go_last_char(int *mainindex, int i, int *prompt)
{
	int x;

	x = *mainindex;
	if (i == 0 || x >= i)
		return ;
	while (x < i)
	{
		right_arrow(mainindex, i, prompt);
		x++;
	}
}
