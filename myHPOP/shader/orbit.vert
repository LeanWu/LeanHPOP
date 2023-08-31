#version 330
layout (location = 0) in vec3 pos;
out vec2 texCoord;
uniform float pi;
uniform int n;
uniform mat4 mat4MVP;
void main()
{
    if(n==0)
    {
        float DEG2RAD = pi / 180.0;
        float x = pos[2] * sin(pos[1] * DEG2RAD) * cos(pos[0] * DEG2RAD);
        float y = pos[2] * sin(pos[1] * DEG2RAD) * sin(pos[0] * DEG2RAD);
        float z = pos[2] * cos(pos[1] * DEG2RAD);
        gl_Position = mat4MVP * vec4(x, y, z, 1.0);
        gl_PointSize=1;
        texCoord = vec2(pos[0] / 360.0, 1.0 - pos[1] / 180.0);
        //纹理的Y方向是从下向上的，而pos.y的正方向是从上向下，所以是1.0 - pos.y / 180.0
    }
    else if(n==1)
    {
        float r=1+pos[2]/6371000.0;
        float x = r * sin(-pos[1]+0.5*pi) * cos(pos[0]+pi);
        float y = r * sin(-pos[1]+0.5*pi) * sin(pos[0]+pi);
        float z = r * cos(-pos[1]+0.5*pi);
        gl_Position = mat4MVP * vec4(x, y, z, 1.0);
        gl_PointSize=1;
    }
    else if(n==2)
    {
        float r=1+pos[2]/6371000.0;
        float x = r * sin(-pos[1]+0.5*pi) * cos(pos[0]+pi);
        float y = r * sin(-pos[1]+0.5*pi) * sin(pos[0]+pi);
        float z = r * cos(-pos[1]+0.5*pi);
        gl_Position = mat4MVP * vec4(x, y, z, 1.0);
        gl_PointSize=10;
    }
}
