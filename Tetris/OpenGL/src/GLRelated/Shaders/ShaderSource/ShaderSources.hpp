namespace ShaderSources
{
    const char *vertexShaderSource = ""
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0";

    const char *fragmentShaderSource = ""
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 shapeColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = shapeColor;\n"
        "}\0";
}

