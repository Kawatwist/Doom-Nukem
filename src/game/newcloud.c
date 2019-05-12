/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newcloud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 11:08:37 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/11 14:39:13 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	show_cloud(t_win *wn)
{
	t_cloudy	*curr;
	t_text		*txt;
	
	txt = findpostxt(wn, "game", "skybox", "cloudy");
	curr = wn->cloud;
	while (curr != NULL)
	{
		if (curr->life_time)
			curr->life_time -= 1;
		else
			curr->life_time2 -= 1;
		curr->pos.x = curr->xbase + (curr->life_time > 0 ? curr->life_time2 - curr->life_time : curr->life_time2 + (curr->life_time * - 1));
		SDL_RenderCopy(wn->rend, txt->txt, NULL, &curr->pos);
		curr = curr->next;
	}
}

static void	sort_cloud(t_win *wn)
{
	(void)wn;
}

static void	check_cloud(t_win *wn, int nb)
{
	t_cloudy	*curr;
	t_cloudy	*curr2;
	int			cloud;

	curr = wn->cloud;
	cloud = 0;
	while (curr != NULL && cloud < nb)
	{
		if (curr != NULL && curr->life_time2 == 0)
		{
			curr2 = curr->next;
			curr == NULL ? free(curr) : 0;
			curr = malloc(sizeof(t_cloudy));
			if (curr2 != NULL)
				curr->next = curr2;
			else
				curr->next = NULL;
			if (cloud == 0)
				wn->cloud = curr;
			init_cloud(curr);
		}
		cloud++;
		init_cloud(curr);
		curr = curr->next;
	}
}

void		main_cloud(t_win *wn)
{
	check_cloud(wn, 5);
	sort_cloud(wn);
	show_cloud(wn);
}
