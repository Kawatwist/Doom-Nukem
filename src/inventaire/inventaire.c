/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:24:52 by naali             #+#    #+#             */
/*   Updated: 2019/06/24 09:45:41 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		ft_init_texture_inventaire(SDL_Rect *src, SDL_Rect *dst)
{
	src->x = 0;
	src->y = 0;
	src->w = 1920;
	src->h = 1080;
	dst->x = 0;
	dst->y = 0;
	dst->w = WINX;// recuperer taille de fenetre
	dst->h = WINY;// recuperer taille de fenetre
}

void		print_inventory(t_print *w)
{
	SDL_Rect	src;
	SDL_Rect	dst;

	ft_init_texture_inventaire(&src, &dst);
	SDL_SetTextureBlendMode(w->texture[inventaire], (SDL_BLENDMODE_ADD * 2));
	SDL_SetRenderTarget(w->renderer[MAP_3D], w->texture[inventaire]);
	SDL_RenderCopy(w->renderer[MAP_3D], w->texture[inventaire], &src, &dst);
}

void		inventory_trigger(int *inv, int print)
{
	*inv = print;
}
