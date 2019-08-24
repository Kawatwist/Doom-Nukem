/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_calcul_world_view.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 12:36:58 by jchardin          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/08/24 11:48:29 by jchardin         ###   ########.fr       */
=======
/*   Updated: 2019/07/27 16:13:34 by lomasse          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

void	ft_calcul_world_view_matrix(t_myraster *raster)
{
	ft_set_raster_trans(0, 0, 0, raster);
	//ft_set_raster_rot_x(raster->ftheta, raster);
	ft_set_raster_rot_x(180, raster);
	//ft_set_raster_rot_y(raster->ftheta, raster);
	//ft_set_raster_rot_z(raster->ftheta * 0.5 + 180, raster);
	ft_set_raster_rot_z(0, raster);
}

void	ft_calcul_world_view(t_mytriangle *triangle, t_myraster *raster)
{
	//ROTATION Z
	ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_z);
	//ROTATION X
	ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_x);
	//TRANSLATION (offset in screen)
	ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_trans);
}

t_myvec		ft_calcul_normal_triangle_and_normalise(t_mytriangle triangle)
{
	t_myvec		normal;

	normal = ft_calculate_normal_of_points(triangle.vertice[0], triangle.vertice[1], triangle.vertice[2]);
	normal = ft_normalise(normal);
	return (normal);
}

int		ft_culling(t_mytriangle *triangle, t_myraster *raster)
{
	t_myvec			normal;

	normal = ft_calcul_normal_triangle_and_normalise(*triangle);
	if (ft_dot_product(normal, ft_vector_sub(triangle->vertice[0], raster->v_camera)) < 0.0)
		return (1);
	else
		return (0);
}

void	ft_calcul_shade(t_mytriangle *triangle, t_myraster *raster) // check gouraud
{
	t_myvec			normal;

	normal = ft_calcul_normal_triangle_and_normalise(*triangle);
	triangle->shade = ft_dot_product(normal, raster->light_direction);
}

void	ft_add_triangle_to_lst(t_mytriangle clipped_triangle, t_mytriangle **triangle_lst)
{
	t_mytriangle	*triangle_node;

	triangle_node = ft_triangle_node_create(clipped_triangle);
	ft_triangle_add_node(triangle_lst, triangle_node);
}

void	ft_calcul_world_and_view_matrix(t_myraster *raster)
{
	//CALCUL DE MATRIX WORLD
	ft_calcul_world_view_matrix(raster);
	//CALUL DE MATRIX VIEW
	raster->mat_camera_view = t_camera_compute_view(raster);
}

void	ft_free_lst(t_mytriangle *triangle_lst_2)
{
	t_mytriangle *current;
	while (triangle_lst_2 != NULL)
	{
		current = triangle_lst_2;
		triangle_lst_2 = triangle_lst_2->next;
		free(current);
	}
}

void	ft_clipping_camera(t_mytriangle *triangle, t_myraster *raster, t_mytriangle **clipped_triangle)
{
	raster->nbr_of_clipped_triangle_created = 0;
	if (triangle->vertice[0].z < 0.1 || triangle->vertice[1].z < 0.1 || triangle->vertice[2].z < 0.1)
		(raster->nbr_of_clipped_triangle_created) = 0; // Un verice ou plus out
	else
	{
		(*clipped_triangle) = triangle; // All inside
		(raster->nbr_of_clipped_triangle_created) = 1;
	}
}

<<<<<<< HEAD
void	ft_clipping_screen(t_mytriangle *triangle_lst,
		t_myraster *raster,
		t_mytriangle **clipped_triangle)
=======
void	ft_clipping_screen(t_win *wn, t_mytriangle *head, t_myraster *raster, t_mytriangle **clipped_triangle)
>>>>>>> master
{
	(void)clipped_triangle;
	if (head != NULL)
		clipping(wn, *head ,&(raster->triangle_lst_2));
}

void	ft_calcul_cam_view(t_mytriangle *triangle, t_myraster *raster)
{
	ft_apply_calucul(ft_matrix_multiply_vector_general, triangle, raster->mat_camera_view);
}

void	ft_calcul_projection_view(t_mytriangle *triangle, t_myraster *raster)
{
	ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_proje);//PROJECTION
}

void	ft_scale_screen(t_mytriangle *triangle)
{
	triangle->vertice[0].x += 1.0;
	triangle->vertice[1].x += 1.0;
	triangle->vertice[2].x += 1.0;

	triangle->vertice[0].y += 1.0;
	triangle->vertice[1].y += 1.0;
	triangle->vertice[2].y += 1.0;


	triangle->vertice[0].x *= 0.5 * (float)XSCREEN;
	triangle->vertice[1].x *= 0.5 * (float)XSCREEN;
	triangle->vertice[2].x *= 0.5 * (float)XSCREEN;

	triangle->vertice[0].y *= 0.5 * (float)YSCREEN;
	triangle->vertice[1].y *= 0.5 * (float)YSCREEN;
	triangle->vertice[2].y *= 0.5 * (float)YSCREEN;
}

void	ft_draw(t_mytriangle *triangle_lst_2, t_win *wn)
{
	t_mytriangle	*keep;
	t_point			start;
	t_point			end;

	keep = triangle_lst_2;
	while (triangle_lst_2 != NULL)
	{
		t_mytriangle	*keep;

		int i = 0;
		while (i < 1920 * 1080)
		{
			if(((t_myraster*)wn->rasterizer->tmp)->s_tex->m_pPixels[i] != 0xFFFFFFFF)
				((t_myraster*)wn->rasterizer->tmp)->s_tex->m_pPixels[i] = 0xFFFFFFFF;
			i++;
		}
		keep = triangle_lst_2;
		while (triangle_lst_2 != NULL)
		{
			//DRAW FILL TRIANGLE WITH SHADE/LIGHT
			/* ft_fill_triangle_shade((*triangle_lst_2), wn, triangle_lst_2->shade); */
			/* ft_draw_triangle_base(&(triangle_lst_2->vertice[0]), &(triangle_lst_2->vertice[1]), &(triangle_lst_2->vertice[2]), wn); */
			ft_draw_textured_triangle(
					triangle_lst_2,
					wn,
					((t_myraster*)wn->rasterizer->tmp)->texture,
					((t_myraster*)wn->rasterizer->tmp)->s_tex);
			triangle_lst_2 = triangle_lst_2->next;
		}
		triangle_lst_2 = keep;
		SDL_UpdateTexture(((t_myraster*)wn->rasterizer->tmp)->texture, NULL,((t_myraster*)wn->rasterizer->tmp)->s_tex-> m_pPixels, 1920 * sizeof(Uint32));
		SDL_RenderCopy(wn->rend, ((t_myraster*)wn->rasterizer->tmp)->texture, NULL, NULL);

