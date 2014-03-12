//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GLSkel3D.h"
#include "Malla.h"
#include "VerticeNormal.h"
#include "PV3D.h"
#include "Cara.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm3D *GLForm3D;

Malla* malla;

//---------------------------------------------------------------------------

__fastcall TGLForm3D::TGLForm3D(TComponent* Owner): TForm(Owner) {}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TGLForm3D::FormCreate(TObject *Sender) {
    hdc=GetDC(Handle);
    SetPixelFormatDescriptor();
    hrc=wglCreateContext(hdc);
    if(hrc==NULL) ShowMessage("Error CreateContex");
    if(wglMakeCurrent(hdc, hrc)==false) ShowMessage("Error MakeCurrent");

    crearObjetosEscena();

    glClearColor(0.6,0.7,0.8,1.0);
    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);   //Defecto

    //C�mara
    eyeX=100.0; eyeY=100.0; eyeZ=100.0;
    lookX=0.0; lookY=0.0; lookZ=0.0;
    upX=0; upY=1; upZ=0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

    //Volumen de vista
    N=1; F=1000;
    xRight=10; xLeft=-xRight;
    yTop=10; yBot=-yTop;

    //Ratio del volumen de vista =1
    //ClientWidth=400;
    //ClientHeight=400;
    RatioViewPort=1.0;


// Creamos una malla

    int numVertices = 4;
    
    PV3D** vertice = new PV3D*[numVertices];
    vertice[0] = new PV3D(0,0,0);
    vertice[1] = new PV3D(1,0,0);
    vertice[2] = new PV3D(0,1,0);
    vertice[3] = new PV3D(0,0,1);

    int numNormales = 4;

    PV3D** normal = new PV3D*[numNormales];
    normal[0] = new PV3D(0.577,0.577,0.577);
    normal[1] = new PV3D(0,0,-1);
    normal[2] = new PV3D(-1,0,0);
    normal[3] = new PV3D(0,-1,0);

    int numVerticeNormal = 3;

    VerticeNormal** arrayVN0 = new VerticeNormal*[numVerticeNormal];
    arrayVN0[0] = new VerticeNormal(1,0);
    arrayVN0[1] = new VerticeNormal(2,0);
    arrayVN0[2] = new VerticeNormal(3,0);

    VerticeNormal** arrayVN1 = new VerticeNormal*[numVerticeNormal];
    arrayVN1[0] = new VerticeNormal(0,1);
    arrayVN1[1] = new VerticeNormal(2,1);
    arrayVN1[2] = new VerticeNormal(1,1);

    VerticeNormal** arrayVN2 = new VerticeNormal*[numVerticeNormal];
    arrayVN2[0] = new VerticeNormal(0,2);
    arrayVN2[1] = new VerticeNormal(3,2);
    arrayVN2[2] = new VerticeNormal(2,2);

    VerticeNormal** arrayVN3 = new VerticeNormal*[numVerticeNormal];
    arrayVN3[0] = new VerticeNormal(1,3);
    arrayVN3[1] = new VerticeNormal(3,3);
    arrayVN3[2] = new VerticeNormal(0,3);

    int numCaras = 4;

    Cara** cara = new Cara*[numCaras];
    cara[0] = new Cara(3,arrayVN0);
    cara[1] = new Cara(3,arrayVN1);
    cara[2] = new Cara(3,arrayVN2);
    cara[3] = new Cara(3,arrayVN3);

    malla = new Malla(numVertices, vertice, numNormales, normal, numCaras, cara);

// Fin crear malla
    
    //Luz0
    glEnable(GL_LIGHT0);
    GLfloat LuzDifusa[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
    GLfloat LuzAmbiente[]={0.3,0.3,0.3,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    GLfloat PosicionLuz0[]={25.0, 25.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, PosicionLuz0);
}

//---------------------------------------------------------------------------


void __fastcall TGLForm3D::SetPixelFormatDescriptor() {
    PIXELFORMATDESCRIPTOR pfd = {
    	sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0 };
    int PixelFormat=ChoosePixelFormat(hdc,&pfd);
    SetPixelFormat(hdc,PixelFormat,&pfd);
}

//---------------------------------------------------------------------------

void __fastcall TGLForm3D::FormResize(TObject *Sender) {
    //Se actualiza puerto de vista y ratio
    if ((ClientHeight<=1.0) || (ClientHeight<=1.0)) {
        ClientWidth=400;
        ClientHeight=400;
        RatioViewPort=1.0;
    }
    else RatioViewPort=(GLfloat)ClientWidth/(GLfloat)ClientHeight;

    glViewport(0,0,ClientWidth,ClientHeight);

    //Se actualiza el volumen de vista
    //para que su ratio coincida con RatioViewPort
    GLfloat RatioVolVista=xRight/yTop;

    if (RatioVolVista>=RatioViewPort) {
     //Aumentamos yTop-yBot
     yTop=xRight/RatioViewPort;
     yBot=-yTop;
     }
    else {
     //Aumentamos xRight-xLeft
     xRight=RatioViewPort*yTop;
     xLeft=-xRight;
     }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xLeft, xRight, yBot, yTop, N, F);

GLScene();
}

//---------------------------------------------------------------------------


void __fastcall TGLForm3D::GLScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Dibujo de los ejes
    glBegin(GL_LINES);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);

        glColor4f(0.0, 1.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);

        glColor4f(0.0, 0.0, 1.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 10.0);
    glEnd();

    //Dibujo de la esfera blanca
    glColor3f(1.0, 1.0, 1.0);
    gluQuadricDrawStyle(esfera, GLU_FILL);
    gluSphere(esfera, 3, 30, 30); 

    malla->dibuja();

    //glFlush();
    SwapBuffers(hdc);
}

//---------------------------------------------------------------------------


void __fastcall TGLForm3D::FormPaint(TObject *Sender) {
    GLScene();
}

//---------------------------------------------------------------------------


void __fastcall TGLForm3D::FormDestroy(TObject *Sender) {
    liberarObjetosEscena();
    ReleaseDC(Handle,hdc);
    wglMakeCurrent(NULL,NULL);
    wglDeleteContext(hrc);

    delete malla;
}

//---------------------------------------------------------------------------


void TGLForm3D::crearObjetosEscena() {
    esfera=gluNewQuadric();
}

//---------------------------------------------------------------------------


void TGLForm3D::liberarObjetosEscena() {
    gluDeleteQuadric(esfera);
}

