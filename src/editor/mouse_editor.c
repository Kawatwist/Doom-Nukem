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
	if (x >= 0 && x <= (edit->indice->map_w / 10) && y <= (edit->indice->map_h / 10) && y >= 0)
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

void		which_cursor(t_win *wn, t_edit *edit)
{
	if (hitbox(wn->input->x, wn->input->y, &edit->tab->tab) == FALSE && wn->input->x > (wn->xscreen / 18))
		edit->indice->on = 1;
	else
	{
		if ((hitbox(wn->input->x, wn->input->y, &edit->tab->tab) == TRUE && edit->tab->in != 1))
			edit->indice->on = 1;
		else
		{
			edit->indice->on = 0;
		}
	}
	hitbox(wn->input->x, wn->input->y, &edit->tab->arrow) == TRUE ? edit->indice->on = 0 : 0;
	edit->cursor_fct[edit->var->cursor & 0xFF](wn, edit);
}
