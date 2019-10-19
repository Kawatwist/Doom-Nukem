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

double	convert_rad_to_deg(double radian)
{
	return (radian * ((double)180) / M_PI);
}

float	angle_correction(float angle)
{
	while (angle >= 360.0)
		angle = angle - 360.0;
	while (angle < 0.0)
		angle = angle + 360.0;
	return (angle);
}

float	ft_float_abs(float x)
{
	return (x >= 0.0 ? x : -x);
}

//delta angle is the angle between "lignt from centre of camera vision" and "light from camera to monster"
float	vertical_delta_angle(t_vec camera, float pitch, t_vec *mst_pos1)
{
	float 	mst_campoistion_angle;
	float	delta_angle_verti;

	mst_campoistion_angle = convert_rad_to_deg(atan2(mst_pos1->y - camera.y, mst_pos1->z - camera.z));
	if (mst_campoistion_angle * pitch < 0)
		delta_angle_verti = mst_campoistion_angle - pitch;
	else
		delta_angle_verti = mst_campoistion_angle + pitch;
	// delta_angle_verti = angle_correction(mst_campoistion_angle) - pitch;
	if (ft_float_abs(delta_angle_verti) >= 360.0)
		delta_angle_verti = 360.0 - ft_float_abs(delta_angle_verti);
	// printf("mst_campoistion_angle++++:%f, delta_angle_verti: %f\n", mst_campoistion_angle, delta_angle_verti);
	return (delta_angle_verti);
}

float	horizontal_delta_angle(t_vec camera, float theta, t_vec *mst_pos1)
{
	float 	mst_campoistion_angle;
	float	delta_angle_hori;

	mst_campoistion_angle = convert_rad_to_deg(atan2(mst_pos1->x - camera.x, mst_pos1->z - camera.z));
	delta_angle_hori = angle_correction(mst_campoistion_angle) - theta;
	if (ft_float_abs(delta_angle_hori) >= 180.0)
		delta_angle_hori = 360.0 - ft_float_abs(delta_angle_hori);
	// printf("mst_campoistion_angle++++:%f, delta_angle_verti: %f\n", mst_campoistion_angle, delta_angle_verti);
	return (delta_angle_hori);
}

void	draw_one_monster(t_win *wn, t_vec *mst_pos1)
{
	SDL_Rect	dst;
	float		delta_angle_hori;
	float		delta_angle_verti;
	t_vec		camera;
	float		theta;
	float		pitch;
	float		distance;
	int			mst_height;
	// float		pos_y;
	// float		pos_x;
	// float		ar;

	// pos_y = 0;
	// pos_x = 0;
	// ar = wn->xscreen / wn->yscreen;
	camera.x =  ((t_myraster*)wn->rasterizer->tmp)->v_camera.x;
	camera.y =  -((t_myraster*)wn->rasterizer->tmp)->v_camera.y;
	camera.z =  -((t_myraster*)wn->rasterizer->tmp)->v_camera.z;
	theta = angle_correction(((t_myraster*)wn->rasterizer->tmp)->theta_camera);
	pitch = angle_correction(((t_myraster*)wn->rasterizer->tmp)->pitch);
	printf("theta camera%f\n", theta);
	printf("pitch camera%f\n", pitch);
	printf("POSITION Camera====(%f, %f, %f)\n", camera.x, camera.y, camera.z);

	delta_angle_hori = horizontal_delta_angle(camera, theta, mst_pos1);
	delta_angle_verti = vertical_delta_angle(camera, pitch, mst_pos1);
	if (ft_float_abs(delta_angle_hori) < ANGLE_DE_VUE_CAMERA / 2
		&& ft_float_abs(delta_angle_verti) < ANGLE_DE_VUE_CAMERA / 2)
	{
		printf("visible@@@@@@@@@@@@@@@@@\n");
		distance = sqrt(pow(camera.x - mst_pos1->x, 2) + pow(camera.z - mst_pos1->z, 2));
		// mst_height = (int)((100 - distance) * 50.0 / distance) + 5;
		mst_height = (int)((100 - distance) * 50.0 / distance);
		mst_height = mst_height / 4;
		printf("\n\n\n\ndelta_angle_hori et vert:(%f, %f)\n\n\n\n", delta_angle_hori, delta_angle_verti);
		// if (delta_angle_verti == 0)
		// 	pos_y = 0;
		// else
		// 	pos_y = (mst_pos1->y - camera.y) / (mst_pos1->z - camera.z) / tan(ft_rad(delta_angle_verti));
		// if (delta_angle_hori == 0)
		// 	pos_x = 0;
		// else
		// 	pos_x = (mst_pos1->x - camera.x) / (mst_pos1->z - camera.z) / ar / tan(ft_rad(delta_angle_hori));
		// printf("position normalisé::::::::::::(%f,%f)\n", pos_x, pos_y);

		// dst = define_rect((int)(wn->xscreen / 2 + wn->xscreen * delta_angle_hori /
		// 		ANGLE_DE_VUE_CAMERA - mst_height / 2), wn->yscreen / 2 - wn->yscreen * pos_y / 2 , mst_height, mst_height);
		// dst = define_rect((int)(wn->xscreen / 2 - wn->xscreen * pos_x / 2 - mst_height / 2), (int)(wn->yscreen / 2 - wn->yscreen * pos_y / 2 - mst_height / 2), mst_height, mst_height);
		dst = define_rect((int)(wn->xscreen / 2 + wn->xscreen * delta_angle_hori /
				 ANGLE_DE_VUE_CAMERA - mst_height / 2), (int)(wn->yscreen / 2 - wn->yscreen * delta_angle_verti / ANGLE_DE_VUE_CAMERA - mst_height / 2), mst_height, mst_height);

			SDL_RenderCopy(wn->rend, findtexture(wn, "game", "monster", "alien"),
				 NULL, &dst);
	}
	else
		printf("NON VISIBLE@@@@@@@@@@\n");
}







void	display_monsters(t_win *wn)
{
	t_vec 		*mst_pos1;
	t_vec 		*mst_pos2;

	mst_pos1 = create_vec(0.0, -9.0, 10.0);
	mst_pos2 = create_vec(1.0, -9.0, 10.0);
	if (line_of_sight(wn->rasterizer->bsp, mst_pos1, mst_pos2, 0))
	{
		printf("Monster in the room\n\n\n\n\n\n");
		draw_one_monster(wn, mst_pos1);
	}
	else
	{
		printf("NO Monster\n\n");
	}
	free(mst_pos1);
	free(mst_pos2);
}
