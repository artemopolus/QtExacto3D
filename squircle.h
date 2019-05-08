#ifndef SQUIRCLE_H
#define SQUIRCLE_H


#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

#include <QVector>



//! [1]
class SquircleRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    SquircleRenderer() : m_t(0), m_program(0) { }
    ~SquircleRenderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }
    void setWindow(QQuickWindow *window);
    void testChangeGeometry();
    void updateTriangle(QVector<float> values);
    void updateArrow(QVector<float> values);
    void addAxes();
    void addVectorBuffer();
    void updateVectorBuffer(QVector3D vec);
    void activateCam() {this->flagCam = 1;alphCam = 25;betaCam = -25;}

public slots:
    void paint();
private slots:
    void initGeometry();

private:
    quint8 changed = 0;
    QMatrix4x4 pMatrix;
    QVector<QVector3D> vertices;
    QVector<QVector3D> colors;
    QVector<int> NbPointObject;

    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram *m_program;
    QQuickWindow *m_window;
    float zeroZ = 0;
    double  alphCam = 0;
    double  betaCam = 0;
    double  distCam = 3.5;
    int     flagCam = 0;
    QPoint lastMousePosition;
    const int MaxNbVectorBuffer = 100;
};
//! [1]

//! [2]
class Squircle : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    Squircle();

    qreal t() const { return m_t; }
    void setT(qreal t);



signals:
    void tChanged();

public slots:
    void sync();
    void cleanup();
    void testChangeGeometry();
    void updateTriangleGeometry(QVector<float> values, const int mode);
    void setAxes(){m_renderer->addAxes(); m_renderer->activateCam();}

private slots:
    void handleWindowChanged(QQuickWindow *win);



private:

    qreal m_t;
    SquircleRenderer *m_renderer;


};
//! [2]

#endif // SQUIRCLE_H
