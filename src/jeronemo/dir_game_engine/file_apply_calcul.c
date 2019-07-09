/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_apply_calcul.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:33:36 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/09 12:46:58 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>


t_mytriangle	ft_apply_calucul(t_myvec function(float**, t_myvec), t_mytriangle triangle, float **matrix)
{
	t_mytriangle	triangle_result;

	triangle_result.vertice[0] = function(matrix, triangle.vertice[0]);
	triangle_result.vertice[1] = function(matrix, triangle.vertice[1]);
	triangle_result.vertice[2] = function(matrix, triangle.vertice[2]);

	return (triangle_result);
}

