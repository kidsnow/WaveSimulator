#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class QOpenGLShaderProgram;

class GridRenderer : public QOpenGLWidget,
                     protected QOpenGLFunctions
{
public:
    GridRenderer(QWidget *parent);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};
