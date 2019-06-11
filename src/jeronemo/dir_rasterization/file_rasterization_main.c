/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization_main.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:57:51 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/11 17:55:36 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_keyboard_event_check(t_win *wn, Uint8 *old, t_mychange *change)
{

	if (wn->state[SDL_SCANCODE_ESCAPE])
		change->quit = TRUE;

	if (wn->state[SDL_SCANCODE_P] == 1 && old[SDL_SCANCODE_P] == 0)
	{
		if (change->projection == 1)
			change->projection = 0;
		else
			change->projection = 1;
		change->modif = 1;
		/* printf("rotation sur x\n"); */
	}
	if (wn->state[SDL_SCANCODE_T] == 1 && old[SDL_SCANCODE_T] == 0)
	{
		if (change->triangle == 1)
			change->triangle = 0;
		else
			change->triangle = 1;
		change->modif = 1;
		/* printf("rotation sur x\n"); */
	}
	if (wn->state[SDL_SCANCODE_J] == 1 )
	{
		change->angle_x += 1;
		change->modif = 1;
		/* printf("rotation sur x\n"); */
	}
	if (wn->state[SDL_SCANCODE_K] == 1 )
	{
		/* printf("rotation sur y\n"); */
		change->angle_y += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_L] == 1 )
	{
		/* printf("rotation sur z\n"); */
		change->angle_z += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_U] == 1 && old[SDL_SCANCODE_U] == 0)
	{
		/* printf("zoom\n"); */
		change->zoom += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_I] == 1 && old[SDL_SCANCODE_I] == 0)
	{
		/* printf("zoom\n"); */
		change->zoom -= 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_W] == 1 && old[SDL_SCANCODE_W] == 0)
	{
		/* printf("Translation UP\n"); */
		change->translation_y -= 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_S] == 1 && old[SDL_SCANCODE_S] == 0)
	{
		/* printf("Translation DOWN\n"); */
		change->translation_y += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_A] == 1 && old[SDL_SCANCODE_A] == 0)
	{
		/* printf("Translation LEFT\n"); */
		change->translation_x -= 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_D] == 1 && old[SDL_SCANCODE_D] == 0)
	{
		/* printf("Translation RIGHT\n"); */
		change->translation_x += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_Z] == 1 && old[SDL_SCANCODE_Z] == 0)
	{
		/* printf("Translation Z\n"); */
		change->translation_z += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_X] == 1 && old[SDL_SCANCODE_X] == 0)
	{
		/* printf("Translation X\n"); */
		change->translation_z -= 5;
		change->modif = 1;
	}
}

void	ft_init_launch_rasterization(t_mykeep *keep, t_mychange *change)
{
	keep->polygon = NULL;
	keep->vec = NULL;

	change->quit = FALSE;
	change->angle_x = 0;
	change->angle_y = 0;
	change->angle_z = 0;
	change->zoom = 1;
	change->translation_x = 0;
	change->translation_y = 0;
	change->translation_z = 0;
	change->modif = 0;
	change->triangle = 0;
	change->old = (Uint8*)malloc(sizeof(Uint8) * 300);
	change->projection = 1;
}

float		ft_get_the_indice_vertex_x(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	x;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	x = vertex_lst->x;
	vertex_lst = keep;
	return (x);
}

float		ft_get_the_indice_vertex_y(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	y;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	y = vertex_lst->y;
	vertex_lst = keep;
	return (y);
}

float		ft_get_the_indice_vertex_z(int indice, t_myvec *vertex_lst)
{
	int		i;
	float	z;

	i = 0;
	t_myvec		*keep;
	keep = vertex_lst;
	while (i < indice)
	{
		vertex_lst = vertex_lst->next;
		i++;
	}
	z = vertex_lst->z;
	vertex_lst = keep;
	return (z);
}
void		ft_apply_modif(t_mywin *s_win, t_mychange *change, t_mykeep *keep)
{
	t_mypolygon *polygon;

	change->modif = 0;
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);

	polygon = s_win->polygon_lst;
	keep->polygon = polygon;
	printf("\n\n\n\n\nAPLY\n");
	while (polygon != NULL)
	{
		printf("\nNEW POLYGON\n");
		if (change->triangle == 0)
		{
			keep->vec = polygon->vertex_lst;
			int i =0;
			/* printf("le AAAA = %d\n", polygon->number_of_vertex); */
			while (polygon->vertex_lst->next != NULL)
			{
				/* printf("le numero = %d\n", i); */
				i++;
				change->result_1.x = polygon->vertex_lst->x;
				change->result_1.y = polygon->vertex_lst->y;
				change->result_1.z = polygon->vertex_lst->z;
				change->result_2.x = polygon->vertex_lst->next->x;
				change->result_2.y = polygon->vertex_lst->next->y;
				change->result_2.z = polygon->vertex_lst->next->z;
				SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
				ft_draw_change(s_win, change);
				polygon->vertex_lst = polygon->vertex_lst->next;
			}
			//bouclage dernier et premier
			change->result_1.x = polygon->vertex_lst->x;
			change->result_1.y = polygon->vertex_lst->y;
			change->result_1.z = polygon->vertex_lst->z;
			polygon->vertex_lst = keep->vec;
			change->result_2.x = polygon->vertex_lst->x;
			change->result_2.y = polygon->vertex_lst->y;
			change->result_2.z = polygon->vertex_lst->z;
			SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
			ft_draw_change(s_win, change);
		}
		else if (change->triangle == 1)
		{
			int i = 0;
			while (i < polygon->number_of_indices - 2)
			{
				change->result_1.x = ft_get_the_indice_vertex_x(polygon->indices[i] ,polygon->vertex_lst);
				change->result_1.y = ft_get_the_indice_vertex_y(polygon->indices[i], polygon->vertex_lst);
				change->result_1.z = ft_get_the_indice_vertex_z(polygon->indices[i], polygon->vertex_lst);


				change->result_2.x = ft_get_the_indice_vertex_x(polygon->indices[i + 1], polygon->vertex_lst);
				change->result_2.y = ft_get_the_indice_vertex_y(polygon->indices[i + 1], polygon->vertex_lst);
				change->result_2.z = ft_get_the_indice_vertex_z(polygon->indices[i + 1], polygon->vertex_lst);


				change->result_3.x = ft_get_the_indice_vertex_x(polygon->indices[i + 2], polygon->vertex_lst);
				change->result_3.y = ft_get_the_indice_vertex_y(polygon->indices[i + 2], polygon->vertex_lst);
				change->result_3.z = ft_get_the_indice_vertex_z(polygon->indices[i + 2], polygon->vertex_lst);
				SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
				ft_draw_change(s_win, change);
				i = i + 3;
			}
		}
		polygon = polygon->next;
	}
	polygon = keep->polygon;
	SDL_RenderPresent(s_win->renderer[J_EDITOR]);
}

void	ft_launch_rasterization(t_mywin *s_win, t_win *wn)
{
	t_mychange			change;
	t_mykeep			keep;

	ft_init_launch_rasterization(&keep, &change);
	ft_launch_bsp_tree(s_win, wn);
	SDL_Init(SDL_INIT_EVERYTHING);
	s_win->current_window = J_EDITOR;
	ft_launch_window(s_win);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);
	while (!change.quit)
	{
		SDL_PollEvent(&(wn->ev));
		wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
		ft_keyboard_event_check(wn , change.old, &change);
		if (change.modif == 1)
			ft_apply_modif(s_win, &change, &keep);
		SDL_Delay(10);
		setkeyboard(change.old, wn->state);
	}
}
