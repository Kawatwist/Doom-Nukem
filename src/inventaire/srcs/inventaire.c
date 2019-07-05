/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 10:37:37 by naali             #+#    #+#             */
/*   Updated: 2019/07/05 13:57:56 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>
#include <inventaire.h>

void		init_inventaire_texture(t_win *wn)
{
	wn->load = ft_strdup("./texture/inventaire/background_copy.tga");
	load_texture(wn, "game", "inventaire", "bg");
}

static void		ft_init_inventaire_pos(t_win *wn, SDL_Rect *src, SDL_Rect *dst)
{
	src->x = 0;
	src->y = 0;
	src->w = 1920;
	src->h = 1080;
	dst->x = 0;
	dst->y = 0;
	dst->w = wn->xscreen;// recuperer taille de fenetre
	dst->h = wn->yscreen;// recuperer taille de fenetre
}

void		print_inventory(t_win *wn)
{
	SDL_Rect	src;
	SDL_Rect	dst;
	SDL_Color	color;
	SDL_Texture	*txt;

	color.r = 0xFF;
	color.g = 0x10;
	color.b = 0x42;
	color.a = 0xFF;
	txt = findtexture(wn, "game", "inventaire", "bg");
	ft_init_inventaire_pos(wn, &src, &dst);
	SDL_SetTextureBlendMode(txt, (SDL_BLENDMODE_MOD));
	SDL_SetRenderTarget(wn->rend, txt);
	SDL_RenderCopy(wn->rend, txt, &src, &dst);
	/* Print inventaire ICI */
	print_text_with_ariel_font(wn, "test", color, src);//test
}
