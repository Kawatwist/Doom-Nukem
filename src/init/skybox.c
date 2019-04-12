/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:34:05 by lomasse           #+#    #+#             */
/*   Updated: 2019/04/12 17:01:12 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	initskybox(t_win **wn)
{
	((*wn)->skybox = malloc(sizeof(t_skybox))) == NULL ? stop_exec("Malloc skybox failed\n", *wn) : 0; 
	(*wn)->tmp[3] = ft_strdup("texture/skybox/sky.tga");
	load_texture(*wn, "game", "skybox", "sky");
	(*wn)->tmp[3] = ft_strdup("texture/skybox/sky2.tga");
	load_texture(*wn, "game", "skybox", "sky2");
}
