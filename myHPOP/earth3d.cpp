#include "earth3d.h"

Earth3D::Earth3D(Earth2D *earth,QWidget *parent)
    : QOpenGLWidget(parent)
{
    earth2D=earth;
    setFixedSize(600,600);
    setWindowIcon(QIcon(":/images/icon.png"));
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(OnTimer()));

    if(earth2D->satellite!=nullptr)
    {
        orbitCount=0;
        orbitVertices.resize(earth2D->longitude.size()*3);
//        qDebug()<<earth2D->longitude.size();
        for(int i=0;i<earth2D->longitude.size();i++)
        {
            orbitVertices[orbitCount++]=earth2D->longitude.at(i);
            orbitVertices[orbitCount++]=earth2D->latitude.at(i);
            orbitVertices[orbitCount++]=earth2D->h.at(i);            
        }
        orbitCount=0;
        todOrbitVertices.resize(earth2D->longitude.size()*3);
//        qDebug()<<earth2D->longitude.size();
        for(int i=0;i<earth2D->longitude.size();i++)
        {
            todOrbitVertices[orbitCount++]=earth2D->longitude.at(i)+earth2D->satellite->time.at(i)*EarthOmega;
            todOrbitVertices[orbitCount++]=earth2D->latitude.at(i);
            todOrbitVertices[orbitCount++]=earth2D->h.at(i);
        }
    }
    m_timer.start(1);

    SetToolBar();
}

void Earth3D::SetToolBar()
{
    earth3DToolBar=new QToolBar("3D窗口工具栏",this);
    earth3DToolBar->setStyleSheet("background-color: rgb(230,230,230);");
    earth3DToolBar->setIconSize(QSize(20,20));

    QAction *actionAxisTranslate=new QAction(QIcon(":/images/axis.png"),"坐标系转换");
    earth3DToolBar->addAction(actionAxisTranslate);
    connect(actionAxisTranslate,SIGNAL(triggered()),this,SLOT(axisTranslateSlot()));
}

void Earth3D::axisTranslateSlot()
{
    includedEarthRotation=!includedEarthRotation;
}

Earth3D::~Earth3D()
{
    m_timer.stop();
    m_pTextures->release();
    delete m_pTextures;
    delete m_pProgram;
}

