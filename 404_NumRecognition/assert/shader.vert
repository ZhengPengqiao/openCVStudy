attribute vec4 vertexPos;
attribute vec4 textureColor;
uniform mat4 proMatrix;
varying vec4 color;

void main(void)
{
    gl_Position = proMatrix * vertexPos;
    color = textureColor;
}
