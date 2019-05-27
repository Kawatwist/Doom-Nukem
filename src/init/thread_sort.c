/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:39:51 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/27 20:14:07 by lomasse          ###   ########.fr       */
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
		//ATT TOUT LES THREADS
		break;
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
