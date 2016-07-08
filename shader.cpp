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
    m_program = glCreateProgram(); // GL cria um programa e retorna uma referência a ele na forma uint (inteiro positivo)
    m_shaders[0] = CreateShader(LoadShader(fileName + ".vsh"), GL_VERTEX_SHADER); // Mesma coisa para os shaders
    m_shaders[1] = CreateShader(LoadShader(fileName + ".fsh"), GL_FRAGMENT_SHADER); // A extensão do arquivo é pessoal

    // Preparando para um caso futuro onde mais shaders serão usados, a implementação está mais genérica
    // Outros shaders incluem o de Tesselation e Geometry
    for(unsigned int i = 0; i < NUM_SHADERS; i++) // Linkando cada shader ao programa
        glAttachShader(m_program, m_shaders[i]); // Sempre usando a referencia em unsigned int

    glBindAttribLocation(m_program, 0, "position"); // Bindando os atributos do mesh no arquivo do shader como attribs
    glBindAttribLocation(m_program, 1, "texCoord");

    // Linkando os shaders do programa, para permitir interação
    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Erro: Programa nao conseguiu linkar");

    // Validação após o procedimento ser feito
    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Erro: Programa invalido");

    // Ganhando acesso ao "uniform" (descrito no V. Shader)
    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

}

Shader::~Shader() {
    // Preparando para um caso futuro onde mais shaders serão usados, a implementação está mais genérica
    for(unsigned int i = 0; i < NUM_SHADERS; i++){
        glDetachShader(m_program, m_shaders[i]); // Separando do programa
        glDeleteShader(m_shaders[i]); // Deletando shaders um por um
    }
    glDeleteProgram(m_program); // Finalmente, deletamos o programa
}

void Shader::Bind() {
    glUseProgram(m_program); // Specificando o programa a ser usado com os shaders
}

void Shader::Update(const Transform &transform, const Camera& camera) {
    // Pegando a Model (ou World) matrix (o resultado final é multiplicado pela projection matrix da camera
    glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

    // Um uniform Matrix 4x4 do openGL com valores float:
    // Specificando o objeto em si, a quantidade de objetos, e um valor True/False para transpor a matriz ou não
    // Por ultimo, o endereço do primeiro elemento da Model Matrix, que da o endereço da matriz
    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_TRUE, &model[0][0]);
    // É muito barato em termos de memória utilizar um uniform como esse, pois serve para todos os vértices
}

static GLuint CreateShader(const std::string& text, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0) // Checando se o shader dado pelo openGL existe ou não
        std::cerr << "Erro: Shader nao foi criado" << std::endl;

    // Já que o openGL é em C, as strings precisam ser convertidas
    const GLchar* shaderSourceCodeStrings[1]; // Chars
    GLint shaderSourceCodeStringLengths[1]; // Tamanho
    shaderSourceCodeStrings[0] = text.c_str();
    shaderSourceCodeStringLengths[0] = text.length();

    // O jeito que o openGL trabalha com o shader dado depende da sua placa de video
    // O "1" significa que só tem uma linha de código fonte
    glShaderSource(shader, 1, shaderSourceCodeStrings, shaderSourceCodeStringLengths); // Definindo o código fonte
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shade nao compilou"); // Checagem final

    return shader;
}

// Stream genérico para ler o arquivo do shader
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
        std::cerr << "Shader nao pode ser lido: " << fileName << std::endl;

    return output;
}

// Checagem de erros do IO
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