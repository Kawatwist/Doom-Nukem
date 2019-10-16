/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:26:17 by jleblond          #+#    #+#             */
/*   Updated: 2019/10/14 14:26:36 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsp.h>
#include "doom.h"
#include "header_game_engine.h"


double		convert_rad_to_deg(double radian)
{
	return (radian * ((double)180) / M_PI);
}

float		angle_limit(float angle)
{
	while (angle >= 360)
		angle = angle - 360;
	while (angle < 0)
		angle = angle + 360;
	return (angle);
}

float	ft_float_abs(float x)
{
	return (x >= 0 ? x : -x);
}

// void	monster_visibility_test(t_win *wn, t_vec *mo_pos1, t_myvec)
// {

// }
// int			convert_mapdis_to_screendis(float distance, t_context *ct)
// {
// 	float	dis_max;
// 	int		wall_height;

// 	dis_max = sqrt(pow(ct->mpp.x, 2) + pow(ct->mpp.y, 2));
// 	wall_height = (int)((dis_max - distance) * 50.0 / distance) + 5;
// 	return (wall_height);
// }

// sous condition que angle de vision de camera est 60 degree!!!!!
void	draw_one_monster(t_win *wn, t_vec *mo_pos1)
{
	SDL_Rect	dst;
	float		mo_camera_angle;
	float		delta_angle;
	t_myvec		camera;
	float		theta_camera;
	float		distance;
	int			mo_height;
	// camera.x =  wn->rasterizer->curr_pos.x;
	// camera.y =  wn->rasterizer->curr_pos.y;
	// camera.z =  wn->rasterizer->curr_pos.z;
	(void)mo_pos1;
	camera.x =  ((t_myraster*)wn->rasterizer->tmp)->v_camera.x;
	camera.y =  -((t_myraster*)wn->rasterizer->tmp)->v_camera.y;
	camera.z =  -((t_myraster*)wn->rasterizer->tmp)->v_camera.z;
	theta_camera = angle_limit(((t_myraster*)wn->rasterizer->tmp)->theta_camera);
	distance = sqrt(pow(camera.x - mo_pos1->x, 2) + pow(camera.z - mo_pos1->z, 2));
	mo_height = (int)((100 - distance) * 50.0 / distance) + 5;
	printf("theta camera%f\n", theta_camera);
	printf("POSITION Camera====(%f, %f, %f)\n", camera.x, camera.y, camera.z);
	mo_camera_angle = convert_rad_to_deg(atan2((mo_pos1->y - camera.y)* (-1), (mo_pos1->x - camera.x)));
	// mo_camera_angle = angle_limit(mo_camera_angle);
	delta_angle = mo_camera_angle - theta_camera;

	if (ft_float_abs(delta_angle) > 150 && mo_camera_angle < theta_camera)
		delta_angle = mo_camera_angle + 360 - theta_camera;
	else if (ft_float_abs(delta_angle) > 150)
		delta_angle = mo_camera_angle - 360 - theta_camera;
	printf("mo_camera_ange:%fdelta ange: %f\n\n\n\n",mo_camera_angle, delta_angle);
	dst = define_rect((int)(wn->xscreen / 2 + wn->xscreen * delta_angle /
		60 - mo_height / 2), wn->yscreen / 2, mo_height, mo_height);
	// dst = define_rect((int)(wn->xscreen / 2 - wn->xscreen * delta_angle /
	// 	60 - mo_height / 2), wn->yscreen / 2, mo_height, mo_height);

	SDL_RenderCopy(wn->rend, findtexture(wn, "game", "monster", "alien"),
		 NULL, &dst);
}


void	display_monsters(t_win *wn)
{
	t_vec 		*mo_pos1;
	t_vec 		*mo_pos2;

	mo_pos1 = create_vec(0.0, -9.0, 10.0);
	mo_pos2 = create_vec(0.0, -9.0, 10.0);
	if (line_of_sight(wn->rasterizer->bsp, mo_pos1, mo_pos2, 0))
	{
		printf("Monster in the room\n\n\n\n\n\n");
		draw_one_monster(wn, mo_pos1);
	}
	else
	{
		printf("NO Monster\n\n");
	}
	free(mo_pos1);
	free(mo_pos2);
}
