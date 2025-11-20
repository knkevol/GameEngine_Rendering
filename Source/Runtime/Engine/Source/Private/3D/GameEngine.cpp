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

// Bones
const std::string GameEngine::rootBone("rootBone");
const std::string GameEngine::center_of_massBone("center_of_massBone");
const std::string GameEngine::ik_foot_rootBone("ik_foot_rootBone");
const std::string GameEngine::ik_foot_lBone("ik_foot_lBone");
const std::string GameEngine::ik_foot_rBone("ik_foot_rBone");
const std::string GameEngine::ik_hand_rootBone("ik_hand_rootBone");
const std::string GameEngine::ik_hand_gunBone("ik_hand_gunBone");
const std::string GameEngine::ik_hand_lBone("ik_hand_lBone");
const std::string GameEngine::ik_hand_rBone("ik_hand_rBone");
const std::string GameEngine::interactionBone("interactionBone");
const std::string GameEngine::pelvisBone("pelvisBone");
const std::string GameEngine::spine_01Bone("spine_01Bone");
const std::string GameEngine::spine_02Bone("spine_02Bone");
const std::string GameEngine::spine_03Bone("spine_03Bone");
const std::string GameEngine::spine_04Bone("spine_04Bone");
const std::string GameEngine::spine_05Bone("spine_05Bone");
const std::string GameEngine::clavicle_lBone("clavicle_lBone");
const std::string GameEngine::upperarm_lBone("upperarm_lBone");
const std::string GameEngine::lowerarm_lBone("lowerarm_lBone");
const std::string GameEngine::hand_lBone("hand_lBone");
const std::string GameEngine::index_metacarpal_lBone("index_metacarpal_lBone");
const std::string GameEngine::index_01_lBone("index_01_lBone");
const std::string GameEngine::index_02_lBone("index_02_lBone");
const std::string GameEngine::index_03_lBone("index_03_lBone");
const std::string GameEngine::middle_metacarpal_lBone("middle_metacarpal_lBone");
const std::string GameEngine::middle_01_lBone("middle_01_lBone");
const std::string GameEngine::middle_02_lBone("middle_02_lBone");
const std::string GameEngine::middle_03_lBone("middle_03_lBone");
const std::string GameEngine::pinky_metacarpal_lBone("pinky_metacarpal_lBone");
const std::string GameEngine::pinky_01_lBone("pinky_01_lBone");
const std::string GameEngine::pinky_02_lBone("pinky_02_lBone");
const std::string GameEngine::pinky_03_lBone("pinky_03_lBone");
const std::string GameEngine::ring_metacarpal_lBone("ring_metacarpal_lBone");
const std::string GameEngine::ring_01_lBone("ring_01_lBone");
const std::string GameEngine::ring_02_lBone("ring_02_lBone");
const std::string GameEngine::ring_03_lBone("ring_03_lBone");
const std::string GameEngine::thumb_01_lBone("thumb_01_lBone");
const std::string GameEngine::thumb_02_lBone("thumb_02_lBone");
const std::string GameEngine::thumb_03_lBone("thumb_03_lBone");
const std::string GameEngine::lowerarm_twist_01_lBone("lowerarm_twist_01_lBone");
const std::string GameEngine::lowerarm_twist_02_lBone("lowerarm_twist_02_lBone");
const std::string GameEngine::upperarm_twist_01_lBone("upperarm_twist_01_lBone");
const std::string GameEngine::upperarm_twist_02_lBone("upperarm_twist_02_lBone");
const std::string GameEngine::clavicle_rBone("clavicle_rBone");
const std::string GameEngine::upperarm_rBone("upperarm_rBone");
const std::string GameEngine::lowerarm_rBone("lowerarm_rBone");
const std::string GameEngine::hand_rBone("hand_rBone");
const std::string GameEngine::index_metacarpal_rBone("index_metacarpal_rBone");
const std::string GameEngine::index_01_rBone("index_01_rBone");
const std::string GameEngine::index_02_rBone("index_02_rBone");
const std::string GameEngine::index_03_rBone("index_03_rBone");
const std::string GameEngine::middle_metacarpal_rBone("middle_metacarpal_rBone");
const std::string GameEngine::middle_01_rBone("middle_01_rBone");
const std::string GameEngine::middle_02_rBone("middle_02_rBone");
const std::string GameEngine::middle_03_rBone("middle_03_rBone");
const std::string GameEngine::pinky_metacarpal_rBone("pinky_metacarpal_rBone");
const std::string GameEngine::pinky_01_rBone("pinky_01_rBone");
const std::string GameEngine::pinky_02_rBone("pinky_02_rBone");
const std::string GameEngine::pinky_03_rBone("pinky_03_rBone");
const std::string GameEngine::ring_metacarpal_rBone("ring_metacarpal_rBone");
const std::string GameEngine::ring_01_rBone("ring_01_rBone");
const std::string GameEngine::ring_02_rBone("ring_02_rBone");
const std::string GameEngine::ring_03_rBone("ring_03_rBone");
const std::string GameEngine::thumb_01_rBone("thumb_01_rBone");
const std::string GameEngine::thumb_02_rBone("thumb_02_rBone");
const std::string GameEngine::thumb_03_rBone("thumb_03_rBone");
const std::string GameEngine::lowerarm_twist_01_rBone("lowerarm_twist_01_rBone");
const std::string GameEngine::lowerarm_twist_02_rBone("lowerarm_twist_02_rBone");
const std::string GameEngine::upperarm_twist_01_rBone("upperarm_twist_01_rBone");
const std::string GameEngine::upperarm_twist_02_rBone("upperarm_twist_02_rBone");
const std::string GameEngine::neck_01Bone("neck_01Bone");
const std::string GameEngine::neck_02Bone("neck_02Bone");
const std::string GameEngine::headBone("headBone");
const std::string GameEngine::thigh_lBone("thigh_lBone");
const std::string GameEngine::calf_lBone("calf_lBone");
const std::string GameEngine::calf_twist_01_lBone("calf_twist_01_lBone");
const std::string GameEngine::calf_twist_02_lBone("calf_twist_02_lBone");
const std::string GameEngine::foot_lBone("foot_lBone");
const std::string GameEngine::ball_lBone("ball_lBone");
const std::string GameEngine::thigh_twist_01_lBone("thigh_twist_01_lBone");
const std::string GameEngine::thigh_twist_02_lBone("thigh_twist_02_lBone");
const std::string GameEngine::thigh_rBone("thigh_rBone");
const std::string GameEngine::calf_rBone("calf_rBone");
const std::string GameEngine::calf_twist_01_rBone("calf_twist_01_rBone");
const std::string GameEngine::calf_twist_02_rBone("calf_twist_02_rBone");
const std::string GameEngine::foot_rBone("foot_rBone");
const std::string GameEngine::ball_rBone("ball_rBone");
const std::string GameEngine::thigh_twist_01_rBone("thigh_twist_01_rBone");
const std::string GameEngine::thigh_twist_02_rBone("thigh_twist_02_rBone");

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

	int PointSize = cubeMeshPositions.size();

	for (int p = 0; p < PointSize; ++p)
	{
		v.push_back(cubeMeshPositions[p]);
	}

	int IndexSize = cubeMeshIndice.size();

	for (int vi = 0; vi < IndexSize; ++vi)
	{
		i.push_back(cubeMeshIndice[vi]);
	}

	SimpleCubeMesh.SetMeshType(MeshType::Normal);
	SimpleCubeMesh.CalculateBounds();

	Texture& TextureBase = CreateTexture(GameEngine::BaseTexture);

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

	bones = {
		{ GameEngine::rootBone, Bone(GameEngine::rootBone, Transform(CharacterSkeleton.GetTargetBoneInfo("root").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("root").Quat)))},
		{ GameEngine::center_of_massBone, Bone(GameEngine::center_of_massBone, Transform(CharacterSkeleton.GetTargetBoneInfo("center_of_mass").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("center_of_mass").Quat)))},
		{ GameEngine::ik_foot_rootBone, Bone(GameEngine::ik_foot_rootBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ik_foot_root").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ik_foot_root").Quat)))},
		{ GameEngine::ik_foot_lBone, Bone(GameEngine::ik_foot_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ik_foot_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ik_foot_l").Quat)))},
		{ GameEngine::ik_foot_rBone, Bone(GameEngine::ik_foot_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ik_foot_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ik_foot_r").Quat)))},
		{ GameEngine::ik_hand_rootBone, Bone(GameEngine::ik_hand_rootBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ik_hand_root").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ik_hand_root").Quat)))},
		{ GameEngine::ik_hand_gunBone, Bone(GameEngine::ik_hand_gunBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ik_hand_gun").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ik_hand_gun").Quat)))},
		{ GameEngine::ik_hand_lBone, Bone(GameEngine::ik_hand_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ik_hand_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ik_hand_l").Quat)))},
		{ GameEngine::ik_hand_rBone, Bone(GameEngine::ik_hand_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ik_hand_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ik_hand_r").Quat)))},
		{ GameEngine::interactionBone, Bone(GameEngine::interactionBone, Transform(CharacterSkeleton.GetTargetBoneInfo("interaction").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("interaction").Quat)))},
		{ GameEngine::pelvisBone, Bone(GameEngine::pelvisBone, Transform(CharacterSkeleton.GetTargetBoneInfo("pelvis").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("pelvis").Quat)))},
		{ GameEngine::spine_01Bone, Bone(GameEngine::spine_01Bone, Transform(CharacterSkeleton.GetTargetBoneInfo("spine_01").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("spine_01").Quat)))},
		{ GameEngine::spine_02Bone, Bone(GameEngine::spine_02Bone, Transform(CharacterSkeleton.GetTargetBoneInfo("spine_02").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("spine_02").Quat)))},
		{ GameEngine::spine_03Bone, Bone(GameEngine::spine_03Bone, Transform(CharacterSkeleton.GetTargetBoneInfo("spine_03").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("spine_03").Quat)))},
		{ GameEngine::spine_04Bone, Bone(GameEngine::spine_04Bone, Transform(CharacterSkeleton.GetTargetBoneInfo("spine_04").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("spine_04").Quat)))},
		{ GameEngine::spine_05Bone, Bone(GameEngine::spine_05Bone, Transform(CharacterSkeleton.GetTargetBoneInfo("spine_05").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("spine_05").Quat)))},
		{ GameEngine::clavicle_lBone, Bone(GameEngine::clavicle_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("clavicle_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("clavicle_l").Quat)))},
		{ GameEngine::upperarm_lBone, Bone(GameEngine::upperarm_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("upperarm_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("upperarm_l").Quat)))},
		{ GameEngine::lowerarm_lBone, Bone(GameEngine::lowerarm_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("lowerarm_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("lowerarm_l").Quat)))},
		{ GameEngine::hand_lBone, Bone(GameEngine::hand_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("hand_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("hand_l").Quat)))},
		{ GameEngine::index_metacarpal_lBone, Bone(GameEngine::index_metacarpal_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("index_metacarpal_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("index_metacarpal_l").Quat)))},
		{ GameEngine::index_01_lBone, Bone(GameEngine::index_01_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("index_01_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("index_01_lBone").Quat)))},
		{ GameEngine::index_02_lBone, Bone(GameEngine::index_02_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("index_02_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("index_02_lBone").Quat)))},
		{ GameEngine::index_03_lBone, Bone(GameEngine::index_03_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("index_03_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("index_03_lBone").Quat)))},
		{ GameEngine::middle_metacarpal_lBone, Bone(GameEngine::middle_metacarpal_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("middle_metacarpal_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("middle_metacarpal_l").Quat)))},
		{ GameEngine::middle_01_lBone, Bone(GameEngine::middle_01_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("middle_01_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("middle_01_lBone").Quat)))},
		{ GameEngine::middle_02_lBone, Bone(GameEngine::middle_02_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("middle_02_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("middle_02_lBone").Quat)))},
		{ GameEngine::middle_03_lBone, Bone(GameEngine::middle_03_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("middle_03_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("middle_03_lBone").Quat)))},
		{ GameEngine::pinky_metacarpal_lBone, Bone(GameEngine::pinky_metacarpal_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("pinky_metacarpal_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("pinky_metacarpal_l").Quat)))},
		{ GameEngine::pinky_01_lBone, Bone(GameEngine::pinky_01_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("pinky_01_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("pinky_01_lBone").Quat)))},
		{ GameEngine::pinky_02_lBone, Bone(GameEngine::pinky_02_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("pinky_02_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("pinky_02_lBone").Quat)))},
		{ GameEngine::pinky_03_lBone, Bone(GameEngine::pinky_03_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("pinky_03_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("pinky_03_lBone").Quat)))},
		{ GameEngine::ring_metacarpal_lBone, Bone(GameEngine::ring_metacarpal_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ring_metacarpal_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ring_metacarpal_l").Quat)))},
		{ GameEngine::ring_01_lBone, Bone(GameEngine::ring_01_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ring_01_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ring_01_lBone").Quat)))},
		{ GameEngine::ring_02_lBone, Bone(GameEngine::ring_02_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ring_02_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ring_02_lBone").Quat)))},
		{ GameEngine::ring_03_lBone, Bone(GameEngine::ring_03_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ring_03_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ring_03_lBone").Quat)))},
		{ GameEngine::thumb_01_lBone, Bone(GameEngine::thumb_01_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thumb_01_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thumb_01_lBone").Quat)))},
		{ GameEngine::thumb_02_lBone, Bone(GameEngine::thumb_02_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thumb_02_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thumb_02_lBone").Quat)))},
		{ GameEngine::thumb_03_lBone, Bone(GameEngine::thumb_03_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thumb_03_lBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thumb_03_lBone").Quat)))},
		{ GameEngine::lowerarm_twist_01_lBone, Bone(GameEngine::lowerarm_twist_01_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("lowerarm_twist_01_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("lowerarm_twist_01_l").Quat)))},
		{ GameEngine::lowerarm_twist_02_lBone, Bone(GameEngine::lowerarm_twist_02_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("lowerarm_twist_02_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("lowerarm_twist_02_l").Quat)))},
		{ GameEngine::upperarm_twist_01_lBone, Bone(GameEngine::upperarm_twist_01_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("upperarm_twist_01_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("upperarm_twist_01_l").Quat)))},
		{ GameEngine::upperarm_twist_02_lBone, Bone(GameEngine::upperarm_twist_02_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("upperarm_twist_02_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("upperarm_twist_02_l").Quat)))},
		{ GameEngine::clavicle_rBone, Bone(GameEngine::clavicle_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("clavicle_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("clavicle_r").Quat)))},
		{ GameEngine::upperarm_rBone, Bone(GameEngine::upperarm_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("upperarm_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("upperarm_r").Quat)))},
		{ GameEngine::lowerarm_rBone, Bone(GameEngine::lowerarm_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("lowerarm_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("lowerarm_r").Quat)))},
		{ GameEngine::hand_rBone, Bone(GameEngine::hand_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("hand_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("hand_r").Quat)))},
		{ GameEngine::index_metacarpal_rBone, Bone(GameEngine::index_metacarpal_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("index_metacarpal_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("index_metacarpal_r").Quat)))},
		{ GameEngine::index_01_rBone, Bone(GameEngine::index_01_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("index_01_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("index_01_r").Quat)))},
		{ GameEngine::index_02_rBone, Bone(GameEngine::index_02_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("index_02_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("index_02_r").Quat)))},
		{ GameEngine::index_03_rBone, Bone(GameEngine::index_03_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("index_03_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("index_03_r").Quat)))},
		{ GameEngine::middle_metacarpal_rBone, Bone(GameEngine::middle_metacarpal_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("middle_metacarpal_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("middle_metacarpal_r").Quat)))},
		{ GameEngine::middle_01_rBone, Bone(GameEngine::middle_01_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("middle_01_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("middle_01_r").Quat)))},
		{ GameEngine::middle_02_rBone, Bone(GameEngine::middle_02_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("middle_02_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("middle_02_r").Quat)))},
		{ GameEngine::middle_03_rBone, Bone(GameEngine::middle_03_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("middle_03_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("middle_03_r").Quat)))},
		{ GameEngine::pinky_metacarpal_rBone, Bone(GameEngine::pinky_metacarpal_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("pinky_metacarpal_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("pinky_metacarpal_r").Quat)))},
		{ GameEngine::pinky_01_rBone, Bone(GameEngine::pinky_01_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("pinky_01_rBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("pinky_01_rBone").Quat)))},
		{ GameEngine::pinky_02_rBone, Bone(GameEngine::pinky_02_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("pinky_02_rBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("pinky_02_rBone").Quat)))},
		{ GameEngine::pinky_03_rBone, Bone(GameEngine::pinky_03_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("pinky_03_rBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("pinky_03_rBone").Quat)))},
		{ GameEngine::ring_metacarpal_rBone, Bone(GameEngine::ring_metacarpal_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ring_metacarpal_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ring_metacarpal_r").Quat)))},
		{ GameEngine::ring_01_rBone, Bone(GameEngine::ring_01_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ring_01_rBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ring_01_rBone").Quat)))},
		{ GameEngine::ring_02_rBone, Bone(GameEngine::ring_02_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ring_02_rBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ring_02_rBone").Quat)))},
		{ GameEngine::ring_03_rBone, Bone(GameEngine::ring_03_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ring_03_rBone").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ring_03_rBone").Quat)))},
		{ GameEngine::thumb_01_rBone, Bone(GameEngine::thumb_01_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thumb_01_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thumb_01_r").Quat)))},
		{ GameEngine::thumb_02_rBone, Bone(GameEngine::thumb_02_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thumb_02_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thumb_02_r").Quat)))},
		{ GameEngine::thumb_03_rBone, Bone(GameEngine::thumb_03_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thumb_03_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thumb_03_r").Quat)))},
		{ GameEngine::lowerarm_twist_01_rBone, Bone(GameEngine::lowerarm_twist_01_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("lowerarm_twist_01_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("lowerarm_twist_01_r").Quat)))},
		{ GameEngine::lowerarm_twist_02_rBone, Bone(GameEngine::lowerarm_twist_02_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("lowerarm_twist_02_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("lowerarm_twist_02_r").Quat)))},
		{ GameEngine::upperarm_twist_01_rBone, Bone(GameEngine::upperarm_twist_01_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("upperarm_twist_01_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("upperarm_twist_01_r").Quat)))},
		{ GameEngine::upperarm_twist_02_rBone, Bone(GameEngine::upperarm_twist_02_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("upperarm_twist_02_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("upperarm_twist_02_r").Quat)))},
		{ GameEngine::neck_01Bone, Bone(GameEngine::neck_01Bone, Transform(CharacterSkeleton.GetTargetBoneInfo("neck_01").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("neck_01").Quat)))},
		{ GameEngine::neck_02Bone, Bone(GameEngine::neck_02Bone, Transform(CharacterSkeleton.GetTargetBoneInfo("neck_02").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("neck_02").Quat)))},
		{ GameEngine::headBone, Bone(GameEngine::headBone, Transform(CharacterSkeleton.GetTargetBoneInfo("head").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("head").Quat)))},
		{ GameEngine::thigh_lBone, Bone(GameEngine::thigh_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thigh_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thigh_l").Quat)))},
		{ GameEngine::calf_lBone, Bone(GameEngine::calf_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("calf_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("calf_l").Quat)))},
		{ GameEngine::calf_twist_01_lBone, Bone(GameEngine::calf_twist_01_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("calf_twist_01_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("calf_twist_01_l").Quat)))},
		{ GameEngine::calf_twist_02_lBone, Bone(GameEngine::calf_twist_02_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("calf_twist_02_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("calf_twist_02_l").Quat)))},
		{ GameEngine::foot_lBone, Bone(GameEngine::foot_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("foot_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("foot_l").Quat)))},
		{ GameEngine::ball_lBone, Bone(GameEngine::ball_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ball_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ball_l").Quat)))},
		{ GameEngine::thigh_twist_01_lBone, Bone(GameEngine::thigh_twist_01_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thigh_twist_01_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thigh_twist_01_l").Quat)))},
		{ GameEngine::thigh_twist_02_lBone, Bone(GameEngine::thigh_twist_02_lBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thigh_twist_02_l").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thigh_twist_02_l").Quat)))},
		{ GameEngine::thigh_rBone, Bone(GameEngine::thigh_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thigh_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thigh_r").Quat)))},
		{ GameEngine::calf_rBone, Bone(GameEngine::calf_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("calf_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("calf_r").Quat)))},
		{ GameEngine::calf_twist_01_rBone, Bone(GameEngine::calf_twist_01_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("calf_twist_01_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("calf_twist_01_r").Quat)))},
		{ GameEngine::calf_twist_02_rBone, Bone(GameEngine::calf_twist_02_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("calf_twist_02_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("calf_twist_02_r").Quat)))},
		{ GameEngine::foot_rBone, Bone(GameEngine::foot_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("foot_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("foot_r").Quat)))},
		{ GameEngine::ball_rBone, Bone(GameEngine::ball_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("ball_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("ball_r").Quat)))},
		{ GameEngine::thigh_twist_01_rBone, Bone(GameEngine::thigh_twist_01_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thigh_twist_01_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thigh_twist_01_r").Quat)))},
		{ GameEngine::thigh_twist_02_rBone, Bone(GameEngine::thigh_twist_02_rBone, Transform(CharacterSkeleton.GetTargetBoneInfo("thigh_twist_02_r").Transform, Quaternion(CharacterSkeleton.GetTargetBoneInfo("thigh_twist_02_r").Quat)))},
	};

	std::vector<std::string> boneOrder = {
		GameEngine::rootBone,
		GameEngine::center_of_massBone,
		GameEngine::ik_foot_rootBone,
		GameEngine::ik_foot_lBone,
		GameEngine::ik_foot_rBone,
		GameEngine::ik_hand_rootBone,
		GameEngine::ik_hand_gunBone,
		GameEngine::ik_hand_lBone,
		GameEngine::ik_hand_rBone,
		GameEngine::interactionBone,
		GameEngine::pelvisBone,
		GameEngine::spine_01Bone,
		GameEngine::spine_02Bone,
		GameEngine::spine_03Bone,
		GameEngine::spine_04Bone,
		GameEngine::spine_05Bone,
		GameEngine::clavicle_lBone,
		GameEngine::upperarm_lBone,
		GameEngine::lowerarm_lBone,
		GameEngine::hand_lBone,
		GameEngine::index_metacarpal_lBone,
		GameEngine::index_01_lBone,
		GameEngine::index_02_lBone,
		GameEngine::index_03_lBone,
		GameEngine::middle_metacarpal_lBone,
		GameEngine::middle_01_lBone,
		GameEngine::middle_02_lBone,
		GameEngine::middle_03_lBone,
		GameEngine::pinky_metacarpal_lBone,
		GameEngine::pinky_01_lBone,
		GameEngine::pinky_02_lBone,
		GameEngine::pinky_03_lBone,
		GameEngine::ring_metacarpal_lBone,
		GameEngine::ring_01_lBone,
		GameEngine::ring_02_lBone,
		GameEngine::ring_03_lBone,
		GameEngine::thumb_01_lBone,
		GameEngine::thumb_02_lBone,
		GameEngine::thumb_03_lBone,
		GameEngine::lowerarm_twist_01_lBone,
		GameEngine::lowerarm_twist_02_lBone,
		GameEngine::upperarm_twist_01_lBone,
		GameEngine::upperarm_twist_02_lBone,
		GameEngine::clavicle_rBone,
		GameEngine::upperarm_rBone,
		GameEngine::lowerarm_rBone,
		GameEngine::hand_rBone,
		GameEngine::index_metacarpal_rBone,
		GameEngine::index_01_rBone,
		GameEngine::index_02_rBone,
		GameEngine::index_03_rBone,
		GameEngine::middle_metacarpal_rBone,
		GameEngine::middle_01_rBone,
		GameEngine::middle_02_rBone,
		GameEngine::middle_03_rBone,
		GameEngine::pinky_metacarpal_rBone,
		GameEngine::pinky_01_rBone,
		GameEngine::pinky_02_rBone,
		GameEngine::pinky_03_rBone,
		GameEngine::ring_metacarpal_rBone,
		GameEngine::ring_01_rBone,
		GameEngine::ring_02_rBone,
		GameEngine::ring_03_rBone,
		GameEngine::thumb_01_rBone,
		GameEngine::thumb_02_rBone,
		GameEngine::thumb_03_rBone,
		GameEngine::lowerarm_twist_01_rBone,
		GameEngine::lowerarm_twist_02_rBone,
		GameEngine::upperarm_twist_01_rBone,
		GameEngine::upperarm_twist_02_rBone,
		GameEngine::neck_01Bone,
		GameEngine::neck_02Bone,
		GameEngine::headBone,
		GameEngine::thigh_lBone,
		GameEngine::calf_lBone,
		GameEngine::calf_twist_01_lBone,
		GameEngine::calf_twist_02_lBone,
		GameEngine::foot_lBone,
		GameEngine::ball_lBone,
		GameEngine::thigh_twist_01_lBone,
		GameEngine::thigh_twist_02_lBone,
		GameEngine::thigh_rBone,
		GameEngine::calf_rBone,
		GameEngine::calf_twist_01_rBone,
		GameEngine::calf_twist_02_rBone,
		GameEngine::foot_rBone,
		GameEngine::ball_rBone,
		GameEngine::thigh_twist_01_rBone,
		GameEngine::thigh_twist_02_rBone
	};

	// Connecting Bones
	for (auto boneIdx = 1; boneIdx < boneOrder.size(); boneIdx++)
	{
		int ParentIdx = CharacterSkeleton.BoneInfoVector[boneIdx - 1].ParentIndex + 1;
		if (ParentIdx < 0) continue;

		Bone& TargetChild = CharacterMesh.GetBone(boneOrder[boneIdx]);
		Bone& TargetParent = CharacterMesh.GetBone(boneOrder[CharacterSkeleton.BoneInfoVector[boneIdx - 1].ParentIndex + 1]);
		TargetChild.SetParent(TargetParent);
	}

	// Moving Weight Information
	cb.resize(v.size(), 0);
	w.resize(v.size());
	for (auto idx = 0; idx < WeightInfo.size(); ++idx)
	{
		char buffers[50];
		sprintf(buffers, "%d, ", idx);
		OutputDebugString(buffers);

		for (std::pair<std::string, float> info : WeightInfo[idx])
		{
			cb[idx]++;
			w[idx].Bones.push_back(info.first);
			w[idx].Values.push_back(info.second);

			char buffer[50];
			sprintf(buffer, "%f, ", info.second);
			OutputDebugString(buffer);
		}
		char bufferEnd[10];
		sprintf(bufferEnd, "\n");
		OutputDebugString(bufferEnd);
	}

	// Animation
	Animation& PistolReloadAnimation = CreateAnimation(GameEngine::PistolReloadAnimation);
	std::vector<std::string>& PistolReloadBoneNames = PistolReloadAnimation.GetBoneNames();;
	std::vector<bool>& PistolReloadBoneUsage = PistolReloadAnimation.GetBoneUsage();
	std::vector<std::vector<Vector3>>& PistolReloadFrameTranslations = PistolReloadAnimation.GetFrameTranslantions();
	std::vector<std::vector<Quaternion>>& PistolReloadFrameQuaternions = PistolReloadAnimation.GetFrameQuaternions();

	PistolReloadBoneNames.resize(boneOrder.size());
	PistolReloadBoneUsage.resize(boneOrder.size(), false);
	PistolReloadFrameTranslations.resize(boneOrder.size(), std::vector<Vector3>());
	PistolReloadFrameQuaternions.resize(boneOrder.size(), std::vector<Quaternion>());
	//애니메이션 임시막음
	//TestLoader.LoadAnimationWithName("PistolReload", boneOrder, OUT PistolReloadBoneNames, OUT PistolReloadBoneUsage, OUT PistolReloadFrameTranslations, OUT PistolReloadFrameQuaternions);

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

//// TODO : Temp, 
//void GameEngine::InterfaceTestFunction()
//{
//	static bool flag = true;
//
//	GameObject& goPlayer = GetGameObject("Player");
//	Mesh& m = GetMesh(goPlayer.GetMeshKey());
//	SKMesh& skm = static_cast<SKMesh&>(m);
//	Bone& NeckBone = skm.GetBone(GameEngine::NeckBone);
//
//	if (flag)
//	{
//		NeckBone.GetTransform().SetLocalRotation(Rotator(50.f, 0.f, 0.f));
//		flag = false;
//	}
//	else
//	{
//		NeckBone.GetTransform().SetLocalRotation(Rotator(-50.f, 0.f, 0.f));
//		flag = true;
//	}
//	
//}