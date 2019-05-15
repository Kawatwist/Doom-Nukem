/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:00:01 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/15 10:37:32 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				init(t_win **wn, int argc, char **argv)
{
	printf("Init\n");
	initwn(wn);
	printf("Init Wn\n");
	initsdl(wn);
	printf("Init SDL\n");
	init_poly(wn);
	printf("Init Poly\n");
	init_input(wn);
	printf("Init Input\n");
	(*wn)->loading = initload2(wn, "./texture/loading.tga");
	(*wn)->loadingscreen = initload2(wn, "./texture/loadingscreen.tga");
	printf("Init Load\n");
	showload(wn, 10);
	printf("Init Draw\n");
	(*wn)->txtnotload = initload2(wn, "./texture/failedload.tga");
	printf("Init Load v2\n");
	showload(wn, 15);
	printf("Init Draw v2\n");
	(*wn)->load = ft_strdup("./texture/menu/cursor.tga");
	load_texture(*wn, "main", "intro", "cursor");
	printf("Init Load v3\n");
	parsearg(argc, argv, wn) == 0 ? stop_exec("Parsing error\n", *wn) : 0;
	printf("Init Parse\n");
	showload(wn, 30);
	printf("Init Draw v4\n");
	(*wn)->quality == 0 ? loadnothread(wn) : loadminimenu(wn);
	printf("Init Load Menu\n");
	(*wn)->load = ft_strdup("./texture/game/hand.tga");
	load_texture(*wn, "game", "hand", "none");
	printf("Init Load Game\n");
	initplayer(wn);
	printf("Init Player\n");
	initskybox(wn);
	printf("Init End\n");
	return (1);
}
