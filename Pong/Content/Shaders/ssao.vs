#version 430 core

layout(location = 0) in vec3 position;

out VS_OUT
{
    vec3 E;
} vs_out;

void main(void)
{
    const vec4 vertices[] = vec4[]( vec4(-1.0, -1.0, 0.5, 1.0),
                                    vec4( 1.0, -1.0, 0.5, 1.0),
                                    vec4(-1.0,  1.0, 0.5, 1.0),
                                    vec4( 1.0,  1.0, 0.5, 1.0) );
    

    //gl_Position = vertices[gl_VertexID];
    gl_Position = vec4(position, 1.0);
    vs_out.E = vertices[gl_VertexID].xyz;
}
