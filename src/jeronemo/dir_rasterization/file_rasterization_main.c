/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization_main.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:57:51 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/05 17:57:32 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>


SDL_Texture		*ft_loadbmp(SDL_Renderer *tmp_renderer, char *path)
{
	SDL_Texture			*txt;
	SDL_Surface			*tmp;

	tmp = SDL_LoadBMP(path);
	txt = SDL_CreateTextureFromSurface(tmp_renderer, tmp);
	if (tmp != NULL)
		SDL_FreeSurface(tmp);
	return (txt);
}

t_myvec	ft_matrix_multiply(float matrix[5][5], t_myvec vertex)
{
	t_myvec		result;

	result.x = (matrix[1][1] * vertex.x) + (matrix[1][2] * vertex.y) + (matrix[1][3] * vertex.z);
	result.y = (matrix[2][1] * vertex.x) + (matrix[2][2] * vertex.y) + (matrix[2][3] * vertex.z);
	result.z = (matrix[3][1] * vertex.x) + (matrix[3][2] * vertex.y) + (matrix[3][3] * vertex.z);
	return (result);
}

t_myvec	ft_translation_x(float value, t_myvec vertex)
{
	t_myvec		result;

	result.x = vertex.x + value;
	result.y = vertex.y;
	result.z = vertex.z;
	return (result);
}

t_myvec	ft_translation_y(float value, t_myvec vertex)
{
	t_myvec		result;

	result.x = vertex.x;
	result.y = vertex.y + value;
	result.z = vertex.z;
	return (result);
}

t_myvec	ft_translation_z(float value, t_myvec vertex)
{
	t_myvec		result;

	result.x = vertex.x;
	result.y = vertex.y;
	result.z = vertex.z + value;
	return (result);
}

t_myvec	ft_scale(float zoom, t_myvec vertex)
{
	float		matrix[5][5];
	t_myvec		result;

	matrix[1][1] = zoom;
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = zoom;
	matrix[2][3] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = zoom;
	result = ft_matrix_multiply(matrix, vertex);
	return (result);
}


float	ft_rad(float angle)
{
	float	result;

	result = angle * (M_PI / 180.0);
	return (result);
}


t_myvec	ft_rotation_x(float angle, t_myvec vertex)
{
	float		matrix[5][5];
	t_myvec		result;

	angle = ft_rad(angle);
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = cos(angle);
	matrix[2][3] = sin(angle);
	matrix[3][1] = 0;
	matrix[3][2] = -sin(angle);
	matrix[3][3] = cos(angle);
	result = ft_matrix_multiply(matrix, vertex);
	return (result);
}

t_myvec	ft_rotation_y(float angle, t_myvec vertex)
{
	float		matrix[5][5];
	t_myvec		result;

	angle = ft_rad(angle);
	matrix[1][1] = cos(angle);
	matrix[1][2] = 0;
	matrix[1][3] = -sin(angle);
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;
	matrix[3][1] = sin(angle);
	matrix[3][2] = 0;
	matrix[3][3] = cos(angle);
	result = ft_matrix_multiply(matrix, vertex);
	return (result);
}

t_myvec	ft_rotation_z(float angle, t_myvec vertex)
{
	float		matrix[5][5];
	t_myvec		result;

	angle = ft_rad(angle);
	matrix[1][1] = cos(angle);
	matrix[1][2] = sin(angle);
	matrix[1][3] = 0;
	matrix[2][1] = -sin(angle);
	matrix[2][2] = cos(angle);
	matrix[2][3] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
	result = ft_matrix_multiply(matrix, vertex);
	return (result);
}

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




