/*
Charmi Dedhia - 130070007
Siddharth Bulia - 130050012

-Reference - Tutorial 7

*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "gl_framework.hpp"

// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 20.0, c_zpos = 43.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;
GLfloat c_tx=0, c_ty=0, c_tz=0;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=true;
//Shader program attribs
GLuint vPosition,vColor,vNormal,vTex;
//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

Starwars* starwars;

//-------------------------------------------------------------------------

#endif
