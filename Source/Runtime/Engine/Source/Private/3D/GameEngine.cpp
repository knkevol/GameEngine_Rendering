#include "Precompiled.h"
using namespace GER::DDD;

// GameObject Factories
PGameObjectFactory GameEngine::PFactory;
ActorFactory GameEngine::ActorFactory;
CharacterFactory GameEngine::CharacterFactory;

// Meshes
const std::size_t GameEngine::ArrowMesh = std::hash<std::string>()("SM_Arrow");
const std::size_t GameEngine::CharacterMesh = std::hash<std::string>()("SK_Character");
const std::size_t GameEngine::CubeMesh = std::hash<std::string>()("M_Cube");

// Textures
const std::size_t GameEngine::BaseTexture = std::hash<std::string>()("T_Base");
const std::size_t GameEngine::CharacterTexture = std::hash<std::string>()("T_Character");

// Animation
const std::size_t GameEngine::PistolReloadAnimation = std::hash<std::string>()("A_PistolReload");

void GameEngine::OnScreenResize(const ScreenPoint& InScreenSize)
{
	_ScreenSize = InScreenSize;
	_MainCamera.SetViewportSize(_ScreenSize);
}

bool GameEngine::Init()
{
	if (_IsInitialized)
	{
		return true;
	}

	// Check Things

	if (_ScreenSize.HasZero())
	{
		return false;
	}

	if (!_InputManager.IsInputReady())
	{
		return false;
	}

	if (!LoadResources())
	{
		return false;
	}

	InitLogChannels();
	RegisterGameObjectFactories();
	LoadAsset();
	//LoadCube(); // Test

	_IsInitialized = true;
	return _IsInitialized;
}

// Logging
PLogs& GameEngine::GetTargetLog(const std::string& LogHeader)
{
	auto MapValue = _LogIndexMap.find(LogHeader);

	if (MapValue != _LogIndexMap.end())
	{
		return _EngineLogs[MapValue->second];
	}

	int NewIndex = NewLogChannel(LogHeader);

	return _EngineLogs[NewIndex];
}

void GameEngine::InitLogChannels()
{
	PLogs EngineLog;
	EngineLog.SetLogHeader("EngineLOG");
	_EngineLogs.push_back(EngineLog);
	_LogIndexMap.insert(std::make_pair("EngineLOG", 0));

	NewLogChannel("InputLOG");
}

int GameEngine::NewLogChannel(const std::string& NewLogHeader)
{
	PLogs NewLogs;
	NewLogs.SetLogHeader(NewLogHeader);
	_EngineLogs.push_back(NewLogs);

	int NewIndex = static_cast<int>(_EngineLogs.size()) - 1;
	_LogIndexMap.insert(std::make_pair(NewLogHeader, NewIndex));

	return NewIndex;
}
// ~ Logging

Mesh& GameEngine::CreateMesh(const std::size_t& InKey)
{
	auto meshPtr = std::make_unique<Mesh>();
	_Meshes.insert({ InKey, std::move(meshPtr) });
	return *_Meshes.at(InKey).get();
}

SKMesh& GameEngine::CreateSKMesh(const std::size_t& InKey)
{
	auto meshPtr = std::make_unique<SKMesh>();
	_Meshes.insert({ InKey, std::move(meshPtr) });
	return static_cast<SKMesh&>(*_Meshes.at(InKey).get());
}

Texture& GameEngine::CreateTexture(const std::size_t& InKey)
{
	auto texturePtr = std::make_unique<Texture>();
	_Textures.insert({ InKey, std::move(texturePtr) });
	return *_Textures.at(InKey).get();
}

Animation& GameEngine::CreateAnimation(const std::size_t& InKey)
{
	auto animPtr = std::make_unique<Animation>();
	_Anims.insert({ InKey, std::move(animPtr) });
	return *_Anims.at(InKey).get();
}

GameObject& GameEngine::CreateNewGameObject(const std::string& InName)
{
	std::size_t inHash = std::hash<std::string>()(InName);
	const auto it = std::lower_bound(SceneBegin(), SceneEnd(), inHash, GameObjectCompare());

	auto newGameObject = std::make_unique<GameObject>(InName);
	if (it != _Scene.end())
	{
		std::size_t targetHash = (*it)->GetHash();
		if (targetHash == inHash)
		{
			// 중복된 키 발생. 무시.
			assert(false);
			return GameObject::Invalid;
		}
		else if (targetHash < inHash)
		{
			_Scene.insert(it + 1, std::move(newGameObject));
		}
		else
		{
			_Scene.insert(it, std::move(newGameObject));
		}
	}
	else
	{
		_Scene.push_back(std::move(newGameObject));
	}

	return GetGameObject(InName);
}

