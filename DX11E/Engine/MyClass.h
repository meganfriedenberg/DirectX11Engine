#pragma once
class MyClass
{
public:
	struct Vector3
	{
		float x, y, z;
	};

	MyClass();
	virtual ~MyClass();
	virtual void Update();

	bool isAlive;
	Vector3 pos;
	Vector3 vel;
};
