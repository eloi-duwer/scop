#include <scop.h>

void	rotation_matrix_X(float *mat, float angle)
{
	float	rot[16];
	float	res[16];

	rot[0] = 1;
	rot[1] = 0;
	rot[2] = 0;
	rot[3] = 0;
	rot[4] = 0;
	rot[5] = (float)cos(angle);
	rot[6] = (float)sin(angle);
	rot[7] = 0;
	rot[8] = 0;
	rot[9] = (float)-sin(angle);
	rot[10] = (float)cos(angle);
	rot[11] = 0;
	rot[12] = 0;
	rot[13] = 0;
	rot[14] = 0;
	rot[15] = 1;
	multMatrix(rot, mat, res);
	memcpy(mat, res, sizeof(float) * 16);
}

void	rotation_matrix_Y(float *mat, float angle)
{
	float	rot[16];
	float	res[16];

	rot[0] = (float)cos(angle);
	rot[1] = 0;
	rot[2] = (float)-sin(angle);
	rot[3] = 0;
	rot[4] = 0;
	rot[5] = 1;
	rot[6] = 0;
	rot[7] = 0;
	rot[8] = (float)sin(angle);
	rot[9] = 0;
	rot[10] = (float)cos(angle);
	rot[11] = 0;
	rot[12] = 0;
	rot[13] = 0;
	rot[14] = 0;
	rot[15] = 1;
	multMatrix(rot, mat, res);
	memcpy(mat, res, sizeof(float) * 16);
}

void	rotation_matrix_Z(float *mat, float angle)
{
	float	rot[16];
	float	res[16];

	rot[0] = (float)cos(angle);
	rot[1] = (float)sin(angle);
	rot[2] = 0;
	rot[3] = 0;
	rot[4] = (float)-sin(angle);
	rot[5] = (float)cos(angle);
	rot[6] = 0;
	rot[7] = 0;
	rot[8] = 0;
	rot[9] = 0;
	rot[10] = 1;
	rot[11] = 0;
	rot[12] = 0;
	rot[13] = 0;
	rot[14] = 0;
	rot[15] = 1;
	multMatrix(mat, rot, res);
	memcpy(mat, res, sizeof(float) * 16);
}
