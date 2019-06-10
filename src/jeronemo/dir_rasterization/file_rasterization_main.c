/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization_main.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:57:51 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/10 10:55:23 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

typedef struct s_mychange
{
	float		angle_x;
	float		angle_y;
	float		angle_z;
	float		translation_x;
	float		translation_y;
	float		translation_z;
	float		zoom;
}				t_mychange;

void	ft_orthographic_projection(void)
{
	printf("Orthographic projection");
}

void	ft_perspective_projection(void)
{
	printf("Perspective projection");
}

void	ft_apply_texture(void)
{
	printf("Apply texture");
}

void	ft_apply_change(t_mywin *s_win, t_mychange change, t_myvec result_1, t_myvec result_2)
{
	t_myputtheline		s_line;

	result_1 = ft_rotation_x(change.angle_x, result_1);
	result_2 = ft_rotation_x(change.angle_x, result_2);
	result_1 = ft_rotation_y(change.angle_y, result_1);
	result_2 = ft_rotation_y(change.angle_y, result_2);
	result_1 = ft_rotation_z(change.angle_z, result_1);
	result_2 = ft_rotation_z(change.angle_z, result_2);
	result_1 = ft_translation_x(change.translation_x, result_1);
	result_2 = ft_translation_x(change.translation_x, result_2);
	result_1 = ft_translation_y(change.translation_y, result_1);
	result_2 = ft_translation_y(change.translation_y, result_2);
	result_1 = ft_translation_z(change.translation_z, result_1);
	result_2 = ft_translation_z(change.translation_z, result_2);
	result_1 = ft_scale(change.zoom, result_1);
	result_2 = ft_scale(change.zoom, result_2);
	s_line.un.a = result_1.x;
	s_line.un.b = result_1.y;
	s_line.deux.a = result_2.x;
	s_line.deux.b = result_2.y;
	ft_draw_line(s_win, &s_line);
}

