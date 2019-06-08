/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:55:47 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/08 10:05:53 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

void	ft_game_engine(t_win *wn)
{
	t_mywin		s_win;
	int			choice;

	choice = 0;
	while (   !(choice >= 1 && choice <= 3)    )
	{
		printf("Hello chef inca\n");
		printf("GAME ENGINE MENU\n");
		printf("=> 1 <= Map editor\n");
		printf("=> 2 <= BSP Generator\n");
		printf("=> 3 <= Graphic engine\n");
		printf("\n");
		printf("Please make your choice\n");
		scanf("%d", &choice);
		printf("hello\n");
	}
	if (choice == 1)
		ft_launch_map_editor(&s_win, wn);
	else if (choice == 2)
		ft_launch_bsp_tree(&s_win, wn);
	else if (choice == 3)
		ft_launch_rasterization(&s_win, wn);
	ft_quit("je quite\n", &s_win);
}
