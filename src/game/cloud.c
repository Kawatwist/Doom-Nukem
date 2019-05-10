/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:57:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/10 08:28:42 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		setcloud(t_win *wn, int nb_cloud)
{
	t_cloud *tmp;
	t_text	*img;
	int		nb;

	tmp = wn->cloud;
	deletcloud(wn);
	setcloudsize(wn);
	nb = 0;
	while (nb < nb_cloud)
	{
		if (tmp->next != NULL)
		{
			tmp = tmp->next;
			nb++;
		}
		else
		{
			(tmp->next = malloc(sizeof(t_cloud))) == NULL
				? stop_exec("Fail malloc cloud\n", wn) : 0;
			tmp = tmp->next;
			img = (findpostxt(wn, "game", "skybox",
						rand() % 2 == 0 ? "bribri" : "cloudy"));
			tmp->txt = img->txt;
			tmp->tmp = 0;
			tmp->flag = 0;
			tmp->size = rand() % 300 + 200;
			tmp->life = (rand() % 350) + 350;
			tmp->start = (rand() % XSCREEN) * 3;
			tmp->sens = (tmp->start > (XSCREEN * 1.5) ? 1 : 0);
			tmp->next = NULL;
			nb++;
		}
	}
}

void		setcloudsize(t_win *wn)
{
	t_cloud *tmp;

	tmp = wn->cloud;
	while (tmp != NULL && tmp->next != NULL)
	{
		tmp->currsize = (((float)(tmp->life / ((tmp->life - tmp->tmp == 0 ? 1 : (tmp->life - tmp->tmp))))) * (tmp->size));
		tmp = tmp->next;
	}
}

void		sort_cloud(t_win *wn)
{
	t_cloud *cur;
	t_cloud	*tmp;
	t_cloud	*tmp_next;
	t_cloud	*tmp_next2;

	cur = wn->cloud;
	while (cur != NULL && cur->next != NULL)
	{
		if (cur == wn->cloud && cur->currsize > cur->next->currsize)
		{
			tmp = cur;
			tmp_next = cur->next;
			tmp_next2 = cur->next->next;
			cur->next = tmp_next2;
			tmp_next->next = cur;
			wn->cloud = tmp_next;
		}
		else if (cur->next->next != NULL
				&& cur->next->currsize > cur->next->next->currsize)
		{
			tmp_next = cur->next;
			tmp_next2 = cur->next->next;
			tmp_next2->next == NULL ? tmp_next->next = NULL :
				(tmp_next->next = tmp_next2->next);
			cur->next = tmp_next2;
			cur->next->next = tmp_next;
		}
		else
			cur = cur->next;
	}
}

void		deletcloud(t_win *wn)
{
	t_cloud *tmp;
	t_cloud *tmp2;

	tmp = wn->cloud;
	while (tmp != NULL && tmp->next != NULL && tmp == wn->cloud)
	{
		if (tmp->flag && !tmp->tmp)
		{
			wn->cloud = tmp->next;
			free(tmp);
			tmp = wn->cloud;
		}
		else
			break ;
	}
	tmp = wn->cloud;
	while (tmp != NULL && tmp->next != NULL && tmp->next->next != NULL)
	{
		if (tmp->next->flag == 1 && tmp->next->tmp == 0)
		{
			tmp2 = tmp->next->next;
			free(tmp->next);
			tmp->next = tmp2;
		}
		else
			tmp = tmp->next;
	}
}

void		show_cloud(t_win *wn, t_cloud *clood)
{
	SDL_Rect	dst;

	dst.x = ((wn->player->rawx)) + clood->start;
	dst.x += (clood->flag == 1 ? clood->tmp : -clood->tmp);
	dst.y = 200 - (wn->player->rawy);
	dst.w = (clood->currsize);
	dst.h = (clood->currsize);
	SDL_RenderCopy(wn->rend, clood->txt, NULL, &dst);
	if (clood->tmp >= clood->life)
		clood->flag = 1;
	clood->tmp += (clood->flag == 0 ? +2 : -2);
}
