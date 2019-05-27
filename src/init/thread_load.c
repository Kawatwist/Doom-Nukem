/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:36:58 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/27 20:07:33 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "tga_reader.h"

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
			printf("APPLY\n");
			while (load != NULL && load->next != NULL)
				load = load->next;
			printf("FIND\n");
			if (load == NULL)
				load = malloc(sizeof(t_load));
			else
			{
				load->next = malloc(sizeof(t_load));
				load = load->next;
			}
			printf("MALLOCED\n");
			load->path = ft_strdup(thd->path);
			load->tga = ret;
			load->txt = NULL;
			load->next = NULL;
			printf("DONE\n");
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			thd->path = changename(thd->path, 27);
		}
	}
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
			load->txt = NULL;
			load->next = NULL;
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			thd->path = changename(thd->path, 25);
		}
	}
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
			load->txt = NULL;
			load->next = NULL;
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			thd->path = changename(thd->path, 25);
		}
	}
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
			load->txt = NULL;
			load->next = NULL;
			pthread_mutex_unlock(&((*wn)->mutex->mutex));
			pthread_cond_signal(&((*wn)->mutex->condition));
			thd->path = changename(thd->path, 25);
		}
	}
	pthread_kill(thd->thd, 0);
	return (NULL);
}
