/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:01:32 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/04 15:06:12 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

void		create_text_texture(t_win *wn, SDL_Texture *texture, int x, SDL_Color color)
{
	char	*text;

	text = ft_itoa(x);
	texture != NULL ? SDL_DestroyTexture(texture) : 0;
	((t_edit *)wn->edit)->indice->surface = TTF_RenderText_Solid(wn->fonts->arial,
		text, color);
	free(text);
	texture = SDL_CreateTextureFromSurface(wn->rend, ((t_edit *)wn->edit)->indice->surface);
	SDL_QueryTexture(texture, NULL, NULL,
		&((t_edit *)wn->edit)->indice->src.w, &((t_edit *)wn->edit)->indice->src.h);
	SDL_FreeSurface(((t_edit *)wn->edit)->indice->surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, &((t_edit *)wn->edit)->indice->src) < 0)
		stop_exec("rendercopy failed\n", wn);
}

void		print_x_y_z(t_win *wn, t_edit *edit)
{
	int x;
	int y;

	x = ((wn->input->x - edit->map->x) * edit->indice->map_w) / edit->map->w / 10;
	y = ((wn->input->y - edit->map->y) * edit->indice->map_h) / edit->map->h / 10;
	if (x >= 0 && x <= edit->indice->map_w && y <= edit->indice->map_h && y >= 0)
	{
		edit->indice->src.x = wn->input->x + 10;
		edit->indice->src.y = wn->input->y + 1;
		create_text_texture(wn, edit->indice->texture_x,
			x, wn->color.violetfonce);
		edit->indice->src.y = wn->input->y + edit->indice->src.h;
		create_text_texture(wn, edit->indice->texture_y, y, wn->color.violet);
		edit->indice->src.y += edit->indice->src.h;
		create_text_texture(wn, edit->indice->texture_z,
			edit->indice->val_z, wn->color.violetrose);
	}
}
/*
static void	bloc_cursor(t_win *wn)
{
	t_point start;
	t_point end;

	SDL_ShowCursor(SDL_DISABLE);
	((t_edit *)wn->edit)->indice->on = 1;
	SDL_SetRenderDrawColor(wn->rend, 238, 10, 214, 0);
	start = create_t_point(wn->input->x, 0);
	end = create_t_point(wn->input->x, wn->yscreen);
	bresenham(wn, &start, &end);
	start = create_t_point(0, wn->input->y);
	end = create_t_point(wn->xscreen, wn->input->y);
	bresenham(wn, &start, &end);
}
*/
void		which_cursor(t_win *wn, t_edit *edit)
{
/*	if (wn->input->x < (wn->xscreen / 7 * 5.5)
		&& wn->input->y < (wn->yscreen / 7 * 6))
		bloc_cursor(wn);
	else
	{
		if (wn->input->y > (3 * wn->yscreen / 7)
			&& wn->input->y < (5.75 * wn->yscreen / 7)
			&& edit->tab->in == 0)
			bloc_cursor(wn);
		else
			edit->indice->on = 0;
	}
*/
	(void)wn;
	edit->cursor_fct[edit->var->cursor & 0xFF](wn, edit);
}
