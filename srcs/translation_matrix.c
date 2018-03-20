#include <scop.h>

void	translation_matrix(float *mat, float x, float y, float z)
{
	float	translation[16];
	float	res[16];

	init_identity_matrix(translation);
	mat[12] = x;
	mat[13] = y;
	mat[14] = z;
	multMatrix(mat, translation, res);
	memcpy(mat, res, sizeof(float) * 16);
}
