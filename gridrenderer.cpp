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
