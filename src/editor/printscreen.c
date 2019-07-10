/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printscreen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 11:07:03 by lomasse           #+#    #+#             */
/*   Updated: 2019/05/24 13:48:54 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void		change_bloc(t_win *wn)
{
	int x;
	int y;

	x = wn->input->x;
	y = wn->input->y;
	if (is_between(x, 5.5 * wn->xscreen / 7, 5.75 * wn->xscreen / 7) == 0
		&& is_between(y, 0, 0.25 * wn->yscreen / 7) == 0)
		wn->edit_image.bgh = 1;
	else if (is_between(x, 5.5 * wn->xscreen / 7, 5.75 * wn->xscreen / 7) == 0
		&& is_between(y, 0.25, 0.5 * wn->yscreen / 7) == 0)
		wn->edit_image.bgh = 0;
	if (is_between(x, 6.75 * wn->xscreen / 7, wn->xscreen) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && wn->edit_image.in == 1)
		wn->edit_image.in = 0;
	else if (is_between(x, 6.75 * wn->xscreen / 7, wn->xscreen) == 0 && is_between(y, 5.75 *
		wn->yscreen / 7, 6 * wn->yscreen / 7) == 0 && wn->edit_image.in == 0)
		wn->edit_image.in = 1;
	if (is_between(x, 5.5 * wn->xscreen / 7, 5.75 * wn->xscreen / 7) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && wn->edit_image.in == 1)
		wn->edit_image.tbp = 0;
	if (is_between(x, 5.75 * wn->xscreen / 7, 6 * wn->xscreen / 7) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && wn->edit_image.in == 1)
		wn->edit_image.tbp = 1;
	if (is_between(x, 6 * wn->xscreen / 7, 6.25 * wn->xscreen / 7) == 0 && is_between(y, 3 *
		wn->yscreen / 7, 3.25 * wn->yscreen / 7) == 0 && wn->edit_image.in == 1)
		wn->edit_image.tbp = 2;
}

static void		test_pop_up(t_win *wn)
{
	SDL_Rect 		rect;
	

	rect = define_rect(wn->xscreen / 3, wn->yscreen / 3, 500, 300);
	
	pop_up_message(wn, "blablablablabla ?", &rect);
}

void		printeditor(t_win *wn)
{
	print_background_editor(wn);
	// (is_path_ok(wn, wn->bg_map.path) == 0 && wn->edit_image.bgh == 0) ? load_background(wn) : 0;
	showmap(wn);
	which_cursor(wn);
	print_tools_editor(wn);
	print_bgh_editor(wn);
	print_tbp_editor(wn);
	wn->editext.on == 1 ? print_x_y_z(wn) : 0;
	test_pop_up(wn);
}
