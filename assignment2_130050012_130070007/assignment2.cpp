/*
  CS 475: Assignment 1
  Made by: Charmi Dedhia(130070007) and Siddharth Bulia(130050012)
  Reference : Tutorial 3 by Parag Chaudari
*/


#include "assignment2.hpp"
using namespace std;

GLuint shaderProgram;
GLuint vbo[4], vao[4];

glm::mat4 rotation_matrix(1.0f), translation_matrix;
glm::mat4 initial_rotation_matrix(1.0f),ortho_matrix;
glm::mat4 final_matrix(1.0f);
glm::vec3 A,E,Vup,n,u,v;

GLuint uRotationMatrix;

char mode='I';
int counter=0;
int initial_size;
//-----------------------------------------------------------------

//6 faces, 2 triangles/face, 3 vertices/triangle
int num_vertices;
std::vector<glm::vec4> v_positions[3];
std::vector<glm::vec4> v_colors[4];
GLfloat L,R,T,B,N,F;



// void centroid(GLdouble c[]){
//   GLdouble x=0.0,y=0.0,z=0.0;
//   vector<glm::vec4> pos_nodup; 
//   for(int i=0;i<v_positions.size();i++){
//     bool duplicate=false;
//     for(int j=0;j<pos_nodup.size();j++){
//       if (v_positions[i]==pos_nodup[j]){
//         duplicate=true;
//         break;
//       }
//     }
//     if(duplicate==false)pos_nodup.push_back(v_positions[i]);
//   }
//   for(int i=0;i<pos_nodup.size();i++){
//     x=x+ pos_nodup[i][0];
//     y=y+pos_nodup[i][1];
//     z=z+pos_nodup[i][2];
//   }
//   c[0] = x/pos_nodup.size();
//   c[1] = y/pos_nodup.size();
//   c[2] = z/pos_nodup.size();
// }

// void remove_redundant_vertices(){
//   v_positions.resize((v_positions.size()/3)*3);
//   v_colors.resize((v_colors.size()/3)*3);
// }

void initBuffersGL(void)
{
  // colorcube();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for(int i=0;i<4;i++)
  {//Ask GL for a Vertex Attribute Object (vao)
    glGenVertexArrays (1, &(vao[i]));
    //Set it as the current array to be used by binding it
    glBindVertexArray (vao[i]);

    //Ask GL for a Vertex Buffer Object (vbo)
    glGenBuffers (1, &vbo[i]);
    //Set it as the current buffer to be used by binding it
    glBindBuffer (GL_ARRAY_BUFFER, vbo[i]);
    //Copy the points into the current buffer
    //std::cout<<v_positions.size()<<" v_positions.size "<<v_colors.size()<<endl;
    glBufferData (GL_ARRAY_BUFFER, (v_positions[i].size()+v_colors[i].size())* sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, v_positions[i].size()* sizeof(glm::vec4), &v_positions[i].front() );
    glBufferSubData( GL_ARRAY_BUFFER, v_positions[i].size()* sizeof(glm::vec4),v_colors[i].size()* sizeof(glm::vec4), &v_colors[i].front() );

    // Load shaders and use the resulting shader program
    std::string vertex_shader_file("vshader.glsl");
    std::string fragment_shader_file("fshader.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = csX75::CreateProgramGL(shaderList);
    glUseProgram( shaderProgram );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    
    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET((v_positions[i].size()*sizeof(glm::vec4))) );

    uRotationMatrix = glGetUniformLocation( shaderProgram, "uRotationMatrix");
  }


}

