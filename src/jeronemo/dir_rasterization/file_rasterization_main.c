/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization_main.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:57:51 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/10 12:17:09 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_keyboard_event_check(Uin8 *state, Uint8 *old, t_mychange *change)
{

	if (wn->state[SDL_SCANCODE_ESCAPE])
		quit = TRUE;
	if (wn->state[SDL_SCANCODE_J] == 1 && old[SDL_SCANCODE_J] == 0)
	{
		change.angle_x += 1;
		change->modif = 1;
		printf("rotation sur x\n");
	}
	if (wn->state[SDL_SCANCODE_K] == 1 && old[SDL_SCANCODE_K] == 0)
	{
		printf("rotation sur y\n");
		change.angle_y += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_L] == 1 && old[SDL_SCANCODE_L] == 0)
	{
		printf("rotation sur z\n");
		change.angle_z += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_U] == 1 && old[SDL_SCANCODE_U] == 0)
	{
		printf("zoom\n");
		change.zoom += 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_I] == 1 && old[SDL_SCANCODE_I] == 0)
	{
		printf("zoom\n");
		change.zoom -= 1;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_W] == 1 && old[SDL_SCANCODE_W] == 0)
	{
		printf("Translation UP\n");
		change.translation_y -= 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_S] == 1 && old[SDL_SCANCODE_S] == 0)
	{
		printf("Translation DOWN\n");
		change.translation_y += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_A] == 1 && old[SDL_SCANCODE_A] == 0)
	{
		printf("Translation LEFT\n");
		change.translation_x -= 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_D] == 1 && old[SDL_SCANCODE_D] == 0)
	{
		printf("Translation RIGHT\n");
		change.translation_x += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_Z] == 1 && old[SDL_SCANCODE_Z] == 0)
	{
		printf("Translation Z\n");
		change.translation_z += 5;
		change->modif = 1;
	}
	if (wn->state[SDL_SCANCODE_X] == 1 && old[SDL_SCANCODE_X] == 0)
	{
		printf("Translation X\n");
		change.translation_z -= 5;
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
}

void		ft_apply_modif()
{
	ft_apply_modif();
	modif = 0;
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
	polygon = s_win->polygon_lst;
	keep = polygon;
	while (polygon != NULL)
	{
		keep_vec = polygon->vertex_lst;
		while (polygon->vertex_lst->next != NULL)
		{
			if (triangle == 0)
			{
				result_1.x = polygon->vertex_lst->x;
				result_1.y = polygon->vertex_lst->y;
				result_1.z = polygon->vertex_lst->z;
				result_2.x = polygon->vertex_lst->next->x;
				result_2.y = polygon->vertex_lst->next->y;
				result_2.z = polygon->vertex_lst->next->z;
			}
			else
			{
				printf("triangle\n");
			}
			ft_draw_change(s_win, change, result_1,  result_2  );
			polygon->vertex_lst = polygon->vertex_lst->next;
		}
		polygon->vertex_lst = keep_vec;
		polygon = polygon->next;
	}
	polygon = keep;
	SDL_RenderPresent(s_win->renderer[J_EDITOR]);
}

void	ft_launch_rasterization(t_mywin *s_win, t_win *wn)
{
	t_mychange			change;
	t_mykeep			keep;


	ft_init_launch_rasterization(keep, &change);
	ft_launch_bsp_tree(s_win, wn);
	SDL_Init(SDL_INIT_EVERYTHING);
	s_win->current_window = J_EDITOR;
	ft_launch_window(s_win);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);
	while (!quit)
	{
		SDL_PollEvent(&(wn->ev));
		wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
		ft_keyboard_event_check(wn->state, old, change);
		if (change.modif == 1)
			ft_apply_modif();
		SDL_Delay(10);
		setkeyboard(old, wn->state);
	}
}
