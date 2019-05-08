/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nothread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:59:14 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/08 16:17:29 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	load_option(t_win **wn)
{
	char	*name;
	int		img;

	name = ft_strdup("texture/intro/option/test0120.tga");
	img = 120;
	while (img <= 179)
	{
		(*wn)->load = name;
		load_texture(*wn, "option", "intro", ft_itoa(img));
		name = changename(name, 25);
		img++;
	}
	free(name);
}

static void	load_editor(t_win **wn)
{
	char	*name;
	int		img;

	name = ft_strdup("texture/intro/edit/test0060.tga");
	img = 60;
	while (img <= 119)
	{
		(*wn)->load = name;
		load_texture(*wn, "editor", "intro", ft_itoa(img));
		name = changename(name, 23);
		img++;
	}
	free(name);
}

static void	load_game(t_win **wn)
{
	char	*name;
	int		img;

	name = ft_strdup("texture/intro/game/test0060.tga");
	img = 60;
	while (img <= 119)
	{
		(*wn)->load = name;
		load_texture(*wn, "game", "intro", ft_itoa(img));
		name = changename(name, 23);
		img++;
	}
	free(name);
}

static void	load_menu(t_win **wn)
{
	char	*name;
	int		img;

	name = ft_strdup("texture/intro/menu/test0001.tga");
	img = 1;
	while (img <= 59)
	{
		(*wn)->load = name;
		load_texture(*wn, "main", "intro", ft_itoa(img));
		name = changename(name, 23);
		img++;
	}
	free(name);
}

void		loadnothread(t_win **wn)
{
	load_menu(wn);
	showload(wn, 50);
	load_game(wn);
	showload(wn, 70);
	load_editor(wn);
	showload(wn, 80);
	load_option(wn);
	showload(wn, 100);
}
