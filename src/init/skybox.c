/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:34:05 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/11 14:36:52 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
static void	init_cloud(t_win **wn)
{
	((*wn)->cloud = malloc(sizeof(t_cloud))) == NULL
		? stop_exec("cloud not malloc\n", *wn) : 0;
	(*wn)->cloud->txt = NULL;
	(*wn)->cloud->tmp = 0;
	(*wn)->cloud->sens = 0;
	(*wn)->cloud->life = 700;
	(*wn)->cloud->flag = 0;
	(*wn)->cloud->start = (rand() % (*wn)->xscreen);
	(*wn)->cloud->next = NULL;
}
*/

void		init_cloud(t_cloudy *cloud)
{
	cloud->id = (rand() % 4) + 1;
	cloud->size = (rand() % 70) + 50;
	cloud->speed = ((rand() % 28) >> 3) + 0.2;
	cloud->ybase = (rand() % 100) + 100;
	cloud->xbase = (rand() % 100) + 100;
	cloud->sens = (cloud->xbase > 150 ? 1 : 0);
	cloud->life_time = (rand() % 500) + 200;
	cloud->life_time2 = cloud->life_time;
	cloud->pos.x = cloud->xbase;
	cloud->pos.y = cloud->ybase;
	cloud->pos.w = cloud->size;
	cloud->pos.h = cloud->size;
	cloud->next = NULL;
}

static void	init_cloudy(t_win **wn)
{
	(*wn)->cloud->id = (rand() % 4) + 1;
	(*wn)->cloud->size = (rand() % 70) + 50;
	(*wn)->cloud->speed = ((rand() % 28) >> 3) + 0.2;
	(*wn)->cloud->ybase = (rand() % 100) + 100;
	(*wn)->cloud->xbase = (rand() % 100) + 100;
	(*wn)->cloud->sens = ((*wn)->cloud->xbase > 150 ? 1 : 0);
	(*wn)->cloud->life_time = (rand() % 500) + 200;
	(*wn)->cloud->life_time2 = (*wn)->cloud->life_time;
	(*wn)->cloud->pos.x = (*wn)->cloud->xbase;
	(*wn)->cloud->pos.y = (*wn)->cloud->ybase;
	(*wn)->cloud->pos.w = (*wn)->cloud->size;
	(*wn)->cloud->pos.h = (*wn)->cloud->size;
	(*wn)->cloud->next = NULL;
}

void		initskybox(t_win **wn)
{
	(*wn)->load = ft_strdup("texture/skybox/sky.tga");
	load_texture(*wn, "game", "skybox", "sky");
	(*wn)->load = ft_strdup("texture/skybox/sky2.tga");
	load_texture(*wn, "game", "skybox", "sky2");
	(*wn)->load = ft_strdup("texture/skybox/sky3.tga");
	load_texture(*wn, "game", "skybox", "sky3");
	(*wn)->load = ft_strdup("texture/skybox/sky4.tga");
	load_texture(*wn, "game", "skybox", "sky4");
	(*wn)->load = ft_strdup("texture/skybox/sky6.tga");
	load_texture(*wn, "game", "skybox", "sky5");
	(*wn)->load = ft_strdup("texture/skybox/cloud.tga");
	load_texture(*wn, "game", "skybox", "cloudy");
	(*wn)->load = ft_strdup("texture/skybox/cloud_briocher.tga");
	load_texture(*wn, "game", "skybox", "bribri");
	((*wn)->cloud = malloc(sizeof(t_cloudy))) == NULL
		? stop_exec("cloud not malloc\n", *wn) : 0;
	init_cloudy(wn);
}
