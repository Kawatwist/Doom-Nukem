/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 10:37:37 by naali             #+#    #+#             */
/*   Updated: 2019/08/12 17:00:11 by naali            ###   ########.fr       */
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
	src->w = wn->xscreen / 3;
	src->h = wn->yscreen / 2;
	dst->x = 0;
	dst->y = wn->yscreen / 4;
	dst->w = wn->xscreen / 3;
	dst->h = wn->yscreen - (wn->yscreen / 4);
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

void		init_inventory(t_win *wn, t_joueurs *j, SDL_Rect *src, SDL_Rect *dst)
{
	j->inv_txt = findtexture(wn, "game", "inventaire", "bg");
	ft_init_inventaire_pos(wn, src, dst);
}

void		print_inventory(t_win *wn, t_joueurs *j, int selected)
{
	int			pos;
	SDL_Rect	src;
	SDL_Rect	dst;

	pos = 0;
	(j->inv_txt == NULL) ? init_inventory(wn, j, &src, &dst) : 0;
	SDL_SetTextureBlendMode(j->inv_txt, SDL_BLENDMODE_MOD);
	SDL_SetRenderTarget(wn->rend, j->inv_txt);
	SDL_RenderCopy(wn->rend, j->inv_txt, &src, &dst);
	/* Print inventaire DEBUT */
	pos = print_weapo_list(wn, j, &selected);
//	print_conso_list(wn, j, selected, pos);
	/* Print inventaire FIN */
}
