/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map_editor_update_show_cross.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 16:46:34 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/05 19:01:29 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <jeronemo.h>

void	ft_init_show_cross(t_mywin *s_win)
{
	s_win->show_cross[0] = 1;
	s_win->show_cross[1] = 0;
	s_win->show_cross[2] = 0;
	s_win->show_cross[3] = 1;
	s_win->show_cross[4] = 0;
}

void	ft_update_show_cross_seconde(t_mywin *s_win, int j)
{
	if (j == 0)
	{
		s_win->show_cross[0] = 1;
		s_win->show_cross[1] = 0;
	}
	else if (j == 1)
	{
		s_win->show_cross[0] = 0;
		s_win->show_cross[1] = 1;
	}
	else if (j == 3)
	{
		s_win->show_cross[3] = 1;
		s_win->show_cross[4] = 0;
	}
	else if(j == 4)
	{
		s_win->show_cross[3] = 0;
		s_win->show_cross[4] = 1;
	}
}

void	ft_update_show_cross(t_mywin *s_win, t_win *wn)
{
			int		j;

			j = 0;
			while (j <= 4)
			{
				if (j != 2 && wn->input->x > s_win->s_localisation_box[j].x &&
						wn->input->x < s_win->s_localisation_box[j].x + s_win->s_localisation_box[j].width)
				{
					if (wn->input->y > s_win->s_localisation_box[j].y &&
							wn->input->y < s_win->s_localisation_box[j].y + s_win->s_localisation_box[j].height)
						ft_update_show_cross_seconde(s_win, j);
				}
				j++;
			}
}
