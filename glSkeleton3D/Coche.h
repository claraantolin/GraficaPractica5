//********************************//
//    COMPONENTES DEL GRUPO:      //
//                                //
//    Marina Bezares Alvarez      //
//    Clara Antolin Garcia        //
//                                //
//********************************//

#ifndef CocheH
#define CocheH

#include <gl\gl.h>
#include <gl\glu.h>

#define PI 3.14159265

#include "Malla.h"
#include "Lista.h"
#include "Cara.h"
//---------------------------------------------------------------------------
class Coche : public Malla
{
   private:

        int numLados;
        int numRodajas;
        int pos;

   public:

        Coche();
        Coche(int nlados, int nRodajas):Malla(0,new Lista<PV3D*>(), 0, new Lista<PV3D*>(), 0, new Lista<Cara*>()){

            // Damos valor a nuestros atributos
            numLados = nlados;
            numRodajas = nRodajas;

            // Damos valor a los atributos de la malla
            numVertices = nlados * nRodajas;
            calculaVertices();
            numNormales = numVertices; //=numCaras, frecuentemente
            numCaras = numVertices;
            calculaCaras();

            //Llamamos a newell para calcular las normales
            RellenaVectorNormalPorNewell();

            pos=0;
        }
        
        ~Coche(){
            numLados = 0;
            numRodajas = 0;          
        };

        GLdouble getAnguloX(){ return anguloX;}
        GLdouble getAnguloY(){ return anguloY;}
        GLdouble getAnguloZ(){ return anguloZ;}
        GLdouble getpos(){ return pos;}

        void setAnguloX(GLdouble angX){ anguloX = angX;}
        void setAnguloY(GLdouble angY){ anguloY = angY;}
        void setAnguloZ(GLdouble angZ){ anguloZ = angZ;}
        void setPos(GLdouble p){ pos = p;}


        void incrementaPos(){
                pos++;
                pos = pos % 60;
                mueveCoche();
        }

        void decrementaPos(){
                pos--;
                pos = pos % 60;
                mueveCoche();
        }

//------------------------------------------------------------------------------
                        /***** calculaVertices *****/
//------------------------------------------------------------------------------

        void calculaVertices(){

            GLdouble t = (2* M_PI * pos) / 60;
            Lista<PV3D*>* matriz = hazMatriz(t,7);
            
            double inc=(2*PI/numLados);
            for(int i=0; i<numLados; i++){
                PV3D* nodo = new PV3D(   cos(2*PI-i*inc)*0.7  , sin(2*PI-i*inc)*0.7  , 0  ,1);
                PV3D* res = multiplicaMatrices(matriz, nodo);
                vertices->ponElem(res);
                delete nodo;
            }

             for(int i=0; i<numLados; i++){
                PV3D* nodo = new PV3D(   cos(2*PI-i*inc)*0.7  , sin(2*PI-i*inc)*0.7   , 0 +0.7 ,1) ;
                PV3D* res = multiplicaMatrices(matriz, nodo);
                vertices->ponElem(res);
                delete nodo;
            }

            delete matriz;
        }

//------------------------------------------------------------------------------
                        /***** calculaCaras *****/
//------------------------------------------------------------------------------

        void calculaCaras(){

            for(int indiceRodaja = 0, lado = 0; indiceRodaja < numRodajas; indiceRodaja++, lado = lado+numLados){
                
                for(int indiceCara = lado, indAux = 0; indiceCara < (lado+numLados); indiceCara++, indAux++){ 

                    Lista<VerticeNormal*>* arrayVN = new Lista<VerticeNormal*>();

                    // Rellenamos arrayVN de la clase Cara
                    arrayVN->ponElem(new VerticeNormal(indiceCara % numVertices ,indiceCara));
                    
                    if(indAux == numLados-1){ // estamos en el ultimo lado de la rodaja actual
                        arrayVN->ponElem(new VerticeNormal(lado % numVertices ,indiceCara));
                        arrayVN->ponElem(new VerticeNormal((lado+numLados) % numVertices ,indiceCara));
                    }else{
                        arrayVN->ponElem(new VerticeNormal((indiceCara+1) % numVertices ,indiceCara));
                        arrayVN->ponElem(new VerticeNormal((indiceCara+numLados+1) % numVertices ,indiceCara));
                    }
                    
                    arrayVN->ponElem(new VerticeNormal((indiceCara+numLados) % numVertices ,indiceCara));

                    caras->ponElem(new Cara(4,arrayVN)); // Siempre una cara va a estar compuesta de 4 vertices, 2 a 2
                }
            }
        }

//------------------------------------------------------------------------------
                        /***** multiplicaMatrices *****/
//------------------------------------------------------------------------------

