//attribute highp vec4 qt_Vertex;
//attribute highp vec4 qt_MultiTexCoord0;
//uniform highp mat4 qt_ModelViewProjectionMatrix;
//varying highp vec4 qt_TexCoord0;

//void main(void)
//{
//    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
//    qt_TexCoord0 = qt_MultiTexCoord0;
//}

//attribute highp vec4 vertices;
//varying highp vec2 coords;
//void main() {
//    gl_Position = vertices;
//    coords = vertices.xy;
//}

uniform mat4 mvpMatrix;
attribute vec4 vertex;
attribute vec4 color;

varying vec4 varyingColor;

void main(void)
{
    varyingColor = color;
    gl_Position = mvpMatrix * vertex;
}
