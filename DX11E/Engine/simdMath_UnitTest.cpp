#include "stdafx.h"
#include "simdMath.h"


//----------------------------------------------------------------------------------------
// UnitTest for the SIMDVector3 class
//----------------------------------------------------------------------------------------
static bool UnitTest_Vector3()
{
    bool isOk = true;

    SIMDVector3 testVector(-1.0f, 0.0f, 3.0f);

    // add 2 vectors
    {
        SIMDVector3 addVector = testVector + SIMDVector3(1.0f, -1.0f, 2.0f);
        isOk &= Math::IsCloseEnuf(addVector.x, 0.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.z, 5.0f);
        addVector = testVector;
        addVector += SIMDVector3(0.0f, 2.0f, -4.0f);
        isOk &= Math::IsCloseEnuf(addVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, 2.0f);
        isOk &= Math::IsCloseEnuf(addVector.z, -1.0f);
    }

    // subtract 2 vectors
    {
        SIMDVector3 subVector = testVector - SIMDVector3(1.0f, -1.0f, 2.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, 1.0f);
        isOk &= Math::IsCloseEnuf(subVector.z, 1.0f);
        subVector = testVector;
        subVector -= SIMDVector3(0.0f, 2.0f, -4.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, -2.0f);
        isOk &= Math::IsCloseEnuf(subVector.z, 7.0f);
    }

    // component multiply
    {
        SIMDVector3 mulVector = testVector * SIMDVector3(1.0f, 2.0f, -3.0f);
        isOk &= Math::IsCloseEnuf(mulVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(mulVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(mulVector.z, -9.0f);
    }

    //scalar multiply
    {
        SIMDVector3 scaleVector = testVector * 2.0f;
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
        SIMDVector3 scaleVector = testVector / 2.0f;
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
        float length = SIMDVector3(4.0f, 0.0f, -3.0f).Length();
        isOk &= Math::IsCloseEnuf(length, 5.0f);
    }

    // normalize
    {
        SIMDVector3 testNorm = testVector;
        testNorm.Normalize();
        isOk &= Math::IsCloseEnuf(testNorm.x, -0.31622777f);
        isOk &= Math::IsCloseEnuf(testNorm.y, 0.0f);
        isOk &= Math::IsCloseEnuf(testNorm.z, 0.9486833f);
        testNorm = Normalize(SIMDVector3(0.0f, -10.0f, 10.0f));
        isOk &= Math::IsCloseEnuf(testNorm.x, 0.0f);
        isOk &= Math::IsCloseEnuf(testNorm.y, -0.70710678f);
        isOk &= Math::IsCloseEnuf(testNorm.z, 0.70710678f);
    }

    // dot product
    {
        SIMDVector3 dotVector(2.0f, 0.5f, -1.0f);
        float dot = Dot(testVector, dotVector);
        isOk &= Math::IsCloseEnuf(dot, -5.0f);
    }

    // cross product
    {
        SIMDVector3 crossVector = Cross(testVector, SIMDVector3(2.0f, 0.5f, -1.0f));
        isOk &= Math::IsCloseEnuf(crossVector.x, -1.5f);
        isOk &= Math::IsCloseEnuf(crossVector.y, 5.0f);
        isOk &= Math::IsCloseEnuf(crossVector.z, -0.5f);

        // x cross y = z
        crossVector = Cross(SIMDVector3(1.0f, 0.0f, 0.0f), SIMDVector3(0.0f, 1.0f, 0.0f));
        isOk &= Math::IsCloseEnuf(crossVector.x, 0.0f);
        isOk &= Math::IsCloseEnuf(crossVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(crossVector.z, 1.0f);

        // y cross z = x
        crossVector = Cross(SIMDVector3(0.0f, 1.0f, 0.0f), SIMDVector3(0.0f, 0.0f, 1.0f));
        isOk &= Math::IsCloseEnuf(crossVector.x, 1.0f);
        isOk &= Math::IsCloseEnuf(crossVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(crossVector.z, 0.0f);

        // x cross z = -y
        crossVector = Cross(SIMDVector3(1.0f, 0.0f, 0.0f), SIMDVector3(0.0f, 0.0f, 1.0f));
        isOk &= Math::IsCloseEnuf(crossVector.x, 0.0f);
        isOk &= Math::IsCloseEnuf(crossVector.y, -1.0f);
        isOk &= Math::IsCloseEnuf(crossVector.z, 0.0f);
    }

    // lerp
    {
        SIMDVector3 testVector(-1.0f, 0.0f, 3.0f);

        SIMDVector3 lerp = Lerp(testVector, SIMDVector3::Zero, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, testVector.x);
        isOk &= Math::IsCloseEnuf(lerp.y, testVector.y);
        isOk &= Math::IsCloseEnuf(lerp.z, testVector.z);
        lerp = Lerp(testVector, SIMDVector3::Zero, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        lerp = Lerp(testVector, SIMDVector3::Zero, 0.5f);
        isOk &= Math::IsCloseEnuf(lerp.x, -0.5f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 1.5f);
        lerp = Lerp(testVector, SIMDVector3::Zero, 2.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, -3.0f);
    }

    // string some together
    {
        SIMDVector3 chainVector = 2.0f * testVector - Cross(SIMDVector3(1.0f, 0.0f, 0.0f), SIMDVector3(0.0f, 1.0f, 0.0f)) * Dot(SIMDVector3(0.0f, 0.0f, 1.0f), SIMDVector3(0.0f, 0.0f, 2.0f));
        isOk &= Math::IsCloseEnuf(chainVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(chainVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(chainVector.z, 4.0f);
    }

    return isOk;
}

//----------------------------------------------------------------------------------------
// UnitTest for the SIMDVector4 class
//----------------------------------------------------------------------------------------
static bool UnitTest_Vector4()
{
    bool isOk = true;

    SIMDVector4 testVector(-1.0f, 0.0f, 3.0f, 1.0f);

    // add 2 vectors
    {
        SIMDVector4 addVector = testVector + SIMDVector4(1.0f, -1.0f, 2.0f, 0.5f);
        isOk &= Math::IsCloseEnuf(addVector.x, 0.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.z, 5.0f);
        isOk &= Math::IsCloseEnuf(addVector.w, 1.5f);
        addVector = testVector;
        addVector += SIMDVector4(0.0f, 2.0f, -4.0f, 0.0f);
        isOk &= Math::IsCloseEnuf(addVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.y, 2.0f);
        isOk &= Math::IsCloseEnuf(addVector.z, -1.0f);
        isOk &= Math::IsCloseEnuf(addVector.w, 1.0f);
    }

    // subtract 2 vectors
    {
        SIMDVector4 subVector = testVector - SIMDVector4(1.0f, -1.0f, 2.0f, 0.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -2.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, 1.0f);
        isOk &= Math::IsCloseEnuf(subVector.z, 1.0f);
        isOk &= Math::IsCloseEnuf(subVector.w, 1.0f);
        subVector = testVector;
        subVector -= SIMDVector4(0.0f, 2.0f, -4.0f, 1.0f);
        isOk &= Math::IsCloseEnuf(subVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(subVector.y, -2.0f);
        isOk &= Math::IsCloseEnuf(subVector.z, 7.0f);
        isOk &= Math::IsCloseEnuf(subVector.w, 0.0f);
    }

    // component multiply
    {
        SIMDVector4 mulVector = testVector * SIMDVector4(1.0f, 2.0f, -3.0f, 1.0f);
        isOk &= Math::IsCloseEnuf(mulVector.x, -1.0f);
        isOk &= Math::IsCloseEnuf(mulVector.y, 0.0f);
        isOk &= Math::IsCloseEnuf(mulVector.z, -9.0f);
        isOk &= Math::IsCloseEnuf(mulVector.w, 1.0f);
    }

    //scalar multiply
    {
        SIMDVector4 scaleVector = testVector * 2.0f;
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
        SIMDVector4 scaleVector = testVector / 2.0f;
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
        float length = SIMDVector4(4.0f, 0.0f, -3.0f, 0.0f).Length();
        isOk &= Math::IsCloseEnuf(length, 5.0f);
    }

    // normalize
    {
        SIMDVector4 testNorm = testVector;
        testNorm.Normalize();
        isOk &= Math::IsCloseEnuf(testNorm.x, -0.3015113445778f);
        isOk &= Math::IsCloseEnuf(testNorm.y, 0.0f);
        isOk &= Math::IsCloseEnuf(testNorm.z, 0.9045340337333f);
        isOk &= Math::IsCloseEnuf(testNorm.w, 0.3015113445778f);
        testNorm = Normalize(SIMDVector4(0.0f, -10.0f, 10.0f, 0.0f));
        isOk &= Math::IsCloseEnuf(testNorm.x, 0.0f);
        isOk &= Math::IsCloseEnuf(testNorm.y, -0.70710678f);
        isOk &= Math::IsCloseEnuf(testNorm.z, 0.70710678f);
        isOk &= Math::IsCloseEnuf(testNorm.w, 0.0f);
    }

    // lerp
    {
        SIMDVector4 lerp = Lerp(testVector, SIMDVector4::Zero, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, testVector.x);
        isOk &= Math::IsCloseEnuf(lerp.y, testVector.y);
        isOk &= Math::IsCloseEnuf(lerp.z, testVector.z);
        isOk &= Math::IsCloseEnuf(lerp.w, testVector.w);
        lerp = Lerp(testVector, SIMDVector4::Zero, 1.0f);
        isOk &= Math::IsCloseEnuf(lerp.x, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.0f);
        lerp = Lerp(testVector, SIMDVector4::Zero, 0.5f);
        isOk &= Math::IsCloseEnuf(lerp.x, -0.5f);
        isOk &= Math::IsCloseEnuf(lerp.y, 0.0f);
        isOk &= Math::IsCloseEnuf(lerp.z, 1.5f);
        isOk &= Math::IsCloseEnuf(lerp.w, 0.5f);
        lerp = Lerp(testVector, SIMDVector4::Zero, 2.0f);
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
static bool MatrixCompare(const SIMDMatrix4& mat1, const SIMDMatrix4& mat2)
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

static SIMDMatrix4 CreateYawPitchRoll(const SIMDVector3& rot)
{
    return SIMDMatrix4::CreateYawPitchRoll(rot.y, rot.x, rot.z);
}

//----------------------------------------------------------------------------------------
// UnitTest for the SIMDMatrix4 class
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
    SIMDMatrix4	testMat(s_testMat);

    //Transform a vector position
    {
        SIMDVector3 pos(100.0f, -200.0f, 300.0f);
        SIMDVector3 testPos = Transform(pos, testMat);
        isOk &= Math::IsCloseEnuf(testPos.x, 60.0f);
        isOk &= Math::IsCloseEnuf(testPos.y, 320.0f);
        isOk &= Math::IsCloseEnuf(testPos.z, 170.0f);
    }

    //Transform a vector direction
    {
        SIMDVector3 dir(-10.0f, 20.0f, -30.0f);
        SIMDVector3 testDir = Transform(dir, testMat, 0.0f);
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
        SIMDMatrix4 testInv = testMat;
        testInv.Invert();
        isOk &= MatrixCompare(testInv, SIMDMatrix4(s_invMat));

        // also testing multiply here
        SIMDMatrix4 testMult = testMat * testInv;
        isOk &= MatrixCompare(testMult, SIMDMatrix4::Identity);
        testMult = testInv * testMat;
        isOk &= MatrixCompare(testMult, SIMDMatrix4::Identity);
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
        const SIMDVector3 s_tran(100.0f, -50.0f, 0.5f);
        SIMDMatrix4 testTran = SIMDMatrix4::CreateTranslation(s_tran);
        isOk &= MatrixCompare(testTran, SIMDMatrix4(s_tranMat));
        SIMDVector3 testTranVec = testTran.GetTranslation();
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
        SIMDMatrix4 testRot = SIMDMatrix4::CreateRotationX(Math::ToRadians(90.0f));
        isOk &= MatrixCompare(testRot, SIMDMatrix4(s_rotMat));
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
        SIMDMatrix4 testRot = SIMDMatrix4::CreateRotationY(Math::ToRadians(-90.0f));
        isOk &= MatrixCompare(testRot, SIMDMatrix4(s_rotMat));
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
        SIMDMatrix4 testRot = SIMDMatrix4::CreateRotationZ(Math::ToRadians(-90.0f));
        isOk &= MatrixCompare(testRot, SIMDMatrix4(s_rotMat));
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
        SIMDVector3 rotation(Math::ToRadians(90.0f), Math::ToRadians(0.0f), Math::ToRadians(0.0f));
        SIMDMatrix4 testRot = CreateYawPitchRoll(rotation);
        isOk &= MatrixCompare(testRot, SIMDMatrix4(s_rotMat));
    }
    {	// 90 degrees yaw
        const float s_rotMat[4][4] =
        {
            { 0.0f, 0.0f, -1.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        SIMDVector3 rotation(Math::ToRadians(0.0f), Math::ToRadians(90.0f), Math::ToRadians(0.0f));
        SIMDMatrix4 testRot = CreateYawPitchRoll(rotation);
        isOk &= MatrixCompare(testRot, SIMDMatrix4(s_rotMat));
    }
    {	// 90 degrees roll
        const float s_rotMat[4][4] =
        {
            { 0.0f, 1.0f, 0.0f, 0.0f },
            { -1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        SIMDVector3 rotation(Math::ToRadians(0.0f), Math::ToRadians(0.0f), Math::ToRadians(90.0f));
        SIMDMatrix4 testRot = CreateYawPitchRoll(rotation);
        isOk &= MatrixCompare(testRot, SIMDMatrix4(s_rotMat));
    }
    {	// 90 degrees yaw, 90 degree pitch
        const float s_rotMat[4][4] =
        {
            { 0.0f, 0.0f, -1.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f, 0.0f },
            { 0.0f, -1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        SIMDVector3 rotation(Math::ToRadians(90.0f), Math::ToRadians(90.0f), Math::ToRadians(0.0f));
        SIMDMatrix4 testRot = CreateYawPitchRoll(rotation);
        isOk &= MatrixCompare(testRot, SIMDMatrix4(s_rotMat));
    }
    {	// 90 degrees yaw, 45 degree pitch, -20 degrees roll
        const float s_rotMat[4][4] =
        {
            { 0.42261824f, 0.90630776f, 0.0f, 0.0f },
            { 0.0f, 0.0f, -1.0f, 0.0f },
            { -0.90630776f, 0.42261824f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f }
        };
        SIMDVector3 rotation(Math::ToRadians(90.0f), Math::ToRadians(45.0f), Math::ToRadians(-20.0f));
        SIMDMatrix4 testRot = CreateYawPitchRoll(rotation);
        SIMDMatrix4 rotXPose = SIMDMatrix4(s_rotMat);
        rotXPose.Transpose();
        isOk &= MatrixCompare(testRot, SIMDMatrix4(rotXPose));
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
        SIMDMatrix4 testScale = SIMDMatrix4::CreateScale(SIMDVector3(0.0f, 2.0f, -0.5f));
        isOk &= MatrixCompare(testScale, SIMDMatrix4(s_scaleMat));
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
        const SIMDVector3 pos(10.0f, 20.0f, 30.0f);
        const SIMDVector3 lookAt(30.0f, 20.0f, 30.0f);
        SIMDMatrix4 testLook = SIMDMatrix4::CreateLookAt(pos, lookAt, SIMDVector3(0.0f, 1.0f, 0.0f));
        isOk &= MatrixCompare(testLook, SIMDMatrix4(s_lookMat));
        SIMDVector3 fwd = Transform(SIMDVector3(0.0f, 0.0f, 1.0f), testLook, 0.0f);
        isOk &= Math::IsCloseEnuf(fwd.x, 1.0f);
        isOk &= Math::IsCloseEnuf(fwd.y, 0.0f);
        isOk &= Math::IsCloseEnuf(fwd.z, 0.0f);
        SIMDVector3 up = Transform(SIMDVector3(0.0f, 1.0f, 0.0f), testLook, 0.0f);
        isOk &= Math::IsCloseEnuf(up.x, 0.0f);
        isOk &= Math::IsCloseEnuf(up.y, 1.0f);
        isOk &= Math::IsCloseEnuf(up.z, 0.0f);
        SIMDVector3 left = Transform(SIMDVector3(1.0f, 0.0f, 0.0f), testLook, 0.0f);
        isOk &= Math::IsCloseEnuf(left.x, 0.0f);
        isOk &= Math::IsCloseEnuf(left.y, 0.0f);
        isOk &= Math::IsCloseEnuf(left.z, -1.0f);
    }

    //beat on that invert some more
    {
        SIMDMatrix4 test = SIMDMatrix4::CreateTranslation(SIMDVector3(-100.0f, 200.0f, 300.0f))
            * SIMDMatrix4::CreateScale(SIMDVector3(0.5f, 2.0f, -3.0f))
            * SIMDMatrix4::CreateYawPitchRoll(0.2f, -1.0f, 0.1f);
        SIMDMatrix4 inv = test;
        inv.Invert();
        isOk &= MatrixCompare(test * inv, SIMDMatrix4::Identity);
    }

    return isOk;
}

/*static*/ bool SIMDVector3::UnitTest()
{
    return UnitTest_Vector3();
}

/*static*/ bool SIMDVector4::UnitTest()
{
    return UnitTest_Vector4();
}

/*static*/ bool SIMDMatrix4::UnitTest()
{
    return UnitTest_Matrix4();
}

