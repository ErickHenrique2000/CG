
#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QTimer>
#include <QVector4D>
#include <vector>
#include <QFile>
#include <cmath>

#include <QApplication>
#include <QKeyEvent>

class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();

    GLuint vboVertices{0};
    GLuint vboColors{0};
    GLuint eboIndices{0};
    GLuint vao{0};
    GLuint vaoTelhado{0};
    GLuint vaoSol{0};

    std::vector<QVector4D> verticesCasa;
    std::vector<QVector4D> colorsCasa;
    std::vector<GLuint> indicesCasa;

    //std::vector<QVector4D> verticesTelhado;

    GLuint shaderProgram{0};

    void createVBOs();
    void createShaders();

    void destroyVBOs();
    void destroyShaders();

    void changeDiagonal();

    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void toggleDarkMode(bool);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QTimer timer;
    bool blinkFlag{false};
    float red{0};
    float blue{0};
    float green{0};
    int qtdVerticesSol{360};
};

#endif // OPENGLWIDGET_H