void rotate(GLfloat x, GLfloat y, GLfloat z){
  GLdouble c[3] = {0,0,0};
  // centroid(c);
  rotation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(c[0],c[1],c[2]));
  rotation_matrix = glm::rotate(rotation_matrix, x, glm::vec3(1.0f,0.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, y, glm::vec3(0.0f,1.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, z, glm::vec3(0.0f,0.0f,1.0f));
  // rotation_matrix = glm::translate(rotation_matrix, glm::vec3(-c[0],-c[1],-c[2]));
  initial_rotation_matrix=rotation_matrix*initial_rotation_matrix;
}

void reinitialize(){
  initial_rotation_matrix=glm::mat4(1.0f);
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(xtrans,ytrans,ztrans));

  ortho_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
  // ortho_matrix=glm::mat4(1.0f);
  // uRotationMatrix = ortho_matrix * initial_rotation_matrix;
  glUniformMatrix4fv(uRotationMatrix, 1, GL_FALSE, glm::value_ptr(translation_matrix* ortho_matrix *initial_rotation_matrix * final_matrix)); 
  for(int i=0;i<3;i++){
    glBindVertexArray(vao[i]);
    glDrawArrays(GL_TRIANGLES, 0,v_positions[i].size());
  }
  glBindVertexArray(vao[3]);
  glLineWidth(10.0);
  glPointSize(5.0);
  glDrawArrays(GL_LINES,0,v_positions[3].size()-1);
  glDrawArrays(GL_POINTS,v_positions[3].size()-1,1);
}

void parseline(std::string line,glm::vec4 vect[]){
  std::string strvec[6];
  int i=0;
  int start=0;
  while(line.find(';')!=-1){
    int end= line.find(';');
    strvec[i]=line.substr(1,end-2);
    line = line.substr(end+1,line.length()-end-1);
    float f[4];
    int j=0; 
    while(strvec[i].find(',')!=-1){
      int end1=strvec[i].find(',');
      f[j]=::atof(strvec[i].substr(0,end1).c_str());
      strvec[i] = strvec[i].substr(end1+1,strvec[i].length()-end1-1);
      j++;
    }
    vect[i]=glm::vec4(f[0],f[1],f[2],f[3]);
    i++;
  }
 
 
}

void load_file(std::string filename,int k){
  std::string line;
  std::ifstream myfile (filename.c_str());
  v_colors[k].clear();
  v_positions[k].clear();
  if (myfile.is_open())
  { 
    while ( getline (myfile,line) )
    { glm::vec4 v[2];
      parseline(line,v);
      v_positions[k].push_back(v[0]);
      v_colors[k].push_back(v[1]);
    }
    myfile.close();
  }

}

