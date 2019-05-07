/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:57:20 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/05 17:11:51 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		setcloudsize(t_win *wn)
{
	t_cloud *tmp;

	tmp = wn->cloud;
	while (tmp != NULL && tmp->next != NULL)
	{
		tmp->currsize = (((float)(tmp->life / ((tmp->life - tmp->tmp == 0 ? 1 : (tmp->life - tmp->tmp))))) * (tmp->size));
//		printf("%d / %d == %d\n", tmp->tmp, tmp->life, tmp->currsize);
		tmp = tmp->next;
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
			tmp->start = (rand() % wn->xscreen) * 3;
			tmp->sens = (tmp->start > (wn->xscreen * 1.5) ? 1 : 0);
			tmp->next = NULL;
			nb++;
		}
	}
}

/*
   static void show_cloud(t_win *wn, int x, char *name)
   {
   int			i;
   static int	tmp = 0;
   static int	flag = 0;
   SDL_Rect	dst;
   t_text		*img;

   i = 0;
   img = findpostxt(wn, "game", "skybox", name);
   SDL_SetRenderDrawColor(wn->rend, 255, 0, 0, 255);
   dst.x = ((wn->player->rawx) * 3) +
   ((flag == 0 ? tmp : (700 + 700 - tmp)) * 2) + x;
   dst.y = 200 - (wn->player->rawy);
   dst.w = 100 * (tmp * 0.01);
   dst.h = 100 * (tmp * 0.01);
   SDL_RenderCopy(wn->rend, img->txt, NULL ,&dst);
   dst.x = ((wn->player->rawx -wn->xscreen) * 3) +
   ((flag == 0 ? tmp : (700 + 700 - tmp)) * 2) + x;
   SDL_RenderCopy(wn->rend, img->txt, NULL ,&dst);
   if (tmp == 0)
   flag = 0;
   else if (tmp >= 700)
   flag = 1;
   tmp += (flag == 0 ? +2 : -2);
   }
   */

static void	sort_cloud(t_win *wn)
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

static void show_cloud3(t_win *wn, t_cloud *clood)
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
/*
   static void show_cloud2(t_win *wn, t_cloud *clood)
   {
   SDL_Rect	dst;

   dst.x = ((wn->player->rawx) * 3) +
   ((clood->flag == 0 ? clood->tmp :
   (clood->life + clood->life +
   (clood->sens == 0 ? (-clood->tmp) : clood->tmp))) * 2) + clood->start;
   dst.y = 200 - (wn->player->rawy);
   dst.w = (clood->life * 0.5) * (clood->tmp * 0.01);
   dst.h = (clood->life * 0.5) * (clood->tmp * 0.01);
   SDL_RenderCopy(wn->rend, clood->txt, NULL ,&dst);
   dst.x = ((wn->player->rawx -wn->xscreen) * 3) +
   ((clood->flag == 0 ? clood->tmp :
   (clood->life + clood->life +
   (clood->sens == 0 ? -clood->tmp :
   clood->tmp)) * 2) + clood->start);
   SDL_RenderCopy(wn->rend, clood->txt, NULL ,&dst);
   if (clood->tmp >= clood->life)
   clood->flag = 1;
   clood->tmp += (clood->flag == 0 ? +2 : -2);
   }
   */

static void	bg2_skybox(t_win *wn)
{
	t_text		*img;
	SDL_Rect	src;
	SDL_Rect	dst;

	(src.y = (wn->player->rawy * 800 / wn->yscreen)) > 400 ? src.y = 400 : 0;
	src.x = 0;
	src.w = 1;
	src.h = 400;
	dst.x = 0;
	dst.y = 0;
	dst.w = wn->xscreen;
	dst.h = wn->yscreen;
	img = findpostxt(wn, "game", "skybox", "sky2");
	SDL_RenderCopy(wn->rend, img->txt, &src, NULL);
}

static void	bg_skybox(t_win *wn)
{
	t_text		*img;
	SDL_Rect	src;
	SDL_Rect	dst;

	src.y = (wn->player->rawy * (1600 - wn->yscreen) / wn->yscreen);
	src.x = ((wn->xscreen - wn->player->rawx) * (4000 - wn->xscreen) / wn->xscreen);
	src.w = wn->xscreen;
	src.h = wn->yscreen;
	dst.x = 0;
	dst.y = 0;
	dst.w = wn->xscreen;
	dst.h = wn->yscreen;
	img = findpostxt(wn, "game", "skybox", "sky");
	SDL_RenderCopy(wn->rend, img->txt, &src, NULL);
}

void		display_skybox(t_win *wn)
{
	t_cloud		*cloood;
	static int	a = 5;
	static int	time = 0;

	setcloud(wn, a);
	setcloudsize(wn);
	sort_cloud(wn);
	SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 0);
	SDL_RenderDrawRect(wn->rend, NULL);
	wn->debugconsole > 5 ? bg_skybox(wn) : bg2_skybox(wn);
	cloood = wn->cloud;
	while (cloood != NULL)
	{
		show_cloud3(wn, cloood);
		cloood = cloood->next;
	}
	time++;
	if (time > (rand() % 200) + 700)
	{
		a ++;
		time = 0;
	}
}