GameObject& GameEngine::GetGameObject(const std::string& InName)
{
	std::size_t targetHash = std::hash<std::string>()(InName);
	const auto it = std::lower_bound(SceneBegin(), SceneEnd(), targetHash, GameObjectCompare());

	return (it != _Scene.end()) ? *(*it).get() : GameObject::Invalid;
}

void GameEngine::RegisterGameObjectFactories()
{
	_Factory.get()->RegisterFactory("PObject", &PFactory);
	_Factory.get()->RegisterFactory("Actor", &ActorFactory);
	_Factory.get()->RegisterFactory("Character", &CharacterFactory);
}

GameObject& GameEngine::CreateNewGameObjectOfClass(const std::string& InName, const std::string& InTypeName)
{
	GameObject* PotentialNewGameObject = _Factory.get()->CreateIfRegistered(InName, InTypeName);
	assert(PotentialNewGameObject);
	// PGameObject* Test = static_cast<PGameObject*>(newGameObject.get());

	std::size_t inHash = std::hash<std::string>()(InName);
	const auto it = std::lower_bound(SceneBegin(), SceneEnd(), inHash, GameObjectCompare());
	auto newGameObject = std::unique_ptr<GameObject>(PotentialNewGameObject);

	if (it != _Scene.end())
	{
		std::size_t targetHash = (*it)->GetHash();
		if (targetHash == inHash)
		{
			// 중복된 키 발생. 무시.
			assert(false);
			return GameObject::Invalid;
		}
		else if (targetHash < inHash)
		{
			_Scene.insert(it + 1, std::move(newGameObject));
		}
		else
		{
			_Scene.insert(it, std::move(newGameObject));
		}
	}
	else
	{
		_Scene.push_back(std::move(newGameObject));
	}

	return GetGameObject(InName);
}

void GameEngine::LoadCube()
{
	constexpr Vector3 CubeSize(0.5f, 0.5f, 0.5f);
	Mesh& SimpleCubeMesh = CreateMesh(GameEngine::CubeMesh);
	auto& v = SimpleCubeMesh.GetVertices();
	auto& i = SimpleCubeMesh.GetIndices();
	auto& uv = SimpleCubeMesh.GetUVs();

	int PointSize = cubeMeshPositions.size();

	for (int p = 0; p < PointSize; ++p)
	{
		v.push_back(cubeMeshPositions[p]);
		uv.push_back(cubeMeshUVs[p]);
	}

	int IndexSize = cubeMeshIndice.size();

	for (int vi = 0; vi < IndexSize; ++vi)
	{
		i.push_back(cubeMeshIndice[vi]);
	}

	SimpleCubeMesh.SetMeshType(MeshType::Normal);
	SimpleCubeMesh.CalculateBounds();

	Texture& TextureBase = CreateTexture(GameEngine::BaseTexture);
	TextureBase.LoadFromPath("Asset/Character/Quinn.fbm/Quinn_");

	OutputDebugString("LoadCube Complete");
}

