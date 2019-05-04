/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:30:09 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/04 17:57:37 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		*loadingthread(void *param)
{
	t_win		**wn;
	t_thread	*thd;
	int			value;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	value = 30;
	while (TRUE)
	{
		pthread_mutex_lock(&((*wn)->mutex->mutex));
		pthread_cond_wait(&((*wn)->mutex->condition), &((*wn)->mutex->mutex));
		value = (*wn)->mutex->load * 70 / 240 + 30;
		printf("%d\n", value);
		pthread_mutex_unlock(&((*wn)->mutex->mutex));
		pthread_cond_signal(&((*wn)->mutex->condition));
		showload(wn, value);
		if ((*wn)->turn == 0)
			break;
		SDL_Delay(100);
	}
	pthread_kill(thd->thd, 0);
	pthread_exit(thd->thd);
	pthread_exit(NULL);
	return (NULL);
}

int			initmutex(t_win **wn)
{
	static pthread_cond_t condition2 = PTHREAD_COND_INITIALIZER;
	static pthread_mutex_t mutex2 = PTHREAD_COND_INITIALIZER;

	((*wn)->mutex = (t_mut *)malloc(sizeof(t_mut))) == NULL ? stop_exec("Malloc mutex failed\n", *wn) : 0;
	(*wn)->mutex->condition = condition2;
	(*wn)->mutex->mutex = mutex2;
	(*wn)->mutex->load = 0;
	return (0);
}
