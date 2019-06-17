/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:59:53 by lomasse           #+#    #+#             */
/*   Updated: 2019/06/17 13:58:17 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	setkeyboard(Uint8 *new, Uint8 *current)
{
	int	i;

	i = -1;
	while (++i < 283)
		new[i] = current[i];
}

void	gameinput(t_win *wn)
{
	(wn->player->rawx += (wn->input->x - (wn->xscreen / 2 ))) >  360
		? wn->player->rawx -= 360 : 0;
	(wn->player->rawy += (wn->input->y - (wn->yscreen / 2))) > YSCREEN 
		? wn->player->rawy = YSCREEN : 0;
//	wn->player->rawx += wn->input->x / XSCREEN;
//	wn->player->rawy += wn->input->y/ YSCREEN;
	wn->player->rawx < 0 ? wn->player->rawx += 360 : 0;
	wn->player->rawy < 0 ? wn->player->rawy = 0 : 0;
	!wn->old[SDL_SCANCODE_ESCAPE] && wn->state[SDL_SCANCODE_ESCAPE] && !(wn->flag & CONSOLE) ? wn->interface = MENU : 0;
	wn->state[SDL_SCANCODE_KP_PLUS] ? wn->player->sensi += 0.1 : 0;
	wn->state[SDL_SCANCODE_KP_MINUS] ? wn->player->sensi -= 0.1 : 0;
	wn->state[SDL_SCANCODE_A] ? wn->player->x += 1 : 0;
	wn->state[SDL_SCANCODE_W] ? wn->player->y += 1 : 0;
	wn->state[SDL_SCANCODE_D] ? wn->player->x -= 1 : 0;
	wn->state[SDL_SCANCODE_S] ? wn->player->y -= 1 : 0;
	wn->state[SDL_SCANCODE_SPACE] ? wn->player->z += 1 : 0;
	wn->state[SDL_SCANCODE_LSHIFT] ? wn->player->z -= 1 : 0;
}
