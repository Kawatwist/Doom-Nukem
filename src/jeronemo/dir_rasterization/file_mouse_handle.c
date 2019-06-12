/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mouse_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:47:41 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/12 14:30:28 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <jeronemo.h>


void	ft_display_menu_panel_cross(t_mywin *s_win, t_mychange *change)
{
	int		i = 0;
	t_mycross		s_cross;
	t_mycolor		s_color;

	if (change->display->projection == perspective)
	{

		s_color = ft_setcolor(PINK);
		s_cross = ft_setcross(
				XSCREEN - 400 + 25,
				30 + (i * 70) + 20,
				50, 10, s_color);
		ft_draw_cross(s_win, &s_cross);
	}
	i++;

	if (change->display->projection == orthographique)
	{
		s_color = ft_setcolor(PINK);
		s_cross = ft_setcross(
				XSCREEN - 400 + 25,
				30 + (i * 70) + 20,
				50, 10, s_color);
		ft_draw_cross(s_win, &s_cross);
	}
	i++;
	if (change->display->culling_face == 1)
	{
		s_color = ft_setcolor(PINK);
		s_cross = ft_setcross(
				XSCREEN - 400 + 25,
				30 + (i * 70) + 20,
				50, 10, s_color);
		ft_draw_cross(s_win, &s_cross);
	}
	i++;
	if (change->display->triangle == 1)
	{
		s_color = ft_setcolor(PINK);
		s_cross = ft_setcross(
				XSCREEN - 400 + 25,
				30 + (i * 70) + 20,
				50, 10, s_color);
		ft_draw_cross(s_win, &s_cross);
	}
	i++;
	if (change->display->triangle_normal == 1)
	{
		s_color = ft_setcolor(PINK);
		s_cross = ft_setcross(
				XSCREEN - 400 + 25,
				30 + (i * 70) + 20,
				50, 10, s_color);
		ft_draw_cross(s_win, &s_cross);
	}
	i++;
	if (change->display->mesh == 1)
	{
		s_color = ft_setcolor(PINK);
		s_cross = ft_setcross(
				XSCREEN - 400 + 25,
				30 + (i * 70) + 20,
				50, 10, s_color);
		ft_draw_cross(s_win, &s_cross);
	}
	i++;
	if (change->display->mesh_normal == 1)
	{
		s_color = ft_setcolor(PINK);
		s_cross = ft_setcross(
				XSCREEN - 400 + 25,
				30 + (i * 70) + 20,
				50, 10, s_color);
		ft_draw_cross(s_win, &s_cross);
	}
}


void	ft_display_panel(t_mywin *s_win, t_mychange *change)
{
	int		nbr_menu;
	char	**menu_name;
	int			i;

	nbr_menu = 8;
	menu_name = (char**)malloc(sizeof(char*) * nbr_menu);
	menu_name[0] = ft_strdup("P ->Perspective");
	menu_name[1] = ft_strdup("P ->Orthographique");
	menu_name[2] = ft_strdup("C ->Culing face");
	menu_name[3] = ft_strdup("T ->Display triangle");
	menu_name[4] = ft_strdup("B ->Display triangle normal");
	menu_name[5] = ft_strdup("M ->Display mesh");
	menu_name[6] = ft_strdup("N ->Display mesh normal");
	menu_name[7] = ft_strdup("Color");

	t_mycolor	s_color;
	t_mysquare	s_square;
	t_mywrite	s_write;
	t_mysquare	*menu_panel;

	menu_panel = malloc(sizeof(t_mysquare));
	i = 0;
	while (i < nbr_menu - 1)
	{

		s_color 			= ft_setcolor(WHITE);
		menu_panel->x		= XSCREEN - 400;
		menu_panel->y		= 30 + (i * 70);
		menu_panel->width	= 50;
		menu_panel->height	= 50;
		s_square = ft_setsquare(
				menu_panel->x,
 				menu_panel->y,
				menu_panel->width,
				menu_panel->height,
				s_color);
		ft_draw_square(s_win, &s_square);
		s_color = ft_setcolor(WHITE);
		//int x, int y, t_mycolor color, int size, char *str
		s_write = ft_setwrite(
				XSCREEN - 300,
 				30 + (i * 70),
				s_color, 20, menu_name[i]);
		ft_write(s_win, &s_write);
		i++;

		ft_display_menu_panel_cross(s_win, change);
	}

}

int	ft_click_perspective()
{
	return (0);
}
int	ft_click_orthographique()
{
	return (0);
}
int	ft_click_culing_face()
{
	return (0);
}
int	ft_click_display_triangle()
{
	return (0);
}
int	ft_click_display_triangle_normal()
{
	return (0);
}
int	ft_click_display_mesh()
{
	return (0);
}
int	ft_click_display_mesh_normal()
{
	return (0);
}
int	ft_click_color()
{
	return (0);
}

void		ft_mouse_event_check(t_win *wn, t_mychange *change)
{
	(void)change;
	if ((wn->input->mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) && ((wn->input->oldmouse & SDL_BUTTON(SDL_BUTTON_LEFT)) == 0)  )


		if (ft_click_perspective())
		{
		}
	if (ft_click_orthographique())
	{
	}
	if (ft_click_culing_face())
	{
	}
	if (ft_click_display_triangle())
	{
	}
	if (ft_click_display_triangle_normal())
	{
	}
	if (ft_click_display_mesh())
	{
	}
	if (ft_click_display_mesh_normal())
	{
	}
	if (ft_click_color())
	{
	}
}