void load_all_models(){
  std::string model1;
  std::string line;
  std::ifstream myfile("myscene.scn"); 
  GLfloat scaling[3],rotating[3],translating[3];
  int j=0;
  while(myfile>>line){
    if(false){}
    else{
      load_file(line,j); 
      std::cout<<line<<std::endl;
      myfile>>scaling[0]>>scaling[1]>>scaling[2];
      myfile>>rotating[0]>>rotating[1]>>rotating[2];
      myfile>>translating[0]>>translating[1]>>translating[2];

      GLfloat scaling_my_matrix[16] = {
        scaling[0], 0, 0, 0,
        0,  scaling[1],0, 0,
        0, 0, scaling[2], 0,
        0, 0, 0, 1
        };
      glm::mat4 my_matrix;
      my_matrix = glm::make_mat4(scaling_my_matrix);

      GLfloat rotating_x_my_matrix[16] = {
        1, 0, 0, 0,
        0, cos(rotating[0]), -1*sin(rotating[0]), 0,
        0, sin(rotating[0]), cos(rotating[0]), 0,
        0, 0, 0, 1
        };

      GLfloat rotating_y_my_matrix[16] = {
        cos(rotating[1]), 0, sin(rotating[1]), 0,
        0, 1, 0, 0,
        -1*sin(rotating[1]), 0, cos(rotating[1]), 0,
        0, 0, 0, 1
        };

      GLfloat rotating_z_my_matrix[16] = {
        cos(rotating[2]), -1*sin(rotating[2]), 0, 0,
        sin(rotating[2]), cos(rotating[2]), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
        };

      GLfloat translation_my_matrix[16] = {
        1,0,0,translating[0],
        0,1,0,translating[1],
        0,0,1,translating[2],
        0,0,0,1
      };
      my_matrix= glm::transpose(glm::make_mat4(translation_my_matrix)) * glm::transpose(glm::make_mat4(rotating_z_my_matrix)) * glm::transpose(glm::make_mat4(rotating_y_my_matrix)) * glm::transpose(glm::make_mat4(rotating_x_my_matrix)) * my_matrix;    
      for(int i=0;i<v_positions[j].size();i++){
        v_positions[j][i]=my_matrix*v_positions[j][i];
      }
      cout<<glm::to_string(my_matrix)<<endl;
      j++;
      if(j>=3){
        break;
      }
    }
  }
  GLfloat eye[3],lookat[3],upVector[3];
  myfile>>eye[0]>>eye[1]>>eye[2]; 
  myfile>>lookat[0]>>lookat[1]>>lookat[2]; 
  myfile>>upVector[0]>>upVector[1]>>upVector[2]; 

  myfile>>L>>R>>T>>B>>N>>F;

  A=glm::vec3(lookat[0],lookat[1],lookat[2]);
  E=glm::vec3(eye[0],eye[1],eye[2]);
  Vup=glm::vec3(upVector[0],upVector[1],upVector[2]);
  n =glm::normalize(E-A);
  u = glm::normalize(glm::cross(Vup,n));
  v = glm::cross(n,u);


  GLfloat vcs_wcs[16]={
    u[0], u[1], u[2], 0,
    v[0], v[1], v[2], 0,
    n[0], n[1], n[2], 0,
    E[0], E[1], E[2], 1
  };
  GLfloat wcs_vcs[16]={
    u[0], u[1], u[2], -1*E[0],
    v[0], v[1], v[2], -1*E[1],
    n[0], n[1], n[2], -1*E[2],
    0, 0, 0, 1
  };
  glm::mat4 wcs_vcs_matrix = glm::transpose(glm::make_mat4(wcs_vcs));
  glm::mat4 wcs_vcs_matrix_inverse = glm::make_mat4(vcs_wcs);
  cout<<glm::to_string(glm::inverse(wcs_vcs_matrix))<<endl;
  cout<<glm::to_string(wcs_vcs_matrix_inverse)<<endl;
  // cout<<glm::to_string(vcs_wcs)
  // cout<<glm::to_string(wcs_vcs_matrix*wcs_vcs_matrix_inverse)<<endl;

  v_positions[3].push_back(glm::vec4(0.0,0.0,0.0,1));
  v_positions[3].push_back(glm::vec4(L,T,-N,1));
  v_positions[3].push_back(glm::vec4(0.0,0.0,0.0,1));
  v_positions[3].push_back(glm::vec4(R,T,-N,1));
  v_positions[3].push_back(glm::vec4(0.0,0.0,0.0,1));
  v_positions[3].push_back(glm::vec4(L,B,-N,1));
  v_positions[3].push_back(glm::vec4(0.0,0.0,0.0,1));
  v_positions[3].push_back(glm::vec4(R,B,-N,1));

  v_positions[3].push_back(glm::vec4(L,T,-N,1));
  v_positions[3].push_back(glm::vec4(L,B,-N,1));
  v_positions[3].push_back(glm::vec4(R,T,-N,1));
  v_positions[3].push_back(glm::vec4(L,T,-N,1));
  v_positions[3].push_back(glm::vec4(R,B,-N,1));
  v_positions[3].push_back(glm::vec4(R,T,-N,1));
  v_positions[3].push_back(glm::vec4(L,B,-N,1));
  v_positions[3].push_back(glm::vec4(R,B,-N,1));

  v_positions[3].push_back(glm::vec4(F/N*L,F/N*T,-F,1));
  v_positions[3].push_back(glm::vec4(L,T,-N,1));
  v_positions[3].push_back(glm::vec4(F/N*R,F/N*T,-F,1));
  v_positions[3].push_back(glm::vec4(R,T,-N,1));
  v_positions[3].push_back(glm::vec4(F/N*L,F/N*B,-F,1));
  v_positions[3].push_back(glm::vec4(L,B,-N,1));
  v_positions[3].push_back(glm::vec4(F/N*R,F/N*B,-F,1));
  v_positions[3].push_back(glm::vec4(R,B,-N,1));

  v_positions[3].push_back(glm::vec4(F/N*L,F/N*T,-F,1));
  v_positions[3].push_back(glm::vec4(F/N*L,F/N*B,-F,1));
  v_positions[3].push_back(glm::vec4(F/N*R,F/N*T,-F,1));
  v_positions[3].push_back(glm::vec4(F/N*R,F/N*B,-F,1));
  v_positions[3].push_back(glm::vec4(F/N*L,F/N*T,-F,1));
  v_positions[3].push_back(glm::vec4(F/N*R,F/N*T,-F,1));
  v_positions[3].push_back(glm::vec4(F/N*L,F/N*B,-F,1));
  v_positions[3].push_back(glm::vec4(F/N*R,F/N*B,-F,1));

  v_positions[3].push_back(glm::vec4(0.0,0.0,0.0,1.0));

  for(int l=0;l<16;l++){
  v_colors[3].push_back(glm::vec4(1,0,1,1));
  cout<<glm::to_string(v_positions[3][l])<<endl;
  }

  for(int l=0;l<16;l++){
  v_colors[3].push_back(glm::vec4(0,1,1,1));
  // cout<<glm::to_string(v_positions[3][l])<<endl;
  }
  v_colors[3].push_back(glm::vec4(1,0,0,1));

  for(int l=0;l<v_positions[3].size();l++){
   cout<<glm::to_string(v_positions[3][l])<<endl;
   v_positions[3][l]=wcs_vcs_matrix_inverse*v_positions[3][l];
   cout<<glm::to_string(v_positions[3][l])<<endl;
  }
  
}

