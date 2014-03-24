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

   public:
        
        Malla();
        Malla(int inumV, Lista<PV3D*>* v, int numN, Lista<PV3D*>* n, int numC, Lista<Cara*>* c){
            numVertices = inumV; vertices = v;
            numNormales = numN;  normales = n;
            numCaras = numC;     caras = c;
            anguloX = 0.0f; anguloY = 0.0f; anguloZ = 0.0f;
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
            
        }; 

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

            if(modoN == 1){

                glBegin(GL_LINES);
                for (int i = 0; i < numCaras; i++) {
                    for (int j = 0; j < caras->iesimo(i)-> getNumVertices(); j++) {
                         
                        int iN = caras->iesimo(i)-> getIndiceNormal(j);
                        int iV = caras->iesimo(i)-> getIndiceVertice(j);
     
                        normalX = normales->iesimo(iN)->getX();
                        normalY = normales->iesimo(iN)->getY();
                        normalZ = normales->iesimo(iN)->getZ();
                             
                        verticeX = vertices->iesimo(iV)->getX();
                        verticeY = vertices->iesimo(iV)->getY();
                        verticeZ = vertices->iesimo(iV)->getZ();

                        // pintamos cada normal, lo hacemos asi para no poner 4 normales por cada cara
                         if(j == 1){
                            glColor3d(3,3,3);
                            glVertex3d(verticeX,verticeY,verticeZ);
                            glVertex3d(verticeX-normalX,verticeY-normalY,verticeZ-normalZ);
                        }

                    }
                }
            }

            for (int i = 0; i < numCaras; i++) {
                                     
                    glLineWidth(1.0);
                    if(modoT == 0)
                        glBegin(GL_POLYGON);
                    else
                        glBegin(GL_LINE_LOOP);

                    for (int j = 0; j < caras->iesimo(i)-> getNumVertices(); j++) {
                         
                        int iN = caras->iesimo(i)-> getIndiceNormal(j);
                        int iV = caras->iesimo(i)-> getIndiceVertice(j);
     
                        normalX = normales->iesimo(iN)->getX();
                        normalY = normales->iesimo(iN)->getY();
                        normalZ = normales->iesimo(iN)->getZ();
                        
                        // Le asignamos una normal a cada vertice
                        glNormal3d(-normalX,-normalY,-normalZ);
                             
                        //Si hubiera coordenadas de textura, aqui se suministrarian
                        //las coordenadas de textura del vertice j con glTexCoor2f(...);
                     
                        verticeX = vertices->iesimo(iV)->getX();
                        verticeY = vertices->iesimo(iV)->getY();
                        verticeZ = vertices->iesimo(iV)->getZ();

                        // Pintamos cada vertice
                        glColor3d(1,1,0);
                        glVertex3d(verticeX,verticeY,verticeZ);

                    } // for 2

                    glEnd();

            }// for 1


            if(modoN == 1) glEnd();
            
            glPopMatrix();

        }// Dibuja
};

#endif