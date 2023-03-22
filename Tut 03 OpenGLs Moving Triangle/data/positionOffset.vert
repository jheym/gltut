#version 330

layout(location = 0) in vec4 position;

// Uniform values do not change from one shader invocation to the next. They are neither inputs nor outputs.
// Uniforms may only change between executions of rendering calls.
// This var gets set by main program calling glGetUniformLocation() using the matching variable name ("offset")
uniform vec2 offset;

void main()
{
	vec4 totalOffset = vec4(offset.x, offset.y, 0.0, 0.0);
	gl_Position = position + totalOffset;
}
