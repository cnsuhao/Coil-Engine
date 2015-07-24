#version 430
//#define M_PI 3.1415926535897932384626433832795

// Input vertex data, different for all executions of this shader.
//layout(location = 0) in float position[3];
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoords;
layout(location = 2) in vec3 normal;

//Out variables
//out vec3 positionWorld;

//Varying variables
out vec2 UV0;
out vec3 normal0;


// Uniforms
//uniform uint time;
//uniform mat4 MVP;

//vars
//int timeVar = 1;

void main(){
    gl_Position =
    //MVP * //MVP
    //vec4(position.x,position.y + sin(time),position.z, 1.0); //Jelly
    vec4(position.x,position.y,position.z, 1.0);
    //gl_Position.w = 1.0;

    //Send out
    UV0 = texcoords;
    //normal0 = (transform * vec4(normal.x,normal.y + sin((position.x*10.0)+ time/250.0)/25.0,normal.z, 0.0)).xyz;
    //normal0 = (MVP * vec4(normal.x,normal.y,normal.z, 0.0)).xyz;
    normal0 = normal;
}

