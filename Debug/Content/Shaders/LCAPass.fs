#version 430

//Varying variables
in vec2 UV0;
in vec3 normal0;

//uniforms
layout(location = 0) uniform sampler2D	diffuse;
uniform float       Amount;
uniform float       Xpos;
uniform float 		Ypos;

// Ouput data
out vec4 color;

void main()
{
	// Output color
    //color = texture2D(diffuse, UV0);
    vec2 UVPixel = vec2(1.0/1280.0, 1.0/720.0);


    color = vec4(texture(diffuse, UV0).x, 0, 0, 0);
    
}
