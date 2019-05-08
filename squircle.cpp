#include "squircle.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

//! [7]
Squircle::Squircle()
    : m_t(0)
    , m_renderer(0)
{
    connect(this, &QQuickItem::windowChanged, this, &Squircle::handleWindowChanged);
}
//! [7]

//! [8]
void Squircle::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void Squircle::testChangeGeometry()
{
    m_renderer->testChangeGeometry();
}

void Squircle::updateTriangleGeometry(QVector<float> values, const int mode)
{
//    if (mode == 0)
//        m_renderer->updateTriangle(values);
//    if (mode == 1)
//        m_renderer->updateArrow(values);
    switch(mode)
    {
    case 0:
        //strValues = QString::number(values[0]) + " " + QString::number(values[1]);
        m_renderer->updateArrow(values);
        break;
    case 1:
        //strValues = QString::number(values[0]);
        m_renderer->updateTriangle(values);
        break;
    case 2:
        //strValues = QString::number(values[0]) + " " + QString::number(values[1]) + "\nscale:10x";
        m_renderer->updateArrow(values);
        break;
    }
}
//! [8]

//! [1]
void Squircle::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &Squircle::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &Squircle::cleanup, Qt::DirectConnection);
//! [1]
        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
//! [3]
        win->setClearBeforeRendering(false);
    }
}


//! [3]

//! [6]
void Squircle::cleanup()
{
    if (m_renderer) {
        delete m_renderer;
        m_renderer = 0;
    }
}

SquircleRenderer::~SquircleRenderer()
{
    delete m_program;
}

void SquircleRenderer::setWindow(QQuickWindow *window)
{
    m_window = window;

    //glViewport(0, 0, m_width, m_height);
}

void SquircleRenderer::testChangeGeometry()
{
    if(!this->changed)
    {
        vertices[0].setX(1);    vertices[0].setY(0); vertices[0].setZ(-3);
        vertices[1].setX(0);    vertices[1].setY(0); vertices[1].setZ(-3);
        vertices[2].setX(-1);    vertices[2].setY(0); vertices[2].setZ(-3);
        this->changed = 1;
    }
    else {
        //vertices << QVector3D(1, 0, -1) << QVector3D(0, 1, -1) << QVector3D(-1, 0, -1);
        vertices[0].setX(1);        vertices[0].setY(0);    vertices[0].setZ(-3);
        vertices[1].setX(0);        vertices[1].setY(1);    vertices[1].setZ(-3);
        vertices[2].setX(-1);       vertices[2].setY(0);    vertices[2].setZ(-3);
        this->changed = 0;
    }
}

void SquircleRenderer::updateTriangle(QVector<float> values)
{
    if (!values.size())
        return;
    /* Просто линия */
    vertices[0].setX(1);        vertices[0].setY(0);    vertices[0].setZ(-3);
    vertices[1].setX(-1);        vertices[1].setY(0);    vertices[1].setZ(-3);
    /* Рисуем текущее положение */
    vertices[2].setX(-1);       vertices[2].setY(2*values[0]);    vertices[2].setZ(-3);
}

void SquircleRenderer::updateArrow(QVector<float> values)
{
    if(values.size() < 2)
        return;
    float x = values[0];
    float y = values[1];
    float coeff = 0.05f;
    /* Центр */
    vertices[0].setX(y*coeff);   vertices[0].setY(x*coeff);    vertices[0].setZ(-3);
    vertices[1].setX(-y*coeff);   vertices[1].setY(-x*coeff);    vertices[1].setZ(-3);
    /* Вектор направления */

    vertices[2].setX(x);   vertices[2].setY(y);    vertices[2].setZ(-3);

}


//! [6]

//! [9]
void Squircle::sync()
{
    if (!m_renderer) {
        m_renderer = new SquircleRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &SquircleRenderer::paint, Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setWindow(window());

}
//! [9]

//! [4]
void SquircleRenderer::paint()
{
    if (!m_program) {
        initializeOpenGLFunctions();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glClearColor(0, 0, 0, 1);

        m_program = new QOpenGLShaderProgram();
        m_program->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex,":/vertexshader.vsh");
        m_program->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment,":/fragmentshader.fsh");
        m_program->bindAttributeLocation("vertex", 0);
        m_program->bindAttributeLocation("color",1);
        m_program->link();
        SquircleRenderer::initGeometry();

    }
