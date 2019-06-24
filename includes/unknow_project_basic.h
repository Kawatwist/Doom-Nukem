#ifndef UNKNOW_PROJECT_BASIC_H
# define UNKNOW_PROJECT_BASIC_H

/* char			*ft_strnew(int size); */
/* int				ft_strlen(char *str); */
/* char			*ft_strdup(char *src); */
/* char			*ft_strjoin(char *src1, char *src2); */
void			ft_stradd(char **src1, char *src2);
void 			ft_putchar(char c);
/* void 			ft_putstr(char *str); */
void 			ft_putnbr(int n);
char			*ft_strcut(char **src, char delim);
/* int				ft_strchr(char *src, char d); */
/* int				get_next_line(const int fd, char **line); */
char			**ft_strsplit(char const *s, char c);
int				ft_tablen(char **tab);
void 			error_exit(int error, char *message);
void			ft_bzero(void *src, size_t nb_bytes);
void			endl();
float			ft_atof(char *s);
/* int				ft_strcmp(char *s1, char *s2); */
int				ft_atoi(const char *str);
int				ft_floor(float source);
float			ft_abs_float(float src);

int				min(int a, int b);
int				max(int a, int b);
float			float_min(float a, float b);
float			float_max(float a, float b);

#endif
