#include "gridrenderer.h"

GridRenderer::GridRenderer(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

QSize GridRenderer::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GridRenderer::sizeHint() const
{
    return QSize(400, 400);
}

void GridRenderer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    float position[] = {
        0.0f,  0.5f, 0.0f, //vertex 1  위 중앙
        0.5f, -0.5f, 0.0f, //vertex 2  오른쪽 아래
        -0.5f, -0.5f, 0.0f //vertex 3  왼쪽 아래
    };

    float color[] = {
        1.0f, 0.0f, 0.0f, //vertex 1 : RED (1,0,0)
        0.0f, 1.0f, 0.0f, //vertex 2 : GREEN (0,1,0)
        0.0f, 0.0f, 1.0f  //vertex 3 : BLUE (0,0,1)
    };

    GLuint bufferObject;
    glGenBuffers(1, &bufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
}

void GridRenderer::paintGL()
{

}

void GridRenderer::resizeGL(int w, int h)
{

}

void GridRenderer::mousePressEvent(QMouseEvent *event)
{

}

void GridRenderer::mouseMoveEvent(QMouseEvent *event)
{

}
