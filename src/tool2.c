/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:34:54 by llejeune          #+#    #+#             */
/*   Updated: 2019/07/10 13:34:56 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void 		print_message(t_win *wn, char *msg, SDL_Color color)
{
	SDL_Rect 	rect;
	int 		w;
	int 		h;
	static Uint32 	time = 0;

	(time == 0) ? time = SDL_GetTicks() : 0;
	if (SDL_GetTicks() - time < 3000)
	{
		TTF_SizeText(wn->fonts->arial_path, msg, &w, &h);
		rect = define_rect(wn->xscreen / 2 - w / 2, 5 * wn->yscreen / 7 - h / 2, w, h);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_ITALIC);
		print_text_with_arial_path_full(wn, msg, color, rect);
		TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	}
	else
	{
		time = 0;
		wn->varedit.map_saved = 0;
	}
}

int 		pop_up_message(t_win *wn, char *msg, SDL_Rect *rect)
{
	int				w;
	int				h;
	SDL_Rect 		position;
	SDL_Surface 	*surface;
	SDL_Texture 	*texture;

	//APPARITION SOURIS
	if (hitbox(wn->input->x, wn->input->y, rect) == TRUE)
		SDL_ShowCursor(SDL_ENABLE);
	//BLOC QUESTION
	surface = SDL_CreateRGBSurface(0, rect->x, rect->y, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 62, 62, 62));
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, rect) < 0)
		stop_exec("rendercopy failed\n", wn);
	TTF_SizeText(wn->fonts->arial_path, msg, &w, &h);
	position = define_rect(rect->x + rect->w /2 - w / 2, rect->y + rect->h / 4, w, h);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
	print_text_with_arial_path_full(wn, msg, wn->color.blanc, position);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	//BLOC YES
	position = define_rect(rect->x, rect->y + rect->h / 4 * 3, rect->w / 2, rect->h / 4);
	surface = SDL_CreateRGBSurface(0, rect->x, rect->y, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, &position) < 0)
		stop_exec("rendercopy failed\n", wn);
	TTF_SizeText(wn->fonts->arial_path, "YES", &w, &h);
	if (mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE && hitbox(wn->input->x, wn->input->y, &position) == TRUE)
		return(1);
	position = define_rect(rect->x + position.w / 2 - w / 2, position.y + position.h / 2 - h / 2, w, h);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
	print_text_with_arial_path_full(wn, "YES", wn->color.noir, position);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	//BLOC NO
	position = define_rect(rect->x + rect->w / 2, rect->y + rect->h / 4 * 3, rect->w / 2, rect->h / 4);
	surface = SDL_CreateRGBSurface(0, rect->x, rect->y, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, &position) < 0)
		stop_exec("rendercopy failed\n", wn);
	TTF_SizeText(wn->fonts->arial_path, "NO", &w, &h);
	if (mouse_pressed(wn, SDL_BUTTON_LEFT) == TRUE && hitbox(wn->input->x, wn->input->y, &position) == TRUE)
		return(2);
	position = define_rect(rect->x + rect->w / 4 * 3 - w / 2, position.y + position.h / 2 - h / 2, w, h);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_BOLD);
	print_text_with_arial_path_full(wn, "NO", wn->color.blanc, position);
	TTF_SetFontStyle(wn->fonts->arial_path, TTF_STYLE_NORMAL);
	return (0);
}