# 🎮 *Rendering Engine Project*
<img width="233" height="500" alt="image" src="https://github.com/user-attachments/assets/3b0fd3ad-01ad-40a7-9c09-5386fb72977f" /> 

본 프로젝트는 이득우의 게임수학 내용을 기반으로, 모듈화된 설계를 중심으로 발전시킨 엔진 프로젝트입니다.

FBX SDK를 연동하여 외부 애셋을 처리할 수 있는 구조로 확장하였습니다.

<br />

✅ 주요 기능

* Static Mesh / Skeletal Mesh 렌더링
* Bone Hierarchy
* Skinning Animation
* Windows GDI 기반 소프트웨어 렌더링 시스템
* Sutherland–Hodgman 알고리즘을 적용한 3D 삼각형 클리핑
* 자체 Rasterizer를 통해 애니메이션 렌더링 구현
* 엔진 모듈 구조 분리 설계 (Math / Import / Engine / Renderer / Player)

<br />
<br />

> Use FBX Version : [FBX SDK 2020.3.7  VS2019](https://aps.autodesk.com/developer/overview/fbx-sdk)
<br />

***

## 📌 Module

### 1️⃣ Engine Module
* 캐릭터의 골격구조(Skeletal) 정의 및 Weight 처리 행렬 계산과 시간에 따른 Bone의 변환 데이터를 관리

* 캐릭터의 3D Vertex 데이터 저장, Texture

* 캐릭터의 SRT행렬을 계산하여 World/Local Matrix 생성 및 View/Projection Matrix를 생성하여 3D 공간을 2D 화면으로 투영

```c++
  FORCEINLINE Matrix4x4 CameraObject::GetPerspectiveViewMatrix() const
  {
  	// 뷰 행렬 관련 요소
  	Vector3 viewX, viewY, viewZ;
  	GetViewAxes(viewX, viewY, viewZ);
  	Vector3 pos = _Transform.GetWorldPosition();
  	float zPos = viewZ.Dot(pos);
  
  	// 투영 행렬 관련 요소
  	float invA = 1.f / _ViewportSize.AspectRatio();
  	float d = 1.f / tanf(Math::Deg2Rad(_FOV) * 0.5f);
  	float dx = invA * d;
  	float invNF = 1.f / (_NearZ - _FarZ);
  	float k = (_FarZ + _NearZ) * invNF;
  	float l = 2.f * _FarZ * _NearZ * invNF;
  
  	return Matrix4x4(
  		Vector4(dx * viewX.X, d * viewY.X, k * viewZ.X, -viewZ.X),
  		Vector4(dx * viewX.Y, d * viewY.Y, k * viewZ.Y, -viewZ.Y),
  		Vector4(dx * viewX.Z, d * viewY.Z, k * viewZ.Z, -viewZ.Z),
  		Vector4(-dx * viewX.Dot(pos), -d * viewY.Dot(pos), -k * zPos + l, zPos)
  	);
  }
  ```

* 객체 생성 로직 및 초기화
  
<br />
<br />


### 2️⃣ Math Module
* 렌더링 엔진 내 모든 객체의 위치, 회전, 크기 및 기하학적 형태를 정의하기 위한 기초 수학 자료형과 연산 로직
  
* 공간 데이터를 처리할 수 있도록 표준화된 인터페이스를 제공하는 엔진의 기초라이브러리 모듈.

* 주요 구성 요소
  * Vector (2, 3, 4)
 
  * Matrix (2x2, 3x3, 4x4)
 
  * Quaternion & Rotator
 
  * Geometric Shapes (Box, Sphere, Plane, Frustum)

<br />
<br />

### 3️⃣ Renerer Module
* Win32 GDI를 활용해 프레임 버퍼를 구축
  
* 코헨-서덜랜드 알고리즘과 같은 기하 연산을 통해 렌더링 성능 최적화와 클리핑 처리를 CPU 레벨에서 구현

*  Vertex 위치 값 * 최종행렬 연산을 통한 쉐이더 정점 변환

<br />
<br />

### 4️⃣ ImportAsset Module
* 정점(Vertex), 인덱스(Index), UV 좌표 등의 Mesh 데이터와 계층 구조로 이루어진 Skeleton(Bone) 데이터 파싱 및 변환

* FBX Node 트리를 순회하며 Bone 계층 구조 처리 및 시간에 따른 각 Bone의 Transform데이터를 저장하여 사용


<br />
<br />

### 5️⃣ GERPlayer Module
* 운영체제로부터 프로세스 권한을 할당받고, 창을 띄우는 WindowsApp 환경 설정

* 엔진 생명 주기 제어(Loop)

* 씬(Scene) 관리

<br />
<br />

