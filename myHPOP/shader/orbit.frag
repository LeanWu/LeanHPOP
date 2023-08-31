#version 330
out vec4 color;
in vec2 texCoord;
uniform int n;
uniform sampler2D Tex;
void main()
{
    if(n==0)
    {
        color = texture(Tex, texCoord);
        //注意，texCoord的值域在0-1之间
    }
    else if(n==1)
    {
        color = vec4(122/255.0,197/255.0,205/255.0,1.0);
    }
    else if(n==2)
    {
        color = vec4(255/255.0,0/255.0,0/255.0,1.0);
    }
}
