/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:57:44 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/25 19:47:25 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>
#include <time.h> ///////////a sup apres

SDL_Texture		*loadbmp(SDL_Renderer *tmp_renderer, char *path);

t_myraster	*ft_init_rasterization(t_win *wn, t_myraster *raster)
{

	raster->s_tex = malloc(sizeof(t_mytext));
	raster->s_tex->tga = load_tga("texturelight.tga");
	if (raster->s_tex->tga == NULL)
	{
		printf("probleme tga\n");
		exit(0);
	}
	/* raster->texture = loadbmp(wn->rend, "texturelight.bmp"); */
	raster->texture = SDL_CreateTexture(wn->rend, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, 1920, 1080);
	raster->s_tex->m_pPixels = malloc(1920*1080*sizeof(Uint32));

	raster->debug = 0;
	raster->s_tex->srcrect.w = 1;
	raster->s_tex->srcrect.h = 1;
	raster->s_tex->dstrect.w = 1;
	raster->s_tex->dstrect.h = 1;

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
	raster->v_camera = ft_create_vector(20.0, -30.0, 0.0);
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
	raster->nbr_of_triangle = wn->rasterizer->nbr_triangle; //de meme
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

	 // while (++(raster->i) < raster->nbr_of_triangle)
	 // {
	 // 	*(raster->triangle) = triangle_array[raster->i];
	 // 	raster->triangle->vertice[0] = ft_normalise((raster->triangle->vertice[0]));
	 // 	raster->triangle->vertice[1] = ft_normalise((raster->triangle->vertice[1]));
	 // 	raster->triangle->vertice[2] = ft_normalise((raster->triangle->vertice[2]));
	 // 	triangle_array[raster->i].texture[0].u = raster->triangle->vertice[0].x;
		// triangle_array[raster->i].texture[0].v = raster->triangle->vertice[0].y;
	 // 	triangle_array[raster->i].texture[0].w = 1;
	 // 	triangle_array[raster->i].texture[1].u = raster->triangle->vertice[1].x;
	 // 	triangle_array[raster->i].texture[1].v = raster->triangle->vertice[1].y;
	 // 	triangle_array[raster->i].texture[1].w = 1;
	 // 	triangle_array[raster->i].texture[2].u = raster->triangle->vertice[2].x;
	 // 	triangle_array[raster->i].texture[2].v = raster->triangle->vertice[2].y;
	 // 	triangle_array[raster->i].texture[2].w = 1;
	 // }


printf("nbr_triangle aaaaaaaaaaa:%d\n", raster->nbr_of_triangle);



	//printf("UPDATE RASTER \n\n");
	raster->i = -1;
	while (++(raster->i) < raster->nbr_of_triangle)
	{






		current_time = clock();
		*(raster->triangle) = triangle_array[raster->i];



		//printf("Raster Triangle: %f %f %f ; %f %f %f ; %f %f %f\n", raster->triangle->vertice[0].x, raster->triangle->vertice[0].y, raster->triangle->vertice[0].z,
		//		raster->triangle->vertice[1].x, raster->triangle->vertice[1].y, raster->triangle->vertice[1].z,
		//		raster->triangle->vertice[2].x, raster->triangle->vertice[2].y, raster->triangle->vertice[2].z);


		//printf("Before world view %f %f %f %f\n", raster->triangle->vertice[0].x,
		//			raster->triangle->vertice[0].y,raster->triangle->vertice[0].z, raster->triangle->vertice[0].w );
		ft_calcul_world_view(raster->triangle, raster); //IN FAIT DES NAN
		//printf("After world view %f %f %f\n", raster->triangle->vertice[0].x,
		//			raster->triangle->vertice[0].y,raster->triangle->vertice[0].z );
		ft_my_time(&(raster->time_world_view), &current_time, &last_time);

		//if (ft_culling(raster->triangle, raster) == 1)
		//{
			ft_my_time(&(raster->time_culling), &current_time, &last_time);

			ft_calcul_shade(raster->triangle, raster);
			//printf("After shade %f %f %f\n", raster->triangle->vertice[0].x,
			//		raster->triangle->vertice[0].y,raster->triangle->vertice[0].z );
			raster->triangle->shade *= 100;
			ft_my_time(&(raster->time_shade), &current_time, &last_time);

			ft_calcul_cam_view(raster->triangle, raster);
			//printf("After cam view %f %f %f\n", raster->triangle->vertice[0].x,
			//		raster->triangle->vertice[0].y,raster->triangle->vertice[0].z );
			ft_my_time(&(raster->time_cam_view), &current_time, &last_time);

			ft_clipping_camera(raster->triangle, wn, &(raster->clipped_triangle));
			raster->nbr_of_clipped_triangle_created = 1;
			while (raster->clipped_triangle)
			{
			//raster->clipped_triangle = raster->triangle;
			//raster->nbr_of_clipped_triangle_created = 1;
				ft_my_time(&(raster->time_clipping_camera), &current_time, &last_time);



			// printf("x1=%f,y1=%f,\n", raster->triangle->vertice[0].x, raster->triangle->vertice[0].y);
			// printf("x2=%f,y2=%f,\n", raster->triangle->vertice[1].x, raster->triangle->vertice[1].y);
			// printf("x3=%f,y3=%f,\n", raster->triangle->vertice[2].x, raster->triangle->vertice[2].y);
			// printf("clip camera\n\n");





				raster->j = 0;
				while (raster->j < raster->nbr_of_clipped_triangle_created)
				{
					//printf("Before projection %f %f %f\n", raster->clipped_triangle[raster->j].vertice[0].x,
					//raster->clipped_triangle[raster->j].vertice[0].y,raster->clipped_triangle[raster->j].vertice[0].z );
					ft_calcul_projection_view(&(raster->clipped_triangle[raster->j]), raster);
					//printf("After projection %f %f %f\n", raster->clipped_triangle[raster->j].vertice[0].x,
					//raster->clipped_triangle[raster->j].vertice[0].y,raster->clipped_triangle[raster->j].vertice[0].z );
					ft_my_time(&(raster->time_projetion), &current_time, &last_time);

					ft_scale_screen(&(raster->clipped_triangle[raster->j]));
					ft_my_time(&(raster->time_scale_screen), &current_time, &last_time);

					ft_store_in_lst(ft_triangle_node_create(raster->clipped_triangle[raster->j]), &raster->triangle_lst); // Place in the linked list @ the right place
					ft_my_time(&(raster->time_add_to_lst), &current_time, &last_time);

					raster->j += 1;
				}
				//printf("%p %p\n", raster->clipped_triangle, raster->clipped_triangle->next);
				raster->clipped_triangle = raster->clipped_triangle->next;
			}
		//}
	}
/**	raster->j = 0;
	raster->triangle_lst_2 = raster->triangle_lst;
	while (raster->triangle_lst_2 != NULL)
	{
		//raster->triangle_lst = raster->triangle_lst->next;
		//if (raster->triangle_lst->vertice[0].x > 0 && raster->triangle_lst->vertice[0].x <= 0)
			printf("%f\n", raster->triangle_lst_2->vertice[0].x );
		raster->triangle_lst_2 = raster->triangle_lst_2->next;
		raster->j++;
	} **/

	ft_clipping_screen(wn, raster->triangle_lst, raster, &(raster->clipped_triangle));

/**	raster->j = 0;
	raster->triangle_lst = raster->triangle_lst_2;
	while (raster->triangle_lst != NULL)
	{
		//raster->triangle_lst = raster->triangle_lst->next;
		//if (raster->triangle_lst->vertice[0].x > 0 && raster->triangle_lst->vertice[0].x <= 0)
			printf("%f\n", raster->triangle_lst->vertice[0].x );
		raster->triangle_lst = raster->triangle_lst->next;
		raster->j++;
	}
	printf("TRIANGLES APRES CLIPPING %d\n",raster->j ); **/
	ft_my_time(&(raster->time_clipping_screen), &current_time, &last_time);

	//printf("fin clipping screen \n");
	//	raster->triangle_lst_2 = raster->triangle_lst;


	// if (raster->triangle_lst_2 != NULL)
	// {
	// 	printf("x1=%f,y1=%f,\n", raster->triangle_lst_2->vertice[0].x, raster->triangle_lst_2->vertice[0].y);
	// 	printf("x2=%f,y2=%f,\n", raster->triangle_lst_2->vertice[1].x, raster->triangle_lst_2->vertice[1].y);
	// 	printf("x3=%f,y3=%f,\n", raster->triangle_lst_2->vertice[2].x, raster->triangle_lst_2->vertice[2].y);
	// 	printf("clip screen\n\n");
	// }







	ft_draw(raster->triangle_lst_2, wn);
	ft_my_time(&(raster->time_draw), &current_time, &last_time);

	ft_free_lst(raster->triangle_lst_2);
	ft_my_time(&(raster->time_free_lst), &current_time, &last_time);

//	SDL_SetRenderDrawColor(wn->rend, 255, 255, 255, 255);
//	SDL_RenderDrawLine(wn->rend, 30, 0, 30, YSCREEN);
//	SDL_RenderDrawLine(wn->rend, XSCREEN - 30, 0, XSCREEN - 30, YSCREEN);
//	SDL_RenderDrawLine(wn->rend, 0, 30, XSCREEN, 30);
//	SDL_RenderDrawLine(wn->rend, 0, YSCREEN - 30, XSCREEN, YSCREEN - 30);

	/**  printf("world view\t=%u\n", raster->time_world_view);
	  printf("culling\t\t=%u\n", raster->time_culling); 
	  printf("shade\t\t=%u\n", raster->time_shade); 
	  printf("cam view\t=%u\n", raster->time_cam_view); 
	  printf("clip camera\t=%u\n", raster->time_clipping_camera); 
	  printf("projection\t=%u\n", raster->time_projetion); 
	  printf("scale\t\t=%u\n", raster->time_scale_screen); 
	  printf("add lst\t\t=%u\n", raster->time_add_to_lst); 
	  printf("clip screen\t=%u\n", raster->time_clipping_screen); 
	  printf("draw\t\t=%u\n", raster->time_draw); 
	  printf("free\t\t=%u\n\n\n\n", raster->time_free_lst); **/

}
