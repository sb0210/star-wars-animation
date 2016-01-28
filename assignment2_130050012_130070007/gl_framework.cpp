#include "gl_framework.hpp"

#define PI 3.14
extern void reinitialize();
extern GLfloat xtrans,ytrans,ztrans;
// extern void add_vertex(GLdouble xpos, GLdouble ypos, GLdouble zpos);
extern  void renderGL();
// extern  void remove_vertex();
extern char mode;
extern int counter;
extern int initial_size;
// extern void load_file(std::string filename);
// extern void save_file(std::string filename);
// extern void centroid(GLdouble c[]);
// extern void remove_redundant_vertices();
extern void rotate(GLfloat x, GLfloat y, GLfloat z);
extern void draw_wcs();
extern void draw_vcs();
extern void draw_ccs();
extern void draw_ndcs();
extern void draw_dcs();
// void clear_screen();
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    // if (key == GLFW_KEY_I && action == GLFW_PRESS){
    //   mode='I';
    //   reinitialize();
    //   xtrans=0;
    //   ytrans=0;
    //   ztrans=0;
    //   counter=0;
    //   std::cout<<"Currently in Inspection Mode\n";
    //   remove_redundant_vertices();
    // }
    // if (key == GLFW_KEY_M && action == GLFW_PRESS){
    //   mode='M';
    //   reinitialize();
    //   xtrans=0;
    //   ytrans=0;
    //   ztrans=0;
    //   counter =0;
    //   remove_redundant_vertices();
    //   std::cout<<"Currently in Modelling Mode\n";
    // }
    // if (key == GLFW_KEY_K && action == GLFW_PRESS){ //save
    //   std::string filename;
    //   std::cout<<"Enter filename to save\n";
    //   std::cin>>filename;
    //   save_file(filename);
    // }
    // if (key == GLFW_KEY_L && action == GLFW_PRESS){ //save
    //   reinitialize();
    //   std::string filename;
    //   std::cout<<"Enter filename to load\n";
    //   std::cin>>filename;
    //   load_file(filename);
    // }
    // if (key == GLFW_KEY_C && action == GLFW_PRESS){
    //   clear_screen();
    // }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    // if(mode=='M') return;
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      rotate(0.0,-PI/6,0.0);
      // yrot -= 1.0;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      // yrot += 1.0;
      rotate(0.0,PI/6,0.0);
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      // xrot -= 1.0;
      rotate(PI/6,0.0,0.0);
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      // xrot += 1.0;
      rotate(-PI/6,0.0,0.0);
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
      // zrot += 1.0;
      rotate(0.0,0.0,PI/6);
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
      // zrot -= 1.0;
      rotate(0.0,0.0,-PI/6);
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
      ytrans += 0.2;
    else if (key == GLFW_KEY_S && action == GLFW_PRESS)
      ytrans -= 0.2;
    else if (key == GLFW_KEY_A && action == GLFW_PRESS)
      xtrans -= 0.2;
    else if (key == GLFW_KEY_D && action == GLFW_PRESS)
      xtrans += 0.2;
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS)
      ztrans += 0.2;
    else if (key == GLFW_KEY_X && action == GLFW_PRESS)
      ztrans -= 0.2;
    else if (key == GLFW_KEY_R && action == GLFW_PRESS){
      reinitialize();
      xtrans = 0;
      ytrans = 0;
      ztrans = 0;
    }
    else if(key == GLFW_KEY_0 && action == GLFW_PRESS){
      draw_wcs();
    }
    else if(key == GLFW_KEY_1 && action == GLFW_PRESS){
      draw_vcs();
    }
    else if(key == GLFW_KEY_2 && action == GLFW_PRESS){
      draw_ccs();
    }
    else if(key == GLFW_KEY_3 && action == GLFW_PRESS){
      draw_ndcs();
    }
    else if(key == GLFW_KEY_4 && action == GLFW_PRESS){
      draw_dcs();
    }

  }

  
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
 /*   if (mode=='I')return;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods==0){
      GLdouble xpos,ypos,zpos=0;
      glfwGetCursorPos(window, &xpos, &ypos); 
      int height,width;
      glfwGetWindowSize(window,&height,&width);
            
      add_vertex(xpos*2/width-1,1-ypos*2/height,zpos);
      renderGL();
     }
     else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods==2){
      GLdouble xpos,ypos,zpos=0;
      glfwGetCursorPos(window, &xpos, &ypos); 
      int height,width;
      glfwGetWindowSize(window,&height,&width);
      std::cout<<"Enter the z value (-1.0 to 1.0)\n";
      std::cin>>zpos;
      while(zpos<-1 || zpos>1){
        std::cout<<"value has to be between -1.0 and 1.0\n";
        std::cin>>zpos;
      }
      add_vertex(xpos*2/width-1,1-ypos*2/height,zpos);
      renderGL();
     }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods==1){
      int height,width;
      remove_vertex();
     renderGL();
     }
*/

  }

};  
  


