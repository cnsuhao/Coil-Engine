#version 430

//Varying variables
in vec2 UV0;
in vec3 normal0;

//uniforms
//uniform int    time;
uniform sampler2D       diffuse;

// Input data
//in vec3 positionWorld;

// Ouput data
layout(location = 0) out vec4 color;

//local variables
//vec4 light = vec4();

void main()
{
	
	//vec3 lightDir = vec3(1.0,1.0, -1.0); //light vector


	// Output color
    color = texture(diffuse, UV0); //base color / texture
    
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	
}
