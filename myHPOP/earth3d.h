#ifndef EARTH3D_H
#define EARTH3D_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QIcon>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include"earth2d.h"

class Earth3D : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Earth3D(Earth2D *earth,QWidget *parent = 0);
    ~Earth3D();

    GLuint                          m_uiTexNum;
    QOpenGLTexture          *       m_pTextures;
    QOpenGLShaderProgram    *       m_pProgram;
    QVector<float>                  m_pVertices;
    int                             m_iCount;
    QTimer                          m_timer;

    bool drawOrbit=false;//是否含轨道数据
    QVector<float> orbitVertices;
    QVector<float> todOrbitVertices;
    int orbitCount;

    QOpenGLVertexArrayObject VAO1;//绘制地球
    QOpenGLVertexArrayObject VAO2;//绘制ECF轨道
    QOpenGLVertexArrayObject VAO3;//绘制TOD轨道

protected:
    void        initializeGL();
    void        paintGL();
    void        resizeGL(int w, int h);

    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    double spinAnglez=0;
//    double spinAngley=0;

    double zoomMagnification=2;
    QVector2D mousePos;

    Earth2D *earth2D=nullptr;
    float PI=acos(-1.0);

    double EarthRotation=0;
    double EarthOmega=2*PI/86400.0;

    bool includedEarthRotation=false;
    void SetToolBar();//设置工具栏
    QToolBar* earth3DToolBar;

public slots:
    void        OnTimer(void);
    void axisTranslateSlot();
};

#endif // EARTH3D_H
