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
}

void		change_bloc(t_win *wn, t_edit *edit)
{
	int x;
	int y;
	SDL_Rect	tab;

	x = wn->input->x;
	y = wn->input->y;
	if (hitbox(x, y, &edit->tab->arrow) == TRUE)
		edit->tab->in = -edit->tab->in;
	tab = define_rect(6 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 2 * wn->xscreen / 8 / 4, 0.5 * wn->yscreen / 8);
	if (hitbox(x, y, &tab) == TRUE && edit->tab->in == 1)
		edit->tab->onglet = 0;
	tab = define_rect(6.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 2 * wn->xscreen / 8 / 4, 0.5 * wn->yscreen / 8);	
	if (hitbox(x, y, &tab) == TRUE && edit->tab->in == 1)
		edit->tab->onglet = 1;
	tab = define_rect(7 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 2 * wn->xscreen / 8 / 4, 0.5 * wn->yscreen / 8);	
	if (hitbox(x, y, &tab) == TRUE && edit->tab->in == 1)
		edit->tab->onglet = 2;
	tab = define_rect(7.5 * wn->xscreen / 8, 0.5 * wn->yscreen / 8, 2 * wn->xscreen / 8 / 4, 0.5 * wn->yscreen / 8);
	if (hitbox(x, y, &tab) == TRUE && edit->tab->in == 1)
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
		if (!is_between(wn->input->x, wn->xscreen / 128, wn->xscreen / 20.21))
			if (!is_between(wn->input->y, wn->yscreen / 6.28, wn->yscreen / 1.1675))
				edit->var->cursor = (wn->input->y - (wn->yscreen / 6.28)) / (wn->yscreen / 14.4) + (edit->var->cursor & 0xFFFF0000);
	(edit->var->cursor & 0xFF) < 0 || (edit->var->cursor & 0xFF) > 9 ? edit->var->cursor = edit->var->cursor & 0xFFFF0000 : 0;
}

static void	showbgpics(t_win *wn, t_edit *edit)
{
	SDL_Rect pos;

	pos.x = edit->map->x;//edit->loadbg->x;
	pos.y = edit->map->y;//edit->loadbg->y;
	pos.w = edit->map->w;
	pos.h = edit->map->h;
	SDL_RenderCopy(wn->rend, edit->tab->bg_pics, NULL, &pos);
}

void		printeditor(t_win *wn)
{
	t_edit 	*edit;

	edit = ((t_edit *)(*wn).edit);
	print_background_editor(wn);
	if (edit->tab->bg_pics != NULL)
		showbgpics(wn, edit);
	// (is_path_ok(wn, wn->bg_map.path) == 0 && wn->edit_image.bgh == 0) ? load_background(wn) : 0;
	showmap(wn, edit);
	checkcursor(wn, edit);
	which_cursor(wn, edit);
	// print_bgh_editor(wn, edit);
	print_tab_editor(wn, edit);
	SDL_RenderCopy(wn->rend, findtexture(wn, "editor", "affichage", "cursor_panel"), NULL, NULL);
	edit->indice->on == 1 ? print_x_y_z(wn, edit) : 0;
	edit->var->cursor = ((edit->var->cursor & 0xFFFF) << 16) + (edit->var->cursor & 0xFFFF); // Save cursor
	print_save_and_reset(wn, edit);
	// test_slider(wn);
}
