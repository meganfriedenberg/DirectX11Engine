#include "stdafx.h"
#include "simdMath.h"


const SIMDVector3 SIMDVector3::Zero(0.0f, 0.0f, 0.0f);
const SIMDVector3 SIMDVector3::One(1.0f, 1.0f, 1.0f);
const SIMDVector3 SIMDVector3::UnitX(1.0f, 0.0f, 0.0f);
const SIMDVector3 SIMDVector3::UnitY(0.0f, 1.0f, 0.0f);
const SIMDVector3 SIMDVector3::UnitZ(0.0f, 0.0f, 1.0f);

const SIMDVector4 SIMDVector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
const SIMDVector4 SIMDVector4::One(1.0f, 1.0f, 1.0f, 1.0f);
const SIMDVector4 SIMDVector4::UnitX(1.0f, 0.0f, 0.0f, 0.0f);
const SIMDVector4 SIMDVector4::UnitY(0.0f, 1.0f, 0.0f, 0.0f);
const SIMDVector4 SIMDVector4::UnitZ(0.0f, 0.0f, 1.0f, 0.0f);
const SIMDVector4 SIMDVector4::UnitW(0.0f, 0.0f, 0.0f, 1.0f);

static const float m4Ident[4][4] =
{
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

const SIMDMatrix4 SIMDMatrix4::Identity(m4Ident);

// Matt Whiting -- these are just copies of the floating point math.  
// Maybe someday I'll make pure SIMD versions of these...
// But not today.
void SIMDMatrix4::Invert()
{
    // Thanks slow math
    float tmp[12]; /* temp array for pairs */
    float src[16]; /* array of transpose source matrix */
    float dst[16]; /* storage */
    float det; /* determinant */
               /* transpose matrix */

               // row 1 to col 1
    src[0] = mat[0][0];
    src[4] = mat[0][1];
    src[8] = mat[0][2];
    src[12] = mat[0][3];

    // row 2 to col 2
    src[1] = mat[1][0];
    src[5] = mat[1][1];
    src[9] = mat[1][2];
    src[13] = mat[1][3];

    // row 3 to col 3
    src[2] = mat[2][0];
    src[6] = mat[2][1];
    src[10] = mat[2][2];
    src[14] = mat[2][3];

    // row 4 to col 4
    src[3] = mat[3][0];
    src[7] = mat[3][1];
    src[11] = mat[3][2];
    src[15] = mat[3][3];

    // 	for (int i = 0; i < 4; i++) {
    // 		src[i] = mat[i*4];
    // 		src[i + 4] = mat[i*4 + 1];
    // 		src[i + 8] = mat[i*4 + 2];
    // 		src[i + 12] = mat[i*4 + 3];
    // 	}
    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];
    /* calculate first 8 elements (cofactors) */
    dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[2] * src[7];
    tmp[1] = src[3] * src[6];
    tmp[2] = src[1] * src[7];
    tmp[3] = src[3] * src[5];
    tmp[4] = src[1] * src[6];
    tmp[5] = src[2] * src[5];
    tmp[6] = src[0] * src[7];
    tmp[7] = src[3] * src[4];
    tmp[8] = src[0] * src[6];
    tmp[9] = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];
    /* calculate second 8 elements (cofactors) */
    dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
    /* calculate determinant */
    det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];
    /* calculate matrix inverse */
    det = 1 / det;
    for (int j = 0; j < 16; j++)
        dst[j] *= det;

    // Set it back
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            mat[i][j] = dst[i * 4 + j];
        }
    }
}

SIMDMatrix4 SIMDMatrix4::CreateFromQuaternion(const Quaternion& q)
{
    float mat[4][4];

    mat[0][0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
    mat[0][1] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
    mat[0][2] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
    mat[0][3] = 0.0f;

    mat[1][0] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
    mat[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
    mat[1][2] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;
    mat[1][3] = 0.0f;

    mat[2][0] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
    mat[2][1] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
    mat[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
    mat[2][3] = 0.0f;

    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;

    return SIMDMatrix4(mat);
}
