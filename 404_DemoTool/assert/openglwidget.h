#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QBasicTimer>
#include <QOpenGLVertexArrayObject>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = 0);
    void timerEvent(QTimerEvent *e);
    ~OpenGLWidget();
    QOpenGLBuffer positionBuf;
    QOpenGLBuffer colorBuf;
    QOpenGLVertexArrayObject mObject;
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    QOpenGLShaderProgram *program;
    GLuint programId;
    GLuint matrixLocation;
    GLuint vertexLocation;
    GLuint clorLocation;
    GLuint verVbo;
    GLuint colorVbo;

    QMatrix4x4 projection;
    QMatrix4x4 matrix;

    float angle;
    QBasicTimer timer;
    GLuint vCount;
signals:

public slots:

};

#endif // OPENGLWIDGET_H
