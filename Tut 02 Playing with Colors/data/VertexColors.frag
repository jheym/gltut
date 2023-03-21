#version 330

// Note: We must use the same interpolation qualifier (smooth) used in the vertex shader.
smooth in vec4 theColor; // Our custom variable comes in from the vertex shader.

// The vertex shader is run only 3 times, but the fragment shader runs once for every fragment produced by the rasterizer.
// Fragments are about one pixel. So that's a lot of fragments depending on the resolution of the window.
out vec4 outputColor;

// Key idea: Fragment interpolation gives each fragment a color value in-between the values for each vertex.
void main()
{
	outputColor = theColor; // Assign the color to each fragment
}
