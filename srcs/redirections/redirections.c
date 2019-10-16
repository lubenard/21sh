/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:57:01 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/16 19:38:49 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh21.h>

int		redirections_w_fork(t_hustru *big_struc, char **lexed_command)
{
	//int		i = 0; //used for debug online

	/*while (lexed_command[i])
		printf("[Parsed redir] |%s|\n", lexed_command[i++]);*/
	return (launch_arrow_w_fork(big_struc, lexed_command));
}

int		redirections(t_hustru *big_struc, char **lexed_command)
{
	//int		i = 0; //used for debug online

	/*while (lexed_command[i])
		printf("[Parsed redir] |%s|\n", lexed_command[i++]);*/
	return (launch_arrow(big_struc, lexed_command));
}
