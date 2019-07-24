/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:57:44 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/24 17:27:08 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>
#include <time.h> ///////////a sup apres

t_myraster	*ft_init_rasterization(t_win *wn, t_myraster *raster)
{
	raster->triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle));
	raster->clipped_triangle = (t_mytriangle*)malloc(sizeof(t_mytriangle) * 3);
	SDL_WarpMouseInWindow(wn->window, wn->xscreen / 2, wn->yscreen / 2);
	raster->mat_trans = ft_make_matrix_5_5();
	raster->mat_rot_x = ft_make_matrix_5_5();
	raster->mat_rot_y = ft_make_matrix_5_5();
	raster->mat_rot_z = ft_make_matrix_5_5();
	raster->mat_proje = ft_make_matrix_5_5();
	ft_set_pro(raster);
	raster->ftheta = 0;
	raster->theta_camera = 0;
	raster->pitch = 0;
	raster->leave_mouse = 0;
	raster->v_camera = ft_create_vector(0.0, 0.0, 0.0);
	raster->avancer = 0;
	raster->reculer = 0;
	raster->translate_left = 0;
	raster->translate_right = 0;
	raster->modif = 1;
	raster->old = (Uint8*)malloc(sizeof(Uint8) * 300);
	raster->quit = 0;
	raster->light_direction = ft_create_vector(0.5, 0.0, -1.0);
	raster->light_direction = ft_normalise(raster->light_direction);




	/* //haut */
	/* { 0.0f, 0.0f, 0.0f },									{ 0.0f, 1.0f, 0.0f }, */

	/* //bas */
	/* { 0.0f, (float)ScreenHeight() - 1, 0.0f },				{ 0.0f, -1.0f, 0.0f }, */

	/* //gauche */
	/* { 0.0f, 0.0f, 0.0f },									{ 1.0f, 0.0f, 0.0f }, */

	/* //droit */
	/* { (float)ScreenWidth() - 1, 0.0f, 0.0f },				{ -1.0f, 0.0f, 0.0f }, */


	//camera
	raster->plane_camera = ft_create_vector(0.0, 0.0, 1.0);
	raster->point_camera = ft_create_vector(0.0, 0.0, 0.1);
	//haut
	raster->point_up_screen = ft_create_vector( 0.0, 0.0, 0.0 );
	raster->plane_up_screen = ft_create_vector( 0.0, 1.0, 0.0 );
	//gauche
	raster->point_left_screen = ft_create_vector( 0.0, 0.0, 0.0 );
	raster->plane_left_screen = ft_create_vector( 1.0, 0.0, 0.0 );
	//droit
	raster->point_right_screen = ft_create_vector( XSCREEN - 1, 0.0, 0.0 );
	raster->plane_right_screen = ft_create_vector( -1.0, 0.0, 0.0 );
	//bas
	raster->point_bottom_screen = ft_create_vector( 0.0, YSCREEN - 1, 0.0 );
	raster->plane_bottom_screen = ft_create_vector( 0.0, -1.0, 0.0 );
	raster->i = 0;   //attention limit le nombre de triangle
	raster->nbr_of_triangle = wn->rasterizer->max; //de meme
	return (raster);
}

void		ft_init_update_raster(t_myraster *raster)
{
	raster->triangle_lst = NULL;
	raster->triangle_lst_2 = NULL;
	ft_make_the_world_spin(0, raster);
	ft_calcul_world_and_view_matrix(raster);
	raster->i = -1;
}

void	SHOW_TRIANGLE(t_mytriangle *trg, int nb)
{
	int	i;

	while (nb)
	{
		i = 0;
		while (i < 3)
		{
			printf("trg[%d] => v%d x : %f | y : %f | z : %f\n", nb - 1, i, trg[nb - 1].vertice[i].x, trg[nb - 1].vertice[i].y, trg[nb - 1].vertice[i].z);
			i++;
		}
		nb -= 1;
	}
}


void		ft_my_time(unsigned int *total, clock_t *current_time, clock_t *last_time)
{
	*last_time = *current_time;
	*current_time = clock();
	*total += (*current_time - *last_time);
}