//! [4] //! [5]
//!
    m_program->bind();

    int m_height = m_viewportSize.height();
    int m_width = m_viewportSize.width();
    if (m_viewportSize.height() == 0) {
        m_height = 1;
    }
    pMatrix.setToIdentity();
    pMatrix.perspective(60.0, (float) m_width / (float) m_height, 0.001, 1000);
    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;
//    if(flagCam)
//    {
        QMatrix4x4 cameraTransformation;
        cameraTransformation.rotate(alphCam, 0, 1, 0);
        cameraTransformation.rotate(betaCam, 1, 0, 0);
        QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distCam);
        QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);
        vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);
//    }

    m_program->setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);

    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);

    m_program->setAttributeArray(0,GL_FLOAT,vertices.constData(),3);
    m_program->setAttributeArray(1,GL_FLOAT,colors.constData(),3);

    m_program->setUniformValue("t", (float) m_t);

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

//    glDrawArrays(GL_TRIANGLES, 0, this->NbPointObject[0]);
//    if(this->NbPointObject.size() > 1){
//        glDrawArrays(GL_LINES, this->NbPointObject[0], this->NbPointObject[1]);
//    }
    switch(this->NbPointObject.size())
    {
    case 2:
        glDrawArrays(GL_LINES, this->NbPointObject[0], this->NbPointObject[1]);
    case 1:
        glDrawArrays(GL_TRIANGLES, 0, this->NbPointObject[0]);
    }

    m_program->disableAttributeArray("vertex");
    m_program->disableAttributeArray("color");
    m_program->release();

    m_window->resetOpenGLState();
}

void SquircleRenderer::initGeometry()
{
    //vertices << QVector3D(-0.5, -0.5,  0.5) << QVector3D( 0.5, -0.5,  0.5) << QVector3D( 0.5,  0.5,  0.5);
    vertices << QVector3D(1, 0, zeroZ) << QVector3D(0, 1, zeroZ) << QVector3D(-1, 0, zeroZ);
    colors << QVector3D(1, 1, 1) << QVector3D(1, 1, 1) << QVector3D(1, 1, 1);
    this->NbPointObject.push_back(3);
}
void SquircleRenderer::addAxes()
{
    //int count = vertices.size();
    vertices << QVector3D(1, 0, zeroZ) << QVector3D(0, 0, zeroZ)
             << QVector3D(0, 1, zeroZ) << QVector3D(0, 0, zeroZ)
             << QVector3D(0, 0, (zeroZ + 1)) << QVector3D(0, 0, zeroZ);
    colors   << QVector3D(1, 0, 0) << QVector3D(1, 0, 0)
             << QVector3D(0, 1, 0) << QVector3D(0, 1, 0)
             << QVector3D(0, 0, 1) << QVector3D(0, 0, 1);
    //count = vertices.size() - count;
    int count = vertices.size();
    this->NbPointObject.push_back(count);
}
void SquircleRenderer::addVectorBuffer()
{
    /* Только вектор */
    vertices << QVector3D(1, 1, zeroZ) << QVector3D(0, 0, zeroZ);
    colors   << QVector3D(1, 0, 1) << QVector3D(1, 0, 1);
    this->NbPointObject.push_back(vertices.size());
    /* Массив прошлых точек */
    for (int i = 0; i < this->MaxNbVectorBuffer; ++i) {
        vertices.push_back(QVector3D(0,0,0));
        colors.push_back(QVector3D(1,0,1));
    }
    this->NbPointObject.push_back(vertices.size());
}

void SquircleRenderer::updateVectorBuffer(QVector3D vec)
{
    if(NbPointObject.size() < 3)
        return;
    this->vertices[NbPointObject[1]] = vec;
    this->vertices.remove(NbPointObject[2]);
    this->vertices.insert(NbPointObject[2],vec);
}
//! [5]
