/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:18:57 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/24 15:38:11 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		start_thread_sort(t_thread thread[1], char value)
{
	if (value == 5)
		pthread_create(&thread[0].thd, NULL, sort_thread, (void *)&(thread[i]));
	else
		pthread_create(&thread[0].thd, NULL, show_thread, (void *)&(thread[i]));
}

void		start_thread_load(t_thread thread[1], char value)
{
	if (value == 1)
	{
		thread[0].path = ft_strdup("./texture/intro/menu/test0059.tga");
		pthread_create(&thread[0].thd, NULL, menu_thread, (void *)&(thread[i]));
	}
	else if (value == 2)
	{
		thread[0].path = ft_strdup("./texture/intro/game/test0119.tga");
		pthread_create(&thread[0].thd, NULL, game_thread, (void *)&(thread[i]));
	}
	else if (value == 3)
	{
		thread[0].path = ft_strdup("./texture/intro/edit/test0119.tga");
		pthread_create(&thread[0].thd, NULL, editor_thread, (void *)&(thread[i]));
	}
	else if (value == 4)
	{
		thread[0].path = ft_strdup("./texture/intro/option/test0179.tga");
		pthread_create(&thread[0].thd, NULL, option_thread, (void *)&(thread[i]));
	}
}

void		init_thread(t_thread thread[1], t_win **wn, char value)
{
	thread[0].wn = *wn;
	thread[0].value = value;
	((thread[0].file = malloc(sizeof(t_load))) == NULL) ? stop_exec("Malloc thread failed\n", *wn) : 0;
	thread[0]->file->next = NULL;
	thread[0]->file->txt = NULL;
	thread[0]->file->tga = NULL;
}

void		main_load_thread(t_win **wn)
{
	t_thread	thread[6];
	char		i;

	i = -1;
	while (++i < 6)
	{
		init_thread(thread[i], wn, i);
		if (i < 5)
			start_thread_load(thread[i], i);
		else
			start_thread_sort(thread[i], i);
	}
	pthread_join((thread[5].thd), NULL);
}
