/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rasterization_main.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 17:57:51 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/27 17:06:21 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>






t_vector3	substract_vector3_to_vector3(t_vector3 a,t_vector3 b)
{
	t_vector3	result;

	result = create_t_vector3(a.x - b.x, a.y - b.y, a.z - b.z);

	return (result);
}



t_vector3	add_vector3_to_vector3(t_vector3 a,t_vector3 b)
{
	t_vector3	result;

	result = create_t_vector3(a.x + b.x, a.y + b.y, a.z + b.z);

	return (result);
}




void	ft_order_triangle_vertice(t_myvec *v1, t_myvec *v2, t_myvec *v3);





