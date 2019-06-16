/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_bsp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchardin <jerome.chardin@outlook.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:51:31 by jchardin          #+#    #+#             */
/*   Updated: 2019/06/08 10:13:37 by jchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

#define FALSE 0
#define TRUE 1

typedef enum			e_myclass
{
	FRONT,
	BACK,
	SPANNING,
	ON_PLANE,
}						t_myclass;

typedef struct			s_myvec
{
	float				x;
	float				y;
	float				z;
	struct s_myvec		*next;
}						t_myvec;

//indice allow you to build multiple triangles using share vectices
typedef struct			s_mypolygon
{
	t_myvec				*vertex_lst;             //liste des vertex
	t_myvec				normal;                  //la normal au polygon
	int					number_of_vertex;        //nombre de vertex
	int					number_of_indices;       //nombre d'indices
	int					*indices;                //la listes des indices apres triangulasisation
	int					id;
	struct s_mypolygon	*next;                   //le prochain noeud dans la liste
}						t_mypolygon;

//structure pour le bsp
typedef struct			s_mynode
{
	t_mypolygon			*splitter;
	struct s_mynode		*front;
	struct s_mynode		*back;
	char				is_leaf;
	char				is_solid;
}						t_mynode;

//structure principale
typedef struct			s_mywin
{
	t_mypolygon			*polygon_lst;

}						t_mywin;

//maths function
float			ft_dot_product(t_myvec v1, t_myvec v2);
t_myvec			ft_cross_product(t_myvec v1, t_myvec v2);
t_myvec			ft_vector_from_two_points(t_myvec v2, t_myvec v1);
int				ft_abs(int number);
float			ft_abs_float(float number);

t_myvec			ft_calculate_normal_of_points(t_myvec vertex1, t_myvec vertex2, t_myvec vertex3);

void			ft_display_the_polygon_list(t_mypolygon *polygon_lst);
t_mypolygon		*ft_read_the_polygon_file(char *argv);
void			ft_process_polygon(t_mypolygon *polygon_lst);
int				ft_classify_polygon(t_mypolygon *plane, t_mypolygon *polygon_node);
int				ft_classify_point(t_myvec point, t_mypolygon *plane);
void			ft_split_polygon(t_mypolygon *poly,
							t_mypolygon *plane,
							t_mypolygon *front_split,
							t_mypolygon *back_split);


void			ft_build_bsp_tree(t_mynode *current_node, t_mypolygon *polygon_lst);
t_mypolygon		*ft_select_the_best_poly_splitter(t_mypolygon *polygon_lst);
void			ft_split_polygon(t_mypolygon *poly,
							t_mypolygon *plane,
							t_mypolygon *front_split,
							t_mypolygon *back_split);


void			ft_add_polygon(t_mypolygon **polygon_lst, t_mypolygon *polygon_node);
void			ft_add_vertex(t_myvec **vertex_lst, t_myvec *vertex_node);
void			ft_afficher_le_bsp(t_mynode *s_node);


