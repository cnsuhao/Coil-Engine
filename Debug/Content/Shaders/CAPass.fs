#version 430

//Varying variables
in vec2 UV0;
in vec3 normal0;

//uniforms
layout(location = 0) uniform sampler2D  diffuse;
uniform float       Amount  = 1;

// Ouput data
out vec4 color;

void main()
{
    // Output color
    //color = texture2D(diffuse, UV0);
   
    //vec2 UVPixel = vec2(1.0/1280.0, 1.0/720.0);
    if(Amount != 0.0)
    {

        vec4 red    = texture( diffuse, 
            vec2(UV0.x - Amount/1000.0, UV0.y - Amount/1000.0))
        * vec4(1,0,0,1);


        vec4 green  = texture( diffuse, vec2(UV0.x, UV0.y + Amount/1000.0)) * vec4(0,1,0,1);
        vec4 blue   = texture( diffuse, 
        vec2(UV0.x + Amount/1000.0, UV0.y - Amount/1000.0))
                * vec4(0,0,1,1);

        color = red + green + blue;
    }else{
        color = texture( diffuse, UV0);
    }
}
