#version 330

smooth in vec4 vVaryingColor;

out vec4 outputColor;

void main()
{
	outputColor = vVaryingColor;
}
