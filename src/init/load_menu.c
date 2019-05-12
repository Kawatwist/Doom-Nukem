/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:00:01 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/11 16:18:27 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		loadminimenu(t_win **wn)
{
	(*wn)->load = ft_strdup("./texture/intro/menu/test0059.tga");
	load_texture(*wn, "main", "intro", "60");
	(*wn)->load = ft_strdup("./texture/intro/edit/test0119.tga");
	load_texture(*wn, "editor", "intro", "119");
	(*wn)->load = ft_strdup("./texture/intro/option/test0179.tga");
	load_texture(*wn, "editor", "intro", "179");
	(*wn)->load = ft_strdup("./texture/intro/game/test0119.tga");
	load_texture(*wn, "game", "intro", "119");
}
/*
static void		initthread(t_thread	thread[1], t_win **wn, int value)
{
	thread[0].wn = *wn;
	thread[0].value = value;
	((thread[0].file = malloc(sizeof(t_load))) == NULL) ? stop_exec("Malloc Failed\n", *wn): 0;
	thread[0]->file->next = NULL;
	thread[0]->file->txt = NULL;
	thread[0]->file->tga = NULL;
}

static void		loadmenu(t_win **wn)
{
	t_thread	thread[6];
	int			i;

	i = -1;
	while (++i < 6)
	{
		initthread(thread[i], wn, i);
	}
//	thread[i].wn = *wn;
//	thread[i].value = i;
//	pthread_create(&thread[i].thd, NULL, load_intro, (void *)&(thread[i]));
//	pthread_join((thread[3].thd), NULL);
}
*/
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
