/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:00:35 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/21 18:42:22 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int			is_fd_redir(t_coord *c, char **tmp)
{
	int	i;

	i = 0;
	while (tmp[c->x][i])
	{
		if (ft_isdigit(tmp[c->x][i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char		**if_fd_redir_end(t_coord *c, char *str, char **tmp)
{
	if (tmp[c->x][c->y - 1] == '&')
	{
		c->k = c->i;
		while (str[c->k])
		{
			ft_putchar(str[c->k]);
			if (ft_isdigit(str[c->k]) == 0 && str[c->k] != '-')
			{
				c->k = 0;
				break ;
			}
			c->k++;
		}
		if (c->k)
		{
			while (str[c->i])
				tmp[c->x][c->y++] = str[c->i++];
			tmp[c->x][c->y] = '\0';
		}
	}
	return (tmp);
}

char		**if_redir(t_coord *c, char **tmp, char *str)
{
	tmp[c->x][c->y] = '\0';
	if (c->i > 0 && is_fd_redir(c, tmp) == 0)
	{
		c->x++;
		c->y = 0;
		tmp[c->x] = ft_strnew(ft_strlen(str));
	}
	c->c = str[c->i];
	which_redir(c);
	while (str[c->i] == c->c || str[c->i] == c->k || str[c->i] == c->r)
		tmp[c->x][c->y++] = str[c->i++];
	tmp[c->x][c->y] = '\0';
	tmp = if_fd_redir_end(c, str, tmp);
	if (str[c->i])
	{
		c->y = -1;
		c->x++;
		tmp[c->x] = ft_strnew(ft_strlen(str));
	}
	c->i--;
	return (tmp);
}

char		*init_r(char ***tmp, t_coord *c, char *str)
{
	if (!str || !(*tmp = malloc(sizeof(char *) * (1000 + 1))))
		return (NULL);
	if (!((*tmp)[c->x] = malloc(sizeof(char*) * (ft_strlen(str) + 3))))
		return (NULL);
	return ("OK");
}

char		**lexer_redir(char *str)
{
	t_coord	c;
	char	**tmp;

	ft_bzero(&c, sizeof(c));
	if (!init_r(&tmp, &c, str))
		return (NULL);
	while (str && str[c.i])
	{
		if (str[c.i] == '>' || str[c.i] == '<' || str[c.i] == '&')
			tmp = if_redir(&c, tmp, str);
		else if (str[c.i] == '\'' || str[c.i] == '\"')
			tmp = fill_with_quotes(&c, str, tmp);
		else
			tmp[c.x][c.y] = str[c.i];
		c.y++;
		c.i++;
	}
	tmp[c.x][c.y] = '\0';
	tmp[c.x + 1] = NULL;
	return (tmp);
}
