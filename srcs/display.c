/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:40:41 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/15 19:22:41 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	display_prompt(char *username, char *curr_dir, int mode)
{
	if (mode == 1)
		ft_putstr("\033[31m");
	ft_putstr(username);
	if (mode == 1)
		ft_putstr("\033[0m");
	ft_putstr(" - ");
	if (mode == 1)
		ft_putstr("\033[36m");
	ft_putstr(curr_dir);
	if (mode == 1)
		ft_putstr("\033[0m");
	ft_putstr(">  ");
}
