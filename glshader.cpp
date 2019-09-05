#include "glshader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <QDebug>

#include "glm/gtc/type_ptr.hpp"

const GLchar* GLShader::readShader(const char* fileName)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        shaderFile.open(fileName);
        std::stringstream vShaderStream;
        // read file's buffer contents into streams
        vShaderStream << shaderFile.rdbuf();
        // close file handlers
        shaderFile.close();
        // convert stream into string
        shaderCode = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        qDebug() << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
        return nullptr;
    }

    return shaderCode.c_str();
}

bool GLShader::compileRenderingShader(const char *vsFileName, const char *fsFileName, const char *gsFileName)
{
    // Retrieve the source codes from filePath
    const GLchar* vertexCode = readShader(vsFileName);
    if (vertexCode == nullptr)
        return false;

    const GLchar* fragmentCode = readShader(fsFileName);
    if (fragmentCode == nullptr)
        return false;

    const GLchar* geometryCode = nullptr;
    if (gsFileName != nullptr)
    {
        geometryCode = readShader(gsFileName);
        if (geometryCode == nullptr)
            return false;
    }

    // Compile shaders
    GLuint vertex, fragment, geometry = 0;
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, nullptr);
    glCompileShader(vertex);
    if (!checkCompileErrors(vertex, "VERTEX"))
        return false;
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, nullptr);
    glCompileShader(fragment);
    if (!checkCompileErrors(fragment, "FRAGMENT"))
        return false;
    // If geometry shader source code is given, also compile geometry shader
    if (geometryCode != nullptr)
    {
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &geometryCode, nullptr);
        glCompileShader(geometry);
        if (!checkCompileErrors(geometry, "GEOMETRY"))
            return false;
    }

    // Shader Program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    if (geometryCode != nullptr)
        glAttachShader(m_id, geometry);

    glLinkProgram(m_id);
    if (!checkCompileErrors(m_id, "PROGRAM"))
        return false;

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryCode != nullptr)
        glDeleteShader(geometry);

    return true;
}

bool GLShader::compileComputingShader(const char *csFileName)
{
    // Retrieve the source codes from filePath
    const GLchar* computeCode = readShader(csFileName);
    if (computeCode == nullptr)
        return false;

    // Compile shaders
    GLuint compute;
    // Compute Shader
    compute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute, 1, &computeCode, nullptr);
    glCompileShader(compute);
    if (!checkCompileErrors(compute, "COMPUTE"))
        return false;

    // Shader Program
    m_id = glCreateProgram();
    glAttachShader(m_id, compute);

    glLinkProgram(m_id);
    if (!checkCompileErrors(m_id, "PROGRAM"))
        return false;

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(compute);

    return true;
}

void GLShader::use()
{
    glUseProgram(m_id);
}

void GLShader::setFloat(const GLchar *name, GLfloat value, GLboolean useShader)
{
    if (useShader)
        this->use();
    glUniform1f(glGetUniformLocation(this->m_id, name), value);
}
void GLShader::setInteger(const GLchar *name, GLint value, GLboolean useShader)
{
    if (useShader)
        this->use();
    glUniform1i(glGetUniformLocation(this->m_id, name), value);
}
void GLShader::setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->m_id, name), x, y);
}
void GLShader::setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
{
    if (useShader)
        this->use();
    glUniform2f(glGetUniformLocation(this->m_id, name), value.x, value.y);
}
void GLShader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->m_id, name), x, y, z);
}
void GLShader::setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
{
    if (useShader)
        this->use();
    glUniform3f(glGetUniformLocation(this->m_id, name), value.x, value.y, value.z);
}
void GLShader::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->m_id, name), x, y, z, w);
}
void GLShader::setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
{
    if (useShader)
        this->use();
    glUniform4f(glGetUniformLocation(this->m_id, name), value.x, value.y, value.z, value.w);
}
void GLShader::setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
    if (useShader)
        this->use();
    glUniformMatrix4fv(glGetUniformLocation(this->m_id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

bool GLShader::checkCompileErrors(GLuint object, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);
            qDebug() << "| ERROR::SHADER: Compile-time error: Type: " << type.c_str() << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- ";
            return false;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);
            qDebug() << "| ERROR::Shader: Link-time error: Type: " << type.c_str() << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- ";
            return false;
        }
    }
    return true;
}
