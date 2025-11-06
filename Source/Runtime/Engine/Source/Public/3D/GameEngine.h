#pragma once

namespace PGE
{
	namespace DDD
	{

		struct GameObjectCompare
		{
			bool operator()(const std::unique_ptr<GameObject>& lhs, std::size_t rhs)
			{
				return lhs->GetHash() < rhs;
			}
		};

		class GameEngine : public EngineInterface
		{
		public:
			GameEngine()
				: _GameMode(std::make_unique<GameMode>())
				, _Factory(std::make_unique<GameObjectTypeFactory>())
			{
			}

		public:
			// 공용 인터페이스
			virtual bool Init() override;
			virtual bool IsInitialized() override { return _IsInitialized; }
			virtual void OnScreenResize(const ScreenPoint& InScreenSize) override;
			virtual InputManager& GetInputManager() override { return _InputManager; }
			virtual std::vector<PLogs>& GetLogs() override { return _EngineLogs; }
			virtual PLogs& GetTargetLog(const std::string& LogHeader) override;

			//// TODO : Temp
			//virtual void InterfaceTestFunction() override;

			// 게임 로직 용도 
			const InputManager& GetInputManager() const { return _InputManager; }
			const std::vector<PLogs>& GetLogs() const { return _EngineLogs; }

			// Logging
			void InitLogChannels();
			int NewLogChannel(const std::string& NewLogHeader);

			// Load Asset
			void LoadCube();
			void LoadAsset();


			// 리소스 관리
			Mesh& CreateMesh(const std::size_t& InKey);
			SKMesh& CreateSKMesh(const std::size_t& InKey);
			Texture& CreateTexture(const std::size_t& InKey);
			Animation& CreateAnimation(const std::size_t& InKey);

			// 게임 오브젝트
			const std::vector<std::unique_ptr<GameObject>>& GetScene() const { return _Scene; }
			std::vector< std::unique_ptr<GameObject>>::const_iterator SceneBegin() const { return _Scene.begin(); }
			std::vector< std::unique_ptr<GameObject>>::const_iterator SceneEnd() const { return _Scene.end(); }
			GameObject& CreateNewGameObject(const std::string& InName);
			GameObject& GetGameObject(const std::string& InName);

			void RegisterGameObjectFactories();
			GameObject& CreateNewGameObjectOfClass(const std::string& InName, const std::string& InTypeName);

			// 메시
			Mesh& GetMesh(const std::size_t& InMeshKey) { return *_Meshes.at(InMeshKey).get(); }
			const Mesh& GetMesh(const std::size_t& InMeshKey) const { return *_Meshes.at(InMeshKey).get(); }

			// Animation
			Animation& GetAnimation(const std::size_t& InAnimKey) { return *_Anims.at(InAnimKey).get(); }
			const Animation& GetAnimation(const std::size_t& InAnimKey) const { return *_Anims.at(InAnimKey).get(); }

			// 카메라 
			FORCEINLINE CameraObject& GetMainCamera() { return _MainCamera; }
			FORCEINLINE const CameraObject& GetMainCamera() const { return _MainCamera; }

			// 메인 텍스처
			FORCEINLINE const Texture& GetTexture(const std::size_t& InTextureKey) const { return *_Textures.at(InTextureKey).get(); }

			//// 본을 그리기 위한 목록
			//std::unordered_map<std::string, GameObject*> GetBoneObjectPtrs() { return _BoneGameObjectPtrs; }

		private:
			bool LoadResources();

