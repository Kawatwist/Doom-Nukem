/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 10:06:33 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/12 15:21:23 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		display_crosshair(t_win *wn)
{
	SDL_SetRenderDrawColor(wn->rend, 0, 0, 0, 0);
	SDL_RenderDrawLine(wn->rend, (XSCREEN / 2) - 5, YSCREEN/2, (XSCREEN / 2) + 5, YSCREEN/2);
	SDL_RenderDrawLine(wn->rend, XSCREEN/2, (YSCREEN / 2) - 5, XSCREEN/2, (YSCREEN / 2) + 5);
	SDL_RenderCopy(wn->rend, ((t_text *)wn->player->weapon->text)->txt, NULL, NULL);
}
