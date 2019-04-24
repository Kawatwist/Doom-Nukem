/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:00:01 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/23 18:36:46 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		loadminimenu(t_win **wn)
{
	(*wn)->tmp[0] = ft_strdup("./texture/intro/menu/test0059.tga");
	load_texture(*wn, "main", "intro", "60");
}

// static void		*loadingthread(void *param)
// {
// 	t_win	**wn;
// 	int		value;
// 	int		i;

// 	i = 0;
// 	wn = &((t_thread *)param)->wn;
// 	value = 30;
// 	while (TRUE)
// 	{
// 		showload(wn, value);
// 		value = ((*wn)->load * 70 / 270) + 30;
// 		i++;
// 		if ((*wn)->turn == 0)
// 			break ;
// 	}
// 	return (0);
// }

static void		loadmenu(t_win **wn)
{
	t_thread	thread[4];
	int			i;
	int			load;

	i = 0;
	load = 0;
	(*wn)->turn = 4;
	while (i < 4)
	{
		thread[i].wn = *wn;
		thread[i].value = i;
		pthread_create(&thread[i].thd, NULL, load_intro, (void *)&(thread[i]));
		i++;
	}
	pthread_join((thread[0].thd), NULL);
	pthread_join((thread[1].thd), NULL);
	pthread_join((thread[2].thd), NULL);
	pthread_join((thread[3].thd), NULL);
	(*wn)->turn = 0;
}

void			showload(t_win **wn, int load)
{
	SDL_Rect	loading;

	loading.x = 20;
	loading.y = (YSCREEN / 4) * 3;
	loading.w = (load * XSCREEN / 100) - 40;
	loading.h = 20;
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
