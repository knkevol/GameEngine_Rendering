#pragma once

namespace GER
{
namespace DDD
{

struct Weight
{
	std::vector<uint8_t> BoneIndices;
	std::vector<float> Values;
};

class SKMesh : public Mesh
{
public:

	virtual bool IsSKMesh() const override { return true; }

	FORCEINLINE bool IsSkinnedMesh() const { return _MeshType == MeshType::Skinned; }
	FORCEINLINE bool HasBone(const std::string& InBoneName) const { return _Bones.find(InBoneName) != _Bones.end(); }

	std::vector<Weight>& GetWeights() { return _Weights; }
	const std::vector<Weight>& GetWeights() const { return _Weights; }

	std::vector<BYTE>& GetConnectedBones() { return _ConnectedBones; }
	const std::vector<BYTE>& GetConnectedBones() const { return _ConnectedBones; }

	Bone& GetBone(const std::string& InBoneName) { return _Bones.at(InBoneName); }
	const Bone& GetBone(const std::string& InBoneName) const { return _Bones.at(InBoneName); }

	std::unordered_map<std::string, Bone>& GetBones() { return _Bones; }
	const std::unordered_map<std::string, Bone>& GetBones() const { return _Bones; }

	const Transform& GetBindPose(const std::string& InBoneName) const { return _Bones.at(InBoneName).GetBindPose(); }

	void BuildBoneIndex(const std::vector<std::string>& InBoneOrder)
	{
		_BoneNames = InBoneOrder;
		_BoneNameToIndex.clear();
		uint8_t idx = 0;
		for (const auto& name : InBoneOrder)
			_BoneNameToIndex[name] = idx++;
	}

	FORCEINLINE bool HasBoneIndex(const std::string& name) const { return _BoneNameToIndex.count(name) > 0; }
	FORCEINLINE uint8_t GetBoneIndex(const std::string& name) const { return _BoneNameToIndex.at(name); }
	FORCEINLINE Bone& GetBoneByIndex(uint8_t idx) { return _Bones.at(_BoneNames[idx]); }
	FORCEINLINE const Bone& GetBoneByIndex(uint8_t idx) const { return _Bones.at(_BoneNames[idx]); }
	FORCEINLINE const Transform& GetBindPoseByIndex(uint8_t idx) const { return _Bones.at(_BoneNames[idx]).GetBindPose(); }

protected:
	std::vector<BYTE> _ConnectedBones;
	std::vector<Weight> _Weights;
	std::unordered_map<std::string, Bone> _Bones;

	std::vector<std::string> _BoneNames;
	std::unordered_map<std::string, uint8_t> _BoneNameToIndex;
};

}
}