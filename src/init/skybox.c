/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:34:05 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/25 11:18:50 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"


static void	init_cloud(t_win **wn)
{
	((*wn)->cloud = malloc(sizeof(t_cloud))) == NULL
		? stop_exec("cloud not malloc\n", *wn) : 0;
	(*wn)->cloud->txt = NULL;
	(*wn)->cloud->tmp = 0;
	(*wn)->cloud->sens = 0;
	(*wn)->cloud->life = 700;
	(*wn)->cloud->flag = 0;
	(*wn)->cloud->start = (rand() % XSCREEN);
	(*wn)->cloud->next = NULL;
}

void		initskybox(t_win **wn)
{
	(*wn)->tmp[3] = ft_strdup("texture/skybox/sky.tga");
	load_texture(*wn, "game", "skybox", "sky");
	(*wn)->tmp[3] = ft_strdup("texture/skybox/sky2.tga");
	load_texture(*wn, "game", "skybox", "sky2");
	(*wn)->tmp[3] = ft_strdup("texture/skybox/cloudy.tga");
	load_texture(*wn, "game", "skybox", "cloudy");
	(*wn)->tmp[3] = ft_strdup("texture/skybox/cloud_briocher.tga");
	load_texture(*wn, "game", "skybox", "bribri");
	init_cloud(wn);
}