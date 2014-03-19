//---------------------------------------------------------------------------
#ifndef GLSkel3DH
#define GLSkel3DH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <gl\gl.h>
#include <gl\glu.h>

#include "Malla.h"
#include "VerticeNormal.h"
#include "PV3D.h"
#include "Cara.h"

//---------------------------------------------------------------------------
class TGLForm3D : public TForm
{
__published:	//IDE-managed Components
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);

private:        //User declarations
    HDC hdc;
    HGLRC hrc;
    GLfloat eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ; //C�mara
    GLdouble RatioViewPort, xLeft, xRight, yBot, yTop, N, F;  //Volumen de vista
    GLUquadricObj* esfera;  //Esfera inicial de la escena
    Malla* malla;
    PV3D** poligono;
    
    void __fastcall SetPixelFormatDescriptor();
    void __fastcall GLScene();
    void crearObjetosEscena();
    void liberarObjetosEscena();
    PV3D* multiplicaMatrices(GLfloat** m, PV3D* p);
    GLfloat** devuelveM(GLfloat t, GLfloat r);

public:		//User declarations
    __fastcall TGLForm3D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm3D *GLForm3D;
//---------------------------------------------------------------------------
#endif