=======
		//printf("=%f\n", triangle_lst_2->vertice[0].x);
		//DRAW FILL TRIANGLE WITH SHADE/LIGHT
		ft_fill_triangle_shade((*triangle_lst_2), wn, triangle_lst_2->shade);
		//DRAW MESH
		ft_draw_triangle_base(&(triangle_lst_2->vertice[0]), &(triangle_lst_2->vertice[1]), &(triangle_lst_2->vertice[2]), wn);
		triangle_lst_2 = triangle_lst_2->next;
>>>>>>> master
	}
	(void)end;
	(void)start;
/*	start.x = 20;
	start.y = 100;
	end.x = 20;
	end.y = YSCREEN - 100;
	drawline(wn, 0xFF0000FF, start, end);
	start.x = XSCREEN - 20;
	start.y = 100;
	end.x = XSCREEN - 20;
	end.y = YSCREEN - 100;
	drawline(wn, 0xFF0000FF, start, end);
	start.x = 20;
	start.y = 100;
	end.x = XSCREEN - 20;
	end.y = 100;
	drawline(wn, 0xFF0000FF, start, end);
	start.x = 20;
	start.y = YSCREEN - 100;
	end.x = XSCREEN - 20;
	end.y = YSCREEN - 100;
	drawline(wn, 0xFF0000FF, start, end);
	triangle_lst_2 = keep;
*/}

void	ft_make_the_world_spin(int turn, t_myraster *raster)
{
	if (turn == 1)
	{
		raster->ftheta += 1;
		if (raster->ftheta == 360 * 2)
			raster->ftheta = 0;
	}
}
