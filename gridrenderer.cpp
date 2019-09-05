#include "gridrenderer.h"
#include "glshader.h"

#include <QDebug>

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    m_shader = new GLShader();

    if (!m_shader->compileRenderingShader("simple.vert", "simple.frag"))
        qFatal("No such shader files...");

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

    glGenVertexArrays(1, &m_triangleVAO);
    glBindVertexArray(m_triangleVAO);

    glGenBuffers(1, &m_triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GridRenderer::paintGL()
{
    glClearColor(0.4f, 0.4f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_triangleVAO);
    m_shader->use();

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFinish();
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
