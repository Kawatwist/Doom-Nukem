/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_apply_calcul.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:33:36 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/11 12:00:24 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header_game_engine.h>


void	ft_apply_calucul(t_myvec function(float**, t_myvec), t_mytriangle *triangle, float **matrix)
{
	triangle->vertice[0] = function(matrix, triangle->vertice[0]);
	triangle->vertice[1] = function(matrix, triangle->vertice[1]);
	triangle->vertice[2] = function(matrix, triangle->vertice[2]);
}

