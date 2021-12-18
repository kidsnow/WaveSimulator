#include "shader.h"

#include <iostream>


Shader::Shader() :
	id_(0)
{
}

Shader::~Shader()
{
	glDeleteProgram(id_);
}


Shader& Shader::Use()
{
    glUseProgram(this->id_);
    return *this;
}

GLchar* ReadShader(const char* fileName) {
    FILE* infile = fopen(fileName, "rb");
    if (!infile) {
        std::cerr << "Unable to open file '" << fileName << "'" << std::endl;
        return NULL;
    }

    fseek(infile, 0, SEEK_END);
    int len = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    GLchar* source = (GLchar*)malloc((len + 1) * sizeof(GLchar));

    fread(source, 1, len, infile);
    fclose(infile);

    source[len] = 0;

    return source;
}

bool Shader::CompileRenderingShader(const char* vsFileName, const char* psFileName, const char* gsFileName)
{
    GLuint sVertex, sFragment, gShader;

    const GLchar* vertexSource = ReadShader(vsFileName);
    if (vertexSource == NULL)
        return false;
    const GLchar* fragmentSource = ReadShader(psFileName);
    if (fragmentSource == NULL)
        return false;
    const GLchar* geometrySource = nullptr;
    if (gsFileName != nullptr)
    {
        geometrySource = ReadShader(gsFileName);
        if (geometrySource == NULL)
            return false;
    }

    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    if (!CheckCompileErrors(sVertex, "VERTEX"))
        return false;
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    if (!CheckCompileErrors(sFragment, "FRAGMENT"))
        return false;
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        if (!CheckCompileErrors(gShader, "GEOMETRY"))
            return false;
    }
    this->id_ = glCreateProgram();
    glAttachShader(this->id_, sVertex);
    glAttachShader(this->id_, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(this->id_, gShader);
    glLinkProgram(this->id_);
    if (!CheckCompileErrors(this->id_, "PROGRAM"))
        return false;
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);


    const int MAX_SHADER_COUNT = 10;
    GLuint	  shaders[MAX_SHADER_COUNT];
    GLsizei	  count;
    glGetAttachedShaders(id_, MAX_SHADER_COUNT, &count, shaders);

    for (int i = 0; i < count; i++)
    {
        GLint param;
        glGetShaderiv(shaders[i], GL_DELETE_STATUS, &param);
    }

    return true;
}

bool Shader::CompileComputingShader(const char* csFileName)
{
    const GLchar* computeSource = ReadShader(csFileName);
    GLuint sCompute;
    sCompute = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(sCompute, 1, &computeSource, NULL);
    glCompileShader(sCompute);
    if (!CheckCompileErrors(sCompute, "COMPUTE"))
        return false;

    this->id_ = glCreateProgram();
    glAttachShader(this->id_, sCompute);
    glLinkProgram(this->id_);
    if (!CheckCompileErrors(this->id_, "PROGRAM"))
        return false;
    glDeleteShader(sCompute);
    return true;
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniform1f(glGetUniformLocation(this->id_, name), value);
}
void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniform1i(glGetUniformLocation(this->id_, name), value);
}
void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->id_, name), x, y);
}
void Shader::SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniform2f(glGetUniformLocation(this->id_, name), value.x, value.y);
}
void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->id_, name), x, y, z);
}
void Shader::SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniform3f(glGetUniformLocation(this->id_, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->id_, name), x, y, z, w);
}
void Shader::SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniform4f(glGetUniformLocation(this->id_, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix2(const GLchar* name, const glm::mat2& matrix, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniformMatrix2fv(glGetUniformLocation(this->id_, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::SetMatrix3(const GLchar* name, const glm::mat3& matrix, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniformMatrix3fv(glGetUniformLocation(this->id_, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader)
{
    if (useShader)
        this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->id_, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


bool Shader::CheckCompileErrors(GLuint object, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
            return false;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
            return false;
        }
    }
    return true;
}