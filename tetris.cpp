//Del'Juan Jackson
//University of Arkansas
//CSCE 4813
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <iostream>
#include <random>
using namespace std;



//---------------------------------------
// Global Variables
//---------------------------------------
int xangle = 0;
int GLOBAL_X = 0;
int GLOBAL_Y = 0;



//---------------------------------------
// Draws square
//---------------------------------------
void draw_square(float x, float y, float w, float R, float G, float B)
{
   glBegin(GL_POLYGON);
   glColor3f(R, G, B);
   glVertex2f(x-w/2, y-w/2);
   glVertex2f(x-w/2, y+w/2);
   glVertex2f(x+w/2, y+w/2);
   glVertex2f(x+w/2, y-w/2);
   glEnd();

   glLineWidth(3);
   glBegin(GL_LINE_LOOP);
   glColor3f(R/2, G/2, B/2);
   glVertex2f(x-w/2, y-w/2);
   glVertex2f(x-w/2, y+w/2);
   glVertex2f(x+w/2, y+w/2);
   glVertex2f(x+w/2, y-w/2);
   glEnd();
}

//---------------------------------------
// Tetrimino Class
//---------------------------------------
class Tetrimino {
   public:
      int x, y, angle;
      bool flag = false;
      char type;
      float R,G,B;
      void draw();
      
      Tetrimino(int x_, int y_, int angle_, bool flag_, 
                  char type_, float R_, float G_, float B_)
      {
         x = x_;
         y = y_;
         angle = angle_;
         type = type_;
         flag = flag_;
         R = R_;
         G = G_;
         B = B_;
      }
};


//---------------------------------------
// Vector to hold tetriminos
//---------------------------------------
vector<Tetrimino> TETRIMINOS;

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-0, 10.0, -0, 20.0, -10.0, 10.0);
}

//---------------------------------------
// Draw one square
//---------------------------------------
// Draw I piece
//---------------------------------------
void draw_I(float x, float y)
{
   float R=0.65, G=0.85, B=1;
   draw_square(x,y,1, R,G,B);
   draw_square(x-1,y,1, R,G,B);
   draw_square(x+1,y,1, R,G,B);
   draw_square(x+2,y,1, R,G,B);
}

//---------------------------------------
// Draw J piece
//---------------------------------------
void draw_J(float x, float y)
{
   float R=0, G=0, B=1;
   draw_square(x,y,1, R,G,B);
   draw_square(x-1,y,1, R,G,B);
   draw_square(x+1,y,1, R,G,B);
   draw_square(x-1,y+1,1, R,G,B);
}

//---------------------------------------
// Draw L piece
//---------------------------------------
void draw_L(float x, float y)
{
   float R=1, G=0.65, B=0;
   draw_square(x,y,1, R,G,B);
   draw_square(x-1,y,1, R,G,B);
   draw_square(x+1,y,1, R,G,B);
   draw_square(x+1,y+1,1, R,G,B);
}

//---------------------------------------
// Draw O piece
//---------------------------------------
void draw_O(float x, float y)
{
   float R=1, G=1, B=0;
   draw_square(x,y,1, R,G,B);
   draw_square(x+1,y,1, R,G,B);
   draw_square(x,y+1,1, R,G,B);
   draw_square(x+1,y+1,1, R,G,B);
}

//---------------------------------------
// Draw T piece
//---------------------------------------
void draw_T(float x, float y)
{
   float R=1, G=0, B=1;
   draw_square(x,y,1, R,G,B);
   draw_square(x-1,y,1, R,G,B);
   draw_square(x+1,y,1, R,G,B);
   draw_square(x,y+1,1, R,G,B);
}

//---------------------------------------
// Draw S piece
//---------------------------------------
void draw_S(float x, float y)
{
   float R=0, G=1, B=0;
   draw_square(x,y,1, R,G,B);
   draw_square(x-1,y,1, R,G,B);
   draw_square(x,y+1,1, R,G,B);
   draw_square(x+1,y+1,1, R,G,B);
}

//---------------------------------------
// Draw Z piece
//---------------------------------------
void draw_Z(float x, float y)
{
   float R=1, G=0, B=0;
   draw_square(x,y,1, R,G,B);
   draw_square(x+1,y,1, R,G,B);
   draw_square(x,y+1,1, R,G,B);
   draw_square(x-1,y+1,1, R,G,B);
}



