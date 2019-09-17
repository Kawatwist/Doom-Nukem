/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 19:02:08 by lomasse           #+#    #+#             */
/*   Updated: 2019/08/04 13:28:36 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	center_map(t_win *wn, t_edit *edit)
{
	edit->map->h = edit->indice->map_h;
	edit->map->w = edit->indice->map_w;
	edit->map->x = (wn->xscreen / 3.5) - (edit->map->w / 2);
	edit->map->y = (wn->yscreen / 3) - ((edit->map->h / 2));
	edit->map->size = 1.6;
}

void		check_hitbox(t_win *wn, t_edit *edit)
{
	SDL_Rect cursor;

	cursor.x =  wn->input->x;
	cursor.y =  wn->input->y;
	(void)edit;
	SDL_SetRenderDrawColor(wn->rend, 255,255,255, 255);
	if (boxhitbox(wn->rend, &cursor, create_rect(720, 200, 200, 200), 0)) // SHOW BACKGROUND MAP
	{
		if (edit->tab->bg_pics != NULL && mouse_pressed(wn, SDL_BUTTON_LEFT))
		{
			free(edit->tab->bg_pics);
			edit->tab->bg_pics = NULL;
		}
	}
	if (mouse_pressed(wn, SDL_BUTTON_LEFT) && boxhitbox(wn->rend, & cursor, create_rect(edit->tab->bg.x, edit->tab->bg.y, edit->tab->bg.w, edit->tab->bg.h), 1))
	{ //  CAN BE MERGE WITH OTHER IF NEEDING MOUSE PRESSING
		edit->loadbg->flag = set_bit(edit->loadbg->flag, WRITE);
	}
}

void		resetmap(t_win *wn, t_edit *edit)
{
	t_elem 		*curr;

	while (edit->elem != NULL)
	{
		curr = edit->elem;
		edit->elem = edit->elem->next;
		remove_poly(curr);
	}
	edit->elem = NULL;
	center_map(wn, edit);
}

static void	control_map(t_win *wn, t_edit *edit)
{
	key_pressed(wn, SDL_SCANCODE_SPACE) ? center_map(wn, edit) : 0;
	wn->state[SDL_SCANCODE_A] ? edit->map->x -= (6.5 - edit->map->size) : 0;
	wn->state[SDL_SCANCODE_D] ? edit->map->x += (6.5 - edit->map->size) : 0;
	wn->state[SDL_SCANCODE_W] ? edit->map->y -= (6.5 - edit->map->size) : 0;
	wn->state[SDL_SCANCODE_S] ? edit->map->y += (6.5 - edit->map->size) : 0;
	wn->state[SDL_SCANCODE_E] && edit->map->size < 6
		&& !wn->old[SDL_SCANCODE_E] ? edit->map->size *= 1.2 : 0;
	wn->state[SDL_SCANCODE_E]
		&& edit->map->size >= 6 ? edit->map->size = 6 : 0;
	wn->state[SDL_SCANCODE_Q] && edit->map->size > 0.5
		&& !wn->old[SDL_SCANCODE_Q] ? edit->map->size *= 0.8 : 0;
	wn->state[SDL_SCANCODE_Q]
		&& edit->map->size <= 0.5 ? edit->map->size = 0.5 : 0;
	wn->state[SDL_SCANCODE_BACKSPACE] ? resetmap(wn, edit) : 0;
	!wn->old[SDL_SCANCODE_P] && wn->state[SDL_SCANCODE_P] ? edit->var->find = -edit->var->find : 0;
}

static void	keyboardtool(t_win *wn, t_edit *edit)
{
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->interface = MENU : 0;
	!(wn->flag & CONSOLE) && key_pressed(wn, SDL_SCANCODE_ESCAPE) ? wn->menu->choice = 0 : 0;
	edit->map->h = edit->indice->map_h * edit->map->size;
	edit->map->w = edit->indice->map_w * edit->map->size;
}

void		inputeditor(t_win *wn)
{
	if (!(wn->input->oldmouse & SDL_BUTTON(SDL_BUTTON_LEFT))
		&& (wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT)))
		zoom_mouse_map(wn, wn->edit, 1);
	else if (!(wn->input->oldmouse & SDL_BUTTON(SDL_BUTTON_RIGHT))
		&& (wn->input->mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)))
		zoom_mouse_map(wn, wn->edit, 0);
	if (!(wn->input->oldmouse & SDL_BUTTON(SDL_BUTTON_LEFT))
		&& (wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT)))
		change_bloc(wn, wn->edit);
	!(((t_edit *)wn->edit)->loadbg->flag & WRITE) ? control_map(wn, wn->edit) : 0;
	keyboardtool(wn, wn->edit);
	mouse_input_poly(wn, wn->edit);
}
