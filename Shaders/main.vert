#version 450

// ----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------

layout(location=0) in vec2 position;
layout(location=1) in vec2 direction;
layout(location=2) in vec3 rgb;

// ----------------------------------------------------------------------------
// Uniform Variables
// ----------------------------------------------------------------------------

layout(location = 0) uniform mat4x4 mM;
layout(location = 1) uniform mat4x4 vM;
layout(location = 2) uniform mat4x4 pM;


// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------
layout(location = 0) out vec4 vs_color;

// ----------------------------------------------------------------------------
// Local Variables
// ----------------------------------------------------------------------------
const vec2 offset[6] = {
	vec2(0.0, 0.0),
	vec2(-0.02, -0.02),
	vec2(-0.03, -0.03),
	vec2(0.0, 0.0),
	vec2(-0.02, -0.02),
	vec2(-0.03, -0.03)
};

const vec2 offset2[6] = {
	vec2(0.0, 0.0),
	vec2(0.0, 0.0),
	vec2(0.01, -0.01),
	vec2(0.0, 0.0),
	vec2(0.0, 0.0),
	vec2(-0.01, 0.01)
};



// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
	vec2 new_dir = normalize(direction);
    vec4 position = vec4(position + offset[gl_VertexID % 6] * new_dir + new_dir.yx * offset2[gl_VertexID % 6], 0.0, 1.0);
	gl_Position = pM * vM * mM * position;
	vs_color = vec4(rgb, 1);
}