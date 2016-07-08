//
// Created by lvrma on 05/07/16.
//

#include <fstream>
#include <iostream>
#include "shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName) {
    m_program = glCreateProgram(); // GL creates a program and returns a reference uint
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vsh"), GL_VERTEX_SHADER); // Same thing for the shaders
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fsh"), GL_FRAGMENT_SHADER); // The file extension is personal

    // Again, preparing for a future case where more shaders will be used
    for(unsigned int i = 0; i < NUM_SHADERS; i++) // Linking each shader to the program
        glAttachShader(m_program, m_shaders[i]); // Always using the handle uint reference

    glBindAttribLocation(m_program, 0, "position"); // Binding attributes from the mesh into the shader file
    glBindAttribLocation(m_program, 1, "texCoord");

    // Linking shaders in the program to enable interaction
    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program failed to link");

    // Validation after all the procedure is done
    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program invalid");

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform"); // Gaining access to the uniform

}

Shader::~Shader() {
    // Again, preparing for a future case where more shaders will be used
    for(unsigned int i = 0; i < NUM_SHADERS; i++){
        glDetachShader(m_program, m_shaders[i]); // Detaching from program
        glDeleteShader(m_shaders[i]); // Deleting shaders one by one
    }
    glDeleteProgram(m_program); // Finally, delete the program
}

void Shader::Bind() {
    glUseProgram(m_program); // Specifying the handle program for the shaders
}

void Shader::Update(const Transform &transform) {

    // Taking the model (or world) matrix
    glm::mat4 model = transform.GetModel();

    // An openGL uniform of Matrix 4x4 floating point values
    // Specify the object, the amount, and TRUE/FALSE to transpose the matrix or not
    // Finally the address of the first element of the model matrix, that yields the address of the matrix
    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_TRUE, &model[0][0]);

    // It's very cheap in memory terms to use this uniform like that, for it serves for all vertices
}

static GLuint CreateShader(const std::string& text, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0) // Checking if openGL has given a real shader or not
        std::cerr << "Error: Shader wasn't created" << std::endl;

    // Since openGL is in C, strings need to be converted
    const GLchar* shaderSourceCodeStrings[1]; // Chars
    GLint shaderSourceCodeStringLengths[1]; // Size
    shaderSourceCodeStrings[0] = text.c_str();
    shaderSourceCodeStringLengths[0] = text.length();

    // The way openGL handles the shader source code depends on your graphics card
    // The "1" means there's only one line of source code
    glShaderSource(shader, 1, shaderSourceCodeStrings, shaderSourceCodeStringLengths); // Assigning source code
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader didn't compile"); // Final checking

    return shader;
}

// Simple stream to read shader file
static std::string LoadShader(const std::string& fileName){
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
        while(file.good()){
            getline(file, line);
            output.append(line+"\n");
        }
    else
        std::cerr << "Unable to load shader: " << fileName << std::endl;

    return output;
}

// IO error checking
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage){
    GLint success = 0;
    GLchar error[1024] = {0};

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE){
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}