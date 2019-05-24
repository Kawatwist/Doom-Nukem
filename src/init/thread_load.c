/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:36:58 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/24 15:39:54 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		*option_thread(void *param)
{
	t_win 		**wn;
	t_thread 	*thd;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	while (TRUE)
	{

	}
}

void		*editor_thread(void *param)
{
	t_win 		**wn;
	t_thread 	*thd;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	while (TRUE)
	{
	}
}

void		*game_thread(void *param)
{
	t_win 		**wn;
	t_thread 	*thd;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	while (TRUE)
	{
	}
}

void		*menu_thread(void *param)
{
	t_win 		**wn;
	t_thread 	*thd;

	wn = &((t_thread *)param)->wn;
	thd = (t_thread *)param;
	while (TRUE)
	{
	}
}
