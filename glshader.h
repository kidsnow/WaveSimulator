#ifndef GLSHADER_H
#define GLSHADER_H

#include <QOpenGLExtraFunctions>
#include <glm/glm.hpp>

class GLShader : public QOpenGLExtraFunctions
{
public:
    // Constructor
    GLShader() { initializeOpenGLFunctions(); }
    // Sets the current shader as active
    void use();
    // Compiles the shader from given source code
    const GLchar* readShader(const char *fileName);
    bool    compileRenderingShader(const char *vsFileName, const char *fsFileName, const char *gsFileName = nullptr); // Note: geometry source code is optional
    bool	compileComputingShader(const char *csFileName);
    // Utility functions
    void    setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
    void    setInteger(const GLchar *name, GLint value, GLboolean useShader = false);
    void    setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void    setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
    void    setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void    setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
    void    setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void    setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
    void    setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
    // State
    GLuint m_id;
    // Checks if compilation or linking failed and if so, print the error logs
    bool    checkCompileErrors(GLuint shader, std::string type);
};

#endif // GLSHADER_H
