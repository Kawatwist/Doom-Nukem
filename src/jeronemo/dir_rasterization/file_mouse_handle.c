/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mouse_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:47:41 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/12 12:59:42 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <jeronemo.h>


void	ft_display_panel()
{
	int		nbr_menu;
	char	**menu_name;
	int			i;

	nbr_menu = 8;
	menu_name = (char**)malloc(sizeof(char*) * nbr_menu);
	menu_name[0] = ft_strdup("Perspective");
	menu_name[1] = ft_strdup("Orthographique");
	menu_name[2] = ft_strdup("Culing face");
	menu_name[3] = ft_strdup("Display triangle");
	menu_name[4] = ft_strdup("Display triangle normal");
	menu_name[5] = ft_strdup("Display mesh");
	menu_name[6] = ft_strdup("Display mesh normal");
	menu_name[7] = ft_strdup("Color");


	i = 0;
	while (i < nbr_menu)
	{

		i++;
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
