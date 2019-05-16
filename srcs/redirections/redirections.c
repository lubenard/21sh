/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/05/16 18:27:45 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh21.h"

void	double_arrow_left(char *command)
{
	(void)command;
}

void	double_arrow_right(char *command)
{
	/*
	** append to file or create it
	*/
	(void)command;
}

void	simple_arrow_left(char *command)
{
	(void)command;
}

void	simple_arrow_right(char *command)
{
	/*
	** create the file or crush it
	*/
	(void)command;
}

void	redirections(char *command)
{
	(void)command;
	if (ft_strstr(command, "<<"))
		double_arrow_left(command);
	else if (ft_strstr(command, ">>"))
		double_arrow_right(command);
	else if (ft_strchr(command, '<'))
		simple_arrow_left(command);
	else if (ft_strchr(command, '>'))
		simple_arrow_right(command);
}
