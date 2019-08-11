#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class QOpenGLShaderProgram;

class GridRenderer : public QOpenGLWidget,
                     protected QOpenGLFunctions
{
public:
    GridRenderer(QWidget *parent = 0);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};
