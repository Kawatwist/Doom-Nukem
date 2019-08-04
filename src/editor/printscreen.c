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

static int	is_between(double x, double min, double max)
{
	if (x >= min && x < max)
		return (0);
	return (1);
}

void		change_bloc(t_win *wn, t_edit *edit)
{
	int x;
	int y;

	x = wn->input->x;
	y = wn->input->y;
	if (is_between(x, 5.5 * wn->xscreen / 7, 5.75 * wn->xscreen / 7) == 0
		&& is_between(y, 0, 0.25 * wn->yscreen / 7) == 0)
		edit->tab->bgh = 1;
	else if (is_between(x, 5.5 * wn->xscreen / 7, 5.75 * wn->xscreen / 7) == 0
		&& is_between(y, 0.25, 0.5 * wn->yscreen / 7) == 0)
		edit->tab->bgh = 0;
	if (is_between(x, 6.75 * wn->xscreen / 7, wn->xscreen) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && edit->tab->in == 1)
		edit->tab->in = 0;
	else if (is_between(x, 6.75 * wn->xscreen / 7, wn->xscreen) == 0 && is_between(y, 5.75 *
		wn->yscreen / 7, 6 * wn->yscreen / 7) == 0 && edit->tab->in == 0)
		edit->tab->in = 1;
	if (is_between(x, 5.5 * wn->xscreen / 7, 5.75 * wn->xscreen / 7) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && edit->tab->in == 1)
		edit->tab->tbp = 0;
	if (is_between(x, 5.75 * wn->xscreen / 7, 6 * wn->xscreen / 7) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && edit->tab->in == 1)
		edit->tab->tbp = 1;
	if (is_between(x, 6 * wn->xscreen / 7, 6.25 * wn->xscreen / 7) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && edit->tab->in == 1)
		edit->tab->tbp = 2;
}

static void	checkcursor(t_win *wn, t_edit *edit)
{
	if (mouse_pressed(wn, SDL_BUTTON_LEFT))
		if (!is_between(wn->input->x, wn->xscreen / 128, wn->xscreen / 20.21))
			if (!is_between(wn->input->y, wn->yscreen / 6.28, wn->yscreen / 1.1675))
				edit->var->cursor = (wn->input->y - (wn->yscreen / 6.28)) / (wn->yscreen / 14.4) + (edit->var->cursor & 0xFFFF0000);
	(edit->var->cursor & 0xFF) < 0 || (edit->var->cursor & 0xFF) > 9 ? edit->var->cursor = edit->var->cursor & 0xFFFF0000 : 0;
}

void		printeditor(t_win *wn)
{
	t_edit 	*edit;

	edit = ((t_edit *)(*wn).edit);
	print_background_editor(wn);
	// (is_path_ok(wn, wn->bg_map.path) == 0 && wn->edit_image.bgh == 0) ? load_background(wn) : 0;
	showmap(wn, edit);
	checkcursor(wn, edit);
	which_cursor(wn, edit);
	// print_tools_editor(wn, edit);
	print_bgh_editor(wn, edit);
	print_tbp_editor(wn, edit);
	SDL_RenderCopy(wn->rend, findtexture(wn, "editor", "affichage", "cursor_panel"), NULL, NULL);
	edit->indice->on == 1 ? print_x_y_z(wn, edit) : 0;
	edit->var->cursor = ((edit->var->cursor & 0xFFFF) << 16) + (edit->var->cursor & 0xFFFF); // Save cursor
}
