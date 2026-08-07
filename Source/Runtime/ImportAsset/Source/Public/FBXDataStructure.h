#pragma once

struct BoneInfo
{
	BoneInfo(FbxNode* InNode, int inIndex, int inParentIndex, const char* inJointName)
		:
		Index(inIndex),
		ParentIndex(inParentIndex),
		Name(inJointName)
	{}

	const char* Name;
	int Index;
	int ParentIndex;
	Vector3 Transform;
	Quaternion Quat;
};

struct SkeletonInfo
{
	std::vector<BoneInfo> BoneInfoVector;

	BoneInfo& GetTargetBoneInfo(const char* JointName)
	{
		for (int i = 0; i < BoneInfoVector.size(); ++i)
		{
			BoneInfo& TargetBone = BoneInfoVector[i];
			if (strcmp(JointName, TargetBone.Name) == 0)
			{

				return TargetBone;
			}
		}

		assert(false);
		return BoneInfoVector[0];
	}
};

struct AnimationInfo
{
	AnimationInfo(std::string AnimationName)
		: AnimationName(AnimationName)
	{}

	const std::string AnimationName;

	std::vector<std::string> BoneNames;
	std::vector<std::vector<Vector3>> FrameTranslations;
	std::vector<std::vector<Rotator>> FrameRotations;
};