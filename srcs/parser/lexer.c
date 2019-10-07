/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubenard <lubenard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 01:36:05 by lubenard          #+#    #+#             */
/*   Updated: 2019/10/08 01:37:04 by lubenard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

char	**malloc_if(t_coord *c, char **q_tab, char *line, char a)
{
	if (c->i > 0 && line[c->i - 1] != a)
	{
		q_tab[c->x][c->y] = '\0';
		c->x += 1;
		q_tab[c->x] = malloc(sizeof(char) * (ft_strlen(line) + 2));
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
		q_tab[c->x] = malloc(sizeof(char) * (ft_strlenu(line) + 2));
	}
	return (q_tab);
}

char	**init_p(t_coord *c, char **line, char **q_tab)
{
	char	*tmp;

	tmp = ft_strtrim(*line);
	free(*line);
	*line = ft_strdup(tmp);
	q_tab = malloc(sizeof(char *) * (ft_occur(*line, ' ') + ft_occur(*line, ';') + 2));
	q_tab[c->x] = malloc(sizeof(char) * (ft_strlen(*line) + 2));
	free(tmp);
	return (q_tab);
}

char	**parse_quote(char *line)
{
	char	**q_tab;
	t_coord	c;

	ft_bzero(&c, sizeof(c));
	q_tab = init_p(&c, &line, q_tab);
	while (line[c.i])
	{
		if (line[c.i] == ' ' || line[c.i]  == ';')
			q_tab = esp_semicolon(&c, q_tab, line);
		else if (line[c.i] == '\"' || line[c.i] == '\'')
		{
			c.c = line[c.i];
			q_tab[c.x][c.y++] = line[c.i++];
			while (line[c.i] && line[c.i] != c.c)
				q_tab[c.x][c.y++] = line[c.i++];
			q_tab[c.x][c.y] = line[c.i];
		}
		else
			q_tab[c.x][c.y] = line[c.i];
		c.y++;
		c.i++;
	}
	q_tab[c.x][c.y] = '\0';
	q_tab[c.x + 1] = NULL;
	return (q_tab);
}

int		main(void)
{
	char	*line;
	char	**q_tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_strdup("\"lol ;  \"     ; ;        a;a\"lo\"  ");
	q_tab = parse_quote(line);
	while (q_tab[i])
	{
		while (q_tab[i][j])
		{
			ft_putchar(q_tab[i][j]);
			j++;
		}
		ft_putchar('\n');
		j = 0;
		i++;
	}
	return (0);
}
