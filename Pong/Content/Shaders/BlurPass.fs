#version 430

//Varying variables
in vec2 UV0;
in vec3 normal0;

//uniforms
layout(location = 0) uniform sampler2D	diffuse;
uniform float		xBlur;
uniform float 		yBlur;
uniform float       xScreen;
uniform float       yScreen;

// Ouput data
out vec4 color;

void main()
{
	// Output color
    //color = texture2D(diffuse, UV0);
    vec2 UVPixel = vec2(1.0/xScreen, 1.0/yScreen);

    //vec4 baseColor = texture( diffuse, vec2(UV0.x, UV0.y));

    //X Samples
    vec4 xSamples[5] = {
    	texture( diffuse, vec2(UV0.x - UVPixel.x * xBlur, UV0.y)),
    	texture( diffuse, vec2(UV0.x - (UVPixel.x * xBlur)/2.0, UV0.y)),
    	texture( diffuse, vec2(UV0.x, UV0.y)),
    	texture( diffuse, vec2(UV0.x + (UVPixel.x * xBlur)/2.0, UV0.y)),
    	texture( diffuse, vec2(UV0.x + UVPixel.x * xBlur, UV0.y))
    };

	vec4 xEndColor = xSamples[0] + xSamples[1] + xSamples[2] + xSamples[3] + xSamples[4];
	xEndColor /= 5.0;
/*
	//int xAmount = round(xBlur);
	int xSampleSize = 1 + xBlur * 2;
	vec4 xSamples[xSampleSize];
	for(int i = 0; i < xBlur; i++)
	{
		xSamples[(xBlur*2) - i] = texture( diffuse, vec2(UV0.x + UVPixel.x*(xBlur-i), UV0.y));
	}
*/
    //Y Samples
    vec4 ySamples[5] = {
    	texture( diffuse, vec2(UV0.x, UV0.y - UVPixel.y * yBlur)),
    	texture( diffuse, vec2(UV0.x, UV0.y - (UVPixel.y * yBlur)/2)),
    	texture( diffuse, vec2(UV0.x, UV0.y)),
    	texture( diffuse, vec2(UV0.x, UV0.y + (UVPixel.y * yBlur)/2)),
    	texture( diffuse, vec2(UV0.x, UV0.y + UVPixel.y * yBlur))
    };

	vec4 yEndColor = ySamples[0] + ySamples[1] + ySamples[2] + ySamples[3] + ySamples[4];
	yEndColor /= 5.0;

    //color = texture( diffuse, Samples[0]);
    //color = Samples[1];
    color = (yEndColor + xEndColor)/2.0;
    //color = texture2D( diffuse, UV0 + 0.005*vec2( sin(time+1024.0*UV0.x),cos(time+768.0*UV0.y)) );
    
}