void	ft_launch_rasterization(t_mywin *s_win, t_win *wn)
{
	SDL_Texture  *ma_texture;
	ma_texture = NULL;
	float			matrix[5][5];
	t_myvec			vec;
	t_myvec			result;

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

	result = ft_matrix_multiply(matrix, vec);
	printf("result =%f =%f =%f\n", result.x, result.y, result.z);

	s_win->current_window = J_EDITOR;

	ft_launch_window(s_win);
	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    SDL_RenderClear(s_win->renderer[J_EDITOR]);

	t_myvec				vertex_1;
	t_myvec				vertex_2;
	t_myvec				vertex_3;
	t_myvec				vertex_4;
	t_myputtheline		s_line;

	vertex_1.x = 1 * 30;
	vertex_1.y = 3 * 30;
	vertex_1.z = 1 * 30;
	vertex_2.x = 3 * 30;
	vertex_2.y = 1 * 30;
	vertex_2.z = 1 * 30;
	vertex_3.x = 5 * 30;
	vertex_3.y = 2 * 30;
	vertex_3.z = 1 * 30;
	vertex_4.x = 3 * 30;
	vertex_4.y = 2 * 30;
	vertex_4.z = 3 * 30;

	SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);
	s_line.un.a = vertex_1.x;
	s_line.un.b = vertex_1.y;
	s_line.deux.a = vertex_2.x;
	s_line.deux.b = vertex_2.y;
	ft_draw_line(s_win, &s_line);
	s_line.un.a = vertex_2.x;
	s_line.un.b = vertex_2.y;
	s_line.deux.a = vertex_3.x;
	s_line.deux.b = vertex_3.y;
	ft_draw_line(s_win, &s_line);
	s_line.un.a = vertex_3.x;
	s_line.un.b = vertex_3.y;
	s_line.deux.a = vertex_1.x;
	s_line.deux.b = vertex_1.y;
	ft_draw_line(s_win, &s_line);

	s_line.un.a = vertex_1.x;
	s_line.un.b = vertex_1.y;
	s_line.deux.a = vertex_4.x;
	s_line.deux.b = vertex_4.y;
	ft_draw_line(s_win, &s_line);
	s_line.un.a = vertex_2.x;
	s_line.un.b = vertex_2.y;
	s_line.deux.a = vertex_4.x;
	s_line.deux.b = vertex_4.y;
	ft_draw_line(s_win, &s_line);
	s_line.un.a = vertex_3.x;
	s_line.un.b = vertex_3.y;
	s_line.deux.a = vertex_4.x;
	s_line.deux.b = vertex_4.y;
	ft_draw_line(s_win, &s_line);




	SDL_RenderPresent(s_win->renderer[J_EDITOR]);
	/* SDL_Delay(1000 * 7); */


	printf("rotation\n");
	/* SDL_Delay(1000 * 7); */

	int			quit;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	float		zoom;
	float		translation_x;
	float		translation_y;
	float		translation_z;
	Uint8		*old;

	quit = FALSE;
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
	zoom = 1;
	translation_x = 0;
	translation_y = 0;
	translation_z = 0;
	old = (Uint8*)malloc(sizeof(Uint8) * 300);

	ma_texture = ft_loadbmp(s_win->renderer[J_EDITOR], "texture.bmp");



	while (!quit)
	{
		SDL_PollEvent(&(wn->ev));
		wn->state = (Uint8*)SDL_GetKeyboardState(NULL);

		if (wn->state[SDL_SCANCODE_ESCAPE])
			quit = TRUE;
		if (wn->state[SDL_SCANCODE_J] == 1 && old[SDL_SCANCODE_J] == 0)
		{
			angle_x += 10;
			printf("rotation sur x\n");
		}
		if (wn->state[SDL_SCANCODE_K] == 1 && old[SDL_SCANCODE_K] == 0)
		{
			printf("rotation sur y\n");
			angle_y += 10;
		}
		if (wn->state[SDL_SCANCODE_L] == 1 && old[SDL_SCANCODE_L] == 0)
		{
			printf("rotation sur z\n");
			angle_z += 10;
		}
		if (wn->state[SDL_SCANCODE_U] == 1 && old[SDL_SCANCODE_U] == 0)
		{
			printf("zoom\n");
			zoom += 1;
		}
		if (wn->state[SDL_SCANCODE_I] == 1 && old[SDL_SCANCODE_I] == 0)
		{
			printf("zoom\n");
			zoom -= 1;
		}
		if (wn->state[SDL_SCANCODE_W] == 1 && old[SDL_SCANCODE_W] == 0)
		{
			printf("Translation UP\n");
			translation_y -= 5;
		}
		if (wn->state[SDL_SCANCODE_S] == 1 && old[SDL_SCANCODE_S] == 0)
		{
			printf("Translation DOWN\n");
			translation_y += 5;
		}
		if (wn->state[SDL_SCANCODE_A] == 1 && old[SDL_SCANCODE_A] == 0)
		{
			printf("Translation LEFT\n");
			translation_x -= 5;
		}
		if (wn->state[SDL_SCANCODE_D] == 1 && old[SDL_SCANCODE_D] == 0)
		{
			printf("Translation RIGHT\n");
			translation_x += 5;
		}
		if (wn->state[SDL_SCANCODE_Z] == 1 && old[SDL_SCANCODE_Z] == 0)
		{
			printf("Translation Z\n");
			translation_z += 5;
		}
		if (wn->state[SDL_SCANCODE_X] == 1 && old[SDL_SCANCODE_X] == 0)
		{
			printf("Translation X\n");
			translation_z -= 5;
		}
		SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 0, 0, 0, 255);
    	SDL_RenderClear(s_win->renderer[J_EDITOR]);
		SDL_SetRenderDrawColor(s_win->renderer[J_EDITOR], 255, 255, 255, 255);


		t_myvec				result_1;
		t_myvec				result_2;
		t_myvec				result_3;
		t_myvec				result_4;


		result_1 = vertex_1;
		result_2 = vertex_2;
		result_3 = vertex_3;
		result_4 = vertex_4;

		result_1 = ft_rotation_x(angle_x, result_1);
		result_2 = ft_rotation_x(angle_x, result_2);
		result_3 = ft_rotation_x(angle_x, result_3);
		result_4 = ft_rotation_x(angle_x, result_4);

		result_1 = ft_rotation_y(angle_y, result_1);
		result_2 = ft_rotation_y(angle_y, result_2);
		result_3 = ft_rotation_y(angle_y, result_3);
		result_4 = ft_rotation_y(angle_y, result_4);

		result_1 = ft_rotation_z(angle_z, result_1);
		result_2 = ft_rotation_z(angle_z, result_2);
		result_3 = ft_rotation_z(angle_z, result_3);
		result_4 = ft_rotation_z(angle_z, result_4);

		result_1 = ft_translation_x(translation_x, result_1);
		result_2 = ft_translation_x(translation_x, result_2);
		result_3 = ft_translation_x(translation_x, result_3);
		result_4 = ft_translation_x(translation_x, result_4);

		result_1 = ft_translation_y(translation_y, result_1);
		result_2 = ft_translation_y(translation_y, result_2);
		result_3 = ft_translation_y(translation_y, result_3);
		result_4 = ft_translation_y(translation_y, result_4);

		result_1 = ft_translation_z(translation_z, result_1);
		result_2 = ft_translation_z(translation_z, result_2);
		result_3 = ft_translation_z(translation_z, result_3);
		result_4 = ft_translation_z(translation_z, result_4);

		result_1 = ft_scale(zoom, result_1);
		result_2 = ft_scale(zoom, result_2);
		result_3 = ft_scale(zoom, result_3);
		result_4 = ft_scale(zoom, result_4);



		//applique texture


		s_line.un.a = result_1.x;
		s_line.un.b = result_1.y;
		s_line.deux.a = result_2.x;
		s_line.deux.b = result_2.y;
		ft_draw_line(s_win, &s_line);
		s_line.un.a = result_2.x;
		s_line.un.b = result_2.y;
		s_line.deux.a = result_3.x;
		s_line.deux.b = result_3.y;
		ft_draw_line(s_win, &s_line);
		s_line.un.a = result_3.x;
		s_line.un.b = result_3.y;
		s_line.deux.a = result_1.x;
		s_line.deux.b = result_1.y;
		ft_draw_line(s_win, &s_line);
		s_line.un.a = result_1.x;
		s_line.un.b = result_1.y;
		s_line.deux.a = result_4.x;
		s_line.deux.b = result_4.y;
		ft_draw_line(s_win, &s_line);
		s_line.un.a = result_2.x;
		s_line.un.b = result_2.y;
		s_line.deux.a = result_4.x;
		s_line.deux.b = result_4.y;
		ft_draw_line(s_win, &s_line);
		s_line.un.a = result_3.x;
		s_line.un.b = result_3.y;
		s_line.deux.a = result_4.x;
		s_line.deux.b = result_4.y;
		ft_draw_line(s_win, &s_line);






		SDL_Rect        srcrect;
		SDL_Rect        dstrect;


    	srcrect.x = 0;
		srcrect.y = 0;
		srcrect.w = 1632;
		srcrect.h = 1185;


		dstrect.x = 10;
		dstrect.y = 10;
		dstrect.w = 100;
		dstrect.h = 100;

		float	delta_x = 0;

		delta_x = result_4.x - result_3.x;
		int i = 0;

		while (i < delta_x)
		{
			dstrect.x = ((i * 1632) / delta_x) + result_3.x;
			SDL_RenderCopy(s_win->renderer[J_EDITOR], ma_texture, &(srcrect), &(dstrect));
			i++;
		}




		SDL_RenderPresent(s_win->renderer[J_EDITOR]);
		SDL_Delay(100);
		setkeyboard(old, wn->state);
	}


	//clear la fenetre
	//afficher un polynome
	//en blanc la forme general
	//en rouge les triangle a l'interrieur
}
