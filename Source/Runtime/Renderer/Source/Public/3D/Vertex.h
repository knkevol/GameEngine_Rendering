
#pragma once

namespace GER
{
namespace DDD
{

struct Vertex3D
{
public:
	constexpr Vertex3D() = default;
	constexpr Vertex3D(const Vector4& InPosition) : Position(InPosition) { }
	constexpr Vertex3D(const Vector4& InPosition, const LinearColor& InColor) : Position(InPosition), Color(InColor) { }
	constexpr Vertex3D(const Vector4& InPosition, const LinearColor& InColor, const Vector2& InUV) : Position(InPosition), Color(InColor), UV(InUV) { }

	constexpr Vertex3D operator*(float InScalar) const
	{
		return Vertex3D(
			Position * InScalar,
			Color * InScalar,
			UV * InScalar
		);
	}

	constexpr Vertex3D operator+(const Vertex3D& InVector) const
	{
		return Vertex3D(
			Position + InVector.Position,
			Color + InVector.Color,
			UV + InVector.UV
		);
	}

	Vector4 Position;
	LinearColor Color;
	Vector2 UV;
};

struct SkinnedVertex3D
{
	Vector4 Position;
	LinearColor Color;
	Vector2 UV;
	UINT32 BoneIndices[4] = { 0, 0, 0, 0 }; // 정점에 영향을 주는 본 4개 인덱스
	float BoneWeights[4] = { 0.f, 0.f, 0.f, 0.f };
};

}
}