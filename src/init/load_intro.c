/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_intro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 09:27:37 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/23 18:41:27 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void		load_main(t_win **wn)
{
	char	*name;
	int		img;

	name = ft_strdup("texture/intro/menu/test0001.tga");
	img = 1;
	while (img <= 59)
	{
		(*wn)->tmp[0] = name;
		load_texture(*wn, "main", "intro", ft_itoa(img));
		name = changename(name, 23);
		img++;
		(*wn)->load += 1;
	}
}

static void		load_option(t_win **wn)
{
	char	*name;
	int		img;

	name = ft_strdup("texture/intro/option/test0120.tga");
	img = 120;
	while (img <= 179)
	{
		(*wn)->tmp[2] = name;
		load_texture(*wn, "option", "intro", ft_itoa(img));
		name = changename(name, 25);
		img++;
		(*wn)->load += 1;
	}
}

static void		load_edit(t_win **wn)
{
	char	*name;
	int		img;

	name = ft_strdup("texture/intro/edit/test0060.tga");
	img = 60;
	while (img <= 119)
	{
		(*wn)->tmp[1] = name;
		load_texture(*wn, "editor", "intro", ft_itoa(img));
		name = changename(name, 23);
		img++;
		(*wn)->load += 1;
	}
}

static void		load_game(t_win **wn)
{
	char	*name;
	int		img;

	name = ft_strdup("texture/intro/game/test0060.tga");
	img = 60;
	while (img <= 119)
	{
		(*wn)->tmp[3] = name;
		load_texture(*wn, "game", "intro", ft_itoa(img));
		name = changename(name, 23);
		img++;
		(*wn)->load += 1;
	}
}

void			*load_intro(void *params)
{
	t_thread	*thd;
	t_win		*wn;
	int			value;

	thd = (t_thread *)params;
	wn = (t_win *)thd->wn;
	value = (int)thd->value;
	value == 0 ? load_main(&wn) : 0;
	value == 1 ? load_option(&wn) : 0;
	value == 2 ? load_edit(&wn) : 0;
	value == 3 ? load_game(&wn) : 0;
	pthread_kill(thd->thd, 0);
	pthread_exit(thd->thd);
	pthread_exit(NULL);
	return (0);
}