void draw_wcs(){
  final_matrix=glm::mat4(1.0f);
}

void draw_vcs(){
    draw_wcs();

  GLfloat vcs_wcs[16]={
    u[0], u[1], u[2], 0,
    v[0], v[1], v[2], 0,
    n[0], n[1], n[2], 0,
    E[0], E[1], E[2], 1
  };

    GLfloat wcs_vcs[16]={
    u[0], u[1], u[2], -1*E[0],
    v[0], v[1], v[2], -1*E[1],
    n[0], n[1], n[2], -1*E[2],
    0, 0, 0, 1
  };
  glm::mat4 wcs_vcs_matrix = glm::inverse(glm::make_mat4(vcs_wcs));
  final_matrix = wcs_vcs_matrix*final_matrix;
}

void draw_ccs(){
  draw_vcs();
  GLfloat Nm[16]={
    1,0,0,0,
    0,1,0,0,
    0,0,-(F+N)/(F-N), -2*F*N/(F-N),
    0,0,-1,0
  };
  GLfloat Sc[16]={
    2*N/(R-L), 0,0,0,
    0,2*N/(T-B),0,0,
    0,0,1,0,
    0,0,0,1
  };
  GLfloat Sh[16]={
    1,0,(R+L)/(2*N),0,
    0,1,(T+B)/(2*N),0,
    0,0,1,0,
    0,0,0,1
  };

  glm::mat4 vcs_to_ccs_matrix =glm::transpose( glm::make_mat4(Sh)*glm::make_mat4(Sc)*glm::make_mat4(Nm));
  final_matrix = vcs_to_ccs_matrix*final_matrix;
}

void draw_ndcs(){
  draw_ccs();
}

void draw_dcs(){
  draw_ndcs();
  GLfloat ndcs_to_dcs_matrix[16]={
    2,0,0,0,
    0,2,0,0,
    0,0,2,0,
    0,0,0,1
  };
  final_matrix=glm::make_mat4(ndcs_to_dcs_matrix)*final_matrix;
}
void vcs_to_ccs(){
  GLfloat Nm[16]={
    1,0,0,0,
    0,1,0,0,
    0,0,-(F+N)/(F-N), -2*F*N/(F-N),
    0,0,-1,0
  };
  GLfloat Sc[16]={
    2*N/(R-L), 0,0,0,
    0,2*N/(T-B),0,0,
    0,0,1,0,
    0,0,0,1
  };
  GLfloat Sh[16]={
    1,0,(R+L)/(2*N),0,
    0,1,(T+B)/(2*N),0,
    0,0,1,0,
    0,0,0,1
  };

  glm::mat4 vcs_to_ccs_matrix =glm::transpose( glm::make_mat4(Sh)*glm::make_mat4(Sc)*glm::make_mat4(Nm));
  for(int l=0;l<4;l++){
    for(int k=0;k<v_positions[l].size();k++){
      v_positions[l][k]=vcs_to_ccs_matrix * v_positions[l][k];
    }
  }
}

