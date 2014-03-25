//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef MallaH
#define MallaH

#include <gl\gl.h>
#include <gl\glu.h>

#include "PV3D.h"
#include "Cara.h"
#include "Lista.h"
//---------------------------------------------------------------------------
class Malla
{
   protected:
    
        int numVertices;
        Lista<PV3D*>* vertices;
        int numNormales; //=numCaras, frecuentemente
        Lista<PV3D*>* normales;
        int numCaras;
        Lista<Cara*>* caras;

        GLdouble anguloX, anguloY, anguloZ;
        GLdouble colorR, colorG, colorB;

   public:
        
        Malla();
        Malla(int inumV, Lista<PV3D*>* v, int numN, Lista<PV3D*>* n, int numC, Lista<Cara*>* c){
            numVertices = inumV; vertices = v;
            numNormales = numN;  normales = n;
            numCaras = numC;     caras = c;
            anguloX = 0.0f; anguloY = 0.0f; anguloZ = 0.0f;
            colorR = 0; colorG = 0; colorB = 1.0;
        };
        
        ~Malla(){
            
            delete vertices;
            delete normales;
            delete caras;

            numVertices = 0;
            numNormales = 0;
            numCaras = 0;

            anguloX = 0;
            anguloY = 0;
            anguloZ = 0;

            colorR = 0;
            colorG = 0;
            colorB = 0;
            
        };

 //------------------------------------------------------------------------------
                        /***** SEtters *****/
//------------------------------------------------------------------------------

        void setColor(GLdouble r, GLdouble g, GLdouble b){
             colorR = r; colorG = g; colorB = b;
        }


//------------------------------------------------------------------------------
                        /***** RellenaVectorNormalPorNewell *****/
//------------------------------------------------------------------------------

        void RellenaVectorNormalPorNewell(){
        
            Cara* c; GLdouble x; GLdouble y; GLdouble z;
            PV3D* vertActual; PV3D* vertSiguiente;

            for(int pos = 0; pos < numCaras; pos++){

                c = caras->iesimo(pos);
                x = 0; y = 0; z = 0;

                for(int i = 0; i < c->getNumVertices(); i++){

                    GLdouble a = c->getIndiceVertice(i);
                    GLdouble b = c->getIndiceVertice((i+1) % c->getNumVertices());
                    vertActual = vertices->iesimo(a);
                    vertSiguiente = vertices->iesimo(b);
                    x += (vertActual->getY() - vertSiguiente->getY()) * (vertActual->getZ() + vertSiguiente->getZ());
                    y += (vertActual->getZ() - vertSiguiente->getZ()) * (vertActual->getX() + vertSiguiente->getX());
                    z += (vertActual->getX() - vertSiguiente->getX()) * (vertActual->getY() + vertSiguiente->getY());

                }

                PV3D* n = new PV3D(x,y,z);
                n->normaliza();
                normales->ponElem(n);
            }

        }// CalculoVectorNormalPorNewell                    

//------------------------------------------------------------------------------
                        /***** dibuja *****/
//------------------------------------------------------------------------------
        
        void dibuja(int modoN, int modoT){
 
            GLdouble normalX, normalY, normalZ;
            GLdouble verticeX, verticeY, verticeZ;
            
            // Dibuja con la rotacion dada por los angulos
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glRotatef(anguloX, 1.0, 0.0, 0.0);
            glRotatef(anguloY, 0.0, 1.0, 0.0);
            glRotatef(anguloZ, 0.0, 0.0, 1.0);

            for (int i = 0; i < numCaras; i++){
                                     
                    glLineWidth(1.0);

                    if(modoT == 0)
                        glBegin(GL_POLYGON);
                    else
                        glBegin(GL_LINE_LOOP);

                    for (int j = 0; j < caras->iesimo(i)-> getNumVertices(); j++) {

                        Cara* cara = caras->iesimoOpt(i);
                        int iN = cara->getIndiceNormal(j);
                        int iV = cara->getIndiceVertice(j);

                        PV3D* normal = normales->iesimoOpt(iN);
                        normalX = normal->getX();
                        normalY = normal->getY();
                        normalZ = normal->getZ();
                        
                        // Le asignamos una normal a cada vertice
                        glNormal3d(-normalX,-normalY,-normalZ);
                             
                        //Si hubiera coordenadas de textura, aqui se suministrarian
                        //las coordenadas de textura del vertice j con glTexCoor2f(...);

                        PV3D* vertice = vertices->iesimoOpt(iV);
                        verticeX = vertice->getX();
                        verticeY = vertice->getY();
                        verticeZ = vertice->getZ();

                        // Pintamos cada vertice
                        glColor3d(colorR,colorG,colorB);
                        glVertex3d(verticeX,verticeY,verticeZ);

                    } // for 2

                    glEnd();

                    // Dibujamos las normales
                    if(modoN == 1){
                        glBegin(GL_LINES);
                            glColor3d(3,3,3);
                            glVertex3d(verticeX,verticeY,verticeZ);
                            glVertex3d(verticeX-normalX,verticeY-normalY,verticeZ-normalZ);
                        glEnd();
                    }

            }// for 1
            
            glPopMatrix();

        }// Dibuja
};

#endif