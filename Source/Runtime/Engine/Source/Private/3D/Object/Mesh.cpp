#include "Precompiled.h"
using namespace GER::DDD;

void Mesh::CalculateBounds()
{
	_SphereBound = Sphere(_Vertices);
	_BoxBound = Box(_Vertices);
}

void Mesh::UploadToGPU(OpenGLDevice& InDevice)
{
	if (_IsUploadedToGPU)
	{
		return;
	}

	std::vector<Vertex3D> gpuVertices;
	gpuVertices.reserve(_Vertices.size());

	for (size_t i = 0; i < _Vertices.size(); ++i)
	{
		const Vector3& pos = _Vertices[i];
		LinearColor color = HasColor() ? _Colors[i] : LinearColor::White;
		Vector2 uv = HasUV() ? _UVs[i] : Vector2::Zero;
		Vector3 normal = HasNormal() ? _Normals[i] : Vector3::UnitZ;
		Vector3 tangent = HasTangent() ? _Tangents[i] : Vector3::UnitX;

		Vertex3D v(Vector4(pos.X, pos.Y, pos.Z, 1.0f), color, uv, normal);
		v.Tangent = tangent;
		gpuVertices.push_back(v);
	}

	std::vector<UINT32> gpuIndices;
	gpuIndices.reserve(_Indices.size());

	for (size_t idx : _Indices)
	{
		gpuIndices.push_back(static_cast<UINT32>(idx));
	}

	_GPUHandle = InDevice.CreateMesh(gpuVertices.data(), gpuVertices.size() * sizeof(Vertex3D), gpuIndices.data(), (UINT32)gpuIndices.size());

	_IsUploadedToGPU = true;
}
