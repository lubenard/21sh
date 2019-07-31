/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymarcill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:08:51 by ymarcill          #+#    #+#             */
/*   Updated: 2019/07/31 20:02:18 by ymarcill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/sh21.h"
#include "../../include/input.h"

char	*get_inline(char *line, t_hist **lkd_hist)
{
	int		*prompt;
	int		*coord;
	char	*tmp;
	int		ret;
	int		i;
	int		r;
	int		t;
	char	buf[9];
	
	i = 0;
	tmp = ft_strnew(1);
	ft_putstr("\e[s");
	prompt = get_coord(get_cursor_position());
	while (42)
	{
		bzero(buf, sizeof(buf));
		if ((ret = read(0, buf, 8)) == -1 || buf[0] == 'q')
			return (line);
		buf[ret] = '\0';
		coord = get_coord(get_cursor_position());
		if (buf[0] == 3 && !buf[1])
		{
			line = ft_strjoinnf(line, buf);
			return (line);
		}
		if (coord[0] == 1)
			prompt[0] = 1;
		if (buf[0] != '\n' && buf[0] > 31 && buf[0] < 127)
		{
			tmp = test1(i, buf, tmp, &prompt);
			i++;
		}
		r = get_row(0, ft_strlenu(tmp), prompt[1]);
		move_with_arrows(buf, ft_strlenu(tmp), prompt, r);
		manage_tab(buf);
		move_toword(tmp, buf, prompt);
		tmp = ft_copy_paste(tmp, buf, &prompt, &i);
		tmp = move_hist(buf, tmp, &prompt, lkd_hist);
		if (buf[0] == '\n')
		{
			t = r;
			if (coord[0] >= prompt[0] & coord[0] < prompt[0] + r)
				t = coord[0] - prompt[0];
			while (t++ < r)
				ft_putstr("\e[B");
			ft_putstr("\r");
			tmp = ft_strjoinnf(tmp, "\n");
			line = ft_strjoinnf(line, tmp);
			return (line);
		}		
		free(coord);
	}
}

int		*quotes_tab(char *line, int *i, int *quotes)
{
	if (line[*i] == '\'')
	{
		while (line[*i++])
		{
			if (line[*i] == '\'')
			{
				quotes[0] = 1;
				break ;
			}
		}
	}
	else if (line[*i] == '\"')
	{
		while (line[*i++])
		{
			if (line[*i] == '\"')
			{
				quotes[1] = 1;
				break ;
			}
		}
	}
	return (quotes);
}

char	*get_quotes(char *line, t_hist **lkd_hist)
{
	int i;
	int	f;
	int	save;
	int	get;
	char	*tmp;
	int	*quotes;

	i = 0;
	f = 0;
	get = 0;
	tmp = NULL;
	quotes = malloc(sizeof(int) * 2);
	quotes[0] = 2;
	quotes[1] = 2;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (line[i] == '\'')
			{
				quotes[0] = 0;
				while (line[i++])
				{
					if (line[i] == '\'')
					{
						quotes[0] = 1;
						break ;
					}
				}
			}
			else if (line[i] == '\"')
			{
				quotes[1] = 0;
				while (line[i++])
				{
					if (line[i] == '\"')
					{
						quotes[1] = 1;
						break ;
					}
				}
			}
			//quotes = quotes_tab(line, &i, quotes);
			if (quotes[0] == 0 || quotes[1] == 0)
			{
				ft_putstr("\r");
				if (quotes[0] == 0)
				{
					save = 0;
					ft_putstr("quotes> ");
				   	quotes[0] ++;
					quotes[1] = 0;
				}
				else
				{
					save = 1;
					ft_putstr("dquotes> ");
					quotes[1]++;
					quotes[0] = 0;
				}
				line = ft_strjoinnf(line, "\n");
				while ((line = get_inline(line, lkd_hist)))
				{
					while (line[i])
					{
						if (line[i] == '\'')
						{
							quotes[0]++;
							if (save == 0)
							{
								get = i;
								break ;
							}
						}
						if (line[i] == '\"')
						{
							quotes[1]++;
							if (save == 1)
							{
								get = i;
								break ;
							}
						}
						i++;
					}
					if ((save == 0 && quotes[0] % 2 == 0) || (save == 1 && quotes[1] % 2 == 0)
						|| line[ft_strlenu(line) - 1] == 3)
					{
						ft_putchar('\n');
						quotes[0] = 3;
						break ;
					}
					ft_putstr("\n\r");
					line[get] == '\"' ? ft_putstr("dquotes> ") : ft_putstr("quotes> ");
				}
				i = get;
			}
		}
		if (line[ft_strlenu(line) - 1] == 3)
			break;
		quotes[0] = 2;
		quotes[1] = 2;
		i++;
	}
	return (line);
}