void		ft_update_raster(t_myraster *raster, t_mytriangle *triangle_array, t_win *wn)
{
	clock_t	current_time;
	clock_t	last_time;

	current_time = 0;
	ft_init_update_raster(raster);


	raster->time_world_view = 0;
	raster->time_culling = 0;
	raster->time_shade = 0;
	raster->time_cam_view = 0;
	raster->time_clipping_camera = 0;
	raster->time_projetion = 0;
	raster->time_scale_screen = 0;
	raster->time_add_to_lst = 0;
	raster->time_z_buffer = 0;
	raster->time_clipping_screen = 0;
	raster->time_draw = 0;
	raster->time_free_lst = 0;




	while (++(raster->i) < raster->nbr_of_triangle)
	{
		current_time = clock();
		*(raster->triangle) = triangle_array[raster->i];

		ft_calcul_world_view(raster->triangle, raster);
		ft_my_time(&(raster->time_world_view), &current_time, &last_time);

		if (ft_culling(raster->triangle, raster) == 1)
		{
			ft_my_time(&(raster->time_culling), &current_time, &last_time);

			ft_calcul_shade(raster->triangle, raster);
			raster->triangle->shade *= 100;
			ft_my_time(&(raster->time_shade), &current_time, &last_time);

			ft_calcul_cam_view(raster->triangle, raster);
			ft_my_time(&(raster->time_cam_view), &current_time, &last_time);

			ft_clipping_camera(raster->triangle, raster, &(raster->clipped_triangle));
			ft_my_time(&(raster->time_clipping_camera), &current_time, &last_time);

			raster->j = 0;
			while (raster->j < raster->nbr_of_clipped_triangle_created)
			{
				ft_calcul_projection_view(&(raster->clipped_triangle[raster->j]), raster);
				ft_my_time(&(raster->time_projetion), &current_time, &last_time);

				ft_scale_screen(&(raster->clipped_triangle[raster->j]));
				ft_my_time(&(raster->time_scale_screen), &current_time, &last_time);

				ft_store_in_lst(ft_triangle_node_create(raster->clipped_triangle[raster->j]), &raster->triangle_lst); // Place in the linked list @ the right place
				ft_my_time(&(raster->time_add_to_lst), &current_time, &last_time);

				raster->j += 1;
			}
		}
	}
	ft_clipping_screen(
			raster->triangle_lst,
			raster,
			&(raster->clipped_triangle));
	ft_my_time(&(raster->time_clipping_screen), &current_time, &last_time);
	ft_draw(raster->triangle_lst_2, wn);
	ft_my_time(&(raster->time_draw), &current_time, &last_time);

	ft_free_lst(raster->triangle_lst_2);
	ft_my_time(&(raster->time_free_lst), &current_time, &last_time);

	SDL_SetRenderDrawColor(wn->rend, 255, 255, 255, 255);
	SDL_RenderDrawLine(wn->rend, 30, 0, 30, YSCREEN);
	SDL_RenderDrawLine(wn->rend, XSCREEN - 30, 0, XSCREEN - 30, YSCREEN);
	SDL_RenderDrawLine(wn->rend, 0, 30, XSCREEN, 30);
	SDL_RenderDrawLine(wn->rend, 0, YSCREEN - 30, XSCREEN, YSCREEN - 30);

	printf("world view\t=%u\n", raster->time_world_view);
	printf("culling\t\t=%u\n", raster->time_culling);
	printf("shade\t\t=%u\n", raster->time_shade);
	printf("cam view\t=%u\n", raster->time_cam_view);
	printf("clip camera\t=%u\n", raster->time_clipping_camera);
	printf("projection\t=%u\n", raster->time_projetion);
	printf("scale\t\t=%u\n", raster->time_scale_screen);
	printf("add lst\t\t=%u\n", raster->time_add_to_lst);
	printf("z buffer\t=%u\n", raster->time_z_buffer);
	printf("clip screen\t=%u\n", raster->time_clipping_screen);
	printf("draw\t\t=%u\n", raster->time_draw);
	printf("free\t\t=%u\n\n\n\n", raster->time_free_lst);

}