void GameEngine::LoadAsset()
{
	FBXLoader& TestLoader = FBXLoader::get();

	SKMesh& CharacterMesh = CreateSKMesh(GameEngine::CharacterMesh);
	auto& v = CharacterMesh.GetVertices();
	auto& i = CharacterMesh.GetIndices();
	auto& uv = CharacterMesh.GetUVs();

	SkeletonInfo CharacterSkeleton;
	std::vector<std::vector<std::pair<std::string, float>>> WeightInfo;

	std::string TexturePath;
	TestLoader.LoadCharacterFBX("Quinn", OUT v, OUT i, OUT uv, OUT TexturePath, OUT CharacterSkeleton, OUT WeightInfo);

	Texture& CharacterTexture = CreateTexture(GameEngine::CharacterTexture);
	CharacterTexture.LoadFromPath(TexturePath);

	CharacterMesh.SetMeshType(MeshType::Normal);
	CharacterMesh.CalculateBounds();

	// Rigging 
	auto& cb = CharacterMesh.GetConnectedBones();
	auto& w = CharacterMesh.GetWeights();
	auto& bones = CharacterMesh.GetBones();
	
	std::vector<std::string> boneOrder;

	BuildSkeletonBones(CharacterMesh, CharacterSkeleton, OUT boneOrder);
	
	CharacterMesh.BuildBoneIndex(boneOrder);

	// Connecting Bones
	for (int i = 0; i < CharacterSkeleton.BoneInfoVector.size(); ++i)
	{
		const auto& boneInfo = CharacterSkeleton.BoneInfoVector[i];
		if (boneInfo.ParentIndex < 0)
		{
			continue;
		}

		Bone& child = CharacterMesh.GetBone(std::string(boneInfo.Name) + "Bone");
		Bone& parent = CharacterMesh.GetBone(std::string(CharacterSkeleton.BoneInfoVector[boneInfo.ParentIndex].Name) + "Bone");

		child.SetParent(parent);
	}

	CharacterMesh.PrecomputeInverseBindPoses();
	CharacterMesh.UpdateSkinMatrices();

	// Moving Weight Information
	cb.resize(v.size(), 0);
	w.resize(v.size());
	for (auto idx = 0; idx < WeightInfo.size(); ++idx)
	{
		for (const std::pair<std::string, float>& info : WeightInfo[idx])
		{
			if (CharacterMesh.HasBoneIndex(info.first))
			{
				cb[idx]++;
				w[idx].BoneIndices.push_back(CharacterMesh.GetBoneIndex(info.first));
				w[idx].Values.push_back(info.second);
			}
		}
	}

	// Animation setting
	Animation& PistolReloadAnimation = CreateAnimation(GameEngine::PistolReloadAnimation);
	std::vector<std::string>& PistolReloadBoneNames = PistolReloadAnimation.GetBoneNames();;
	std::vector<bool>& PistolReloadBoneUsage = PistolReloadAnimation.GetBoneUsage();
	std::vector<std::vector<Vector3>>& PistolReloadFrameTranslations = PistolReloadAnimation.GetFrameTranslantions();
	std::vector<std::vector<Quaternion>>& PistolReloadFrameQuaternions = PistolReloadAnimation.GetFrameQuaternions();

	PistolReloadBoneNames.resize(boneOrder.size());
	PistolReloadBoneUsage.resize(boneOrder.size(), false);
	PistolReloadFrameTranslations.resize(boneOrder.size(), std::vector<Vector3>());
	PistolReloadFrameQuaternions.resize(boneOrder.size(), std::vector<Quaternion>());
	// Animation
	TestLoader.LoadAnimationWithName("PistolReload", boneOrder, OUT PistolReloadBoneNames, OUT PistolReloadBoneUsage, OUT PistolReloadFrameTranslations, OUT PistolReloadFrameQuaternions);

	// Check Loaded Animation & SKMesh's Skeleton Order
	for (auto boneIdx = 1; boneIdx < boneOrder.size(); boneIdx++)
	{
		if (PistolReloadBoneUsage[boneIdx])
		{
			assert(boneOrder[boneIdx].compare(PistolReloadBoneNames[boneIdx]) == 0);

		}
	}

	Mesh& arrow = CreateMesh(GameEngine::ArrowMesh);
	arrow.GetVertices().resize(arrowPositions.size());
	arrow.GetIndices().resize(arrowIndice.size());
	arrow.GetColors().resize(arrowPositions.size());
	std::copy(arrowPositions.begin(), arrowPositions.end(), arrow.GetVertices().begin());
	std::copy(arrowIndice.begin(), arrowIndice.end(), arrow.GetIndices().begin());
	std::fill(arrow.GetColors().begin(), arrow.GetColors().end(), LinearColor::Gray);

	OutputDebugString("LoadAsset Complete");
	return;
}

bool GameEngine::LoadResources()
{
	return true;
}

void GameEngine::BuildSkeletonBones(SKMesh& InMesh, SkeletonInfo& InSkeleton, std::vector<std::string>& OutBoneOrder)
{
	auto& bones = InMesh.GetBones();

	for (const BoneInfo& boneInfo : InSkeleton.BoneInfoVector)
	{
		const std::string boneKey = std::string(boneInfo.Name) + "Bone";
		bones.emplace(boneKey, Bone(boneKey, Transform(boneInfo.Transform, Quaternion(boneInfo.Quat))));

		OutBoneOrder.push_back(boneKey);
	}
}