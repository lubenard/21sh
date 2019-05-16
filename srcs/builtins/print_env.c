/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:15:46 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/16 15:56:58 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

void	print_env(t_env *lkd_env)
{
	while (lkd_env)
	{
		if (ft_strcmp(lkd_env->env_line, ""))
		{
			ft_putstr(lkd_env->env_line);
			ft_putchar('\n');
		}
		lkd_env = lkd_env->next;
	}
}
