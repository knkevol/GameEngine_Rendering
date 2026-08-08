#include "Precompiled.h"
using namespace GER::DDD;

void SKMesh::UploadToGPU(OpenGLDevice& InDevice)
{
	if (_IsUploadedToGPU)
	{
		return;
	}

	BuildFixedBoneWeight();

	// 여러 정점데이터를 하나의 구조체에 묶어서 저장(인터리빙)
	std::vector<SkinnedVertex3D> gpuVertices;
	gpuVertices.reserve(_Vertices.size());

	for (size_t i = 0; i < _Vertices.size(); ++i)
	{
		SkinnedVertex3D vert;
		vert.Position = Vector4(_Vertices[i].X, _Vertices[i].Y, _Vertices[i].Z, 1.0f);
		vert.Color = HasColor() ? _Colors[i] : LinearColor::White;
		vert.UV = HasUV() ? _UVs[i] : Vector2::Zero;
		vert.Normal = HasNormal() ? _Normals[i] : Vector3::UnitZ;

		const BoneWeight4& fw = _FixedWeights[i];
		for (int k = 0; k < 4; ++k)
		{
			vert.BoneIndices[k] = fw.Indices[k];
			vert.BoneWeights[k] = fw.Weight[k];
		}

		gpuVertices.push_back(vert);
	}

	// Idx도 UINT32로 gpu에 맞춰 복사
	std::vector<UINT32> gpuIndices;
	gpuIndices.reserve(_Indices.size());
	for (size_t idx : _Indices)
	{
		gpuIndices.push_back(static_cast<UINT32>(idx));
	}

	// GPU Upload
	_GPUHandle = InDevice.CreateSkinnedMesh(gpuVertices.data(), gpuVertices.size() * sizeof(SkinnedVertex3D), gpuIndices.data(), (UINT32)gpuIndices.size());

	_IsUploadedToGPU = true;
}

void SKMesh::BuildFixedBoneWeight()
{
	size_t vertexCount = _Vertices.size();
	_FixedWeights.resize(vertexCount);

	for (size_t vi = 0; vi < vertexCount; ++vi)
	{
		const Weight& w = _Weights[vi];
		size_t count = w.BoneIndices.size();

		std::vector<size_t> order(count);

		// 가중치 큰 순으로 정렬
		for (size_t k = 0; k < count; ++k)
		{
			order[k] = k;
		}
		std::sort(order.begin(), order.end(), [&](size_t a, size_t b) {return w.Values[a] > w.Values[b]; });

		BoneWeight4 fixed;
		size_t take = (count < 4) ? count : 4;
		float sum = 0.f;

		for (size_t k = 0; k < take; ++k)
		{
			size_t srcIdx = order[k];
			fixed.Indices[k] = static_cast<UINT32>(w.BoneIndices[srcIdx]);
			fixed.Weight[k] = w.Values[srcIdx];
			sum += fixed.Weight[k];
		}

		// sum값 정규화
		if (sum > 0.0001f)
		{
			for (int k = 0; k < 4; ++k)
			{
				fixed.Weight[k] /= sum;
			}
		}

		_FixedWeights[vi] = fixed;

		
	}

}
