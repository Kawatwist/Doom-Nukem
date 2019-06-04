/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:55:47 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/04 17:56:50 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	ft_jeronemo(t_win *wn)
{
	t_mywin	s_win;

	printf("hello chef inca\n");
	SDL_Init(SDL_INIT_EVERYTHING);
	ft_launch_map_editor(&s_win, wn);
	ft_launch_rasterization();
	//ft_quit("je quite\n", &s_win);
	//ft_launch_bsp_tree(&s_win, wn);

	exit(0);
}