void ccs_to_ndcs(){
  for(int l=0;l<4;l++){
    for(int k=0;k<v_positions[l].size();k++){
      for(int i=0;i<4;i++){
        v_positions[l][k][i]=v_positions[l][k][i]/v_positions[l][k][3];
      }
    }
  }
}

void ndcs_to_dcs(){
  //glfwGetWindowSize(window,&height,&width);
  GLfloat ndcs_to_dcs_matrix[16]={
    2,0,0,0,
    0,2,0,0,
    0,0,2,0,
    0,0,0,1
  };

  for(int l=0;l<4;l++){
    for(int k=0;k<v_positions[l].size();k++){
      v_positions[l][k]=glm::make_mat4(ndcs_to_dcs_matrix) * v_positions[l][k];
    }
  }
}
/*
void add_vertex(GLdouble xpos, GLdouble ypos, GLdouble zpos){
    if(counter==0){
      initial_size=v_positions.size();
    }
    counter++;
    if(counter<=3){
      glm::vec4 posvec=glm::vec4(xpos,ypos,zpos,1.0);
      v_positions.push_back(posvec);
      GLdouble c1=1.0f;
      GLdouble c2=1.0f;
      GLdouble c3=1.0f;
      glm::vec4 colorvec=glm::vec4(c1,c2,c3,1.0);
      v_colors.push_back(colorvec);
      initBuffersGL();
   }
   else{
    v_positions.push_back(v_positions[initial_size]);
    v_positions.push_back(v_positions[v_positions.size()-2]);
    v_colors.push_back(v_colors[initial_size]);
    v_colors.push_back(v_colors[v_colors.size()-2]);
    glm::vec4 posvec=glm::vec4(xpos,ypos,zpos,1.0);
      v_positions.push_back(posvec);
      GLdouble c1=1.0f;
      GLdouble c2=1.0f;
      GLdouble c3=1.0f;
      glm::vec4 colorvec=glm::vec4(c1,c2,c3,1.0);
      v_colors.push_back(colorvec);
     
      initBuffersGL();
   }
}

void remove_vertex(){
  if(v_positions.size()==0){
    return;
  }
  if(counter>0 && counter<=3){
  std::cout<<glm::to_string(v_positions[v_colors.size()-1])<<std::endl;
  v_positions.pop_back();
  v_colors.pop_back();
  std::cout<<glm::to_string(v_positions[v_colors.size()-1])<<std::endl;
  initBuffersGL();
  if(counter>0)
  counter--;
  std::cout<<counter<<"\n";
  }
  else{
  v_positions.pop_back();
  v_colors.pop_back();
  v_positions.pop_back();
  v_colors.pop_back();
  v_positions.pop_back();
  v_colors.pop_back();
  initBuffersGL();
  if(counter>0)
  counter--;
  }

}

void save_file(std::string filename){
  std::ofstream myfile;
  myfile.open(filename.c_str());
  v_positions.resize((v_positions.size()/3)*3);
  v_colors.resize((v_colors.size()/3)*3);
  for(int i=0; i<v_positions.size();i++){
     myfile<<"("<<v_positions[i][0]<<','<<v_positions[i][1]<<','<<v_positions[i][2]<<','<<v_positions[i][3]<<",);";
     myfile<<"("<<v_colors[i][0]<<','<<v_colors[i][1]<<','<<v_colors[i][2]<<','<<v_colors[i][3]<<",);\n";
   }
   myfile.close();
}

void clear_screen(){
  v_positions.clear();
  v_colors.clear();
}*/
//-----------------------------------------------------------------


int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475 Assignment 1", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window); 

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
/*  std::cout<<"L: Load file\nS: Save file\nM: Modelling Mode\nI: Inspection Mode\nC: Clear Screen\n";
  std::cout<<"When in Inspection mode: \n Up, Down, Left, Right, PgUp, PgDn: rotation about X, Y and Z axis respectively\n R: move origin to centroid \n A,D,W,S,Z,X: move along X, Y and Z axes respectively\n";
  std::cout<<"When in modelling mode:\n Left click: add point with z=0\n Ctrl + Left Click: Add point with custom Z value\n Shift + Left Click: Remove Point\n";

  std::cout<<"Currently in Inspection Mode\n";*/
  load_all_models();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

