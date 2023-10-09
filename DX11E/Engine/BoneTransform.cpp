#include "stdafx.h"
#include "BoneTransform.h"

BoneTransform::BoneTransform()
{

}
BoneTransform::BoneTransform(Vector3 vec, Quaternion q)
{
	mTranslate = vec;
	mRotation = q;
}

Matrix4 BoneTransform::toMatrix() const
{
	Matrix4 rotation = Matrix4::CreateFromQuaternion(mRotation);
	Matrix4 translation = Matrix4::CreateTranslation(mTranslate);

	return rotation * translation;
}
BoneTransform BoneTransform::Interpolate(const BoneTransform& a, const BoneTransform& b, float f)
{
	Vector3 lerped = Lerp(a.mTranslate, b.mTranslate, f);
	Quaternion l = Slerp(a.mRotation, b.mRotation, f);

	BoneTransform bt(lerped, l);

	return bt;
}