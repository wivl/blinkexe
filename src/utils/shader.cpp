#include "shader.hpp"

unsigned int make_shader(
    const std::string& vertex_filepath, const std::string& fragment_filepath) {

    //To store all the shader modules
    std::vector<unsigned int> modules;

    //Add a vertex shader module
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));

    //Add a fragment shader module
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    //Attach all the modules then link the program
    unsigned int shader = glCreateProgram();
    for (unsigned int shaderModule : modules) {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);

    //Check the linking worked
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader linking error:\n" << errorLog << '\n';
    }

    //Modules are now unneeded and can be freed
    for (unsigned int shaderModule : modules) {
        glDeleteShader(shaderModule);
    }

    return shader;

}

unsigned int make_module(const std::string& filepath, unsigned int module_type) {

    std::ifstream file;
    std::stringstream buffered_lines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line)) {
        //std::cout << line << std::endl;
        buffered_lines << line << '\n';
    }
    std::string shader_source = buffered_lines.str();
    const char* shader_src = shader_source.c_str();
    buffered_lines.str("");
    file.close();

    unsigned int shader_module = glCreateShader(module_type);
    glShaderSource(shader_module, 1, &shader_src, nullptr);
    glCompileShader(shader_module);

    int success;
    glGetShaderiv(shader_module, GL_COMPILE_STATUS, &success);
    if (!success) {
        char error_log[1024];
        glGetShaderInfoLog(shader_module, 1024, NULL, error_log);
        std::cout << "Shader Module compilation error:\n" << error_log << std::endl;
    }

    return shader_module;
}