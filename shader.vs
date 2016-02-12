#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) in vec3 normal;

out vec2 UV;
out vec3 norm;
uniform float Time;

mat3 rotationMatrix(vec3 axis, float angle)
{
	axis = normalize(axis);
	float s = sin(angle);
	float c = cos(angle);
	float oc = 1.0 - c;
	
	return mat3(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s, 
	oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s, 
	oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c);
}

void main(){

	mat3 rotmat = rotationMatrix(vec3(0,1,0), Time);
	rotmat = rotmat * rotationMatrix(vec3(1,0,0), Time*0.1);
    gl_Position =  vec4(rotmat * in_position,1);
    UV = texcoord;
    norm = rotmat * normal;
}