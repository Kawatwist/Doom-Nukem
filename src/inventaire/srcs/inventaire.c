/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 10:37:37 by naali             #+#    #+#             */
/*   Updated: 2019/07/08 08:28:02 by naali            ###   ########.fr       */
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
	dst->w = wn->xscreen;
	dst->h = wn->yscreen;
}

void			choose_item_color(SDL_Color *color, int isselected)
{
	if (isselected == 1)
	{
		color->r = 0xFF;
		color->g = 0x10;
		color->b = 0x42;
		color->a = 0xFF;
	}
	else
	{
		color->r = 0xFF;
		color->g = 0x42;
		color->b = 0xFF;
		color->a = 0xFF;
	}
}

void		print_inventory(t_win *wn, t_joueurs *j, int selected)
{
	int			pos;
	SDL_Rect	src;
	SDL_Rect	dst;
	SDL_Texture	*txt;

	pos = 0;
	txt = findtexture(wn, "game", "inventaire", "bg");
	ft_init_inventaire_pos(wn, &src, &dst);
	SDL_SetTextureBlendMode(txt, SDL_BLENDMODE_MOD);
	SDL_SetRenderTarget(wn->rend, txt);
	SDL_RenderCopy(wn->rend, txt, &src, &dst);
	/* Print inventaire DEBUT */
	pos = print_weapo_list(wn, j, &selected);
	print_conso_list(wn, j, selected, pos);
	/* Print inventaire FIN */
}
