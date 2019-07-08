/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bsp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:57:02 by jchardin          #+#    #+#             */
/*   Updated: 2019/07/08 14:43:10 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <jeronemo.h>

typedef struct		s_mypoint
{
	int				x;
	int				y;
	int				set;
}					t_mypoint;

typedef struct		s_mypointf
{
	double				x;
	double				y;
}					t_mypointf;

void			ft_build_bsp_tree(t_mynode *current_node, t_mypolygon *polygon_lst);
t_mypolygon		*ft_select_the_best_poly_splitter(t_mypolygon *polygon_lst);
void			ft_split_polygon(t_mypolygon *poly,
							t_mypolygon *plane,
							t_mypolygon *front_split,
							t_mypolygon *back_split);
void			ft_add_polygon(t_mypolygon **polygon_lst, t_mypolygon *polygon_node);
void			ft_afficher_le_bsp(t_mynode *s_node);
void			ft_display_the_polygon_list(t_mypolygon *polygon_lst);
t_mypolygon		*ft_read_the_polygon_file(void);
void			ft_process_polygon(t_mypolygon *polygon_lst);
int				ft_classify_polygon(t_mypolygon *plane, t_mypolygon *polygon_node);
int				ft_classify_point(t_myvec point, t_mypolygon *plane);
void			ft_split_polygon(t_mypolygon *poly,
							t_mypolygon *plane,
							t_mypolygon *front_split,
							t_mypolygon *back_split);
