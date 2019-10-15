/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 15:10:40 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/12 18:51:38 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

void		which_redir(t_coord *c)
{
	if (c->c == '&')
	{
		c->k = '<';
		c->r = '>';
	}
	else
	{
		c->k = '&';
		c->r = c->c == '<' ? '>' : '<';
	}
}

char		**if_redir(t_coord *c, char **tmp, char *str)
{
	if (c->i > 0)
	{
		tmp[c->x][c->y] = '\0';
		c->x++;
		c->y = 0;
		tmp[c->x] = ft_strnew(ft_strlen(str));
	}
	c->c = str[c->i];
	which_redir(c);
	while (str[c->i] == c->c || str[c->i] == c->k || str[c->i] == c->r)
		tmp[c->x][c->y++] = str[c->i++];
	tmp[c->x][c->y] = '\0';
	c->y = -1;
	c->x++;
	tmp[c->x] = ft_strnew(ft_strlen(str));
	c->i--;
	return (tmp);
}

char		**init_r(char **tmp, t_coord *c, char *str)
{
	if (!(tmp = malloc(sizeof(char *) * (1000 + 1))))
		return (NULL);
	if (!(tmp[c->x] = malloc(sizeof(char*) * ft_strlen(str) + 3)))
		return (NULL);
	return (tmp);
}

char		**lexer_redir(char *str)
{
	t_coord	c;
	char	**tmp;

	ft_bzero(&c, sizeof(c));
	tmp = init_r(tmp, &c, str);
	while (str && str[c.i])
	{
		if (str[c.i] == '>' || str[c.i] == '<' || str[c.i] == '&')
			tmp = if_redir(&c, tmp, str);	
		else if (str[c.i] == '\'' || str[c.i] == '\"')
		{
			c.c = str[c.i];
			tmp[c.x][c.y++] = str[c.i++];
			while (str[c.i] && str[c.i] != c.c)
				tmp[c.x][c.y++] = str[c.i++];
			tmp[c.x][c.y] = str[c.i];
		}
		else
			tmp[c.x][c.y] = str[c.i];
		c.y++;
		c.i++;
	}
	tmp[c.x][c.y] = '\0';
	tmp[c.x + 1] = NULL;
	return (tmp);
}
