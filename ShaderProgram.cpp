#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glew.h>

class ShaderProgram
{
protected:
    GLuint Program;
public:

    ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath) {      //Compiles shader
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try {                                                           //Extracting shaders code from file
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure error) {
            std::cout << error.what() << std::endl;
        }

        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();
        GLuint vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);      // 
        glShaderSource(vertex, 1, &vShaderCode, NULL);  //Compiling vertex shader
        glCompileShader(vertex);                        //
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);        //
        glCompileShader(fragment);                              //Compiling fragment shader    
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);   //
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        //Creating Shader program
        this->Program = glCreateProgram();  //Creating an empty program  
        glAttachShader(this->Program, vertex);		//Attaching shaders
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        glDeleteShader(fragment);		//Deleting shaders which we won't need anymore
        glDeleteShader(vertex);
    }

    void Use() {
        glUseProgram(this->Program);
    }
};

#endif