void	ft_launch_rasterization(t_mywin *s_win, t_win *wn)
{
	SDL_Texture			*ma_texture;
	float				matrix[5][5];
	t_myvec				vec;
	t_mychange			change;
	int					quit;
	Uint8				*old;
	int					modif;
	int					triangle;
	t_myvec				result_1;
	t_myvec				result_2;
	t_mypolygon			*polygon;
	t_mypolygon			*keep;
	t_myvec				*keep_vec;


	vec.x = 1;
	vec.y = 2;
	vec.z = 3;

	matrix[1][1] = 11;
	matrix[1][2] = 12;
	matrix[1][3] = 13;
	matrix[2][1] = 21;
	matrix[2][2] = 22;
	matrix[2][3] = 23;
	matrix[3][1] = 31;
	matrix[3][2] = 32;
	matrix[3][3] = 33;

	quit = FALSE;
	change.angle_x = 0;
	change.angle_y = 0;
	change.angle_z = 0;
	change.zoom = 1;
	change.translation_x = 0;
	change.translation_y = 0;
	change.translation_z = 0;
	s_win->current_window = J_EDITOR;
	ma_texture = NULL;

	modif = 0;
	triangle = 0;

	old = (Uint8*)malloc(sizeof(Uint8) * 300);

	ft_launch_bsp_tree(s_win, wn);
	SDL_Init(SDL_INIT_EVERYTHING);
	ft_launch_window(s_win);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);
	while (!quit)
	{
		SDL_PollEvent(&(wn->ev));
		wn->state = (Uint8*)SDL_GetKeyboardState(NULL);
		if (wn->state[SDL_SCANCODE_ESCAPE])
			quit = TRUE;
		if (wn->state[SDL_SCANCODE_J] == 1 && old[SDL_SCANCODE_J] == 0)
		{
			change.angle_x += 1;
			modif = 1;
			printf("rotation sur x\n");
		}
		if (wn->state[SDL_SCANCODE_K] == 1 && old[SDL_SCANCODE_K] == 0)
		{
			printf("rotation sur y\n");
			change.angle_y += 1;
			modif = 1;
		}
		if (wn->state[SDL_SCANCODE_L] == 1 && old[SDL_SCANCODE_L] == 0)
		{
			printf("rotation sur z\n");
			change.angle_z += 1;
			modif = 1;
		}
		if (wn->state[SDL_SCANCODE_U] == 1 && old[SDL_SCANCODE_U] == 0)
		{
			printf("zoom\n");
			change.zoom += 1;
			modif = 1;
		}
		if (wn->state[SDL_SCANCODE_I] == 1 && old[SDL_SCANCODE_I] == 0)
		{
			printf("zoom\n");
			change.zoom -= 1;
			modif = 1;
		}
		if (wn->state[SDL_SCANCODE_W] == 1 && old[SDL_SCANCODE_W] == 0)
		{
			printf("Translation UP\n");
			change.translation_y -= 5;
			modif = 1;
		}
		if (wn->state[SDL_SCANCODE_S] == 1 && old[SDL_SCANCODE_S] == 0)
		{
			printf("Translation DOWN\n");
			change.translation_y += 5;
			modif = 1;
		}
		if (wn->state[SDL_SCANCODE_A] == 1 && old[SDL_SCANCODE_A] == 0)
		{
			printf("Translation LEFT\n");
			change.translation_x -= 5;
			modif = 1;
		}
		if (wn->state[SDL_SCANCODE_D] == 1 && old[SDL_SCANCODE_D] == 0)
		{
			printf("Translation RIGHT\n");
			change.translation_x += 5;
			modif = 1;
		}
		if (wn->state[SDL_SCANCODE_Z] == 1 && old[SDL_SCANCODE_Z] == 0)
		{
			printf("Translation Z\n");
			change.translation_z += 5;
			modif = 1;
		}
		if (wn->state[SDL_SCANCODE_X] == 1 && old[SDL_SCANCODE_X] == 0)
		{
			printf("Translation X\n");
			change.translation_z -= 5;
			modif = 1;
		}
		if (modif == 1)
		{
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

					ft_apply_change(s_win, change, result_1,  result_2  );
					polygon->vertex_lst = polygon->vertex_lst->next;
				}
				polygon->vertex_lst = keep_vec;
				polygon = polygon->next;
			}
			polygon = keep;
			SDL_RenderPresent(s_win->renderer[J_EDITOR]);
		}
		SDL_Delay(10);
		setkeyboard(old, wn->state);
	}
}
	//clear la fenetre
	//afficher un polynome
	//en blanc la forme general
	//en rouge les triangle a l'interrieur

	/* ma_texture = ft_loadbmp(s_win->renderer[J_EDITOR], "texture.bmp"); */
			//applique texture
			/* SDL_Rect        srcrect; */
			/* SDL_Rect        dstrect; */
    		/* srcrect.x = 0; */
			/* srcrect.y = 0; */
			/* srcrect.w = 1632; */
			/* srcrect.h = 1185; */
			/* dstrect.x = 10; */
			/* dstrect.y = 10; */
			/* dstrect.w = 100; */
			/* dstrect.h = 100; */
			/* float	delta_x = 0; */
			/* delta_x = result_4.x - result_3.x; */
			/* int i = 0; */
			/* while (i < delta_x) */
			/* { */
			/* 	dstrect.x = ((i * 1632) / delta_x) + result_3.x; */
			/* 	SDL_RenderCopy(s_win->renderer[J_EDITOR], ma_texture, &(srcrect), &(dstrect)); */
			/* 	i++; */
			/* } */

/* SDL_Texture		*ft_loadbmp(SDL_Renderer *tmp_renderer, char *path) */
/* { */
/* 	SDL_Texture			*txt; */
/* 	SDL_Surface			*tmp; */

/* 	tmp = SDL_LoadBMP(path); */
/* 	txt = SDL_CreateTextureFromSurface(tmp_renderer, tmp); */
/* 	if (tmp != NULL) */
/* 		SDL_FreeSurface(tmp); */
/* 	return (txt); */
/* } */
