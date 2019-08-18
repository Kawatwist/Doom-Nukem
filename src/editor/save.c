/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 13:53:20 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/07 13:53:27 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void 		print_save_and_reset(t_win *wn, t_edit *edit)
{
	int			w;
	int			h;
	SDL_Rect	position;
	SDL_Surface *surface;
	SDL_Texture *texture;

	//BLOC SAVE
	position = define_rect(6 * wn->xscreen / 8, 0, wn->xscreen / 8, 0.5 * wn->yscreen / 8);
	if (hitbox(wn->input->x, wn->input->y, &position) == TRUE && mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE)
	{
		ft_launch_rasterization(wn);
		edit->var->map_saved = 1;
		// sauvegarde fichier;
	}
	if (edit->var->map_saved == 1)
	{
		print_message(wn, "Map saved.", wn->color.blanc);
		//wn->varedit.map_saved = 0;
	}
	surface = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	if (texture == NULL)
        stop_exec("FAIL\n", wn);
    SDL_FreeSurface(surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, &position) < 0)
		stop_exec("rendercopy failed in save\n", wn);
	SDL_DestroyTexture(texture);
	TTF_SizeText(wn->fonts->ariel, "SAVE", &w, &h);
	position = define_rect(6.5 * wn->xscreen / 8 - (w / 2), 0.25 * wn->yscreen / 8 - (h / 2), w, h);
	TTF_SetFontStyle(wn->fonts->ariel, TTF_STYLE_BOLD);
	print_text_with_ariel_font(wn, "SAVE", wn->color.blanc, position);
	TTF_SetFontStyle(wn->fonts->ariel, TTF_STYLE_NORMAL);

	//BLOC RESET
	position = define_rect(7 * wn->xscreen / 8, 0, wn->xscreen / 8, 0.5 * wn->yscreen / 8);
	if (hitbox(wn->input->x, wn->input->y, &position) == TRUE && mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE)
		resetmap(wn, edit);
	surface = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, &position) < 0)
		stop_exec("rendercopy failed in reset\n", wn);
	SDL_DestroyTexture(texture);
	TTF_SizeText(wn->fonts->ariel, "RESET", &w, &h);
	position = define_rect(7.5 * wn->xscreen / 8 - (w / 2), 0.25 * wn->yscreen / 8 - (h / 2), w, h);
	TTF_SetFontStyle(wn->fonts->ariel, TTF_STYLE_BOLD);
	print_text_with_ariel_font(wn, "RESET", wn->color.noir, position);
	TTF_SetFontStyle(wn->fonts->ariel, TTF_STYLE_NORMAL);
}

// void 		save_the_map(t_win *wn)
// {
// 	SDL_Rect 	rect;

// 	rect = define_rect(wn->xscreen / 2 - 250, wn->yscreen / 2 - 150, 500, 300);
// 	if (key_pressed(wn, SDL_SCANCODE_ESCAPE) == TRUE && wn->elem != NULL)
// 	{
// 		if (pop_up_message(wn, "Save the map?", &rect) == 1)
// 		{
// 			traduire map en t_poly
// 			sauver map dans fichier
// 		}
// 		if (pop_up_message(wn, "Save the map?", &rect) == 2)
// 		{
// 			free la wn->elem
// 			tout remettre à zero
// 		}
// 	}
// 	(wn->edit_image.bgh == 0) ? print_save_and_reset(wn) : 0 ;
// }
