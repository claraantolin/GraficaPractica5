//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "GLSkel3D.h"
#define PI 3.14159265

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
    /*glBegin(GL_LINES);
        glColor4d(1.0, 0.0, 0.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(10.0, 0.0, 0.0);

        glColor4d(0.0, 1.0, 0.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 10.0, 0.0);

        glColor4d(0.0, 0.0, 1.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 10.0);
    glEnd();*/


    int radio = 1;
    int valor = 0;


    Lista<Lista<PV3D*>*>* poligonos = new Lista<Lista<PV3D*>*>();
    int lados = 50;
    for(int valor=0; valor<15; valor++){
        float t = (2* M_PI * valor) / 15.0;

        Lista<PV3D*>* matriz = hazMatriz(t,7);  
        Lista<PV3D*>* poligono = new Lista<PV3D*>();

        glColor4d(0,3,0, 1.0);
        glBegin(GL_LINE_LOOP);
            double inc=(2*PI/lados);
            for(int i=0; i<lados; i++){
                PV3D* nodo = new PV3D(radio*cos(2*PI-i*inc) , radio*sin(2*PI-i*inc),0,1);
                poligono->ponElem(nodo);
                //glVertex3d(radio*cos(2*PI-i*inc) , radio*sin(2*PI-i*inc),0) ;
            }
        glEnd();

        glColor4d(0.0, 0.0, 0, 1.0);
        glBegin(GL_POINTS);
        for(int t=0; t<1000; t++){
           //glVertex3d(3*cos(t), 2 * cos(1.5*t), 3*sin(t));
           glVertex3d(7*cos(t), 0, 7*sin(t));
        }
        glEnd();

        Lista<PV3D*>* poligonoAux = new Lista<PV3D*>();
        glColor4d(1,0,1, 1.0);
        glBegin(GL_LINE_LOOP);
            for(int i=0; i<lados; i++){
                PV3D* res = multiplicaMatrices(matriz, poligono->iesimo(i));
                poligonoAux->ponElem(res);
                
                glVertex3d(res->getX(), res->getY(), res->getZ());
             
            }
        glEnd();

        poligonos->ponElem(poligonoAux);

        delete matriz; delete poligono;
    }

    Lista<PV3D*>* poligono1;
    Lista<PV3D*>* poligono2;
    for(int j = 0; j < 15; j++){
        int n = 3;
        poligono1 = poligonos->iesimo(j%15);
        poligono2 = poligonos->iesimo((j+1)%15);
        
        for(int i = 0 ; i < lados-1; i++){
            glColor4d(0,3,0, 1.0);
            glBegin(GL_LINE_LOOP);
                PV3D* p1 = poligono1->iesimo(i);
                PV3D* p3 = poligono2->iesimo(i);
                glVertex3d(p3->getX(),p3->getY(),p3->getZ());
                glVertex3d(p1->getX(),p1->getY(),p1->getZ());
            glEnd();

            glColor4d(0,3,0, 1.0);
            glBegin(GL_LINES);
                PV3D* p2 = poligono1->iesimo(i+1);
                PV3D* p4 = poligono2->iesimo(i+1);
                glVertex3d(p2->getX(),p2->getY(),p2->getZ());
                glVertex3d(p4->getX(),p4->getY(),p4->getZ());
            glEnd();

        }
    }

    //delete poligonos;

    //Dibujo de la esfera blanca
    /*glColor3d(1.0, 1.0, 1.0);
    gluQuadricDrawStyle(esfera, GLU_FILL);
    gluSphere(esfera, 3, 30, 30); */

    //malla->dibuja();

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

// Creamos una malla
    
    // Creamos los vertices
    int numVertices = 4;

    PV3D** vertice = new PV3D*[numVertices];
    vertice[0] = new PV3D(0,0,0);
    vertice[1] = new PV3D(1,0,0);
    vertice[2] = new PV3D(0,1,0);
    vertice[3] = new PV3D(0,0,1);

    // Creamos las caras

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

    //Creamos la malla

    int numNormales = 4;

    malla = new Malla(numVertices, vertice, numNormales, new PV3D*[numNormales], numCaras, cara);

    // Calculamos la normal para cada cara de la malla
    malla->RellenaVectorNormalPorNewell();

// Fin crear malla


}

//---------------------------------------------------------------------------


void TGLForm3D::liberarObjetosEscena() {
    gluDeleteQuadric(esfera);
    delete malla;
}

//---------------------------------------------------------------------------

Lista<PV3D*>* TGLForm3D::hazMatriz(GLfloat t, GLfloat r){

        Lista<PV3D*>* matriz = new Lista<PV3D*>();

        //PV3D* n = new PV3D(-1 * cos(t),0, sin(t), 0);
        //PV3D* b = new PV3D(0,-1, 0, 0);
        //PV3D* tM = new PV3D(-1 * sin(t),0, cos(t), 0);
        //PV3D* c = new PV3D(r * cos(t),0, r*sin(t), 1);

        PV3D* n = new PV3D(-1 * cos(t),0, -sin(t), r* cos(t));
        PV3D* b = new PV3D(0,-1, 0, 0);
        PV3D* tM = new PV3D(-sin(t),0, cos(t),  r*sin(t));
        PV3D* c = new PV3D(0,0,0, 1);

        matriz->ponElem(n); matriz->ponElem(b); matriz->ponElem(tM); matriz->ponElem(c); 

        return matriz;
}

PV3D* TGLForm3D::multiplicaMatrices(Lista<PV3D*>* m, PV3D* p){


        PV3D* n = m->iesimo(0);
        GLfloat xPrima = n->getX() * p->getX() + n->getY() * p->getY() + n->getZ() * p->getZ() + n->getW() * p->getW();

        PV3D* b = m->iesimo(1);
        GLfloat yPrima = b->getX() * p->getX() + b->getY() * p->getY() + b->getZ() * p->getZ() + b->getW() * p->getW();

        PV3D* t = m->iesimo(2);
        GLfloat zPrima = t->getX() * p->getX() + t->getY() * p->getY() + t->getZ() * p->getZ() + t->getW() * p->getW();

        PV3D* c = m->iesimo(3);
        GLfloat wPrima = c->getX() * p->getX() + c->getY() * p->getY() + c->getZ() * p->getZ() + c->getW() * p->getW();

        return new PV3D(xPrima, yPrima, zPrima, wPrima);

}

