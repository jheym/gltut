#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

smooth out vec4 theColor; // Define the output variable. "smooth" is an interpolation qualifier.
// out vec4 gl_Position; Not needed because gl_Position is a builtin, as gl_* variables are. 
void main()
{
	gl_Position = position; // Assign in values to the output variable (vertex position in clip space)
	theColor = color; // Assign in values to the output variable (color associated with the vertex position)
	// User-defined outputs, like theColor above, have no intrinsic meaning to the system.
	// They only have an effect in so far as other shader stages use them.
}
