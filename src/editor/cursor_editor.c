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

	if (((edit->var->cursor & 0xFFFF0000) >> 16) != CURSOR)
		selected = NULL;
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
{ // ATTENTION CHANGEMENT DE CURSEUR QUAND LE POLY N'EST PAS FINI
	t_point start;
	t_point end;
	SDL_Rect	rect;

	rect = define_rect(6 * wn->xscreen / 8, 0, 2 * wn->xscreen / 8, 0.5 * wn->yscreen / 8);
	if ((hitbox(wn->input->x, wn->input->y, &edit->tab->tab, 0) == TRUE && edit->tab->in == 1) || hitbox(wn->input->x, wn->input->y, &edit->tab->arrow, 0) == TRUE || hitbox(wn->input->x, wn->input->y, &rect, 0) == TRUE || wn->input->x < (wn->xscreen / 18))
		SDL_ShowCursor(SDL_ENABLE);
	else
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
	if (key_pressed(wn, SDL_SCANCODE_SPACE))
		edit->map->size = 1;
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
	if (key_pressed(wn, SDL_SCANCODE_SPACE))
	{
		edit->map->x = (wn->xscreen >> 1) - (edit->map->w);
		edit->map->y = (wn->yscreen >> 1) - ((edit->map->h / 2));
	}
	x = wn->input->x;
	y = wn->input->y;

}

void	select_cursor(t_win *wn, t_edit *edit)
{
	static SDL_Rect	box = {0, 0, 0, 0};
	static char		click = 0;
	t_point			**tmp;
	
	if (((edit->var->cursor & 0xFFFF0000) >> 16) == SELECT)
	{
		if (mouse_pressed(wn, SDL_BUTTON_LEFT))
		{
			if (click == 0)
			{
				box.x = wn->input->x;
				box.y = wn->input->y;
			}
			else if (wn->state[SDL_SCANCODE_LSHIFT] && edit->selected != NULL)
			{
				box.w = wn->input->x - box.x;
				box.h = wn->input->y - box.y;
				tmp = find_box_point(wn, edit, box);
				edit->selected = addtmptoselection(tmp, edit->selected);
			}
			else
			{
				box.w = wn->input->x - box.x;
				box.h = wn->input->y - box.y;
				if (edit->selected != NULL)
					free(edit->selected);
				edit->selected = find_box_point(wn, edit, box);
			}
			click = (click < 1 ? click += 1 : 0); // RESET
		}
		else
		{
			if (click == 1)
			{
				box.w = wn->input->x - box.x;
				box.h = wn->input->y - box.y;
			}
		}
		if (mouse_pressed(wn, SDL_BUTTON_RIGHT) || key_pressed(wn, SDL_SCANCODE_BACKSPACE))
		{
			if (edit->selected != NULL)
			{
				free(edit->selected);
				edit->selected = NULL;
			}
		}
	}
	SDL_SetRenderDrawColor(wn->rend, 255, 100, 100, 0);
	if (click >= 1)
		SDL_RenderDrawRect(wn->rend, &box);
}

void	wand_cursor(t_win *wn, t_edit *edit)
{
	static t_elem	*closer = NULL;
	int				diff;
	int				tmp;
	t_elem			*elem;
	t_point			*curr;

	elem = edit->elem;
	diff = 0x7FFFFFFF;
	if (edit->elem != NULL)
	{
		if ((closer != NULL && mouse_pressed(wn, SDL_BUTTON_RIGHT)) || wn->state[SDL_SCANCODE_LSHIFT])
			closer = NULL;
		if (((edit->var->cursor & 0xFFFF0000) >> 16) == WAND && mouse_pressed(wn, SDL_BUTTON_LEFT) && closer == NULL)
		{
			while (elem != NULL)
			{
				curr = find_center_linked(&elem);
				tmp = fabs((curr->x * edit->map->size * 10) - wn->input->x) + ((curr->y * edit->map->size * 10) - wn->input->y);	

				if (tmp < diff && tmp > 0)
				{
					diff = tmp;
					closer = elem;
				}
				elem = elem->next;
			}
			if (wn->state[SDL_SCANCODE_LSHIFT])
				edit->selected = addtmptoselection(cpy_elem_selected(closer), edit->selected); // NEED SECURE
			else
			{
				free(edit->selected);
				edit->selected = cpy_elem_selected(closer); // NEED SECURE
			}
		}
	}
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
	if (key_pressed(wn, SDL_SCANCODE_BACKSPACE))
		edit->var->swapvar = 0;
	x = wn->input->x;
	y = wn->input->y;
}

