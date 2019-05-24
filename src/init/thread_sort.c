/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:39:51 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/24 14:00:25 by lomasse          ###   ########.fr       */
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
	}
}

void		*show_thread(void *param)
{
	t_win		**wn;
	t_thread	*thd;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	while (TRUE)
	{
	}
}
