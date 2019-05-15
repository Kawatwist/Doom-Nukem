/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:34:05 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/15 10:55:56 by lomasse          ###   ########.fr       */
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
	(void)wn;
/*	(*wn)->cloud->id = (rand() % 4) + 1;
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
*/}

static void	loadsky(t_win **wn, char *path, char *name)
{
	if	(((*wn)->load = ft_strdup(path)) == NULL)
		return ;
	printf("Dup\n");
	load_texture(*wn, "game", "skybox", name);
	printf("Load\n");
	if ((*wn)->load != NULL)
		free((*wn)->load);
}


void		initskybox(t_win **wn)
{
	printf("Before\n");
	loadsky(wn, "texture/skybox/sky.tga\0", "sky\0");
	printf("Before 1\n");
	loadsky(wn, "texture/skybox/sky2.tga\0", "sky2\0");
	printf("Before 2\n");
	loadsky(wn, "texture/skybox/sky3.tga\0", "sky3\0");
	printf("Before 3\n");
	loadsky(wn, "texture/skybox/sky4.tga\0", "sky4\0");
	printf("Before 4\n");
	loadsky(wn, "texture/skybox/sky6.tga\0", "sky5\0");
	printf("Before 5\n");
	loadsky(wn, "texture/skybox/cloud.tga\0", "cloudy\0");
	printf("Before 6\n");
//	loadsky(wn, "texture/skybox/cloud_briocher.tga\0", "bribri\0");
//	((*wn)->cloud = malloc(sizeof(t_cloudy))) == NULL
//		? stop_exec("cloud not malloc\n", *wn) : 0;
	init_cloudy(wn);
	printf("DONE\n");
}
