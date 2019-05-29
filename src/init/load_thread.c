/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:18:57 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/29 14:56:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		start_thread_sort(t_thread *thread)
{
	pthread_create(&thread->thd, NULL, show_thread, (void *)(thread));
}

static void		start_thread_load(t_thread *thread, char value)
{
	if (value == 1)
	{
		thread->path = ft_strdup("./texture/intro/menu/test0059.tga");
		pthread_create(&thread->thd, NULL, menu_thread, (void *)(thread));
	}
	else if (value == 2)
	{
		thread->path = ft_strdup("./texture/intro/game/test0119.tga");
		pthread_create(&thread->thd, NULL, game_thread, (void *)(thread));
	}
	else if (value == 3)
	{
		thread->path = ft_strdup("./texture/intro/edit/test0119.tga");
		pthread_create(&thread->thd, NULL, editor_thread, (void *)(thread));
	}
	else if (value == 4)
	{
		thread->path = ft_strdup("./texture/intro/option/test0179.tga");
		pthread_create(&thread->thd, NULL, option_thread, (void *)(thread));
	}
}

static void		init_thread(t_thread *thread, t_win **wn, char value)
{
	thread->wn = *wn;
	thread->value = value;
}

void		main_load_thread(t_win **wn)
{
	t_thread	*thread;
	int			i;

	i = -1;
	thread = malloc(sizeof(t_thread) * 6);
	(*wn)->mutex->alive = 15;
	while (++i < 5)
	{
		init_thread((t_thread*)&(thread[i]), wn, i);
		if (i < 5)
			start_thread_load((t_thread*)&(thread[i]), i);
		else
			start_thread_sort((t_thread*)&(thread[i]));
	}
	sort_thread(wn);
	pthread_join((thread[5].thd), NULL);
}
