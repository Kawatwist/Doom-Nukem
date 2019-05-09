/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:34:05 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/07 13:32:32 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


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

void		initskybox(t_win **wn)
{
	(*wn)->load = ft_strdup("texture/skybox/sky.tga");
	load_texture(*wn, "game", "skybox", "sky");
	(*wn)->load = ft_strdup("texture/skybox/sky2.tga");
	load_texture(*wn, "game", "skybox", "sky2");
	(*wn)->load = ft_strdup("texture/skybox/cloudy.tga");
	load_texture(*wn, "game", "skybox", "cloudy");
	(*wn)->load = ft_strdup("texture/skybox/cloud_briocher.tga");
	load_texture(*wn, "game", "skybox", "bribri");
	init_cloud(wn);
}
