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
	t_mypolygon		*new_lst;

	wn->rasterizer->tmp = (void *)ft_input_event_check(wn, wn->rasterizer->tmp);
	//############
	if ((((t_myraster*)wn->rasterizer->tmp)->modif == 1 && wn->interface == DGAME) || wn->interface == RGAME)
	{
//		ft_clear_window(wn);
		new_lst = NULL;
		ft_walk_bsp_tree(wn->rasterizer->bsp_node, &(((t_myraster *)wn->rasterizer->tmp)->v_camera), &new_lst);
 		ft_display_the_polygon_list(new_lst);

		wn->rasterizer->triangle_array = ft_get_triangles_array(new_lst);
		wn->rasterizer->nbr_triangle = ft_get_nbr_of_triangle(new_lst);
		printf("nbr_triangle%d\n", wn->rasterizer->nbr_triangle);
		((t_myraster*)wn->rasterizer->tmp)->nbr_of_triangle = wn->rasterizer->nbr_triangle;

		ft_update_raster(wn->rasterizer->tmp, wn->rasterizer->triangle_array, wn);
		((t_myraster *)wn->rasterizer->tmp)->modif = 0;
//		if (wn->interface == DGAME)
		SDL_RenderPresent(wn->rend);
	}
}

void	ft_launch_rasterization(t_win *wn)
{
	wn->rasterizer->polygon_lst = NULL;
  	wn->rasterizer->polygon_lst = ft_read_the_polygon_file();
	ft_launch_bsp_tree(wn->rasterizer->polygon_lst, &(wn->rasterizer->bsp_node)); // PROTECTION POUR SAVE FROM EDITOR

	// wn->rasterizer->triangle_array = ft_get_triangles_array(wn->rasterizer->polygon_lst);
	// wn->rasterizer->nbr_triangle = ft_get_nbr_of_triangle(wn->rasterizer->polygon_lst);
	wn->rasterizer->tmp = malloc(sizeof(t_myraster));
	wn->rasterizer->tmp = ft_init_rasterization(wn, (t_myraster*)(wn->rasterizer->tmp));
}
