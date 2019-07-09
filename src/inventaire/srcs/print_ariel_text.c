/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ariel_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:05:07 by jleblond          #+#    #+#             */
/*   Updated: 2019/07/09 14:52:09 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			print_text_with_ariel_font(t_win *wn, char *s, SDL_Color color, SDL_Rect position)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = TTF_RenderText_Solid(wn->fonts->ariel, s, color);
	if (surface == NULL)
		stop_exec("TTF_RenderText() failed", wn);
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);//<-- Memory Problem
	if (texture == NULL)
		stop_exec("SDL_CreateTextureFromSurface() failed", wn);
	SDL_FreeSurface(surface);
	SDL_RenderCopy(wn->rend, texture, NULL, &position);
}
