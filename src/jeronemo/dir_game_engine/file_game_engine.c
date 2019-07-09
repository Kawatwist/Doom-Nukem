/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_game_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:16:31 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/09 14:17:49 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

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

void	ft_launch_rasterization(t_win *wn)
{
	t_myraster			raster;
	t_mytriangle		*triangle_array;
	t_mypolygon			*polygon_lst;
	int					max;

	polygon_lst = NULL;
	polygon_lst = ft_read_the_polygon_file();
	ft_launch_bsp_tree(polygon_lst);
	triangle_array = ft_get_triangles_array(polygon_lst);
	max = ft_get_nbr_of_triangle(polygon_lst);
	ft_init_rasterization(wn, &raster);
	/* ft_display_triangle_array(s_win, triangle_array, max); */
	while (!raster.quit)
	{
		ft_input_event_check(wn, &raster);
		if (raster.modif == 1 && !raster.quit)
		{
			ft_clear_window(wn);
			ft_update_raster(&raster, triangle_array, max, wn);
			SDL_RenderPresent(wn->rend);
			SDL_Delay(30);
			raster.modif = 0;
		}
		setkeyboard(raster.old, wn->state);
	}
}
