/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:00:48 by ymarcill          #+#    #+#             */
/*   Updated: 2019/10/21 15:40:23 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

char	**malloc_if(t_coord *c, char **q_tab, char *line, char a)
{
	if (c->i > 0 && line[c->i - 1] != a)
	{
		q_tab[c->x][c->y] = '\0';
		c->x += 1;
		q_tab[c->x] = malloc(sizeof(char) * (ft_strlen(line) + 3));
		return (q_tab);
	}
	return (q_tab);
}

char	**esp_semicolon(t_coord *c, char **q_tab, char *line)
{
	if (line[c->i] == ' ')
	{
		q_tab = malloc_if(c, q_tab, line, ';');
		c->y = -1;
		while (line[c->i] == ' ')
			c->i++;
		c->i--;
	}
	else if (line[c->i] == ';')
	{
		q_tab = malloc_if(c, q_tab, line, ' ');
		c->y = 0;
		while (line[c->i] == ';')
			q_tab[c->x][c->y++] = line[c->i++];
		q_tab[c->x][c->y] = '\0';
		c->y = -1;
		c->x++;
		c->i--;
		q_tab[c->x] = malloc(sizeof(char) * (ft_strlenu(line) + 3));
	}
	return (q_tab);
}

char	**init_p(t_coord *c, char **line, char **q_tab)
{
	char	*tmp;

	tmp = ft_strtrim(*line);
	*line = ft_strdup(tmp);
	if (!(q_tab = malloc(sizeof(char *) *
	(ft_occur(*line, ' ') + ft_occur(*line, ';') + 3))))
		return (NULL);
	if (!(q_tab[c->x] = malloc(sizeof(char) * (ft_strlen(*line) + 4))))
		return (NULL);
	free(tmp);
	return (q_tab);
}

char	**fill_with_quotes(t_coord *c, char *line, char **q_tab)
{
	c->c = line[c->i];
	q_tab[c->x][c->y++] = line[c->i++];
	while (line[c->i] && line[c->i] != c->c)
		q_tab[c->x][c->y++] = line[c->i++];
	q_tab[c->x][c->y] = line[c->i];
	return (q_tab);
}

char	**main_lexer(char *line)
{
	char	**q_tab;
	t_coord	c;

	q_tab = NULL;
	ft_bzero(&c, sizeof(c));
	if (!line || (q_tab = init_p(&c, &line, q_tab)) == NULL)
		return (NULL);
	while (line && line[c.i])
	{
		if (line[c.i] == ' ' || line[c.i] == ';')
			q_tab = esp_semicolon(&c, q_tab, line);
		else if (line[c.i] == '\"' || line[c.i] == '\'')
			q_tab = fill_with_quotes(&c, line, q_tab);
		else
			q_tab[c.x][c.y] = line[c.i];
		c.y++;
		c.i++;
	}
	q_tab[c.x][c.y] = '\0';
	q_tab[c.x + 1] = NULL;
	free(line);
	return (q_tab);
}
