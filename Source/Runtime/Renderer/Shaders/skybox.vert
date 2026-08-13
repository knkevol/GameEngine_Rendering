#version 330 core

layout(location = 0) in vec3 aPosition;

layout(std140) uniform CameraBlock
{
	mat4 uView;
	mat4 uProjection;
	vec4 uViewPosition;
};

out vec3 vTexCoord;

void main()
{
	// 이동성분제거 => 고정
	mat4 viewNoTrans = mat4(mat3(uView));

	vec4 pos = uProjection * viewNoTrans * vec4(aPosition, 1.0);

	gl_Position = pos.xyww;

	vTexCoord = aPosition;

}