/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_vector_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 19:42:03 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/30 11:09:49 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>

t_myvec        ft_normalise(t_myvec vector)
{
   	float        l;

   	l = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
   	vector.x /= l;
   	vector.y /= l;
   	vector.z /= l;
   	return (vector);
}

t_myvec		ft_vector_sub(t_myvec v2, t_myvec v1)
{
	t_myvec result;

	result.x = v2.x - v1.x;
	result.y = v2.y - v1.y;
	result.z = v2.z - v1.z;
	return (result);
}