        PV3D* multiplicaMatrices(Lista<PV3D*>* m, PV3D* p){

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

//------------------------------------------------------------------------------
                        /***** hazMatriz *****/
//------------------------------------------------------------------------------

        /*Lista<PV3D*>* hazMatriz(GLfloat t, GLfloat r){

            Lista<PV3D*>* matriz = new Lista<PV3D*>();

            PV3D* n = new PV3D(-1 * cos(t),0, -sin(t), r* cos(t));
            PV3D* b = new PV3D(0,-1, 0, 0);
            PV3D* tM = new PV3D(-sin(t),0, cos(t),  r*sin(t));
            PV3D* c = new PV3D(0,0,0, 1);

            matriz->ponElem(n); matriz->ponElem(b); matriz->ponElem(tM); matriz->ponElem(c);
            return matriz;
        }*/

//------------------------------------------------------------------------------
                        /***** hazMatriz *****/
//------------------------------------------------------------------------------

        Lista<PV3D*>* hazMatriz(GLfloat t, GLfloat r){

            //C(t) = (3cos(t), 2cos(1,5t), 3sen(t));
            //C'(t) = (-3sen(t), 3sen(1,5t), 3cos(t));
            //C''(t) = (-3cos(t), -4,5cos(1,5t), -3sen(t))

            //M(t) = (N(t), B(t), T(t), C(t))
            //       ( 0  ,  0  ,  0  ,  1  )

            /*PV3D* c = new PV3D(3*cos(t)*2, 2*cos(1.5*t)*2, 3*sin(t)*2,1);
            PV3D* cPrima = new PV3D (-3*sin(t)*2, 3*sin(1.5*t)*2, 3*cos(t)*2,1);
            PV3D* cPrimaPrima = new PV3D (-3*cos(t)*2, -4.5*cos(1.5*t)*2, -3*sin(t)*2,1);*/

            PV3D* c = new PV3D(3*cos(t)*2, 2*cos(1.5*t)*2, 3*sin(t)*2,1);
            PV3D* cPrima = new PV3D (-3*sin(t)*2, -2*sin(1.5*t)*2, 3*cos(t)*2,1);
            PV3D* cPrimaPrima = new PV3D (-3*cos(t)*2, -2*cos(1.5*t)*2, -3*sin(t)*2,1);

            //T(t) = C'(t) normalizado
            PV3D* tM = new PV3D(cPrima->getX(),cPrima->getY(),cPrima->getZ(), cPrima->getW());
            tM->normaliza();

            //B(t)= C'(t) x C''(t)
            PV3D* b = cPrima-> productoVectorial(cPrimaPrima);    
            b->normaliza();
            //PV3D* p = cPrimaPrima->productoVectorial(cPrima);

            //N(t)= B(x) x T(x)
            PV3D* n = b->productoVectorial(tM);
            n->normaliza();

            PV3D* primeraFila = new PV3D(n->getX(), b->getX(), tM->getX(), c->getX());
            PV3D* segundaFila = new PV3D(n->getY(), b->getY(), tM->getY(), c->getY());
            PV3D* terceraFila = new PV3D(n->getZ(), b->getZ(), tM->getZ(), c->getZ());
            PV3D* cuartaFila  = new PV3D(0, 0, 0, 1);

            delete n; delete b; delete tM; delete c; delete cPrima; delete cPrimaPrima;

            Lista<PV3D*>* matriz = new Lista<PV3D*>();
            matriz->ponElem(primeraFila); matriz->ponElem(segundaFila); matriz->ponElem(terceraFila); matriz->ponElem(cuartaFila);
            return matriz;
        }

//------------------------------------------------------------------------------
                        /***** dibujaCoche *****/
//------------------------------------------------------------------------------

        void dibujaCoche(int modoN, int modoT){
        
            dibuja(modoN, modoT);

            //Dibujamos las tapas del coche
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glRotatef(anguloX, 1.0, 0.0, 0.0);
            glRotatef(anguloY, 0.0, 1.0, 0.0);
            glRotatef(anguloZ, 0.0, 0.0, 1.0);
            glColor3d(0,0,1);
            glLineWidth(1.0);

            glBegin(GL_POLYGON);
                for(int i =0 ; i<4; i++)
                        glVertex3d(vertices->iesimo(i)->getX(), vertices->iesimo(i)->getY(), vertices->iesimo(i)->getZ());
            glEnd();

            glBegin(GL_POLYGON);
                for(int i =4 ; i<8; i++)
                        glVertex3d(vertices->iesimo(i)->getX(), vertices->iesimo(i)->getY(), vertices->iesimo(i)->getZ());
            glEnd();

            glPopMatrix();
        }


//------------------------------------------------------------------------------
                        /***** rotaCoche *****/
//------------------------------------------------------------------------------

        void rotaCoche(tipo){
            switch(tipo){
                case 0:
                    anguloY -= 10.0f;
                    break;
                case 1:
                    anguloY += 10.0f;
                    break;
                case 2:
                    anguloX -= 10.0f;
                    break;
                case 3:
                    anguloX += 10.0f;
                    break;
                case 4:
                    anguloZ -= 10.0f;
                    break;
                case 5:
                    anguloZ += 10.0f;
                    break;
                default: break;
            }
        }

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
                        /***** mueveCoche *****/
//------------------------------------------------------------------------------
       void mueveCoche( ){
           delete vertices; delete normales; delete caras;

           vertices = new Lista<PV3D*>();
           normales = new Lista<PV3D*>();
           caras = new Lista<Cara*>();

           calculaVertices();

           numNormales = numVertices; //=numCaras, frecuentemente
           numCaras = numVertices;
           calculaCaras();

           //Llamamos a newell para calcular las normales
           RellenaVectorNormalPorNewell();
           
        }

};

#endif