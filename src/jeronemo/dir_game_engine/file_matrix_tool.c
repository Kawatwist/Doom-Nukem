/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_matrix_tool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 17:17:48 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/27 17:17:56 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <header_game_engine.h>

float	**ft_make_matrix_5_5(void)
{
	float	**matrix;
	int		i;
	int		j;

	i = 0;
	matrix = (float**)malloc(sizeof(float*) * 5);
	while(i < 5)
	{
		matrix[i] = (float*)malloc(sizeof(float) * 5);
		i++;
	}
	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			matrix[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (matrix);
}
