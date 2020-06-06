#include <scop.h>

void	init_identity_matrix(t_mat4x4 *mat)
{
	mat->mat[0][0] = 1.0f;
	mat->mat[0][1] = 0.0f;
	mat->mat[0][2] = 0.0f;
	mat->mat[0][3] = 0.0f;
	mat->mat[1][0] = 0.0f;
	mat->mat[1][1] = 1.0f;
	mat->mat[1][2] = 0.0f;
	mat->mat[1][3] = 0.0f;
	mat->mat[2][0] = 0.0f;
	mat->mat[2][1] = 0.0f;
	mat->mat[2][2] = 1.0f;
	mat->mat[2][3] = 0.0f;
	mat->mat[3][0] = 0.0f;
	mat->mat[3][1] = 0.0f;
	mat->mat[3][2] = 0.0f;
	mat->mat[3][3] = 1.0f;
}

void	init_projection_matrix(int height, int width, t_mat4x4 *mat)
{
	float	near;
	float	far;
	float	theta;

	near = 0.1f;
	far = 100.0f;
	theta = (float)tan(45.0 * 0.5 * M_PI / 180.0);
	init_identity_matrix(mat);
	mat->mat[0][0] = 1 / (((float)width / (float)height) * theta);
	mat->mat[1][1] = 1 / theta;
	mat->mat[0][2] = 0;
	mat->mat[1][2] = 0;
	mat->mat[2][2] = (far + near) / (-far + near);
	mat->mat[2][3] = -(2 * far * near) / (far - near);
	mat->mat[3][2] = -1;
	mat->mat[3][3] = 0;
}

void	init_view_matrix(t_vec3 *pos, t_vec3 *center, t_vec3 *up, t_mat4x4 *ret)
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;

	vec3_sub(pos, center, &z);
	vec3_normalize(&z, &z);
	vec3_cross(up, &z, &x);
	vec3_normalize(&x, &x);
	vec3_cross(&z, &x, &y);
	ret->mat[0][0] = x.x;
	ret->mat[0][1] = x.y;
	ret->mat[0][2] = x.z;
	ret->mat[0][3] = -vec3_dot(&x, pos);
	ret->mat[1][0] = y.x;
	ret->mat[1][1] = y.y;
	ret->mat[1][2] = y.z;
	ret->mat[1][3] = -vec3_dot(&y, pos);
	ret->mat[2][0] = z.x;
	ret->mat[2][1] = z.y;
	ret->mat[2][2] = z.z;
	ret->mat[2][3] = -vec3_dot(&z, pos);
	ret->mat[3][0] = 0;
	ret->mat[3][1] = 0;
	ret->mat[3][2] = 0;
	ret->mat[3][3] = 1;
}

void	construct_model_matrix(t_object *obj)
{
	init_identity_matrix(&obj->model_matrix);
	obj->model_matrix.mat[0][0] = obj->dimensions.x;
	obj->model_matrix.mat[1][1] = obj->dimensions.y;
	obj->model_matrix.mat[2][2] = obj->dimensions.z;
	mat4x4_mult(&obj->model_matrix, &obj->rotation_matrix, &obj->model_matrix);
	mat4x4_displace(&obj->model_matrix, obj->world_position.x, \
		obj->world_position.y, obj->world_position.z);
}
