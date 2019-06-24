#ifndef UNKNOW_PROJECT_VECTOR_H
# define UNKNOW_PROJECT_VECTOR_H

typedef struct	s_vector4
{
    float		x;
    float		y;
    float		z;
    float		w;
}				t_vector4;

t_vector4	create_t_vector4(float p_x, float p_y, float p_z, float p_w);
t_vector4	*initialize_t_vector4(float p_x, float p_y, float p_z, float p_w);
void 		print_t_vector4(t_vector4 vector, char *str);

typedef struct	s_vector3
{
    float		x;
    float		y;
    float		z;
}				t_vector3;

t_vector3	create_t_vector3(float p_x, float p_y, float p_z);
t_vector3	*initialize_t_vector3(float p_x, float p_y, float p_z);
t_vector3	add_vector3_to_vector3(t_vector3 a,t_vector3 b);
t_vector3	substract_vector3_to_vector3(t_vector3 a,t_vector3 b);
t_vector3	mult_vector3_by_vector3(t_vector3 a,t_vector3 b);
t_vector3	mult_vector3_by_float(t_vector3 a, float b);
t_vector3	divide_vector3_by_vector3(t_vector3 a,t_vector3 b);
t_vector3	divide_vector3_by_float(t_vector3 a, float b);
t_vector3	inv_t_vector3(t_vector3 src);
void		swap_t_vector3(t_vector3 *a, t_vector3 *b);
void 		print_t_vector3(t_vector3 vector, char *str);
t_vector3	substract_float_to_vector3(t_vector3 b, float a);
t_vector3	add_float_to_vector3(t_vector3 b, float a);
int			t_vector3_equal(t_vector3 a, t_vector3 b);

typedef struct	s_vector2
{
    float		x;
    float		y;
}				t_vector2;

t_vector2	create_t_vector2(float p_x, float p_y);
t_vector2	*initialize_t_vector2(float p_x, float p_y);
void 		print_t_vector2(t_vector2 vector, char *str);

typedef struct	s_vector4_int
{
    int			x;
    int			y;
    int			z;
    int			w;
}				t_vector4_int;

t_vector4_int
			create_t_vector4_int(int p_x, int p_y, int p_z, int p_w);
t_vector4_int
			*initialize_t_vector4_int(int p_x, int p_y, int p_z, int p_w);
void 		print_t_vector4_int(t_vector4_int vector, char *str);

typedef struct	s_vector3_int
{
    int			x;
    int			y;
    int			z;
}				t_vector3_int;

t_vector3_int
			create_t_vector3_int(int p_x, int p_y, int p_z);
t_vector3_int
			*initialize_t_vector3_int(int p_x, int p_y, int p_z);
void 		t_vector3_int_swap(t_vector3_int *a, t_vector3_int *b);
void 		t_vector3_int_add(t_vector3_int *src, int delta_x, int delta_y);
void 		set_t_vector3_int(t_vector3_int *src, int p_x, int p_y, int p_z);
void 		print_t_vector3_int(t_vector3_int vector, char *str);

typedef struct	s_vector2_int
{
    int			x;
    int			y;
}				t_vector2_int;

t_vector2_int
				create_t_vector2_int(int p_x, int p_y);
t_vector2_int
				*initialize_t_vector2_int(int p_x, int p_y);
void 		t_vector2_int_swap(t_vector2_int *a, t_vector2_int *b);
void 		t_vector2_int_add(t_vector2_int *src, int delta_x, int delta_y);
void 		set_t_vector2_int(t_vector2_int *src, int p_x, int p_y);
void 		print_t_vector2_int(t_vector2_int vector, char *str);

#endif
