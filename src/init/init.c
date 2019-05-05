/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:00:01 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/05 16:47:03 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		loadminimenu(t_win **wn)
{
	(*wn)->tmp[0] = ft_strdup("./texture/intro/menu/test0059.tga");
	load_texture(*wn, "main", "intro", "60");
	(*wn)->tmp[1] = ft_strdup("./texture/intro/edit/test0119.tga");
	load_texture(*wn, "editor", "intro", "119");
}

static void		loadmenu(t_win **wn)
{
	t_thread	thread[5];
	int			i;
	int			load;

	i = 0;
	load = 0;
	(*wn)->turn = 4;
	while (i < 5)
	{
		thread[i].wn = *wn;
		thread[i].value = i;
		if (i < 4)
			pthread_create(&thread[i].thd, NULL, load_intro, (void *)&(thread[i]));
		else
			pthread_create(&thread[i].thd, NULL, loadingthread, (void *)&(thread[i]));
		i++;
	}
	pthread_join((thread[0].thd), NULL);
	pthread_join((thread[1].thd), NULL);
	pthread_join((thread[2].thd), NULL);
	pthread_join((thread[3].thd), NULL);
	(*wn)->turn = 0;
	pthread_join((thread[4].thd), NULL);
}

void			showload(t_win **wn, int load)
{
	SDL_Rect	loading;

	loading.x = 40;
	loading.y = (YSCREEN / 4) * 3.6;
	loading.w = (load * XSCREEN / 100) - 80;
	loading.h = 30;
	SDL_RenderCopy((*wn)->rend, (*wn)->loadingscreen, NULL, NULL);
	SDL_RenderCopy((*wn)->rend, (*wn)->loading, NULL, &loading);
	SDL_RenderPresent((*wn)->rend);
}

int				init(t_win **wn, int argc, char **argv)
{
	SDL_Event	ev;

	initwn(wn);
	initsdl(wn);
	init_input(wn);
	initplayer(wn);
	SDL_PollEvent(&ev);
	SDL_PollEvent(&ev);
	(*wn)->loading = initload2(wn, "./texture/loading.tga");
	(*wn)->loadingscreen = initload2(wn, "./texture/loadingscreen.tga");
	showload(wn, 10);
	(*wn)->txtnotload = initload2(wn, "./texture/failedload.tga");
	showload(wn, 15);
	(*wn)->tmp[0] = ft_strdup("./texture/menu/cursor.tga");
	load_texture(*wn, "main", "intro", "cursor");
	parsearg(argc, argv, wn) == 0 ? stop_exec("Parsing error\n", *wn) : 0;
	showload(wn, 30);
	(*wn)->quality == 0 ? loadmenu(wn) : loadminimenu(wn);
	initskybox(wn);
	return (1);
}
