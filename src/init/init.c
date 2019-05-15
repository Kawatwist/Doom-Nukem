/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:00:01 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/15 07:34:55 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				init(t_win **wn, int argc, char **argv)
{
	//SDL_Event	ev;
	(void)argc;
	(void)argv;

	initwn(wn);
	initsdl(wn);
	init_input(wn);
	initplayer(wn);
//	SDL_PollEvent(&ev);
//	SDL_PollEvent(&ev);
//	(*wn)->loading = initload2(wn, "./texture/loading.tga");
//	(*wn)->loadingscreen = initload2(wn, "./texture/loadingscreen.tga");
//	showload(wn, 10);
//	(*wn)->txtnotload = initload2(wn, "./texture/failedload.tga");
//	showload(wn, 15);
//	(*wn)->load = ft_strdup("./texture/menu/cursor.tga");
//	load_texture(*wn, "main", "intro", "cursor");
//	parsearg(argc, argv, wn) == 0 ? stop_exec("Parsing error\n", *wn) : 0;
//	showload(wn, 30);
//	(*wn)->quality == 0 ? loadnothread(wn) : loadminimenu(wn);
//	initskybox(wn);
	return (1);
}
