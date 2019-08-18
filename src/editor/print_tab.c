/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 13:31:05 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/08 13:31:08 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void    display_tab(t_win *wn, t_edit *edit)
{
    edit->tab->onglet == 0 ? edit->tab->texture_tab =
	findtexture(wn, "editor", "affichage", "params") : 0;
	edit->tab->onglet == 1 ? edit->tab->texture_tab =
	findtexture(wn, "editor", "affichage", "texts") : 0;
	edit->tab->onglet == 2 ? edit->tab->texture_tab =
	findtexture(wn, "editor", "affichage", "blocs") : 0;
	edit->tab->onglet == 3 ? edit->tab->texture_tab =
	findtexture(wn, "editor", "affichage", "background_map") : 0;
	(edit->tab->texture_tab == NULL) ?
	stop_exec("texture params failed in print_tab\n", wn) : 0;
}

void    exec_tab(t_win *wn, t_edit *edit)
{
    // edit->tab->onglet == 0 && edit->tab->in == 1 ? fonction textures : 0;
	// edit->tab->onglet == 1 && edit->tab->in == 1 ? fonction persos : 0;
	// edit->tab->onglet == 2 && edit->tab->in == 1 ? fonction coordonnees : 0;
	edit->tab->onglet == 3 && edit->tab->in == 1 ? print_bg(wn, edit) : 0;
	(edit->tab->texture_tab == NULL) ?
	stop_exec("texture params failed in print_tab\n", wn) : 0;
}

void	display_slider(t_win *wn, SDL_Rect rect, SDL_Texture *texture)
{
	SDL_Texture 	*motif;
	SDL_Rect 		tmp;
	static int 		move = 0;
	int 			slider_height;
	int		 		size;

	SDL_QueryTexture(texture, NULL, NULL, &size, &size);
	slider_height = rect.h * rect.h / size;
	tmp = define_rect(rect.x + rect.w + 0.1 * wn->xscreen / 8, rect.y, 0.1 * wn->xscreen / 8, rect.h);
	motif = findtexture(wn, "editor", "affichage", "back_slider");
	SDL_RenderCopy(wn->rend, motif, NULL, &tmp) < 0 ? stop_exec("rendercopy failed in display_slider\n", wn) : 0;
	motif = findtexture(wn, "editor", "affichage", "slider_window");
	SDL_QueryTexture(motif, NULL, NULL, &size, &size);
	if (size <= rect.h)
		SDL_RenderCopy(wn->rend, motif, NULL, &tmp) < 0 ? stop_exec("rendercopy failed in display_slider 2\n", wn) : 0;
	else
	{
		move = wn->input->y - move;
		tmp = define_rect(rect.x + rect.w + 0.1 * wn->xscreen / 8, rect.y + move, 0.1 * wn->xscreen / 8, slider_height);
		SDL_RenderCopy(wn->rend, motif, NULL, &tmp) < 0 ? stop_exec("rendercopy failed in display_slider 3\n", wn) : 0;
		move = wn->input->y;
	}
}

void 		test_slider(t_win *wn)
{
	SDL_Rect	rect;
	SDL_Texture		*texture;

	rect = define_rect(wn->xscreen / 3, 0, wn->xscreen / 4, wn->yscreen / 4);
	texture = findtexture(wn, "editor", "affichage", "slider_window");
	display_slider(wn, rect, texture);
}

// void 	scroll_texture(t_win *wn, t_edit *edit, SDL_Rect rect)
// {
// 	// SDL_Rect 	slide_area;
// 	// SDL_Rect 	slider;
// 	// int 			slider_height;
// 	SDL_Texture 	*texture;

	
// 	// si texture.h <= rect.h ====> on affiche rien et slide_area.h == texture.h
// 	// else ====> fonction affichage slider et slide_area.h == rect.h
// 	// 	affichage slider
// 	// 		slider = define_rect(rect.x + 7 * rect.w / 8, rect.y, rect.w / 8, slider_height);
// 	// 		rendercopy(NULL, slider);
// }