void	resize_cursor(t_win *wn, t_edit *edit)
{
	static t_point	range = {0,0,0, NULL};
	static t_point  *center = NULL;
	static int 		x = 0;
	static int 		y = 0;
	static char		actif = -1;
	// t_point			tmp;
	int				nb;

	if (!(((edit->var->cursor & 0xFFFF0000) >> 16) == RESIZE) || actif == -1)
	{
		x = wn->input->x;
		y = wn->input->y;
		actif = -1;
	}
	if (mouse_pressed(wn, SDL_BUTTON_LEFT) && (((edit->var->cursor & 0xFFFF0000) >> 16) == RESIZE))
		actif *= -1;
	if ((center == NULL || (((edit->var->cursor & 0xFFFF0000) >> 16) != RESIZE)) && edit->selected != NULL)
	{
		center = find_center(edit->selected);
		edit->center = &center;
	}
	if (edit->selected != NULL && center != NULL)
	{
		nb = 0;
		while (edit->selected[nb] != NULL)
		{
			range.x = center->x - edit->selected[nb]->x;
			range.y = center->y - edit->selected[nb]->y;
			range = normalize(range);
			if ((fabsf(center->x - edit->selected[nb]->x) + fabsf(center->y - edit->selected[nb]->y)) > 10 && (((range.x / 100) * (x - wn->input->x) < 0) || ((range.y / 100) * (y - wn->input->y < 0))))
			{
				edit->selected[nb]->x += (range.x / 100) * (x - wn->input->x);
				edit->selected[nb]->y += (range.y / 100) * (y - wn->input->y);
			}
			nb++;
		}
	}
	x = wn->input->x;
	y = wn->input->y;
}

void	rotate_cursor(t_win *wn, t_edit *edit) // ROTATE
{
	static t_point  *center = NULL;
	static float	saverot = 0;
	static float	anglex = 0;
	static int 		x = 0;
	static int 		y = 0;
	t_point			tmp;
	int				nb;

	if (center == NULL && edit->selected == NULL)
		;
	else if (edit->selected != NULL && (edit->var->cursor & 0xFFFF0000) >> 16 == ROTATE)
	{
		center = find_center(edit->selected);
		edit->center = &center;
	}
	if (mouse_pressed(wn, SDL_BUTTON_LEFT))
		saverot = 0;
	if (center != NULL && wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT) && (edit->var->cursor & 0xFFFF0000) >> 16 == ROTATE)
	{
		anglex = (float)((x - wn->input->x)) / 4;
		anglex += (float)((y - wn->input->y)) / 4;
		nb = 0;
		while (edit->selected[nb] != NULL)
		{
			tmp.x = edit->selected[nb]->x - center->x;
			tmp.y = edit->selected[nb]->y - center->y;
			edit->selected[nb]->x = (cos(anglex * 0.0174533) * (tmp.x)) - (sin(anglex * 0.0174533) * (tmp.y)) + center->x;
			edit->selected[nb]->y = (sin(anglex * 0.0174533) * (tmp.x)) + (cos(anglex * 0.0174533) * (tmp.y)) + center->y;
			nb++;
		}
		saverot += anglex;
	}
	if (mouse_pressed(wn, SDL_BUTTON_RIGHT) && edit->selected != NULL)
	{
		nb = 0;
		while (edit->selected[nb] != NULL)
		{
			tmp.x = edit->selected[nb]->x - center->x;
			tmp.y = edit->selected[nb]->y - center->y;
			edit->selected[nb]->x = (cos(-saverot * 0.0174533) * (tmp.x)) - (sin(-saverot * 0.0174533) * (tmp.y)) + center->x;
			edit->selected[nb]->y = (sin(-saverot * 0.0174533) * (tmp.x)) + (cos(-saverot * 0.0174533) * (tmp.y)) + center->y;
			nb++;
		}
		saverot = 0;
	}
	x = wn->input->x;
	y = wn->input->y;
}
