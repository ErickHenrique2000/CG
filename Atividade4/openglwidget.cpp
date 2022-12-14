#include "openglwidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

OpenGLWidget::~OpenGLWidget()
{
    destroyVBOs();
    destroyShaders();
}

void OpenGLWidget::resizeGL(int w, int h){
    update();
}

void OpenGLWidget::createShaders(){
    makeCurrent();
    destroyShaders();
    QFile vs(":/shaders/vshader.glsl");
    QFile fs(":/shaders/fshader.glsl");

    if(!vs.open(QFile::ReadOnly | QFile::Text)) return;
    if(!fs.open(QFile::ReadOnly | QFile::Text)) return;

    auto byteArrayVs{vs.readAll()};
    auto byteArrayFs{fs.readAll()};
    const char *c_strVs{byteArrayVs};
    const char *c_strFs{byteArrayFs};

    vs.close();
    fs.close();
    GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &c_strVs, 0);
    glCompileShader(vertexShader);
    GLint isCompiled{0};

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){
        GLint maxLength{0};
        glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader,maxLength,&maxLength,&infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteShader(vertexShader);
        return;
    }

    GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader,1,&c_strFs,0);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&isCompiled);

    if(isCompiled == GL_FALSE){
        GLint maxLength{0};
        glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader,maxLength,&maxLength,&infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    GLint isLinked{0};
    glGetProgramiv(shaderProgram,GL_LINK_STATUS, &isLinked);

    if(isLinked == GL_FALSE)
    {
        GLint maxLength{0};
        glGetProgramiv(shaderProgram,GL_INFO_LOG_LENGTH,&maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram,maxLength,&maxLength, &infoLog[0]);
        qDebug("%s",&infoLog[0]);
        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    glDetachShader(shaderProgram,vertexShader);
    glDetachShader(shaderProgram,fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void OpenGLWidget::destroyShaders(){
    makeCurrent();
    glDeleteProgram(shaderProgram);
}

void OpenGLWidget::createVBOs()
{
    makeCurrent();
    destroyVBOs();
    vertices.resize(4);
    colors.resize(4);
    indices.resize(6); //2*3
    vertices[0] = QVector4D(-0.5, -0.5 , 0, 1);
    vertices[1] = QVector4D( 0.5, -0.5 , 0, 1);
    vertices[2] = QVector4D( 0.5, 0.5 , 0, 1);
    vertices[3] = QVector4D(-0.5, 0.5 , 0, 1);
    // Create colors for the vertices
    colors[0] = QVector4D(1, 0, 0, 1); // Red
    colors[1] = QVector4D(0, 1, 0, 1); // Green
    colors[2] = QVector4D(0, 0, 1, 1); // Blue
    colors[3] = QVector4D(1, 1, 0, 1); // Yellow
    // Topology of the mesh ( square )
    indices[0] = 0; indices[1] = 1; indices[2] = 2;
    indices[3] = 2; indices[4] = 3; indices[5] = 0;

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glGenBuffers(1,&vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER,vboVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(QVector4D),vertices.data(),
    GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);
    glGenBuffers (1, &vboColors);
    glBindBuffer (GL_ARRAY_BUFFER,vboColors);
    glBufferData (GL_ARRAY_BUFFER,colors.size()*sizeof(QVector4D),colors.data(),
    GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);
    glGenBuffers (1, &eboIndices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indices.size() * sizeof (GLuint), indices.data() ,
    GL_STATIC_DRAW);
}

void OpenGLWidget::destroyVBOs(){
    makeCurrent ();
    glDeleteBuffers(1, &vboVertices);
    glDeleteBuffers (1, &vboColors);
    glDeleteBuffers (1, &eboIndices);
    glDeleteVertexArrays (1, &vao);
    vboVertices=0;
    eboIndices=0;
    vboColors=0;
    vao=0;

}

void OpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);

    qDebug("OpenGL Version: %s",glGetString(GL_VERSION));
    qDebug("GLSL Version: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));

    connect(&timer, &QTimer::timeout, this, &OpenGLWidget::animate);
    timer.start(0);
    elapsedTimer.start();

    createShaders();
    createVBOs();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    GLint locScaling{glGetUniformLocation(shaderProgram, "scaling")};
    GLint locTranslation{glGetUniformLocation(shaderProgram, "translation")};

    glBindVertexArray(vao);

    //Player
    glUniform4f(locTranslation, -0.8f, playerPosY, 0, 0);
    glUniform1f(locScaling, 0.2f);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    //Target
    glUniform4f(locTranslation, 0.8f, targetPosY, 0, 0);
    glUniform1f(locScaling, 0.2f);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    //projectile
    if(shotting){
        glUniform4f(locTranslation, projectilePos[0], projectilePos[1], 0, 0);
        glUniform1f(locScaling, 0.05f);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void OpenGLWidget::keyPressEvent(QKeyEvent*event){
    switch(event->key()){
        case Qt::Key_Up:
            playerPosYOffset = 2.0f;
            break;
        case Qt::Key_Down:
            playerPosYOffset = -2.0f;
            break;
        case Qt::Key_Space:
            if(!shotting){
                shotting = true;
                projectilePos[0] = -0.7;
                projectilePos[1] = playerPosY;
            }
            break;
        case Qt::Key_Escape:
            QApplication::quit();
            break;//desnecessario
    }
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Up:
            playerPosYOffset = 0.0f;
            break;
        case Qt::Key_Down:
            playerPosYOffset = 0.0f;
            break;
        }
}

void OpenGLWidget::animate(){
    float elTime{elapsedTimer.restart()/1000.0f};

    targetPosY += targetPosYOffset*elTime;

    if(targetPosYOffset > 0){
        if(targetPosY > 0.8f){
            targetPosY = 0.8f;
            targetPosYOffset *= -1;
        }
    }else{
        if(targetPosY < -0.8f){
            targetPosY = -0.8f;
            targetPosYOffset *= -1;
        }
    }

    // player

    playerPosY += playerPosYOffset*elTime;

    if(playerPosY > 0.8f) playerPosY = 0.8f;
    if(playerPosY < -0.8f) playerPosY = -0.8f;

    // tiro
    if(shotting){
        projectilePos[0] += 3.0f*elTime;
        if(projectilePos[0] > 0.8f){
            if(std::fabs(projectilePos[1] - targetPosY) < 0.125f){
                numHits++;
                qDebug("Hit!!!");
                emit updateHitsLabel(QString("#Hits: %1").arg(numHits));
                shotting = false;
            }
            if(projectilePos[0] > 1.0f){
                shotting = false;
            }
        }
    }

    update();
}


