#version 430 core
out vec4 outColor;

in vec2 UV;
in vec3 norm;

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

vec3 correctGamma(vec3 inp){
	vec3 gamma = vec3(1.0/2.2, 1.0/2.2, 1.0/2.2);
	return vec3(pow(inp.r, gamma.r),
	pow(inp.g, gamma.g),
	pow(inp.b, gamma.b));
}

void main()
{
	vec2 pos = vec2(sin(Time), cos(Time));
	float dt = max(0, dot(normalize(norm), normalize(vec3(pos.x,1,pos.y))));
	outColor = vec4(correctGamma(vec3(dt)), 1);
}