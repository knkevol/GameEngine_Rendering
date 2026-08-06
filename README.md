# 🎮 OpenGL Rendering Engine

> **CPU Software Renderer를 OpenGL 3.3 Core Profile 기반 GPU Renderer로 확장한 Rendering Engine**

## 📖 Overview

본 프로젝트는 기존 Win32 GDI 기반 Software Renderer를 OpenGL 3.3 Core Profile 기반 GPU Renderer로 확장한 렌더링 엔진입니다.

FBX SDK 기반 Asset Pipeline과 Skeletal Animation 시스템을 유지하면서 CPU에서 수행하던 렌더링과 스키닝을 GPU 기반으로 이전하였습니다.

<img width="790" height="620" alt="Image" src="https://github.com/user-attachments/assets/4c1f7d12-3691-46ee-9357-e323f5639a88" />


---

## 📌 Engine Architecture

```text
Application
      │
      ▼
Rendering System Interface
      │
 ┌────┴────┐
 │         │
WindowRSI  OpenGLRSI
              │
              ▼
         OpenGLDevice
              │
      Shader / VAO / VBO
```

---

## 📌 WGL Context Initialization

```text
Dummy Context
      │
      ▼
Load wglCreateContextAttribsARB
      │
      ▼
Create OpenGL 3.3 Core Context
      │
      ▼
Delete Dummy Context
```

Legacy Context에서만 WGL 확장 함수를 획득할 수 있는 특성을 고려하여 2단계 초기화를 구현했습니다.

---

## 📌 GPU Vertex Skinning

기존 CPU Software Skinning

```cpp
position = BoneMatrix * InverseBindPose * position;
```

GPU Skinning

```glsl
mat4 skin =
BoneMatrices[idx.x] * weight.x +
BoneMatrices[idx.y] * weight.y +
BoneMatrices[idx.z] * weight.z +
BoneMatrices[idx.w] * weight.w;

gl_Position = Projection * View * World * skin * vec4(Position,1.0);
```

### 변경사항

- CPU Skinning 제거
- GPU 병렬 처리
- Vertex Shader 기반 Animation

---

## 📌 Rendering Pipeline

```text
FBX Import
    │
Mesh / Skeleton
    │
Animation Update
    │
Skin Matrix Upload
    │
Vertex Shader
    │
Rasterization
    │
Fragment Shader
    │
FrameBuffer
```

---

## 📌 주요 구현 내용

## OpenGL GPU Renderer

- OpenGL 3.3 Core Profile 구축
- WGL 기반 Context 생성
- GLAD 함수 로더 적용
- GPU Resource(OpenGLDevice) 구현

## Rendering Backend

- RSI 추상화 유지
- OpenGLRSI 구현
- CPU/GPU Backend 교체 가능 구조

## GPU Skinning

- Bone Weight 상위 4개 정규화
- Vertex Attribute 업로드
- GLSL Vertex Shader Skinning

## Rendering Features

- Frustum Culling
- Wireframe
- Bone Debug
- Depth Buffer View
- Debug Overlay

---

## 📌 Tech Stack

|Category|Technology|
|---|---|
|Language|C++|
|Graphics API|OpenGL 3.3|
|Window|Win32 API / WGL|
|Loader|GLAD|
|Shader|GLSL|
|Asset|FBX SDK 2020.3.7|
|IDE|Visual Studio 2022|

---

## 📌 CPU vs GPU Renderer

|CPU Renderer|GPU Renderer|
|---|---|
|Win32 GDI|OpenGL 3.3|
|Software Rasterizer|Hardware Rasterizer|
|CPU Vertex Skinning|GPU Vertex Skinning|
|CPU Rendering|Programmable Pipeline|
|Software Draw Loop|Vertex/Fragment Shader|

