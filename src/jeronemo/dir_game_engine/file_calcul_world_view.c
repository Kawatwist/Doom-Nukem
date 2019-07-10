/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_calcul_world_view.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 12:36:58 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/10 12:44:47 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>


t_mytriangle	ft_calcul_world_view(t_mytriangle triangle, t_myraster *raster)
{
		//ROTATION Z
		triangle = ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_z);
		//ROTATION X
		triangle = ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_rot_x);
		//TRANSLATION (offset in screen)
		triangle = ft_apply_calucul(ft_matrix_multiply_vector, triangle, raster->mat_trans);
		return (triangle);
}