//---------------------------------------
// Draw function for tetriminos
//---------------------------------------
void Tetrimino::draw()
{
   switch(type)
   {
      case 'i':
      case 'I':
      draw_I(x,y);
      break;

      case 'j':
      case 'J':
      draw_J(x,y);
      break;

      case 'l':
      case 'L':
      draw_L(x,y);
      break;

      case 'o':
      case 'O':
      draw_O(x,y);
      break;

      case 's':
      case 'S':
      draw_S(x,y);
      break;

      case 't':
      case 'T':
      draw_T(x,y);
      break;

      case 'Z':
      case 'z':
      draw_Z(x,y);
      break;
   }
   glFlush();
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   for(Tetrimino &tetrad : TETRIMINOS)
   {
         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();
         glTranslatef(tetrad.x, tetrad.y,0);
         glRotatef(tetrad.angle, 0.0, 0.0, 1.0);
         glTranslatef(-tetrad.x, -tetrad.y,0);
         tetrad.draw();
   }
   glFlush();
}

//---------------------------------------
// Acts as a CLEAR function
//---------------------------------------
void MAKE_FALSE()
{
   xangle = 0;
   GLOBAL_X = 0;
   GLOBAL_Y = 0;

   for(Tetrimino &tetrad: TETRIMINOS)
      {
         tetrad.flag = false;
      }
}

//---------------------------------------
// Key Callbacks
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 'i':
   case 'I':
   {
      MAKE_FALSE();
      Tetrimino i_trad(2,7,0,true,'i',1,0,0);
      TETRIMINOS.push_back(i_trad);
   }
   break;
   case 'j':
   case 'J':
   {
      MAKE_FALSE();
      Tetrimino j_trad(7,7,0,true,'j',1,0,0);
      TETRIMINOS.push_back(j_trad);
   }
   break;
   case 'l':
   case 'L':
   {
      MAKE_FALSE();
      Tetrimino l_trad(2,10,0,true,'l',1,0,0);
      TETRIMINOS.push_back(l_trad);
   }
   break;
   case 'o':
   case 'O':
   {
      MAKE_FALSE();
      Tetrimino o_trad(8,12,0,true,'o',1,0,0);
      TETRIMINOS.push_back(o_trad);
   }
   break;
   case 's':
   case 'S':
   {
      MAKE_FALSE();
      Tetrimino s_trad(5,10,0,true,'s',1,0,0);
      TETRIMINOS.push_back(s_trad);
   }
   break;
   case 't':
   case 'T':
   {
      MAKE_FALSE();
      Tetrimino t_trad(7,7,0,true,'t',1,0,0);
      TETRIMINOS.push_back(t_trad);
   }
   break;
   case 'z':
   case 'Z':
   {
      MAKE_FALSE();
      Tetrimino z_trad(4,14,0,true,'z',1,0,0);
      TETRIMINOS.push_back(z_trad);
   }
   break;
   case 'x':
   {
      for(Tetrimino &tetrad : TETRIMINOS)
      {
         if(tetrad.flag != false)
         {
            tetrad.angle += 90;
         }

      }
   }
   break;
   case 'X':
   {
      for(Tetrimino &tetrad : TETRIMINOS)
      {
         if(tetrad.flag != false)
         {
            tetrad.angle -= 90;
         }
      }
   }
   break;
   case ' ':
   {
      MAKE_FALSE();
   }
   break;
   default:
      break;
   }
   display();
}

//---------------------------------------
// Special Key Callbacks
//---------------------------------------
void special(int key, int x, int y)
{
  for(Tetrimino &tetrad : TETRIMINOS)
 { 
   switch (key)
   {
      case GLUT_KEY_UP:{
         if(tetrad.flag != false && tetrad.y <= 17)
            {
               tetrad.y += 1;
            }
      }
     break;
     case GLUT_KEY_DOWN:{
     if(tetrad.flag != false && tetrad.y >= 2)
            {
               tetrad.y -= 1;
            }
      }
      break;
      case GLUT_KEY_LEFT:{
      if(tetrad.flag != false && tetrad.x >= 3)
            {
               tetrad.x -= 1;
            }
      }
         break;
      case GLUT_KEY_RIGHT:{
      if(tetrad.flag != false  && tetrad.x <= 7)
            {
               tetrad.x += 1;
            }
      }
         break;
   }               
}
   glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitWindowSize(400, 800);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Tetris");
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   glutDisplayFunc(display);
   init();
   glutMainLoop();
   return 0;
}

