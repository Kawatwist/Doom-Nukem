/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:39:51 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/29 04:13:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		*sort_thread(t_win **wn)
{
	t_load	*cur;

	while (TRUE)
	{
		pthread_mutex_lock(&((*wn)->mutex->mutex));
		pthread_cond_wait(&((*wn)->mutex->condition), &((*wn)->mutex->mutex));
		cur = (*wn)->mutex->load;
		while (cur->next != NULL && cur->done)
			cur = cur->next;
		while (!cur->done)
		{
			add_tga(*wn, cur->tga, cur->path);
			cur->done = 1;
			if (cur->next != NULL)
				cur = cur->next;
			else
				break;
		}
		if (!((*wn)->mutex->alive & 0xFF) && cur->next == NULL && cur->done)
		{
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			break;
		}
		pthread_mutex_unlock(&((*wn)->mutex->mutex));
		pthread_cond_signal(&((*wn)->mutex->condition));
		SDL_Delay(20);
	}
	return (NULL);
}

void		*show_thread(void *param)
{
	t_win		**wn;
	t_thread	*thd;
//	int			i;
//	t_load		*cur;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	while (TRUE)
	{
/*		i = 0;
		pthread_mutex_lock(&((*wn)->mutex->mutex));
		pthread_cond_wait(&((*wn)->mutex->condition), &((*wn)->mutex->mutex));
		cur = (*wn)->mutex->load;
		while (cur->next != NULL)
		{
			cur = cur->next;
			i++;
		}
		showload(wn, (i * 70 / 249) + 30);
		if (!((*wn)->mutex->alive & 0xFF))
		{
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			break;
		}
		pthread_mutex_unlock(&((*wn)->mutex->mutex));
		pthread_cond_signal(&((*wn)->mutex->condition));
		SDL_Delay(200);
*/		
		break;
	}
	pthread_kill(thd->thd, 0);
	return (NULL);
}
