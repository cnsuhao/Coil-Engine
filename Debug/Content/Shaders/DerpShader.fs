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
    color =
    //vec4(1.0,0.0,0.0,1.0)//
    texture2D(diffuse, UV0) //texture2D(diffuse, UV0)                      // base color / texture
    //* clamp(dot(lightDir, normal0), 0.0, 1.0)    //Lighting
    ;
    /*


	//Camera variables
	vec3 eyeVec = vec3(0,0,-3.3);//Camera vector

	//Material variables
	float Sm = 5.6;	//specular component
	float f = 120.0;//specular exponential factor (the famous shininess in OpenGL)

	//Light variables
	float Sl = 5.6; //specular component


	vec3 N = normalize(normal0);
	vec3 L = normalize(lightDir);

	float lambertTerm = dot(N,L);

	//Specular

	if(lambertTerm > 0.0)
	{
		
		vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow( max(dot(R, E), 0.0), f );
		//color += (Sl * Sm * specular);	
	}
	*/
	

	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	
}
