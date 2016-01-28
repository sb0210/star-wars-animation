

#include <cstdlib>
#include <cmath>
#include <fstream>
#include <GL/glut.h>

static float angle=0.0,ratio;
static float x=0.0f,y=1.75f,z=5.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
static GLint snowman_display_list;

bool recording=true;
unsigned int framenum=0;
unsigned char *pRGB;

int SCREEN_WIDTH=640;
int SCREEN_HEIGHT=360;

void capture_frame(unsigned int framenum)
{
  //global pointer float *pRGB
  pRGB = new unsigned char [3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1) ];


  // set the framebuffer to read
  //default for double buffered
  glReadBuffer(GL_BACK);

  glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment
  
  glReadPixels(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
  char filename[200];
  sprintf(filename,"frame_%04d.ppm",framenum);
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
  out.close();

  //function to store pRGB in a file named count
  delete pRGB;
}

void resize(int w, int h)
{
  
  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if(h == 0) h = 1;
  
  ratio = 1.0f * w / h;

  SCREEN_WIDTH=w;
  SCREEN_HEIGHT=h;
  // Reset the coordinate system before modifying
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);
  
  // Set the clipping volume
  gluPerspective(45, ratio, 1, 1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f, 1.0f, 0.0f);
}


void drawSnowMan() 
{
  glColor3f(1.0f, 1.0f, 1.0f);
  
  // Draw Body	
  glTranslatef(0.0f ,0.75f, 0.0f);
  glutSolidSphere(0.75f,20,20);
  
  
  // Draw Head
  glTranslatef(0.0f, 1.0f, 0.0f);
  glutSolidSphere(0.25f,20,20);
  
  // Draw Eyes
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.05f, 0.10f, 0.18f);
  glutSolidSphere(0.05f,10,10);
  glTranslatef(-0.1f, 0.0f, 0.0f);
  glutSolidSphere(0.05f,10,10);
  glPopMatrix();
  
  // Draw Nose
  glColor3f(1.0f, 0.5f , 0.5f);
  glRotatef(0.0f,1.0f, 0.0f, 0.0f);
  glutSolidCone(0.08f,0.5f,10,2);
}



GLuint createDL() 
{
  GLuint snowManDL;
  
  // Create the id for the list
  snowManDL = glGenLists(1);
  
  // start list
  glNewList(snowManDL,GL_COMPILE);
  
  // call the function that contains the rendering commands
  drawSnowMan();
  
  // endList
  glEndList();
  
  return(snowManDL);
}

void initScene() 
{
  glEnable(GL_DEPTH_TEST);
  snowman_display_list = createDL();
}

void display(void) 
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Draw ground
  
  glColor3f(0.9f, 0.9f, 0.9f);
  glBegin(GL_QUADS);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glVertex3f( 100.0f, 0.0f, -100.0f);
  glEnd();

  // Draw 36 SnowMen
  
  for(int i = -3; i < 3; i++)
    for(int j=-3; j < 3; j++) {
      glPushMatrix();
      glTranslatef(i*10.0,0,j * 10.0);
      glCallList(snowman_display_list);
      glPopMatrix();
    }

  if (recording)
    capture_frame(framenum++);

  glutSwapBuffers();
}

void orientMe(float ang) 
{
  lx = sin(ang);
  lz = -cos(ang);
  glLoadIdentity();
  gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f, 1.0f, 0.0f);
}


void moveMeFlat(int i) 
{
  x = x + i*(lx)*0.1;
  z = z + i*(lz)*0.1;
  glLoadIdentity();
  gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
}

void processNormalKeys(unsigned char key, int x, int y) 
{

  if (key == 27) exit(0);
}


void inputKey(int key, int x, int y) 
{
  switch (key) {
  case GLUT_KEY_LEFT : angle -= 0.01f;orientMe(angle);break;
  case GLUT_KEY_RIGHT : angle +=0.01f;orientMe(angle);break;
  case GLUT_KEY_UP : moveMeFlat(1);break;
  case GLUT_KEY_DOWN : moveMeFlat(-1);break;
  }
}


int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutCreateWindow("SnowMen from Lighthouse 3D");
  
  initScene();
  
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(inputKey);
  
  glutDisplayFunc(display);
  glutIdleFunc(display);
  
  glutReshapeFunc(resize);
  
  glutMainLoop();
  
  return(0);
}
