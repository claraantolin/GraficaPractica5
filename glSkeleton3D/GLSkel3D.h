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
#include "Lista.h"
#include "RollerCoaster.h"
#include "Coche.h"

//---------------------------------------------------------------------------
class TGLForm3D : public TForm
{
__published:	//IDE-managed Components
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormPaint(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);

private:        //User declarations
    HDC hdc;
    HGLRC hrc;
    GLfloat eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ; //Cámara
    GLdouble RatioViewPort, xLeft, xRight, yBot, yTop, N, F;  //Volumen de vista
    
    GLUquadricObj* esfera;  //Esfera inicial de la escena
    RollerCoaster* rollerCoaster;
    Malla* malla;
    Coche* coche;
    int modo;   // si es 0 no se dibujan las normales, si es 1 se dibujan las normales
    
    void __fastcall SetPixelFormatDescriptor();
    void __fastcall GLScene();
    void crearObjetosEscena();
    void liberarObjetosEscena();
    PV3D* multiplicaMatrices(Lista<PV3D*>* m, PV3D* p);
    GLfloat** devuelveM(GLfloat t, GLfloat r);
    Lista<PV3D*>* hazMatriz(GLfloat t, GLfloat r);

public:		//User declarations
    __fastcall TGLForm3D(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGLForm3D *GLForm3D;
//---------------------------------------------------------------------------
#endif
