/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_show_host.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naali <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 11:56:02 by naali             #+#    #+#             */
/*   Updated: 2019/10/16 11:56:05 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "server.h"

void	inputhost(t_win *wn)
{
	key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MULTI : 0;
	key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 40 : 0;
	key_pressed(wn, SDL_SCANCODE_ESCAPE) ? freeserv(wn, (t_server *)wn->serv) : 0;
	if ((wn->menu->ask & 0x03) == 1 || (wn->menu->ask & 0x03) == 2)
	{
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? pthread_kill((pthread_t)wn->menu->conv[0], 1) : 0;
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->ask = wn->menu->ask & (U_MAX - 0x03) : 0;
	}
	if ((wn->menu->ask & 0x0C) >> 2 == 1 || (wn->menu->ask & 0x0C) >> 2 == 2)
	{
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? pthread_kill((pthread_t)wn->menu->conv[1], 1) : 0;
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->ask = wn->menu->ask & (U_MAX - 0x0C) : 0;
	}
	if ((wn->menu->ask & 0x30) >> 4 == 1 || (wn->menu->ask & 0x30) >> 4  == 2)
	{
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? pthread_kill((pthread_t)wn->menu->conv[2], 1) : 0;
		key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->ask = wn->menu->ask & (U_MAX - 0x30) : 0;
	}
	//key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 40 : 0;
	if ((wn->menu->ask & 0x03) == 0 && hitbox(wn->input->x, wn->input->y, create_rect(707, 338, 528, 114)) && mouse_pressed(wn, SDL_BUTTON_LEFT))
		wn->menu->ask += 1;
	if ((wn->menu->ask & 0x0C) == 0 && hitbox(wn->input->x, wn->input->y, create_rect(707, 622, 528, 114)) && mouse_pressed(wn, SDL_BUTTON_LEFT))
		wn->menu->ask += (1 << 2);
	if ((wn->menu->ask & 0x30) == 0 && hitbox(wn->input->x, wn->input->y, create_rect(707, 853, 528, 114)) && mouse_pressed(wn, SDL_BUTTON_LEFT))
		wn->menu->ask += (1 << 4);
}

void	showhost(t_win *wn)
{
	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "menu", "Host"), NULL, NULL);
	if (wn->serv != NULL && ((t_server *)wn->serv)->username)
		print_one_line(wn, ((t_server *)wn->serv)->username, 880, 150);
	if ((wn->menu->ask & 0x03) == 3)
		print_one_line(wn, ((t_server *)wn->serv)->user[0].name, 880, 380);
	else if ((wn->menu->ask & 0x03) == 1 || (wn->menu->ask & 0x03) == 2)
		print_one_line(wn, "Waiting", 880, 380);
	else
		print_one_line(wn, "Free slot", 880, 380);
	if (((wn->menu->ask & 0x0C) >> 2) == 3)
		print_one_line(wn, ((t_server *)wn->serv)->user[1].name, 880, 660);
	else if (((wn->menu->ask & 0x0C) >> 2) == 1 || ((wn->menu->ask & 0x0C) >> 2) == 2)
		print_one_line(wn, "Waiting...", 880, 660);
	else
		print_one_line(wn, "Free slot", 880, 660);
	if (((wn->menu->ask & 0x30) >> 4) == 3)
		print_one_line(wn, ((t_server *)wn->serv)->user[2].name, 880, 890);
	else if (((wn->menu->ask & 0x30) >> 4) == 1 || ((wn->menu->ask & 0x30) >> 4) == 2)
		print_one_line(wn, "Waiting...", 880, 890);
	else
		print_one_line(wn, "Free slot", 880, 890);
//	SDL_RenderFillRect(wn->rend, create_rect(wn->xscreen / 1.4, wn->yscreen >> 1, 50, 50));
//	SDL_RenderFillRect(wn->rend, create_rect(wn->xscreen / 1.4, wn->yscreen / 1.6, 50, 50));
//	SDL_RenderFillRect(wn->rend, create_rect(wn->xscreen / 1.4, wn->yscreen / 1.4, 50, 50));
}
