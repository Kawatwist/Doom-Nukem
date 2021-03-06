/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:01:32 by llejeune          #+#    #+#             */
/*   Updated: 2019/06/11 15:01:34 by llejeune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void		create_text_texture(t_win *wn, SDL_Texture *texture, int x, SDL_Color color)
{
	char	*text;

	text = ft_itoa(x);
	texture != NULL ? SDL_DestroyTexture(texture) : 0;
	wn->editext.surface = TTF_RenderText_Solid(wn->fonts->arial,
		text, color);
	free(text);
	texture = SDL_CreateTextureFromSurface(wn->rend, wn->editext.surface);
	SDL_QueryTexture(texture, NULL, NULL,
		&wn->editext.src.w, &wn->editext.src.h);
	SDL_FreeSurface(wn->editext.surface);
	if (SDL_RenderCopy(wn->rend, texture, NULL, &wn->editext.src) < 0)
		stop_exec("rendercopy failed\n", wn);
}

void		print_x_y_z(t_win *wn)
{
	int x;
	int y;

	x = ((wn->input->x - wn->map->x) * wn->editext.map_w) / wn->map->w;
	y = ((wn->input->y - wn->map->y) * wn->editext.map_h) / wn->map->h;
	if (x >= 0 && x <= wn->editext.map_w && y <= wn->editext.map_h && y >= 0)
	{
		wn->editext.src.x = wn->input->x + 10;
		wn->editext.src.y = wn->input->y + 1;
		create_text_texture(wn, wn->editext.texture_x,
			x, wn->color.violetfonce);
		wn->editext.src.y = wn->input->y + wn->editext.src.h;
		create_text_texture(wn, wn->editext.texture_y, y, wn->color.violet);
		wn->editext.src.y += wn->editext.src.h;
		create_text_texture(wn, wn->editext.texture_z,
			wn->editext.val_z, wn->color.violetrose);
	}
}

static void	bloc_cursor(t_win *wn)
{
	t_point start;
	t_point end;

	SDL_ShowCursor(SDL_DISABLE);
	wn->editext.on = 1;
	SDL_SetRenderDrawColor(wn->rend, 238, 10, 214, 0);
	start = create_t_point(wn->input->x, 0);
	end = create_t_point(wn->input->x, wn->yscreen);
	bresenham(wn, &start, &end);
	start = create_t_point(0, wn->input->y);
	end = create_t_point(wn->xscreen, wn->input->y);
	bresenham(wn, &start, &end);
}

void		which_cursor(t_win *wn)
{
	if (wn->input->x < (wn->xscreen / 7 * 5.5)
		&& wn->input->y < (wn->yscreen / 7 * 6))
		bloc_cursor(wn);
	else
	{
		if (wn->input->y > (3 * wn->yscreen / 7)
			&& wn->input->y < (5.75 * wn->yscreen / 7)
			&& wn->edit_image.in == 0)
			bloc_cursor(wn);
		else
			wn->editext.on = 0;
	}
}
