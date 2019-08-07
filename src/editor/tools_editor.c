/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llejeune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:51:44 by llejeune          #+#    #+#             */
/*   Updated: 2019/08/07 19:56:31 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <editor.h>

t_point		**find_box_point(t_win *wn, t_edit *edit, SDL_Rect box)
{
	t_point **ret;
	t_elem	*elem;
	t_point *point;
	int		nb;

	(void)wn;
	nb = 0;
	elem = edit->elem;
	while(elem)
	{
		point = elem->point;
		while (point)
		{
			if (hitbox(edit->map->x + (point->x * edit->map->size * 10), edit->map->y + point->y * edit->map->size * 10, &box))
				nb++;
			point = point->next;
		}
		elem = elem->next;
	}
	printf("%d\n", nb);
	ret = malloc(sizeof(t_point) * nb); // SECURE	
	elem = edit->elem;
	nb = 0;
	while(elem)
	{
		point = elem->point;
		while (point)
		{
			if (hitbox(edit->map->x + (point->x * edit->map->size * 10), edit->map->y + point->y * edit->map->size * 10, &box))
			{
				printf("BEFORE %d\n", nb);
				ret[nb] = point;
				nb++;
			}
			point = point->next;
		}
		elem = elem->next;
	}
	printf("%d\n", nb);
	ret[nb] = NULL;
	printf("APRES\n");
	return (ret);
}

t_point		*find_point_before(t_win *wn, t_edit *edit)
{
	int		distance;
	int		olddistance;
	t_elem	*elem;
	t_point	*check;
	t_point	*point;

	elem = edit->elem;
	distance = 999;
	olddistance = 999;
	while (elem != NULL)
	{
		check = elem->point;
		while (check != NULL && check->next != NULL)
		{
			distance = (wn->input->x - (edit->map->x + (check->x * edit->map->size * 10)) > 0
					? wn->input->x - (edit->map->x + (check->x * edit->map->size * 10))
					: (edit->map->x + (check->x * edit->map->size * 10)) - wn->input->x)
					+ (wn->input->y - (edit->map->y + (check->y * edit->map->size * 10)) > 0
					? wn->input->y - (edit->map->y + (check->y * edit->map->size * 10))
					: (edit->map->y + (check->y * edit->map->size * 10)) - wn->input->y);
			if (distance < olddistance)
			{
				point = check;
				olddistance = distance;
			}
			if (!olddistance)
				return (point);
			check = check->next;
		}
		elem = elem->next;
	}
	if (olddistance == 999)
		return (NULL);
	return (point);
}

t_point		*find_closer_point(t_win *wn, t_edit *edit)
{
	int		distance;
	int		olddistance;
	t_elem	*elem;
	t_point	*check;
	t_point	*point;

	elem = edit->elem;
	distance = 999;
	olddistance = 999;
	while (elem != NULL)
	{
		check = elem->point;
		while (check != NULL)
		{
			distance = (wn->input->x - (edit->map->x + (check->x * edit->map->size * 10)) > 0
					? wn->input->x - (edit->map->x + (check->x * edit->map->size * 10))
					: (edit->map->x + (check->x * edit->map->size * 10)) - wn->input->x)
					+ (wn->input->y - (edit->map->y + (check->y * edit->map->size * 10)) > 0
					? wn->input->y - (edit->map->y + (check->y * edit->map->size * 10))
					: (edit->map->y + (check->y * edit->map->size * 10)) - wn->input->y);
			if (distance < olddistance)
			{
				point = check;
				olddistance = distance;
			}
			if (!olddistance)
				return (point);
			check = check->next;
		}
		elem = elem->next;
	}
	if (olddistance == 999)
		return (NULL);
	return (point);
}

SDL_Color	making_color(unsigned char r, unsigned char g, unsigned char b,
	unsigned char a)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

void		load_color(t_win *wn)
{
	wn->color.noir = making_color(0, 0, 0, 0);
	wn->color.violetfonce = making_color(188, 7, 237, 0);
	wn->color.violet = making_color(199, 62, 236, 0);
	wn->color.violetrose = making_color(212, 115, 238, 0);
	wn->color.red = making_color(255, 0, 0, 0);
	wn->color.blanc = making_color(255, 255, 255, 0);
}

SDL_Rect	define_rect(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

t_point		create_t_point(int x, int y)
{
	t_point new;

	new.x = x;
	new.y = y;
	return (new);
}
