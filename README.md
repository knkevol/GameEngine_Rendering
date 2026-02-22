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
<br />
<br />


### 2️⃣ Math Module
* 렌더링 엔진 내 모든 객체의 위치, 회전, 크기 및 기하학적 형태를 정의하기 위한 기초 수학 자료형과 연산 로직을 담고 있습니다.
  
* 공간 데이터를 처리할 수 있도록 표준화된 인터페이스를 제공하는 엔진의 기초라이브러리 모듈입니다.

* 주요 구성 요소
  * Vector (2, 3, 4)
 
  * Matrix (2x2, 3x3, 4x4)
 
  * Quaternion & Rotator
 
  * Geometric Shapes (Box, Sphere, Plane, Frustum)

<br />
<br />

### 3️⃣ Renerer Module

<br />
<br />

### 4️⃣ ImportAsset Module

<br />
<br />

### 5️⃣ GERPlayer Module

<br />
<br />


<br />
<br />


(Gif 및 모듈별 상세 내용 추가)
