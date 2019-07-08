/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventaire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 10:37:37 by naali             #+#    #+#             */
/*   Updated: 2019/07/08 06:31:29 by naali            ###   ########.fr       */
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

static void		ft_init_itemsname_pos(t_win *wn, SDL_Rect *dst, int pos, int size)
{
	dst->x = (wn->xscreen / 77);
	dst->y = (wn->yscreen / 18) + (pos * 30);
	dst->w = 10 * size;// recuperer taille de fenetre
	dst->h = 25;// recuperer taille de fenetre
}

static void		choose_name_color(SDL_Color *color, int isselected)
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

static void		print_test_names(t_win *wn, char *name, int pos, int isselected)
{
	SDL_Rect	dst;
	SDL_Color	color;

	choose_name_color(&color, isselected);
	ft_init_itemsname_pos(wn, &dst, pos, ft_strlen(name));
	print_text_with_ariel_font(wn, name, color, dst);
}

void		print_inventory(t_win *wn)
{
	SDL_Rect	src;
	SDL_Rect	dst;
	SDL_Texture	*txt;

	txt = findtexture(wn, "game", "inventaire", "bg");
	ft_init_inventaire_pos(wn, &src, &dst);
	SDL_SetTextureBlendMode(txt, (SDL_BLENDMODE_MOD));
	SDL_SetRenderTarget(wn->rend, txt);
	SDL_RenderCopy(wn->rend, txt, &src, &dst);
	/* Print inventaire ICI */
	print_test_names(wn, "Salut", 0, 1);
	print_test_names(wn, "Comment", 1, 0);
	print_test_names(wn, "vas ?", 2, 0);
}
