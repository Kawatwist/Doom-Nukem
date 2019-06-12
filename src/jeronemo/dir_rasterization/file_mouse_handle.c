/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_mouse_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:47:41 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/12 11:57:29 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <jeronemo.h>

void		ft_mouse_event_check(t_win *wn, t_mychange *change)
{
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

}
