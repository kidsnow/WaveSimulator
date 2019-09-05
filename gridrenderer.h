#pragma once

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>

class GLShader;

class GridRenderer : public QOpenGLWidget,
                     protected QOpenGLExtraFunctions
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
    GLuint m_triangleVAO;
    GLuint m_triangleVBO;
    GLShader *m_shader;
};
