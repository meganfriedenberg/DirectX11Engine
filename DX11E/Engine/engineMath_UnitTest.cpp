#include "stdafx.h"
#include "engineMath.h"

//----------------------------------------------------------------------------------------
// UnitTest for the Vector2 class
//----------------------------------------------------------------------------------------
/*static*/ bool Vector2::UnitTest()
{
    bool isOk = true;

    Vector2 testVector(-1.0f, 0.0f);

    // add 2 vectors
    {
        Vector2 addVector = testVector + Vector2(1.0f, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.x, 0.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, -1.0f);
        addVector = testVector;
        addVector += Vector2(0.0f, 2.0f);
        isOk &= Math::IsCloseEnuf(addVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, 2.0f);
    }

    // subtract 2 vectors
    {
        Vector2 subVector = testVector - Vector2(1.0f, -1.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, 1.0f);
        subVector = testVector;
        subVector -= Vector2(0.0f, 2.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, -2.0f);
    }

    // component multiply
    {
        Vector2 mulVector = testVector * Vector2(1.0f, 2.0f);
        isOk &= Math::IsCloseEnuf(mulVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(mulVector.y, 0.0f);
    }

    //scalar multiply
    {
        Vector2 scaleVector = testVector * 2.0f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        scaleVector = 0.5f * testVector;
        isOk &= Math::IsCloseEnuf(scaleVector.x, -0.5f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        scaleVector = testVector;
        scaleVector *= -3.0f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, 3.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
    }

    //scalar divide
    {
        Vector2 scaleVector = testVector / 2.0f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, -0.5f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        scaleVector = testVector;
        scaleVector /= -0.5f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, 2.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
    }

    // length
    {
        float lengthSq = testVector.LengthSq();
        isOk &= Math::IsCloseEnuf(lengthSq, 1.0f);
        float length = Vector2(4.0f, 3.0f).Length();
        isOk &= Math::IsCloseEnuf(length, 5.0f);
    }

    // normalize
    {
        Vector2 testNorm = testVector;
        testNorm.Normalize();
        isOk &= Math::IsCloseEnuf(testNorm.x, -1.0f);
        isOk &= Math::IsCloseEnuf(testNorm.y, 0.0f);
        testNorm = Normalize(Vector2(10.0f, -10.0f));
        isOk &= Math::IsCloseEnuf(testNorm.x, 0.70710678f);
        isOk &= Math::IsCloseEnuf(testNorm.y, -0.70710678f);
    }

    // dot product
    {
        Vector2 dotVector(2.0f, 0.5f);
        float dot = Dot(testVector, dotVector);
        isOk &= Math::IsCloseEnuf(dot, -2.0f);
    }

    // lerp
    {
        Vector2 testVector(-1.0f, 0.0f);

        Vector2 lerp = Lerp(testVector, Vector2::Zero, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, testVector.x);
        isOk &= Math::IsCloseEnuf(lerp.y, testVector.y);
        lerp = Lerp(testVector, Vector2::Zero, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        lerp = Lerp(testVector, Vector2::Zero, 0.5f);
        isOk &= Math::IsCloseEnuf(lerp.x, -0.5f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        lerp = Lerp(testVector, Vector2::Zero, 2.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
    }

    return isOk;
}

//----------------------------------------------------------------------------------------
// UnitTest for the Vector3 class
//----------------------------------------------------------------------------------------
static bool UnitTest_Vector3()
{
    bool isOk = true;

    Vector3 testVector(-1.0f, 0.0f, 3.0f);

    // add 2 vectors
    {
        Vector3 addVector = testVector + Vector3(1.0f, -1.0f, 2.0f);
        isOk &= Math::IsCloseEnuf(addVector.x, 0.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.z, 5.0f);
        addVector = testVector;
        addVector += Vector3(0.0f, 2.0f, -4.0f);
        isOk &= Math::IsCloseEnuf(addVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, 2.0f);
        isOk &= Math::IsCloseEnuf(addVector.z, -1.0f);
    }

    // subtract 2 vectors
    {
        Vector3 subVector = testVector - Vector3(1.0f, -1.0f, 2.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, 1.0f);
        isOk &= Math::IsCloseEnuf(subVector.z, 1.0f);
        subVector = testVector;
        subVector -= Vector3(0.0f, 2.0f, -4.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, -2.0f);
        isOk &= Math::IsCloseEnuf(subVector.z, 7.0f);
    }

    // component multiply
    {
        Vector3 mulVector = testVector * Vector3(1.0f, 2.0f, -3.0f);
        isOk &= Math::IsCloseEnuf(mulVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(mulVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(mulVector.z, -9.0f);
    }

    //scalar multiply
    {
        Vector3 scaleVector = testVector * 2.0f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, 6.0f);
        scaleVector = 0.5f * testVector;
        isOk &= Math::IsCloseEnuf(scaleVector.x, -0.5f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, 1.5f);
        scaleVector = testVector;
        scaleVector *= -3.0f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, 3.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, -9.0f);
    }

    //scalar divide
    {
        Vector3 scaleVector = testVector / 2.0f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, -0.5f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, 1.5f);
        scaleVector = testVector;
        scaleVector /= -0.5f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, 2.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, -6.0f);
    }

    // length
    {
        float lengthSq = testVector.LengthSq();
        isOk &= Math::IsCloseEnuf(lengthSq, 10.0f);
        float length = Vector3(4.0f, 0.0f, -3.0f).Length();
        isOk &= Math::IsCloseEnuf(length, 5.0f);
    }

    // normalize
    {
        Vector3 testNorm = testVector;
        testNorm.Normalize();
        isOk &= Math::IsCloseEnuf(testNorm.x, -0.31622777f);
        isOk &= Math::IsCloseEnuf(testNorm.y, 0.0f);
        isOk &= Math::IsCloseEnuf(testNorm.z, 0.9486833f);
        testNorm = Normalize(Vector3(0.0f, -10.0f, 10.0f));
        isOk &= Math::IsCloseEnuf(testNorm.x, 0.0f);
        isOk &= Math::IsCloseEnuf(testNorm.y, -0.70710678f);
        isOk &= Math::IsCloseEnuf(testNorm.z, 0.70710678f);
    }

    // dot product
    {
        Vector3 dotVector(2.0f, 0.5f, -1.0f);
        float dot = Dot(testVector, dotVector);
        isOk &= Math::IsCloseEnuf(dot, -5.0f);
    }

    // cross product
    {
        Vector3 crossVector = Cross(testVector, Vector3(2.0f, 0.5f, -1.0f));
        isOk &= Math::IsCloseEnuf(crossVector.x, -1.5f);
        isOk &= Math::IsCloseEnuf(crossVector.y, 5.0f);
        isOk &= Math::IsCloseEnuf(crossVector.z, -0.5f);

        // x cross y = z
        crossVector = Cross(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        isOk &= Math::IsCloseEnuf(crossVector.x, 0.0f);
        isOk &= Math::IsCloseEnuf(crossVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(crossVector.z, 1.0f);

        // y cross z = x
        crossVector = Cross(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
        isOk &= Math::IsCloseEnuf(crossVector.x, 1.0f);
        isOk &= Math::IsCloseEnuf(crossVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(crossVector.z, 0.0f);

        // x cross z = -y
        crossVector = Cross(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));
        isOk &= Math::IsCloseEnuf(crossVector.x, 0.0f);
        isOk &= Math::IsCloseEnuf(crossVector.y, -1.0f);
        isOk &= Math::IsCloseEnuf(crossVector.z, 0.0f);
    }

    // lerp
    {
        Vector3 testVector(-1.0f, 0.0f, 3.0f);

        Vector3 lerp = Lerp(testVector, Vector3::Zero, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, testVector.x);
        isOk &= Math::IsCloseEnuf(lerp.y, testVector.y);
        isOk &= Math::IsCloseEnuf(lerp.z, testVector.z);
        lerp = Lerp(testVector, Vector3::Zero, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        lerp = Lerp(testVector, Vector3::Zero, 0.5f);
        isOk &= Math::IsCloseEnuf(lerp.x, -0.5f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 1.5f);
        lerp = Lerp(testVector, Vector3::Zero, 2.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, -3.0f);
    }

    // string some together
    {
        Vector3 chainVector = 2.0f * testVector - Cross(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)) * Dot(Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 2.0f));
        isOk &= Math::IsCloseEnuf(chainVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(chainVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(chainVector.z, 4.0f);
    }

    return isOk;
}

//----------------------------------------------------------------------------------------
// UnitTest for the Vector4 class
//----------------------------------------------------------------------------------------
static bool UnitTest_Vector4()
{
    bool isOk = true;

    Vector4 testVector(-1.0f, 0.0f, 3.0f, 1.0f);

    // add 2 vectors
    {
        Vector4 addVector = testVector + Vector4(1.0f, -1.0f, 2.0f, 0.5f);
        isOk &= Math::IsCloseEnuf(addVector.x, 0.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.z, 5.0f);
        isOk &= Math::IsCloseEnuf(addVector.w, 1.5f);
        addVector = testVector;
        addVector += Vector4(0.0f, 2.0f, -4.0f, 0.0f);
        isOk &= Math::IsCloseEnuf(addVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, 2.0f);
        isOk &= Math::IsCloseEnuf(addVector.z, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.w, 1.0f);
    }

    // subtract 2 vectors
    {
        Vector4 subVector = testVector - Vector4(1.0f, -1.0f, 2.0f, 0.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, 1.0f);
        isOk &= Math::IsCloseEnuf(subVector.z, 1.0f);
        isOk &= Math::IsCloseEnuf(subVector.w, 1.0f);
        subVector = testVector;
        subVector -= Vector4(0.0f, 2.0f, -4.0f, 1.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, -2.0f);
        isOk &= Math::IsCloseEnuf(subVector.z, 7.0f);
        isOk &= Math::IsCloseEnuf(subVector.w, 0.0f);
    }

    // component multiply
    {
        Vector4 mulVector = testVector * Vector4(1.0f, 2.0f, -3.0f, 1.0f);
        isOk &= Math::IsCloseEnuf(mulVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(mulVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(mulVector.z, -9.0f);
        isOk &= Math::IsCloseEnuf(mulVector.w, 1.0f);
    }

    //scalar multiply
    {
        Vector4 scaleVector = testVector * 2.0f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, 6.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.w, 2.0f);
        scaleVector = 0.5f * testVector;
        isOk &= Math::IsCloseEnuf(scaleVector.x, -0.5f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, 1.5f);
        isOk &= Math::IsCloseEnuf(scaleVector.w, 0.5f);
        scaleVector = testVector;
        scaleVector *= -3.0f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, 3.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, -9.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.w, -3.0f);
    }

    //scalar divide
    {
        Vector4 scaleVector = testVector / 2.0f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, -0.5f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, 1.5f);
        isOk &= Math::IsCloseEnuf(scaleVector.w, 0.5f);
        scaleVector = testVector;
        scaleVector /= -0.5f;
        isOk &= Math::IsCloseEnuf(scaleVector.x, 2.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.z, -6.0f);
        isOk &= Math::IsCloseEnuf(scaleVector.w, -2.0f);
    }

    // length
    {
        float lengthSq = testVector.LengthSq();
        isOk &= Math::IsCloseEnuf(lengthSq, 11.0f);
        float length = Vector4(4.0f, 0.0f, -3.0f, 0.0f).Length();
        isOk &= Math::IsCloseEnuf(length, 5.0f);
    }

    // normalize
    {
        Vector4 testNorm = testVector;
        testNorm.Normalize();
        isOk &= Math::IsCloseEnuf(testNorm.x, -0.3015113445778f);
        isOk &= Math::IsCloseEnuf(testNorm.y, 0.0f);
        isOk &= Math::IsCloseEnuf(testNorm.z, 0.9045340337333f);
        isOk &= Math::IsCloseEnuf(testNorm.w, 0.3015113445778f);
        testNorm = Normalize(Vector4(0.0f, -10.0f, 10.0f, 0.0f));
        isOk &= Math::IsCloseEnuf(testNorm.x, 0.0f);
        isOk &= Math::IsCloseEnuf(testNorm.y, -0.70710678f);
        isOk &= Math::IsCloseEnuf(testNorm.z, 0.70710678f);
        isOk &= Math::IsCloseEnuf(testNorm.w, 0.0f);
    }

    // lerp
    {
        Vector4 lerp = Lerp(testVector, Vector4::Zero, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, testVector.x);
        isOk &= Math::IsCloseEnuf(lerp.y, testVector.y);
        isOk &= Math::IsCloseEnuf(lerp.z, testVector.z);
        isOk &= Math::IsCloseEnuf(lerp.w, testVector.w);
        lerp = Lerp(testVector, Vector4::Zero, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.0f);
        lerp = Lerp(testVector, Vector4::Zero, 0.5f);
        isOk &= Math::IsCloseEnuf(lerp.x, -0.5f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 1.5f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.5f);
        lerp = Lerp(testVector, Vector4::Zero, 2.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, -3.0f);
        isOk &= Math::IsCloseEnuf(lerp.w, -1.0f);
    }

    return isOk;
}

//----------------------------------------------------------------------------------------
// Compares 2 matrices for use in the UnitTest()
//----------------------------------------------------------------------------------------
static bool MatrixCompare(const Matrix3& mat1, const Matrix3& mat2)
{
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 3; ++x)
        {
            if (false == Math::IsCloseEnuf(mat1.mat[y][x], mat2.mat[y][x]))
                return false;
        }
    }

    return true;
}

//----------------------------------------------------------------------------------------
// Compares 2 matrices for use in the UnitTest()
//----------------------------------------------------------------------------------------
static bool MatrixCompare(const Matrix4& mat1, const Matrix4& mat2)
{
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (false == Math::IsCloseEnuf(mat1.mat[y][x], mat2.mat[y][x]))
                return false;
        }
    }

    return true;
}

static Matrix4 CreateYawPitchRoll(const Vector3& rot)
{
    return Matrix4::CreateYawPitchRoll(rot.y, rot.x, rot.z);
}

//----------------------------------------------------------------------------------------
// UnitTest for the Matrix4 class
//----------------------------------------------------------------------------------------
static bool UnitTest_Matrix4()
{
    bool isOk = true;

    // this matrix has a 0.5 scale on X, a 90 degree rotation around X, and a translation of (10, 20, -30)
    const float	s_testMat[4][4] =
    {
        { 0.5f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, -1.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 10.0f, 20.0f, -30.0f, 1.0f }
    };
    Matrix4	testMat(s_testMat);

    //Transform a vector position
    {
        Vector3 pos(100.0f, -200.0f, 300.0f);
        Vector3 testPos = Transform(pos, testMat);
        isOk &= Math::IsCloseEnuf(testPos.x, 60.0f);
        isOk &= Math::IsCloseEnuf(testPos.y, 320.0f);
        isOk &= Math::IsCloseEnuf(testPos.z, 170.0f);
    }

    //Transform a vector direction
    {
        Vector3 dir(-10.0f, 20.0f, -30.0f);
        Vector3 testDir = Transform(dir, testMat, 0.0f);
        isOk &= Math::IsCloseEnuf(testDir.x, -5.0f);
        isOk &= Math::IsCloseEnuf(testDir.y, -30.0f);
        isOk &= Math::IsCloseEnuf(testDir.z, -20.0f);
    }

    //Invert a matrix
    {
        const float	s_invMat[4][4] =
        {
            { 2.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, -1.0f, 0.0f, 0.0f },
            { -20.0f, -30.0f, -20.0f, 1.0f }
        };
        Matrix4 testInv = testMat;
        testInv.Invert();
        isOk &= MatrixCompare(testInv, Matrix4(s_invMat));

        // also testing multiply here
        Matrix4 testMult = testMat * testInv;
        isOk &= MatrixCompare(testMult, Matrix4::Identity);
        testMult = testInv * testMat;
        isOk &= MatrixCompare(testMult, Matrix4::Identity);
    }

    //create a translation matrix
    {
        const float s_tranMat[4][4] =
        {
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 100.0f, -50.0f, 0.5f, 1.0f }
        };
        const Vector3 s_tran(100.0f, -50.0f, 0.5f);
        Matrix4 testTran = Matrix4::CreateTranslation(s_tran);
        isOk &= MatrixCompare(testTran, Matrix4(s_tranMat));
        Vector3 testTranVec = testTran.GetTranslation();
        isOk &= Math::IsCloseEnuf(testTranVec.x, s_tran.x);
        isOk &= Math::IsCloseEnuf(testTranVec.y, s_tran.y);
        isOk &= Math::IsCloseEnuf(testTranVec.z, s_tran.z);
    }

    //create a rotation in X
    {
        const float s_rotMat[4][4] =
        {
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, -1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        Matrix4 testRot = Matrix4::CreateRotationX(Math::ToRadians(90.0f));
        isOk &= MatrixCompare(testRot, Matrix4(s_rotMat));
    }

    //create a rotation in Y
    {
        const float s_rotMat[4][4] =
        {
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { -1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        Matrix4 testRot = Matrix4::CreateRotationY(Math::ToRadians(-90.0f));
        isOk &= MatrixCompare(testRot, Matrix4(s_rotMat));
    }

    //create a rotation in Z
    {
        const float s_rotMat[4][4] =
        {
            { 0.0f, -1.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        Matrix4 testRot = Matrix4::CreateRotationZ(Math::ToRadians(-90.0f));
        isOk &= MatrixCompare(testRot, Matrix4(s_rotMat));
    }

    //create from yaw, pitch, and roll
    {	// 90 degrees pitch
        const float s_rotMat[4][4] =
        {
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, -1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        Vector3 rotation(Math::ToRadians(90.0f), Math::ToRadians(0.0f), Math::ToRadians(0.0f));
        Matrix4 testRot = CreateYawPitchRoll(rotation);
        isOk &= MatrixCompare(testRot, Matrix4(s_rotMat));
    }
    {	// 90 degrees yaw
        const float s_rotMat[4][4] =
        {
            { 0.0f, 0.0f, -1.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        Vector3 rotation(Math::ToRadians(0.0f), Math::ToRadians(90.0f), Math::ToRadians(0.0f));
        Matrix4 testRot = CreateYawPitchRoll(rotation);
        isOk &= MatrixCompare(testRot, Matrix4(s_rotMat));
    }
    {	// 90 degrees roll
        const float s_rotMat[4][4] =
        {
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { -1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        Vector3 rotation(Math::ToRadians(0.0f), Math::ToRadians(0.0f), Math::ToRadians(90.0f));
        Matrix4 testRot = CreateYawPitchRoll(rotation);
        isOk &= MatrixCompare(testRot, Matrix4(s_rotMat));
    }
    {	// 90 degrees yaw, 90 degree pitch
        const float s_rotMat[4][4] =
        {
            { 0.0f, 0.0f, -1.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, -1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        Vector3 rotation(Math::ToRadians(90.0f), Math::ToRadians(90.0f), Math::ToRadians(0.0f));
        Matrix4 testRot = CreateYawPitchRoll(rotation);
        isOk &= MatrixCompare(testRot, Matrix4(s_rotMat));
    }
    {	// 90 degrees yaw, 45 degree pitch, -20 degrees roll
        const float s_rotMat[4][4] =
        {
            { 0.42261824f, 0.90630776f, 0.0f, 0.0f },
            { 0.0f, 0.0f, -1.0f, 0.0f },
            { -0.90630776f, 0.42261824f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        Vector3 rotation(Math::ToRadians(90.0f), Math::ToRadians(45.0f), Math::ToRadians(-20.0f));
        Matrix4 testRot = CreateYawPitchRoll(rotation);
        Matrix4 rotXPose = Matrix4(s_rotMat);
        rotXPose.Transpose();
        isOk &= MatrixCompare(testRot, Matrix4(rotXPose));
    }

    //create a scale
    {
        const float s_scaleMat[4][4] =
        {
            { 0.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 2.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, -0.5f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        Matrix4 testScale = Matrix4::CreateScale(Vector3(0.0f, 2.0f, -0.5f));
        isOk &= MatrixCompare(testScale, Matrix4(s_scaleMat));
    }

    //create a lookAt
    {
        const float s_lookMat[4][4] =
        {
            { 0.0f, 0.0f, -1.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 10.0f, 20.0f, 30.0f, 1.0f }
        };
        const Vector3 pos(10.0f, 20.0f, 30.0f);
        const Vector3 lookAt(30.0f, 20.0f, 30.0f);
        Matrix4 testLook = Matrix4::CreateLookAt(pos, lookAt, Vector3(0.0f, 1.0f, 0.0f));
        isOk &= MatrixCompare(testLook, Matrix4(s_lookMat));
        Vector3 fwd = Transform(Vector3(0.0f, 0.0f, 1.0f), testLook, 0.0f);
        isOk &= Math::IsCloseEnuf(fwd.x, 1.0f);
        isOk &= Math::IsCloseEnuf(fwd.y, 0.0f);
        isOk &= Math::IsCloseEnuf(fwd.z, 0.0f);
        Vector3 up = Transform(Vector3(0.0f, 1.0f, 0.0f), testLook, 0.0f);
        isOk &= Math::IsCloseEnuf(up.x, 0.0f);
        isOk &= Math::IsCloseEnuf(up.y, 1.0f);
        isOk &= Math::IsCloseEnuf(up.z, 0.0f);
        Vector3 left = Transform(Vector3(1.0f, 0.0f, 0.0f), testLook, 0.0f);
        isOk &= Math::IsCloseEnuf(left.x, 0.0f);
        isOk &= Math::IsCloseEnuf(left.y, 0.0f);
        isOk &= Math::IsCloseEnuf(left.z, -1.0f);
    }

    //beat on that invert some more
    {
        Matrix4 test = Matrix4::CreateTranslation(Vector3(-100.0f, 200.0f, 300.0f))
            * Matrix4::CreateScale(Vector3(0.5f, 2.0f, -3.0f))
            * Matrix4::CreateYawPitchRoll(0.2f, -1.0f, 0.1f);
        Matrix4 inv = test;
        inv.Invert();
        isOk &= MatrixCompare(test * inv, Matrix4::Identity);

        // test the GetScale
        Vector3 scale = test.GetScale();
        isOk &= Math::IsCloseEnuf(scale.x, 0.5f);
        isOk &= Math::IsCloseEnuf(scale.y, 2.0f);
        isOk &= Math::IsCloseEnuf(scale.z, 3.0f);
    }

    //check the axis functions
    {
        Matrix4 test = Matrix4::CreateRotationX(Math::ToRadians(90.0f));
        Vector3 x = test.GetXAxis();
        Vector3 y = test.GetYAxis();
        Vector3 z = test.GetZAxis();
        isOk &= Math::IsCloseEnuf(x.x, 1.0f);
        isOk &= Math::IsCloseEnuf(x.y, 0.0f);
        isOk &= Math::IsCloseEnuf(x.z, 0.0f);
        isOk &= Math::IsCloseEnuf(y.x, 0.0f);
        isOk &= Math::IsCloseEnuf(y.y, 0.0f);
        isOk &= Math::IsCloseEnuf(y.z, 1.0f);
        isOk &= Math::IsCloseEnuf(z.x, 0.0f);
        isOk &= Math::IsCloseEnuf(z.y, -1.0f);
        isOk &= Math::IsCloseEnuf(z.z, 0.0f);
    }

    return isOk;
}

/*static*/ bool Vector3::UnitTest()
{
    return UnitTest_Vector3();
}

/*static*/ bool Vector4::UnitTest()
{
    return UnitTest_Vector4();
}

/*static*/ bool Matrix4::UnitTest()
{
    return UnitTest_Matrix4();
}

/*static*/ bool Matrix3::UnitTest()
{
    bool isOk = true;

    // this matrix has a 0.5 scale on X, a 90 degree rotation around X, and a translation of (10, 20, -30)
    const float	s_testMat[3][3] =
    {
        { 0.5f, 0.0f, 0.0f },
        { 0.0f, 0.0f, -1.0f },
        { 0.0f, 1.0f, 0.0f }
    };
    Matrix3	testMat(s_testMat);

    //Transform a Vector2 direction
    {
        const float	s_rotMat[3][3] =
        {
            { 0.0f, 0.5f, 0.0f },
            { -0.5f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.5f }
        };
        Matrix3	rot(s_rotMat);
        Vector2 dir(30.0f, -26.0f);
        Vector2 testDir = Transform(dir, rot);
        isOk &= Math::IsCloseEnuf(testDir.x, 13.0f);
        isOk &= Math::IsCloseEnuf(testDir.y, 15.0f);
    }

    //Transform a Vector3 direction
    {
        Vector3 dir(-10.0f, 20.0f, -30.0f);
        Vector3 testDir = Transform(dir, testMat);
        isOk &= Math::IsCloseEnuf(testDir.x, -5.0f);
        isOk &= Math::IsCloseEnuf(testDir.y, -30.0f);
        isOk &= Math::IsCloseEnuf(testDir.z, -20.0f);
    }

    //Transpose a matrix
    {
        const float	s_invMat[3][3] =
        {
            { 0.5f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, -1.0f, 0.0f }
        };
        Matrix3 testInv = testMat;
        testInv.Transpose();
        isOk &= MatrixCompare(testInv, Matrix3(s_invMat));

        // also testing multiply here
        Matrix3 testRot = Matrix3::CreateRotation(Math::ToRadians(63.0f));
        testInv = testRot;
        testInv.Transpose();
        Matrix3 testMult = testRot * testInv;
        isOk &= MatrixCompare(testMult, Matrix3::Identity);
        testMult = testInv * testRot;
        isOk &= MatrixCompare(testMult, Matrix3::Identity);
    }

    //create a rotation in Z
    {
        const float s_rotMat[3][3] =
        {
            { 0.0f, -1.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f }
        };
        Matrix3 testRot = Matrix3::CreateRotation(Math::ToRadians(-90.0f));
        isOk &= MatrixCompare(testRot, Matrix3(s_rotMat));
    }

    //create a translation matrix
    {
        const float s_tranMat[3][3] =
        {
            { 1.0f, 0.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f },
            { 100.0f, -50.0f, 1.0f }
        };
        const Vector2 s_tran(100.0f, -50.0f);
        Matrix3 testTran = Matrix3::CreateTranslation(s_tran);
        isOk &= MatrixCompare(testTran, Matrix3(s_tranMat));
        const Vector2 s_test(-10.0f, -20.0f);
        Vector2 tran = Transform(s_test, testTran, 1.0f);
        isOk &= Math::IsCloseEnuf(tran.x, 90.0f);
        isOk &= Math::IsCloseEnuf(tran.y, -70.0f);
    }

    //create from rotation, translation, and scale
    {
        const float s_rotMat[3][3] =
        {
            { 0.0f, 0.5f, 0.0f },
            { -0.5f, 0.0f, 0.0f },
            { -10.0f, 20.0f, 1.0f }
        };
        Vector3 rotation(Math::ToRadians(90.0f), Math::ToRadians(0.0f), Math::ToRadians(0.0f));
        Matrix3 testRot = Matrix3::CreateRotation(Math::ToRadians(90.0f));
        Matrix3 testTran = Matrix3::CreateTranslation(Vector2(-10.0f, 20.0f));
        Matrix3 testScale = Matrix3::CreateScale(0.5f);
        Matrix3 testCombine = testScale * testRot * testTran;
        isOk &= MatrixCompare(testCombine, Matrix3(s_rotMat));
    }

    //create a scale
    {
        const float s_scaleMat[3][3] =
        {
            { 2.0f, 0.0f, 0.0f },
            { 0.0f, -0.5f, 0.0f },
            { 0.0f, 0.0f, 1.0f },
        };
        Matrix3 testScale = Matrix3::CreateScale(Vector2(2.0f, -0.5f));
        isOk &= MatrixCompare(testScale, Matrix3(s_scaleMat));
    }

    return isOk;
}

/*static*/ bool Quaternion::UnitTest()
{
    bool isOk = true;

    {
        Quaternion quat(Vector3::UnitZ, Math::PiOver2);
        Matrix4 mat = Matrix4::CreateFromQuaternion(quat);
        Vector3 vec(1.0f, 2.0f, 3.0f);
        Vector3 testVec = Transform(vec, mat);
        isOk &= Math::IsCloseEnuf(testVec.x, -2.0f);
        isOk &= Math::IsCloseEnuf(testVec.y, 1.0f);
        isOk &= Math::IsCloseEnuf(testVec.z, 3.0f);
    }

    {
        Quaternion q1(Vector3::UnitX, Math::PiOver2);
        Quaternion q2(Vector3::UnitY, Math::PiOver2);
        
        Quaternion lerp = Lerp(q1, q2, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.7071067811865475f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.7071067811865475f);

        lerp = Lerp(q1, q2, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.7071067811865475f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.7071067811865475f);

        lerp = Lerp(q1, q2, 0.5f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.408248305f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.408248305f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.816496611f);

        lerp = Slerp(q1, q2, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.7071067811865475f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.7071067811865475f);

        lerp = Slerp(q1, q2, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.7071067811865475f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.7071067811865475f);

        lerp = Slerp(q1, q2, 0.5f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.408248305f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.408248305f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.816496611f);
    }
    
    return isOk;
}

