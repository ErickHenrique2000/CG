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

}

void OpenGLWidget::toggleDarkMode(bool changeToDarkMode){
    makeCurrent();
    if(changeToDarkMode){
        glClearColor(0,0,0,1);
        darkMode = true;
    }else{
        glClearColor(1,1,1,1);
        darkMode = false;
    }
    createVBOs();
    update();
}

void OpenGLWidget::createShaders(){
    makeCurrent();
    destroyShaders();
    QFile vs(":/shaders/vshader1.glsl");
    QFile fs(":/shaders/fshader1.glsl");

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

void OpenGLWidget::createVBOs(){
    makeCurrent();
    destroyVBOs();

    verticesCasa.resize(4);
    colorsCasa.resize(4);
    indicesCasa.resize(6); // 2*3 dois triangulos * tres vertices

    verticesCasa[0] = QVector4D(-0.5, -1, 0, 1);
    verticesCasa[1] = QVector4D(0.5, -1, 0, 1);
    verticesCasa[2] = QVector4D(0.5, 0, 0, 1);
    verticesCasa[3] = QVector4D(-0.5, 0, 0, 1);

    colorsCasa[0] = QVector4D(0, 0, 1, 1);
    colorsCasa[1] = QVector4D(0, 0, 1, 1);
    colorsCasa[2] = QVector4D(0, 0, 1, 1);
    colorsCasa[3] = QVector4D(0, 0, 1, 1);

    indicesCasa[0] = 0;
    indicesCasa[1] = 1;
    indicesCasa[2] = 2;
    indicesCasa[3] = 2;
    indicesCasa[4] = 3;
    indicesCasa[5] = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, verticesCasa.size()*sizeof(QVector4D), verticesCasa.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &vboColors);
    glBindBuffer (GL_ARRAY_BUFFER,vboColors);
    glBufferData (GL_ARRAY_BUFFER,colorsCasa.size()*sizeof(QVector4D),colorsCasa.data(),GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboIndices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesCasa.size() * sizeof (GLuint), indicesCasa.data() , GL_STATIC_DRAW);

    // sol

    verticesSol.resize(qtdVerticesSol + 2);
    colorsSol.resize(qtdVerticesSol + 2);
    indicesSol.resize(qtdVerticesSol * 3 + 3);

    float incXSol{0.5};
    float escalaSol{1.0};
    if(darkMode){
        incXSol=-0.5;
        escalaSol = 0.7;
    }

    int i = 0;
    for(i = 0; i <= qtdVerticesSol; i++){
        verticesSol[i] = QVector4D(std::sin(i*3.14/180)*0.3*escalaSol + incXSol, std::cos(i*3.14/180)*0.5*escalaSol + 0.5, 0, 1);
        if(!darkMode){
            colorsSol[i] = QVector4D(1, 1, 0, 1);
        }else{
            colorsSol[i] = QVector4D(192.0/255.0, 192.0/255.0, 192.0/255.0, 1);
        }

    }
    verticesSol[qtdVerticesSol+1] = QVector4D(incXSol, 0.5, 0, 1);

    if(!darkMode){
        colorsSol[qtdVerticesSol+1] = QVector4D(1, 1, 0, 1);
    }else{
        colorsSol[qtdVerticesSol+1] = QVector4D(192.0/255.0, 192.0/255.0, 192.0/255.0, 1);
    }

    int z = 0;
    for(i = 0; i <= qtdVerticesSol*3; i = i + 3){
        indicesSol[i] = z;
        indicesSol[i+1] = z+1;
        indicesSol[i+2] = qtdVerticesSol;
        z++;
    }

    glGenVertexArrays(1, &vaoSol);
    glBindVertexArray(vaoSol);

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, verticesSol.size()*sizeof(QVector4D), verticesSol.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &vboColors);
    glBindBuffer (GL_ARRAY_BUFFER,vboColors);
    glBufferData (GL_ARRAY_BUFFER,colorsSol.size()*sizeof(QVector4D),colorsSol.data(),GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboIndices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesSol.size() * sizeof (GLuint), indicesSol.data() , GL_STATIC_DRAW);

    //telhado

    verticesTelhado.resize(3);
    colorsTelhado.resize(3);
    indicesTelhado.resize(3);

    verticesTelhado[0] = QVector4D(-0.5, 0, 0, 1);
    verticesTelhado[1] = QVector4D(0, 0.5, 0, 1);
    verticesTelhado[2] = QVector4D(0.5, 0, 0, 1);

    if(!darkMode){
        colorsTelhado[0] = QVector4D(150.0/255, 75.0/255, 0, 1);
        colorsTelhado[1] = QVector4D(150.0/255, 75.0/255, 0, 1);
        colorsTelhado[2] = QVector4D(150.0/255, 75.0/255, 0, 1);
    }else{
        colorsTelhado[0] = QVector4D(118.0/255, 47.0/255, 32.0/255, 1);
        colorsTelhado[1] = QVector4D(118.0/255, 47.0/255, 32.0/255, 1);
        colorsTelhado[2] = QVector4D(118.0/255, 47.0/255, 32.0/255, 1);
    }


    indicesTelhado[0] = 0;
    indicesTelhado[1] = 1;
    indicesTelhado[2] = 2;

    glGenVertexArrays(1, &vaoTelhado);
    glBindVertexArray(vaoTelhado);

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, verticesTelhado.size()*sizeof(QVector4D), verticesTelhado.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,nullptr);
    glEnableVertexAttribArray(0);

    glGenBuffers (1, &vboColors);
    glBindBuffer (GL_ARRAY_BUFFER,vboColors);
    glBufferData (GL_ARRAY_BUFFER,colorsTelhado.size()*sizeof(QVector4D),colorsTelhado.data(),GL_STATIC_DRAW);
    glVertexAttribPointer (1, 4, GL_FLOAT , GL_FALSE , 0, nullptr);
    glEnableVertexAttribArray (1);

    glGenBuffers (1, &eboIndices);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndices);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER , indicesTelhado.size() * sizeof (GLuint), indicesTelhado.data() , GL_STATIC_DRAW);



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
    glClearColor(1,1,1,1);
    qDebug("OpenGL Version: %s",glGetString(GL_VERSION));
    qDebug("GLSL Version: %s",glGetString(GL_SHADING_LANGUAGE_VERSION));
    createShaders();
    createVBOs();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vaoSol);
    glDrawElements(GL_TRIANGLES, qtdVerticesSol*3 + 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(vaoTelhado);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


    //changeDiagonal();
}

void OpenGLWidget::changeDiagonal(){
    makeCurrent();
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER , eboIndices);
    // glMappBuffer-> mac
    auto idx{static_cast<GLuint*>(glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER , 0,
    indicesCasa.size()*sizeof(GL_UNSIGNED_INT),GL_MAP_WRITE_BIT))};
    idx[0] = 0; idx[1] = 1; idx[2] = 3;
    idx[3] = 1; idx[4] = 2; idx[5] = 3;
    glUnmapBuffer (GL_ELEMENT_ARRAY_BUFFER) ;
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent*event){
    switch(event->key()){
        case Qt::Key_Escape:
        QApplication::quit();
        break;//desnecessario
    }
}

