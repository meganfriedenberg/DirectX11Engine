#pragma once
#include <engineMath.h>
class BoneTransform
{
public:
	BoneTransform();
	BoneTransform(Vector3 vec, Quaternion q);
	Matrix4 toMatrix() const;
	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f);

	Quaternion mRotation;
	Vector3 mTranslate;

};

