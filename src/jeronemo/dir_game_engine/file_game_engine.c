/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_game_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:45:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/08/25 19:11:55 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <header_game_engine.h>
t_mypolygon		*ft_read_the_polygon_file(void);

t_mycolor	ft_setcolor(int rrr, int ggg, int bbb)
{
	t_mycolor	s_color;

	s_color.rrr = rrr;
	s_color.ggg = ggg;
	s_color.bbb = bbb;
	 return (s_color);
}

     void	ft_game_engine(t_win *wn)
{
	ft_launch_rasterization(wn);
 }

void	turn_rast(t_win *wn)
{
	 wn->rasterizer->tmp = (void *)ft_input_event_check(wn, wn->rasterizer->tmp);
	//############
	if ((((t_myraster*)wn->rasterizer->tmp)->modif == 1 && wn->interface == DGAME) || wn->interface == RGAME)
	{
	/**	ft_clear_window(wn);
		ft_init_update_raster(wn->rasterizer->tmp);


		//ici v_camera est ok
		wn->rasterizer->curr_pos.x = ((t_myraster*)wn->rasterizer->tmp)->v_camera.x;
		wn->rasterizer->curr_pos.y = ((t_myraster*)wn->rasterizer->tmp)->v_camera.y;
		wn->rasterizer->curr_pos.z = ((t_myraster*)wn->rasterizer->tmp)->v_camera.z;
		wn->rasterizer->poly_list = render_bsp(wn->rasterizer->bsp, &wn->rasterizer->curr_pos);
		//print_poly_list(wn->rasterizer->poly_list);
		printf("BFR POS %f %f %f %d\n", wn->rasterizer->curr_pos.x, wn->rasterizer->curr_pos.y, wn->rasterizer->curr_pos.z, ((t_myraster*)wn->rasterizer->tmp)->nbr_of_triangle);
		wn->rasterizer->tmp2 = make_triangles(wn->rasterizer->poly_list, &((t_myraster*)wn->rasterizer->tmp)->nbr_of_triangle);
		printf("POS %f %f %f %d\n", wn->rasterizer->curr_pos.x, wn->rasterizer->curr_pos.y, wn->rasterizer->curr_pos.z, ((t_myraster*)wn->rasterizer->tmp)->nbr_of_triangle);

		//tmp2 = triangle array
		// + jai besoin du nombre max de triangle

		//wn->rasterizer->max = ft_get_nbr_of_triangle(wn->rasterizer->tmp3);

		ft_update_raster(wn->rasterizer->tmp, wn->rasterizer->tmp2, wn); **/
//		ft_clear_window(wn);
		wn->rasterizer->curr_pos.x = ((t_myraster*)wn->rasterizer->tmp)->v_camera.x;
		wn->rasterizer->curr_pos.y = ((t_myraster*)wn->rasterizer->tmp)->v_camera.y;
		wn->rasterizer->curr_pos.z = ((t_myraster*)wn->rasterizer->tmp)->v_camera.z;
		wn->rasterizer->poly_list = render_bsp(wn->rasterizer->bsp, &wn->rasterizer->curr_pos);
		wn->rasterizer->triangle_array = make_triangles(wn->rasterizer->poly_list, &wn->rasterizer->nbr_triangle);
		//! COCO 
		ft_update_raster(wn->rasterizer->tmp, wn->rasterizer->triangle_array , wn);
		((t_myraster *)wn->rasterizer->tmp)->modif = 0;
//		if (wn->interface == DGAME)
		SDL_RenderPresent(wn->rend);
	}
}

void	ft_launch_rasterization(t_win *wn)
{
	/** wn->rasterizer->tmp3 = NULL;
	//wn->rasterizer->tmp3 = ft_read_the_polygon_file();
	//ft_launch_bsp_tree(wn->rasterizer->tmp3);
	//wn->rasterizer->tmp2 = ft_get_triangles_array(wn->rasterizer->tmp3); **/
	wn->rasterizer->polygon_lst = NULL;
  	//wn->rasterizer->polygon_lst = ft_read_the_polygon_file();
	//ft_launch_bsp_tree(wn->rasterizer->polygon_lst); // PROTECTION POUR SAVE FROM EDITOR
	//wn->rasterizer->triangle_array = ft_get_triangles_array(wn->rasterizer->polygon_lst);
	//wn->rasterizer->nbr_triangle = ft_get_nbr_of_triangle(wn->rasterizer->polygon_lst);
	wn->rasterizer->tmp = malloc(sizeof(t_myraster));
	wn->rasterizer->tmp = ft_init_rasterization(wn, (t_myraster*)(wn->rasterizer->tmp));
	wn->rasterizer->bsp = bsp_compile();
	wn->rasterizer->curr_pos.x = ((t_myraster*)wn->rasterizer->tmp)->v_camera.x;
	wn->rasterizer->curr_pos.y = ((t_myraster*)wn->rasterizer->tmp)->v_camera.y;
	wn->rasterizer->curr_pos.z = ((t_myraster*)wn->rasterizer->tmp)->v_camera.z;
	wn->rasterizer->poly_list = render_bsp(wn->rasterizer->bsp, &wn->rasterizer->curr_pos);
	wn->rasterizer->triangle_array = make_triangles(wn->rasterizer->poly_list, &wn->rasterizer->nbr_triangle);
	// wn->rasterizer->triangle_array = make_triangles(wn->rasterizer->poly_list, &wn->rasterizer->nbr_triangle);
	//wn->rasterizer->tmp = malloc(sizeof(t_myraster));
	//wn->rasterizer->tmp = ft_init_rasterization(wn, (t_myraster*)(wn->rasterizer->tmp));
}
