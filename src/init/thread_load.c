/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:36:58 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/29 03:07:55 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "tga_reader.h"

static void	set_terminated(t_win **wn, int value)
{
	pthread_mutex_lock(&((*wn)->mutex->mutex));
	pthread_cond_wait(&((*wn)->mutex->condition), &((*wn)->mutex->mutex));
	printf("BEFORE => %d\n", (*wn)->mutex->alive);
	(*wn)->mutex->alive = ((*wn)->mutex->alive & (0xFF - (1 << value)));
	printf("AFTER => %d\n", (*wn)->mutex->alive);
	pthread_mutex_unlock(&((*wn)->mutex->mutex));
	pthread_cond_signal(&((*wn)->mutex->condition));
}

void		*option_thread(void *param)
{
	t_win 		**wn;
	t_thread 	*thd;
	t_tga		*ret;
	t_load		*load;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	while (TRUE)
	{
		if ((ret = load_tga(thd->path)) == NULL)
			break;
		else
		{
			pthread_mutex_lock(&((*wn)->mutex->mutex));
			pthread_cond_wait(&((*wn)->mutex->condition), &((*wn)->mutex->mutex));
			load = (*wn)->mutex->load;
			while (load != NULL && load->next != NULL)
				load = load->next;
			if (load == NULL)
				load = malloc(sizeof(t_load));
			else
			{
				load->next = malloc(sizeof(t_load));
				load = load->next;
			}
			load->path = ft_strdup(thd->path);
			load->tga = ret;
			load->done = 0;
			load->txt = NULL;
			load->next = NULL;
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			thd->path = changename(thd->path, 27);
			printf("PATH option ~===> %s\n", thd->path);
		}
	}
	set_terminated(wn, 0);
	pthread_kill(thd->thd, 0);
	return (NULL);
}

void		*editor_thread(void *param)
{
	t_win 		**wn;
	t_thread 	*thd;
	t_tga		*ret;
	t_load		*load;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	load = (*wn)->mutex->load;
	while (TRUE)
	{
		if ((ret = load_tga(thd->path)) == NULL)
			break;
		else
		{
			pthread_mutex_lock(&((*wn)->mutex->mutex));
			pthread_cond_wait(&((*wn)->mutex->condition), &((*wn)->mutex->mutex));
			while (load != NULL && load->next != NULL)
				load = load->next;
			if (load == NULL)
				load = malloc(sizeof(t_load));
			else
			{
				load->next = malloc(sizeof(t_load));
				load = load->next;
			}
			load->path = ft_strdup(thd->path);
			load->tga = ret;
			load->done = 0;
			load->txt = NULL;
			load->next = NULL;
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			thd->path = changename(thd->path, 25);
			printf("PATH editor ~===> %s\n", thd->path);
		}
	}
	set_terminated(wn, 1);
	pthread_kill(thd->thd, 0);
	return (NULL);
}

void		*game_thread(void *param)
{
	t_win 		**wn;
	t_thread 	*thd;
	t_tga		*ret;
	t_load		*load;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	load = (*wn)->mutex->load;
	while (TRUE)
	{
		if ((ret = load_tga(thd->path)) == NULL)
			break;
		else
		{
			pthread_mutex_lock(&((*wn)->mutex->mutex));
			pthread_cond_wait(&((*wn)->mutex->condition), &((*wn)->mutex->mutex));
			while (load != NULL && load->next != NULL)
				load = load->next;
			if (load == NULL)
				load = malloc(sizeof(t_load));
			else
			{
				load->next = malloc(sizeof(t_load));
				load = load->next;
			}
			load->path = ft_strdup(thd->path);
			load->tga = ret;
			load->done = 0;
			load->txt = NULL;
			load->next = NULL;
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			thd->path = changename(thd->path, 25);
			printf("PATH game ~===> %s\n", thd->path);
		}
	}
	set_terminated(wn, 2);
	pthread_kill(thd->thd, 0);
	return (NULL);
}

void		*menu_thread(void *param)
{
	t_win 		**wn;
	t_thread 	*thd;
	t_tga		*ret;
	t_load		*load;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	load = (*wn)->mutex->load;
	while (TRUE)
	{
		if ((ret = load_tga(thd->path)) == NULL)
			break;
		else
		{
			pthread_mutex_lock(&((*wn)->mutex->mutex));
			pthread_cond_wait(&((*wn)->mutex->condition), &((*wn)->mutex->mutex));
			while (load != NULL && load->next != NULL)
				load = load->next;
			if (load == NULL)
				load = malloc(sizeof(t_load));
			else
			{
				load->next = malloc(sizeof(t_load));
				load = load->next;
			}
			load->path = ft_strdup(thd->path);
			load->tga = ret;
			load->done = 0;
			load->txt = NULL;
			load->next = NULL;
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			thd->path = changename(thd->path, 25);
			printf("PATH menu ~===> %s\n", thd->path);
		}
	}
	set_terminated(wn, 3);
	pthread_kill(thd->thd, 0);
	return (NULL);
}
