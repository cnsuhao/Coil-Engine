#version 430

//Varying variables
in vec2 UV0;
in vec3 normal0;

//uniforms
uniform sampler2D       diffuse;
uniform float			time;

// Ouput data
out vec4 color;

void main()
{
	// Output color
    //color = texture2D(diffuse, UV0);
    color = texture2D( diffuse, UV0 + 0.005*vec2( sin(time+1280.0*UV0.x),cos(time+720.0*UV0.y)) );
    // color.y = 0.0;
    // color.z = 0.0;
    //color = texture2D( diffuse, UV0 + 0.005*vec2( sin(time+1024.0*UV0.x),cos(time+768.0*UV0.y)) );
    
}