		public: // 주요 키 값
			//	 본
			static const std::string GameEngine::rootBone;
			static const std::string GameEngine::center_of_massBone;
			static const std::string GameEngine::ik_foot_rootBone;
			static const std::string GameEngine::ik_foot_lBone;
			static const std::string GameEngine::ik_foot_rBone;
			static const std::string GameEngine::ik_hand_rootBone;
			static const std::string GameEngine::ik_hand_gunBone;
			static const std::string GameEngine::ik_hand_lBone;
			static const std::string GameEngine::ik_hand_rBone;
			static const std::string GameEngine::interactionBone;
			static const std::string GameEngine::pelvisBone;
			static const std::string GameEngine::spine_01Bone;
			static const std::string GameEngine::spine_02Bone;
			static const std::string GameEngine::spine_03Bone;
			static const std::string GameEngine::spine_04Bone;
			static const std::string GameEngine::spine_05Bone;
			static const std::string GameEngine::clavicle_lBone;
			static const std::string GameEngine::upperarm_lBone;
			static const std::string GameEngine::lowerarm_lBone;
			static const std::string GameEngine::hand_lBone;
			static const std::string GameEngine::index_metacarpal_lBone;
			static const std::string GameEngine::index_01_lBone;
			static const std::string GameEngine::index_02_lBone;
			static const std::string GameEngine::index_03_lBone;
			static const std::string GameEngine::middle_metacarpal_lBone;
			static const std::string GameEngine::middle_01_lBone;
			static const std::string GameEngine::middle_02_lBone;
			static const std::string GameEngine::middle_03_lBone;
			static const std::string GameEngine::pinky_metacarpal_lBone;
			static const std::string GameEngine::pinky_01_lBone;
			static const std::string GameEngine::pinky_02_lBone;
			static const std::string GameEngine::pinky_03_lBone;
			static const std::string GameEngine::ring_metacarpal_lBone;
			static const std::string GameEngine::ring_01_lBone;
			static const std::string GameEngine::ring_02_lBone;
			static const std::string GameEngine::ring_03_lBone;
			static const std::string GameEngine::thumb_01_lBone;
			static const std::string GameEngine::thumb_02_lBone;
			static const std::string GameEngine::thumb_03_lBone;
			static const std::string GameEngine::lowerarm_twist_01_lBone;
			static const std::string GameEngine::lowerarm_twist_02_lBone;
			static const std::string GameEngine::upperarm_twist_01_lBone;
			static const std::string GameEngine::upperarm_twist_02_lBone;
			static const std::string GameEngine::clavicle_rBone;
			static const std::string GameEngine::upperarm_rBone;
			static const std::string GameEngine::lowerarm_rBone;
			static const std::string GameEngine::hand_rBone;
			static const std::string GameEngine::index_metacarpal_rBone;
			static const std::string GameEngine::index_01_rBone;
			static const std::string GameEngine::index_02_rBone;
			static const std::string GameEngine::index_03_rBone;
			static const std::string GameEngine::middle_metacarpal_rBone;
			static const std::string GameEngine::middle_01_rBone;
			static const std::string GameEngine::middle_02_rBone;
			static const std::string GameEngine::middle_03_rBone;
			static const std::string GameEngine::pinky_metacarpal_rBone;
			static const std::string GameEngine::pinky_01_rBone;
			static const std::string GameEngine::pinky_02_rBone;
			static const std::string GameEngine::pinky_03_rBone;
			static const std::string GameEngine::ring_metacarpal_rBone;
			static const std::string GameEngine::ring_01_rBone;
			static const std::string GameEngine::ring_02_rBone;
			static const std::string GameEngine::ring_03_rBone;
			static const std::string GameEngine::thumb_01_rBone;
			static const std::string GameEngine::thumb_02_rBone;
			static const std::string GameEngine::thumb_03_rBone;
			static const std::string GameEngine::lowerarm_twist_01_rBone;
			static const std::string GameEngine::lowerarm_twist_02_rBone;
			static const std::string GameEngine::upperarm_twist_01_rBone;
			static const std::string GameEngine::upperarm_twist_02_rBone;
			static const std::string GameEngine::neck_01Bone;
			static const std::string GameEngine::neck_02Bone;
			static const std::string GameEngine::headBone;
			static const std::string GameEngine::thigh_lBone;
			static const std::string GameEngine::calf_lBone;
			static const std::string GameEngine::calf_twist_01_lBone;
			static const std::string GameEngine::calf_twist_02_lBone;
			static const std::string GameEngine::foot_lBone;
			static const std::string GameEngine::ball_lBone;
			static const std::string GameEngine::thigh_twist_01_lBone;
			static const std::string GameEngine::thigh_twist_02_lBone;
			static const std::string GameEngine::thigh_rBone;
			static const std::string GameEngine::calf_rBone;
			static const std::string GameEngine::calf_twist_01_rBone;
			static const std::string GameEngine::calf_twist_02_rBone;
			static const std::string GameEngine::foot_rBone;
			static const std::string GameEngine::ball_rBone;
			static const std::string GameEngine::thigh_twist_01_rBone;
			static const std::string GameEngine::thigh_twist_02_rBone;
			// ~ 본

				// 메시
			static const std::size_t CubeMesh;
			static const std::size_t CharacterMesh;
			static const std::size_t ArrowMesh;


			// 텍스처
			static const std::size_t BaseTexture;
			static const std::size_t CharacterTexture;

			// Animation
			static const std::size_t PistolReloadAnimation;

			// GameObject Factories
			static PGameObjectFactory PFactory;
			static ActorFactory ActorFactory;
			static CharacterFactory CharacterFactory;



		private:
			bool _IsInitialized = false;

			std::unique_ptr<GameMode> _GameMode;
			std::unique_ptr<GameObjectTypeFactory> _Factory;

			ScreenPoint _ScreenSize;
			InputManager _InputManager;
			CameraObject _MainCamera;

			std::vector<PLogs> _EngineLogs;
			std::unordered_map<std::string, int> _LogIndexMap;

			std::vector<std::unique_ptr<GameObject>> _Scene;
			std::unordered_map<std::size_t, std::unique_ptr<Mesh>> _Meshes;
			std::unordered_map<std::size_t, std::unique_ptr<Texture>> _Textures;
			std::unordered_map<std::string, GameObject*> _BoneGameObjectOtrs;
			std::unordered_map<std::size_t, std::unique_ptr<Animation>> _Anims;


		};



	}
}