void Earth3D::initializeGL()
{
    initializeOpenGLFunctions();
    m_iCount = 0;
    m_uiTexNum = 0;

    //给顶点赋值
    int iAngleStep = 10, iR = 1;
    m_pVertices.resize(180 / iAngleStep * 360 / iAngleStep * 6 * 3);
    for(int iLongitude = 0; iLongitude < 360; iLongitude += iAngleStep)
    {
        for(int iLatitude = 0; iLatitude < 180; iLatitude += iAngleStep)
        {
            m_pVertices[m_iCount++] = iLongitude;
            m_pVertices[m_iCount++] = iLatitude;
            m_pVertices[m_iCount++] = iR;

            m_pVertices[m_iCount++] = iLongitude;
            m_pVertices[m_iCount++] = iLatitude + iAngleStep;
            m_pVertices[m_iCount++] = iR;

            m_pVertices[m_iCount++] = iLongitude + iAngleStep;
            m_pVertices[m_iCount++] = iLatitude + iAngleStep;
            m_pVertices[m_iCount++] = iR;

            m_pVertices[m_iCount++] = iLongitude + iAngleStep;
            m_pVertices[m_iCount++] = iLatitude + iAngleStep;
            m_pVertices[m_iCount++] = iR;

            m_pVertices[m_iCount++] = iLongitude + iAngleStep;
            m_pVertices[m_iCount++] = iLatitude;
            m_pVertices[m_iCount++] = iR;

            m_pVertices[m_iCount++] = iLongitude;
            m_pVertices[m_iCount++] = iLatitude;
            m_pVertices[m_iCount++] = iR;
        }
    }

    m_pProgram = new QOpenGLShaderProgram;
    m_pProgram->addShaderFromSourceFile(QOpenGLShader::Vertex,":/shader/orbit.vert");
    m_pProgram->addShaderFromSourceFile(QOpenGLShader::Fragment,":/shader/orbit.frag");
    m_pProgram->bind();
    m_pProgram->link();

    QOpenGLBuffer VBO1(QOpenGLBuffer::VertexBuffer);

    if(VAO1.isCreated()==false)
    {
        VAO1.create();
    }
    VAO1.bind();
    VBO1.create();
    VBO1.bind();
    VBO1.allocate(m_pVertices.data(),sizeof(float)*m_pVertices.size());
    m_pProgram->setAttributeBuffer(0,GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
    m_pProgram->enableAttributeArray(0);
    QImage img(QString(":/earth/Basic.bmp"));
    m_pTextures = new QOpenGLTexture(img.mirrored());
    m_pProgram->setUniformValue("Tex", m_uiTexNum);
    m_pProgram->setUniformValue("pi", PI);
    m_pProgram->release();
    VAO1.release();

    if(earth2D->satellite!=nullptr)
    {
        if(VAO2.isCreated()==false)
        {
            VAO2.create();
        }
        QOpenGLBuffer VBO2(QOpenGLBuffer::VertexBuffer);
        VAO2.bind();
        VBO2.create();
        VBO2.bind();
        VBO2.allocate(orbitVertices.data(),sizeof(float)*orbitVertices.size());
        m_pProgram->setAttributeBuffer(0,GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
        m_pProgram->enableAttributeArray(0);
        m_pProgram->release();
        VAO2.release();

        if(VAO3.isCreated()==false)
        {
            VAO3.create();
        }
        QOpenGLBuffer VBO3(QOpenGLBuffer::VertexBuffer);
        VAO3.bind();
        VBO3.create();
        VBO3.bind();
        VBO3.allocate(todOrbitVertices.data(),sizeof(float)*todOrbitVertices.size());
        m_pProgram->setAttributeBuffer(0,GL_FLOAT, 0, 3, sizeof(GLfloat) * 3);
        m_pProgram->enableAttributeArray(0);
        m_pProgram->release();
        VAO3.release();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void Earth3D::paintGL()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //QMatrix4x4在声明时被默认为单位矩阵
    QMatrix4x4 m1, m2, m3,m4, m;//m1投影矩阵，m2观察矩阵，m3模型矩阵
    m1.ortho(-zoomMagnification, zoomMagnification, -zoomMagnification, zoomMagnification, -50.0f, 50.0f);
    m2.lookAt(QVector3D(2,0,0), QVector3D(0,0,0), QVector3D(0,0,10));
    m3.rotate(spinAnglez, 0.0f, 0.0f, 1.0f);
    m = m1 * m2 * m3 ;

    if(earth2D->satellite!=nullptr)
    {
        EarthRotation=earth2D->satellite->time.at(earth2D->mCounts)*EarthOmega;
        EarthRotation=EarthRotation*180/PI;
//        qDebug()<<EarthRotation;
        m4.rotate(spinAnglez+EarthRotation, 0.0f, 0.0f, 1.0f);
        m = m1 * m2 * m4;
    }
    m_pProgram->setUniformValue("mat4MVP", m);

    m_pProgram->bind();
    VAO1.bind();
    m_pTextures->bind();
    m_pProgram->setUniformValue("n",0);
    glDrawArrays(GL_TRIANGLES, 0, m_iCount / 3);
    m_pTextures->release();
    VAO1.release();

    if(includedEarthRotation==true)
    {
        if(earth2D->satellite!=nullptr)
        {
            if(earth2D->drawAllOrbit==true)
            {
                VAO2.bind();
                m_pProgram->setUniformValue("n",1);
                glDrawArrays(GL_LINE_STRIP,0,orbitCount/3);
                VAO2.release();
            }
            else if(earth2D->drawAllOrbit==false)//绘制卫星当前圈轨道
            {
                //绘制跨180°的轨道各圈
                if(earth2D->TurnNumber.size()!=0)
                {
                    int drawIndex;//获取当前圈
                    if(earth2D->mCounts<=earth2D->TurnNumber.at(0))
                    {
                        drawIndex=0;
                    }
                    else if(earth2D->mCounts>earth2D->TurnNumber.last())
                    {
                        drawIndex=earth2D->TurnNumber.size();
                    }
                    else
                    {
                        for(int i=0;i<earth2D->TurnNumber.size()-1;i++)
                        {
                            if(earth2D->mCounts>earth2D->TurnNumber.at(i) and earth2D->mCounts<=earth2D->TurnNumber.at(i+1))
                            {
                                drawIndex=i+1;
                            }
                        }
                    }

                    //绘制指定圈
                    if(drawIndex==0)//第一圈
                    {
                        int drawNumber=earth2D->TurnNumber.at(0)+1;
                        VAO2.bind();
                        m_pProgram->setUniformValue("n",1);
                        glDrawArrays(GL_LINE_STRIP,0,drawNumber);
                        VAO2.release();
                    }
                    else if(drawIndex==earth2D->TurnNumber.size())//最后一圈
                    {
                        int drawNumber=earth2D->longitude.size()-1-earth2D->TurnNumber.last();
                        VAO2.bind();
                        m_pProgram->setUniformValue("n",1);
                        glDrawArrays(GL_LINE_STRIP,earth2D->TurnNumber.last(),drawNumber);
                        VAO2.release();
                    }
                    else//中间各圈
                    {
                        int drawNumber=earth2D->TurnNumber.at(drawIndex)-earth2D->TurnNumber.at(drawIndex-1);
                        VAO2.bind();
                        m_pProgram->setUniformValue("n",1);
                        glDrawArrays(GL_LINE_STRIP,earth2D->TurnNumber.at(drawIndex-1),drawNumber);
                        VAO2.release();
                    }
                }
                else if(earth2D->TurnNumber.size()==0)
                {
                    VAO2.bind();
                    m_pProgram->setUniformValue("n",1);
                    glDrawArrays(GL_LINE_STRIP,0,orbitCount/3);
                    VAO2.release();
                }
            }

    //        qDebug()<<earth2D->mCounts;
            VAO2.bind();
            m_pProgram->setUniformValue("n",2);
            glDrawArrays(GL_POINTS,earth2D->mCounts,1);
            VAO2.release();
        }
    }
    else if(includedEarthRotation==false)
    {
        m = m1 * m2 * m3 ;
        m_pProgram->setUniformValue("mat4MVP", m);

        if(earth2D->satellite!=nullptr)
        {
            if(earth2D->drawAllOrbit==true)
            {
                VAO3.bind();
                m_pProgram->setUniformValue("n",1);
                glDrawArrays(GL_LINE_STRIP,0,orbitCount/3);
                VAO3.release();
            }
            else if(earth2D->drawAllOrbit==false)//绘制卫星当前圈轨道
            {
                //绘制跨180°的轨道各圈
                if(earth2D->TurnNumber.size()!=0)
                {
                    int drawIndex;//获取当前圈
                    if(earth2D->mCounts<=earth2D->TurnNumber.at(0))
                    {
                        drawIndex=0;
                    }
                    else if(earth2D->mCounts>earth2D->TurnNumber.last())
                    {
                        drawIndex=earth2D->TurnNumber.size();
                    }
                    else
                    {
                        for(int i=0;i<earth2D->TurnNumber.size()-1;i++)
                        {
                            if(earth2D->mCounts>earth2D->TurnNumber.at(i) and earth2D->mCounts<=earth2D->TurnNumber.at(i+1))
                            {
                                drawIndex=i+1;
                            }
                        }
                    }

                    //绘制指定圈
                    if(drawIndex==0)//第一圈
                    {
                        int drawNumber=earth2D->TurnNumber.at(0)+1;
                        VAO3.bind();
                        m_pProgram->setUniformValue("n",1);
                        glDrawArrays(GL_LINE_STRIP,0,drawNumber);
                        VAO3.release();
                    }
                    else if(drawIndex==earth2D->TurnNumber.size())//最后一圈
                    {
                        int drawNumber=earth2D->longitude.size()-1-earth2D->TurnNumber.last();
                        VAO3.bind();
                        m_pProgram->setUniformValue("n",1);
                        glDrawArrays(GL_LINE_STRIP,earth2D->TurnNumber.last(),drawNumber);
                        VAO3.release();
                    }
                    else//中间各圈
                    {
                        int drawNumber=earth2D->TurnNumber.at(drawIndex)-earth2D->TurnNumber.at(drawIndex-1);
                        VAO3.bind();
                        m_pProgram->setUniformValue("n",1);
                        glDrawArrays(GL_LINE_STRIP,earth2D->TurnNumber.at(drawIndex-1),drawNumber);
                        VAO3.release();
                    }
                }
                else if(earth2D->TurnNumber.size()==0)
                {
                    VAO3.bind();
                    m_pProgram->setUniformValue("n",1);
                    glDrawArrays(GL_LINE_STRIP,0,orbitCount/3);
                    VAO3.release();
                }
            }

            //        qDebug()<<earth2D->mCounts;
            VAO3.bind();
            m_pProgram->setUniformValue("n",2);
            glDrawArrays(GL_POINTS,earth2D->mCounts,1);
            VAO3.release();
        }
    }
}

void Earth3D::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void Earth3D::OnTimer(void)
{
    if(360 == spinAnglez)
    {
        spinAnglez = 0;
    }
    update();
}

void Earth3D::wheelEvent(QWheelEvent *e)
{
    if(e->delta()>0)
    {
        zoomMagnification=zoomMagnification+0.1;
    }
    else
    {
        zoomMagnification=zoomMagnification-0.1;
    }
    update();
}

void Earth3D::mousePressEvent(QMouseEvent *e)
{
    mousePos = QVector2D(e->pos());
}

void Earth3D::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton)
    {
        QVector2D newPos = (QVector2D)e->pos();
        QVector2D diff = newPos - mousePos;
        qreal anglez = diff.x()/3.6;
//        qreal angley = diff.y()/3.6;
        spinAnglez=spinAnglez+anglez;

        mousePos = newPos;
        update();
    }
}
