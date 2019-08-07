/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_editor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 12:06:16 by lomasse           #+#    #+#             */
/*   Updated: 2019/08/07 19:41:04 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	cursor(t_win *wn, t_edit *edit)
{
	static t_point	*selected = NULL;
	static int		x = 0;
	static int		y = 0;
	int				i;

	if (((edit->var->cursor & 0xFFFF0000) >> 16) == CURSOR && wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (mouse_pressed(wn, SDL_BUTTON_LEFT) && edit->selected == NULL)
			selected = find_closer_point(wn, edit);
		if (selected != NULL)
		{
			selected->x += (wn->input->x - x) / edit->map->size / 10;
			selected->y += (wn->input->y - y) / edit->map->size / 10;
		}
		else if (edit->selected != NULL)
		{
			i = 0;
			while (edit->selected[i] != NULL)
			{
				edit->selected[i]->x += (wn->input->x - x) / edit->map->size / 10;
				edit->selected[i]->y += (wn->input->y - y) / edit->map->size / 10;
				i++;
			}
		}
	}
	x = wn->input->x;
	y = wn->input->y;
}

void	draw_cursor(t_win *wn, t_edit *edit)
{
	t_point start;
	t_point end;

	(void)edit;
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(wn->rend, 238, 10, 214, 0);
	start = create_t_point(wn->input->x, 0);
	end = create_t_point(wn->input->x, wn->yscreen);
	bresenham(wn, &start, &end);
	start = create_t_point(0, wn->input->y);
	end = create_t_point(wn->xscreen, wn->input->y);
	bresenham(wn, &start, &end);
}

void	erase_cursor(t_win *wn, t_edit *edit)
{
	static t_point	*selected = NULL;
	static int		x = 0;
	static int		y = 0;

	if (((edit->var->cursor & 0xFFFF0000) >> 16) == ERASE && wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (mouse_pressed(wn, SDL_BUTTON_LEFT))
		{
			selected = find_point_before(wn, edit);
			if (selected != NULL && selected->next != NULL && selected->next->next != NULL)
				selected->next = selected->next->next;
		}
		if (selected != NULL)
		{
			selected->x += (wn->input->x - x) / edit->map->size / 10;
			selected->y += (wn->input->y - y) / edit->map->size / 10;
		}
	}
	x = wn->input->x;
	y = wn->input->y;
}

void	zoom_cursor(t_win *wn, t_edit *edit)
{
	if (edit->map->size < 6 && mouse_pressed(wn, SDL_BUTTON_LEFT) && ((edit->var->cursor & 0xFFFF0000) >> 16) == ZOOM)
		edit->map->size += 0.2;
	if (edit->map->size > 0.4 && mouse_pressed(wn, SDL_BUTTON_RIGHT) && ((edit->var->cursor & 0xFFFF0000) >> 16) == ZOOM)
		edit->map->size -= 0.2;
}

void	hand_cursor(t_win *wn, t_edit *edit)
{
	static int x = 0;
	static int y = 0;

	if (((edit->var->cursor & 0xFFFF0000) >> 16) == HAND && wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		edit->map->x += wn->input->x - x;
		edit->map->y += wn->input->y - y;
	}
	x = wn->input->x;
	y = wn->input->y;

}

void	select_cursor(t_win *wn, t_edit *edit)
{
	static SDL_Rect	box = {0, 0, 0, 0};
	static char		click = 0;
	
	if (((edit->var->cursor & 0xFFFF0000) >> 16) == SELECT)
	{
		if (mouse_pressed(wn, SDL_BUTTON_LEFT))
		{
			if (click == 0)
			{
				box.x = wn->input->x;
				box.y = wn->input->y;
			}
			else
			{
				box.w = wn->input->x - box.x;
				box.h = wn->input->y - box.y;
				if (edit->selected != NULL)
					free(edit->selected);
				edit->selected = find_box_point(wn, edit, box);
				//find point in box
				// ADD SQUARE TO LIST
			}
			click = (click == 0 ? 1 : 0); // RESET
		}
		else
		{
			if (click == 1)
			{
				box.w = wn->input->x - box.x;
				box.h = wn->input->y - box.y;
			}
		}
	}
	SDL_SetRenderDrawColor(wn->rend, 255, 100, 100, 0);
	if (click >= 1)
		SDL_RenderDrawRect(wn->rend, &box);
}

void	wand_cursor(t_win *wn, t_edit *edit)
{
	(void)wn;
	(void)edit;
}

void	form_cursor(t_win *wn, t_edit *edit)
{
	static SDL_Rect square = {0, 0, 0, 0};
	static char		click = 0;
	
	if (((edit->var->cursor & 0xFFFF0000) >> 16) == FORM)
	{
		if (mouse_pressed(wn, SDL_BUTTON_LEFT))
		{
			if (click == 0)
			{
				square.x = wn->input->x;
				square.y = wn->input->y;
			}
			else
			{
				square.w = wn->input->x - square.x;
				square.h = wn->input->y - square.y;
				// ADD SQUARE TO LIST
			}
			//click = (click == 0 ? 1 : 0); // RESET
			click += 1;
		}
		else
		{
			if (click == 1)
			{
				square.w = wn->input->x - square.x;
				square.h = wn->input->y - square.y;
			}
		}
	}
	if (click >= 1)
		SDL_RenderDrawRect(wn->rend, &square);
}

void	swap_cursor(t_win *wn, t_edit *edit)
{
	static int x = 0;
	static int y = 0;

	if (((edit->var->cursor & 0xFFFF0000) >> 16) == SWAP && wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		edit->var->swapvar += ((short)((wn->input->x - x) & 0xFFFF) << 16);
		edit->var->swapvar += ((short)(wn->input->y - y) & 0xFFFF);
	}
	x = wn->input->x;
	y = wn->input->y;
}
void	resize_cursor(t_win *wn, t_edit *edit)
{
	(void)wn;
	(void)edit;
}
