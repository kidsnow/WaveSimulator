#include "gridrenderer.h"

GridRenderer::GridRenderer(QWidget *parent) :
    QOpenGLWidget(parent)
{
}

void GridRenderer::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void GridRenderer::resizeGL(int w, int h)
{

}

void GridRenderer::paintGL()
{

}
