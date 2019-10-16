/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printscreen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:07:03 by lomasse           #+#    #+#             */
/*   Updated: 2019/08/04 15:16:30 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		print_background_editor(t_win *wn)
{
	SDL_Surface		*surface;
	SDL_Texture		*texture;

	surface = SDL_CreateRGBSurface(0, wn->xscreen, wn->yscreen, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 66, 66, 66));
	texture = SDL_CreateTextureFromSurface(wn->rend, surface);
	SDL_FreeSurface(surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, NULL) < 0)
		stop_exec("rendercopy failed\n", wn);
	SDL_DestroyTexture(texture);
}

void		change_bloc(t_win *wn, t_edit *edit)
{
	int x;
	int y;
	SDL_Rect	tab;

	x = wn->input->x;
	y = wn->input->y;
	if (hitbox(x, y, &edit->tab->arrow, 0) == TRUE)
		edit->tab->in = -edit->tab->in;
	tab = define_rect(6 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 2 * wn->xscreen / 8 / 4, 0.5 * wn->yscreen / 8);
	if (hitbox(x, y, &tab, 0) == TRUE && edit->tab->in == 1)
		edit->tab->onglet = 0;
	tab = define_rect(6.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 2 * wn->xscreen / 8 / 4, 0.5 * wn->yscreen / 8);	
	if (hitbox(x, y, &tab, 0) == TRUE && edit->tab->in == 1)
		edit->tab->onglet = 1;
	tab = define_rect(7 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 2 * wn->xscreen / 8 / 4, 0.5 * wn->yscreen / 8);	
	if (hitbox(x, y, &tab, 0) == TRUE && edit->tab->in == 1)
		edit->tab->onglet = 2;
	tab = define_rect(7.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 2 * wn->xscreen / 8 / 4, 0.5 * wn->yscreen / 8);
	if (hitbox(x, y, &tab, 0) == TRUE && edit->tab->in == 1)
		edit->tab->onglet = 3;
}

static int	is_between(double x, double min, double max)
{
	if (x >= min && x < max)
		return (0);
	return (1);
}

static void	checkcursor(t_win *wn, t_edit *edit)
{
	if (mouse_pressed(wn, SDL_BUTTON_LEFT))
		if (!is_between(wn->input->x, wn->xscreen / 101, wn->xscreen / 32.54))
			if (!is_between(wn->input->y, wn->yscreen / 8.64, wn->yscreen / 1.434))
				edit->var->cursor = ((wn->input->y - (wn->yscreen / 8.64)) / 58) + (edit->var->cursor & 0xFFFF0000);
	(edit->var->cursor & 0xFF) < 0 || (edit->var->cursor & 0xFF) > 10 ? edit->var->cursor = edit->var->cursor & 0xFFFF0000 : 0;
}

static void	showbgpics(t_win *wn, t_edit *edit)
{
	SDL_Rect pos;

	pos.x = edit->map->x + edit->loadbg->x;
	pos.y = edit->map->y + edit->loadbg->y;
	pos.w = edit->map->w + (edit->loadbg->w * edit->loadbg->size);
	pos.h = edit->map->h + (edit->loadbg->h * edit->loadbg->size);
	SDL_RenderCopy(wn->rend, edit->tab->bg_pics, NULL, &pos);
}

void		printeditor(t_win *wn)
{
	t_edit 	*edit;

	edit = ((t_edit *)(*wn).edit);
	print_background_editor(wn);
	if (edit->tab->bg_pics != NULL)
		showbgpics(wn, edit);
	showmap(wn, edit);
	checkcursor(wn, edit);
	which_cursor(wn, edit);
	
	info_bar(wn, edit);// <=============== ICI 30MO per ticks
	print_tab_editor(wn, edit); // <============== ICI 250MO per ticks
	SDL_Rect	*pos = create_rect(0, 0, 72, 1080);
	SDL_RenderCopy(wn->rend, findtexture(wn, "editor", "affichage", "cursor_panel"), NULL, pos);
	free(pos);
	edit->indice->on == 1 ? print_x_y_z(wn, edit) : 0;
	edit->var->cursor = ((edit->var->cursor & 0xFFFF) << 16) + (edit->var->cursor & 0xFFFF); // Save cursor
	print_save_and_reset(wn, edit);
	check_hitbox(wn, wn->edit);
	edit->var->find == 1 ? draw_to_find_position(wn, wn->edit) : 0;
	// test_slider(wn);
}
