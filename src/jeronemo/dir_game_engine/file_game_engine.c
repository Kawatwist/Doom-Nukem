/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_game_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 11:45:42 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/11 14:32:27 by jchardin         ###   ########.fr       */
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
	if ((((t_myraster*)wn->rasterizer->tmp)->modif == 1 && wn->interface == DGAME) || wn->interface == RGAME)
	{
		ft_clear_window(wn);

		wn->rasterizer->curr_pos.x = ((t_myraster*)wn->rasterizer->tmp)->v_camera.x;
		wn->rasterizer->curr_pos.y = ((t_myraster*)wn->rasterizer->tmp)->v_camera.y;
		wn->rasterizer->curr_pos.z = ((t_myraster*)wn->rasterizer->tmp)->v_camera.z;
		wn->rasterizer->poly_list = render_bsp(wn->rasterizer->bsp, &wn->rasterizer->curr_pos);
		wn->rasterizer->tmp2 = make_triangles(wn->rasterizer->poly_list);
		printf("POS %f %f %f\n", wn->rasterizer->curr_pos.x, wn->rasterizer->curr_pos.y, wn->rasterizer->curr_pos.z);

		ft_init_update_raster(wn->rasterizer->tmp);


		//ici v_camera est ok


		//tmp2 = triangle array
		// + jai besoin du nombre max de triangle

		wn->rasterizer->max = ft_get_nbr_of_triangle(wn->rasterizer->tmp3);

		ft_update_raster(wn->rasterizer->tmp, wn->rasterizer->tmp2, wn);
		((t_myraster *)wn->rasterizer->tmp)->modif = 0;
		if (wn->interface == DGAME)
			SDL_RenderPresent(wn->rend);
	}
}

void	ft_launch_rasterization(t_win *wn)
{
	wn->rasterizer->tmp3 = NULL;
	//wn->rasterizer->tmp3 = ft_read_the_polygon_file();
	//ft_launch_bsp_tree(wn->rasterizer->tmp3);
	//wn->rasterizer->tmp2 = ft_get_triangles_array(wn->rasterizer->tmp3);
	wn->rasterizer->tmp = malloc(sizeof(t_myraster));
	wn->rasterizer->tmp = ft_init_rasterization(wn, (t_myraster*)(wn->rasterizer->tmp));
	wn->rasterizer->bsp = bsp_compile();
	wn->rasterizer->curr_pos.x = ((t_myraster*)wn->rasterizer->tmp)->v_camera.x;
	wn->rasterizer->curr_pos.y = ((t_myraster*)wn->rasterizer->tmp)->v_camera.y;
	wn->rasterizer->curr_pos.z = ((t_myraster*)wn->rasterizer->tmp)->v_camera.z;
	wn->rasterizer->poly_list = render_bsp(wn->rasterizer->bsp, &wn->rasterizer->curr_pos);
	wn->rasterizer->tmp2 = make_triangles(wn->rasterizer->poly_list);
	//wn->rasterizer->tmp = malloc(sizeof(t_myraster));
	//wn->rasterizer->tmp = ft_init_rasterization(wn, (t_myraster*)(wn->rasterizer->tmp));
}
