/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_order_z_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:13:58 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/10 16:26:41 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

void	ft_order_triangle_z_buffer(t_mytriangle **triangle_lst_lst)
{
	float			z1;
	float			z2;


	t_mytriangle *triangle_lst = *triangle_lst_lst;
	t_mytriangle	*keep;

	if (triangle_lst == NULL)
		return;
	keep = triangle_lst;
	while (triangle_lst->next != NULL)
	{
		z1 = (triangle_lst->vertice[0].z + triangle_lst->vertice[1].z + triangle_lst->vertice[2].z) / 3;
		z2 = (triangle_lst->next->vertice[0].z + triangle_lst->next->vertice[1].z + triangle_lst->next->vertice[2].z) / 3;
		if (z1 > z2)  ///jai inverser
		{
			ft_swap_node_with_the_next(&keep, triangle_lst);
			triangle_lst = keep;
		}
		else
			triangle_lst = triangle_lst->next;
		if (triangle_lst == NULL)
			break;
	}
	*triangle_lst_lst = keep;
}
