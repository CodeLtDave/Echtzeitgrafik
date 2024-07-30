static const GLchar* simpleFragmentShaderSource =
"#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 color;\n"
"void main() {\n"
" color = vec4(ourColor, 1.0f);\n"
"}\0";