#pragma once

namespace GER
{
	struct CameraUBOData
	{
		Matrix4x4 View;
		Matrix4x4 Projection;
		Vector4 ViewPosition;
	};

	struct DirectionalLightData
	{
		Vector4 Direction; // 광원 -> 표면
		Vector4 Color; // rgb = 색상, a = 세기
	};

	struct PointLightData
	{
		Vector4 Position;
		Vector4 Color;
		Vector4 Attenuation;  // x=constant, y=linear, z=quadratic, w 미사용
	};

	struct SpotLightData
	{
		Vector4 Position;
		Vector4 Dirention;
		Vector4 Color;
		Vector4 Attenuation;
		Vector4 CutoffAngles;
	};

	constexpr int MAX_POINT_LIGHT = 4;

	struct LightUBOData
	{
		DirectionalLightData DirLight;
		PointLightData PointLights[MAX_POINT_LIGHT];
		SpotLightData SpotLight;
		UINT32 PointLightCount = 0;
		float _Padding[3] = { 0.f, 0.f, 0.f };
	};
}
