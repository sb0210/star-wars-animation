#ifndef _GL_FRAMEWORK_CPP_
#define _GL_FRAMEWORK_CPP_

#include "starwars.hpp"
#include "gl_framework.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot;
extern GLfloat c_xpos,c_ypos,c_zpos;
extern GLfloat c_up_x,c_up_y,c_up_z;
extern GLfloat c_tx, c_ty, c_tz;
extern bool enable_perspective;
extern Starwars* starwars;
extern float light1,light2,light3;
extern void zoom_in(float val);
extern void rotate_around_camera(float x, float y, float z);
extern void rotate_around_lookat(float x, float y, float z);
extern void store_key_frames();
extern void load_key_frames();
extern void create_key_frames();
extern void start_playback();
void reset_files();
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
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS){
          starwars->currentBot= 1- starwars->currentBot; 
          starwars->CurrentNode("parent");
          std::cout<<starwars->currentBot<<std::endl;
    }
    else if (key == GLFW_KEY_H && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("hip"); 
      else
        starwars->CurrentNode("head");         
    }
    else if (key == GLFW_KEY_J && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("torso"); 
      else
        starwars->CurrentNode("parent");    
        }     
    else if (key == GLFW_KEY_B && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("lThigh"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_N && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("rThigh"); 
      else
        starwars->CurrentNode("neck");      
        }   
    else if (key == GLFW_KEY_V && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("lLowerLeg"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_M && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("rLowerLeg"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_C && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("lFoot"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_COMMA && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("rFoot"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_Y && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("lUpperArm"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_U && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("rUpperArm"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_T && action == GLFW_PRESS && mods==0){
      if(starwars->currentBot==0)
        starwars->CurrentNode("lLowerArm"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_I && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("rLowerArm"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_R && action == GLFW_PRESS && mods==0){
      if(starwars->currentBot==0)
        starwars->CurrentNode("lPalm"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_O && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("rPalm"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("neck"); 
      else
        starwars->CurrentNode("body");      
        }   
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS){
      if(starwars->currentBot==0)
        starwars->CurrentNode("head"); 
      else
        starwars->CurrentNode("body");      
        }
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS && mods==1){
        light1 = -1* light1;
      }

    else if (key == GLFW_KEY_2 && action == GLFW_PRESS && mods==1){
        light2 = -1* light2;
      }

    else if (key == GLFW_KEY_3 && action == GLFW_PRESS && mods==1){
        light3 = -1* light3;
      }
   
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && mods==0)
      starwars->curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && mods==0)
      starwars->curr_node->inc_ry();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS && mods==0)
      starwars->curr_node->dec_rx();
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && mods==0)
      starwars->curr_node->inc_rx();
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && mods==0)
      starwars->curr_node->dec_rz();
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && mods==0)
      starwars->curr_node->inc_rz();
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && mods==1)
      starwars->moveBot(-1,0,0);
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && mods==1)
      starwars->moveBot(1,0,0);
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS && mods==1)
      starwars->moveBot(0,1,0);
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS && mods==1)
      starwars->moveBot(0,-1,0);
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS && mods==1)
      starwars->moveBot(0,0,1);
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS && mods==1)
      starwars->moveBot(0,0,-1);
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS && mods==0)
      rotate_around_camera(0,5,0);
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS && mods==0)
      rotate_around_camera(0,-5,0);
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS && mods==0)
      rotate_around_camera(5,0,0);
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS && mods==0)
      rotate_around_camera(-5,0,0);
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS && mods==0)
      rotate_around_camera(0,0,5);
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS && mods==0)
      rotate_around_camera(0,0,-5);

    else if (key == GLFW_KEY_A  && action == GLFW_PRESS && mods==2)
      rotate_around_lookat(0,5,0);
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS && mods==2)
      rotate_around_lookat(0,-5,0);
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS && mods==2)
      rotate_around_lookat(5,0,0);
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS && mods==2)
      rotate_around_lookat(-5,0,0);
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS && mods==2)
      rotate_around_lookat(0,0,5);
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS && mods==2)
      rotate_around_lookat(0,0,-5);

    else if (key == GLFW_KEY_A  && action == GLFW_PRESS && mods==1){
      c_xpos -= 0.5;
      c_tx -= 0.5;
    }
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS && mods==1){
      c_xpos += 0.5;
      c_tx += 0.5;
    }
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS && mods==1){
      c_zpos -= 0.5;
      c_tz -= 0.5;
    }
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS && mods==1){
      c_zpos += 0.5;        
      c_tz += 0.5;        
    }
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS && mods==1){
      c_ypos -= 0.5;
      c_ty -= 0.5;
    }
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS && mods==1){
      c_ypos += 0.5;         
      c_ty += 0.5;         
    }
    else if (key == GLFW_KEY_R  && action == GLFW_PRESS && mods==1){
      c_yrot = c_xrot = c_zrot= 0;
      c_up_x = 0;
      c_up_z = 0;
      c_up_y = 1.0;         
      c_tx = c_ty = c_tz = 0;
      c_xpos = 0.0;
      c_ypos = 20.0;
      c_zpos = 43.0;
    }
    else if (key == GLFW_KEY_R  && action == GLFW_PRESS && mods==2){
      reset_files();
    }
    else if(key ==GLFW_KEY_Z && action == GLFW_PRESS && mods==0){
      zoom_in(1);
    }
    else if(key ==GLFW_KEY_Z && action == GLFW_PRESS && mods==1){
      zoom_in(-1);
    }
    else if(key == GLFW_KEY_T && action== GLFW_PRESS && mods==1){
      starwars->toggle_texture();
    }
    else if(key ==GLFW_KEY_SPACE && action==GLFW_PRESS && mods==0){
      store_key_frames();
    }
    else if(key ==GLFW_KEY_SPACE && action==GLFW_PRESS && mods==1){
      start_playback();
    }  
    else if(key ==GLFW_KEY_SPACE && action==GLFW_PRESS && mods==2){
      create_key_frames();
    }  
  }
};  
#endif

