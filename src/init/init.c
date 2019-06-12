/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:00:01 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/30 15:16:06 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				init(t_win **wn, int argc, char **argv)
{
	initwn(wn);
	initsdl(wn);
	init_poly(wn);
	init_rast(wn);
	init_input(wn);
	(*wn)->loading = initload2(wn, "./texture/loading.tga");
	(*wn)->loadingscreen = initload2(wn, "./texture/loadingscreen.tga");
	showload(wn, 10);
	(*wn)->txtnotload = initload2(wn, "./texture/failedload.tga");
	showload(wn, 15);
	(*wn)->load = ft_strdup("./texture/menu/cursor.tga");
	load_texture(*wn, "main", "intro", "cursor");
	load_fonts(*wn);
	parsearg(argc, argv, wn) == 0 ? stop_exec("Parsing error\n", *wn) : 0;
	showload(wn, 30);
	!((*wn)->flag & LQ) ? loadnothread(wn) : loadminimenu(wn);
	(*wn)->load = ft_strdup("./texture/game/hand.tga");
	load_texture(*wn, "game", "hand", "none");
	(*wn)->load = ft_strdup("./texture/Menu_game.tga");
	load_texture(*wn, "game", "menu", "menu");
	(*wn)->load = ft_strdup("./texture/Menu_game_LG.tga");
	load_texture(*wn, "game", "menu", "LG");
	(*wn)->load = ft_strdup("./texture/Menu_game_NG.tga");
	load_texture(*wn, "game", "menu", "NG");
	initplayer(wn);
	initskybox(wn);
	return (1);
}
