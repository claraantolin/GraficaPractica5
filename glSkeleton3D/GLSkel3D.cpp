//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GLSkel3D.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"
TGLForm3D *GLForm3D;

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

    //Cámara
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
        glColor4d(1.0, 0.0, 0.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(10.0, 0.0, 0.0);

        glColor4d(0.0, 1.0, 0.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 10.0, 0.0);

        glColor4d(0.0, 0.0, 1.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 10.0);
    glEnd();


    
    rollerCoaster->setColor(0,0,1);
    rollerCoaster->dibujaRoller(modoNormales, modoTransparencia);

    coche->setColor(0.1,0.9,0.1);
    coche->dibujaCoche(modoNormales, 0);

    //Dibujo de la esfera blanca
    /*glColor3d(1.0, 1.0, 1.0);
    gluQuadricDrawStyle(esfera, GLU_FILL);
    gluSphere(esfera, 3, 30, 30); */

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
}

//---------------------------------------------------------------------------

void TGLForm3D::crearObjetosEscena() {
    esfera = gluNewQuadric();
    rollerCoaster = new RollerCoaster(10,30);
    coche = new Coche(4,2);
    coche->incrementaPos();
    modoNormales = 0;
    modoTransparencia = 1;
}

//---------------------------------------------------------------------------

void TGLForm3D::liberarObjetosEscena() {
    gluDeleteQuadric(esfera);
    delete rollerCoaster;
    delete coche;
}

//---------------------------------------------------------------------------



void __fastcall TGLForm3D::FormKeyPress(TObject *Sender, char &Key)
{

    switch(Key){

        // Rotacion con respecto al eje y (verde)
        case '8':   // Sentido de las agujas del rejor
            rollerCoaster->rotaRoller(0);
            coche->rotaCoche(0);
            break;
        case '2':   // Contrario a las agujas del reloj
            rollerCoaster->rotaRoller(1);
            coche->rotaCoche(1);
            break;
        
        // Rotacion con respecto al eje x (rojo)
        case '6':
            rollerCoaster->rotaRoller(2);
            coche->rotaCoche(2);
            break;
        case '4':
            rollerCoaster->rotaRoller(3);
            coche->rotaCoche(3);
            break;
        
        // Rotacion con respecto al eje z (azul)
        case 'a':
            rollerCoaster->rotaRoller(4);
            coche->rotaCoche(4);
            break;
        case 'z':
            rollerCoaster->rotaRoller(5);
            coche->rotaCoche(5);
            break;
        
        // Mostrar la montaña rusa en forma de malla o de armazon
        case 'g':   // Se dibuja el armazon
            modoTransparencia = 0;
            break;
        case 'h':   // Se dibujan las rayas
            modoTransparencia = 1;
            break;

        // Teclas para mostrar o no las normales
        case 'j':   // Se muestran las normales
            modoNormales = 1;
            break;
        case 'k':   // Se ocultan las normales
            modoNormales = 0;
            break;

        //Movimiento del coche
        case 'q':
            coche->incrementaPos();
            break;
        case 'w':   
            coche->decrementaPos();
            break;
        
        default:
            break;
    }

    GLScene();
}

//---------------------------------------------------------------------------

