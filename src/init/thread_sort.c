/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:39:51 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/28 18:46:16 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		*sort_thread(void *param)
{
	t_win		**wn;
	t_thread	*thd;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	while (TRUE)
	{
		// AJOUTE LES TGA
		pthread_mutex_lock(&((*wn)->mutex->mutex));
		pthread_cond_wait(&((*wn)->mutex->condition), &((*wn)->mutex->mutex));
		printf("Value = %d\n", (*wn)->mutex->alive & 0xFF);
		if (!((*wn)->mutex->alive & 0xFF))
		{
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			break;
		}
		pthread_mutex_unlock(&((*wn)->mutex->mutex));
		pthread_cond_signal(&((*wn)->mutex->condition));
		SDL_Delay(30);
	}
	return (NULL);
}

void		*show_thread(void *param)
{
	t_win		**wn;
	t_thread	*thd;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	while (TRUE)
	{
		break;
	}
	pthread_kill(thd->thd, 0);
	return (NULL);
}
