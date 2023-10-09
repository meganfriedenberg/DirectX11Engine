#pragma once
#include "engineMath.h"
#include "Graphics.h"

namespace Lights
{
	struct PointLightData
	{
		Vector3 lightColor = Vector3::Zero;
		float padding; // I think we only need one padding here
		Vector3 position = Vector3::Zero;
		float innerRadius = 0;
		float outerRadius = 0; // Start of 4 boundary
		bool isEnabled = false; // need 3 bytes to fill in rest
		float additionalPadding;
		float additionalPadding2; // is now a multiple of 16
	};

	const int MAX_POINT_LIGHTS = 8;
 //   #define MAX_POINT_LIGHTS 8

	struct LightingConstants
	{
		Vector3 c_ambient = Vector3::Zero;
		float padding;
		PointLightData c_pointLight[MAX_POINT_LIGHTS];
	};
}

