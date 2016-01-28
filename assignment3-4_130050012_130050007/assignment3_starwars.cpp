/* Assignment 3-4 
Name : Siddharth Bulia & Charmi Dedhia
Roll : 130050012 & 130070007 
*/
#include "assignment3_starwars.hpp"
#include "play_backUtils.cpp"

GLuint shaderProgram;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;
glm::mat3 normal_matrix;

GLuint uModelViewMatrix;
GLuint viewMatrix;
GLuint normalMatrix;
GLint b, enableTexture, is_cone;
float L=-5,R=5,B=-5,T=5,N=5,F=150;
GLuint enableLight1,enableLight2, enableLight3;
GLint diffuse,ambient,specular,shininess;
float light1=1,light2=1,light3=1; 
int enable_animation=0;

int fps = 30;
std::ofstream outfile;
std::ifstream infile;

bool recording=true;
unsigned int framenum=0;
unsigned char *pRGB;

int SCREEN_WIDTH=512;
int SCREEN_HEIGHT=512;


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
  sprintf(filename,"frames/frame_%04d.ppm",framenum);
  std::ofstream out(filename, std::ios::out);
  out<<"P6"<<std::endl;
  out<<SCREEN_WIDTH<<" "<<SCREEN_HEIGHT<<" 255"<<std::endl;
  out.write(reinterpret_cast<char const *>(pRGB), (3 * (SCREEN_WIDTH+1) * (SCREEN_HEIGHT + 1)) * sizeof(int));
  out.close();

  //function to store pRGB in a file named count
  delete pRGB;
}



void zoom_in(float val){
    glm::vec3 camera = glm::vec3(c_xpos,c_ypos, c_zpos);
    glm::vec3 camera_target = glm::vec3(c_tx,c_ty, c_tz);
    glm::vec3 dir = glm::normalize(camera_target - camera);
    camera = camera + val*dir;
    c_xpos = camera.x;
    c_ypos = camera.y;
    c_zpos = camera.z;
}

void rotate_around_lookat(float xrot, float yrot, float zrot){
    glm::mat4 temp_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
    temp_rotation_matrix = glm::rotate(temp_rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
    temp_rotation_matrix = glm::rotate(temp_rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));

    glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0);
    glm::vec4 c_up = temp_rotation_matrix * glm::vec4(c_up_x,c_up_y,c_up_z, 1.0);
    glm::vec4 c_lookatPos = glm::vec4(c_tx,c_ty,c_tz,1.0);

    glm::mat4 lookat_trans1= glm::translate(glm::mat4(1.0f), glm::vec3(-c_lookatPos));
    glm::mat4 lookat_trans2 = glm::translate(glm::mat4(1.0f),glm::vec3(c_lookatPos));
    glm::mat4 lookat_trans =lookat_trans2 * temp_rotation_matrix*lookat_trans1;
    glm::vec4 new_camera = lookat_trans * glm::vec4(c_xpos,c_ypos,c_zpos,1.0);
    c_xpos =new_camera.x;
    c_ypos =new_camera.y;
    c_zpos =new_camera.z;

    c_up_x = c_up.x;
    c_up_y = c_up.y;
    c_up_z = c_up.z;

}

void rotate_around_camera(float xrot,float yrot,float zrot){

    glm::mat4 temp_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
    temp_rotation_matrix = glm::rotate(temp_rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
    temp_rotation_matrix = glm::rotate(temp_rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));

    glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0);
    glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0);
    glm::vec4 c_lookatPos = glm::vec4(c_tx,c_ty,c_tz,1.0);

    glm::mat4 lookat_trans1= glm::translate(glm::mat4(1.0f), glm::vec3(-c_pos));
    glm::mat4 lookat_trans2 = glm::translate(glm::mat4(1.0f),glm::vec3(c_pos));
    glm::mat4 lookat_trans =lookat_trans2 * temp_rotation_matrix*lookat_trans1;
    glm::vec4 new_cameratarget = lookat_trans * glm::vec4(c_tx, c_ty, c_tz,1.0);
    c_up = temp_rotation_matrix * c_up;
    c_tx =new_cameratarget.x;
    c_ty =new_cameratarget.y;
    c_tz =new_cameratarget.z;

    c_up_x = c_up.x;
    c_up_y = c_up.y;
    c_up_z = c_up.z;

}

void initBuffersGL(void)
{

    // Load shaders and use the resulting shader program
    std::string vertex_shader_file("07_vshader.glsl");
    std::string fragment_shader_file("07_fshader.glsl");

    std::vector<GLuint> shaderList;
    shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

    shaderProgram = csX75::CreateProgramGL(shaderList);
    glUseProgram( shaderProgram );

    // getting the attributes from the shader program
    vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
    vNormal = glGetAttribLocation( shaderProgram, "vNormal" ); 
    vTex = glGetAttribLocation(shaderProgram, "vTex");
    uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
    viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
    normalMatrix = glGetUniformLocation( shaderProgram, "normalMatrix");
    b = glGetUniformLocation(shaderProgram, "b");
    is_cone = glGetUniformLocation(shaderProgram, "is_cone");
    enableTexture=glGetUniformLocation(shaderProgram, "enable_texture");
    enableLight1=glGetUniformLocation(shaderProgram, "light1");
    enableLight2=glGetUniformLocation(shaderProgram, "light2");
    enableLight3=glGetUniformLocation(shaderProgram, "light3");
    diffuse = glGetUniformLocation(shaderProgram, "diffuse");
    ambient = glGetUniformLocation(shaderProgram, "ambient");
    specular = glGetUniformLocation(shaderProgram, "specular");
    shininess = glGetUniformLocation(shaderProgram, "shininess");


    //note that the buffers are initialized in the e constructors
    starwars = new Starwars();
    outfile.open("keyframes.txt", std::ios_base::app);
}


void renderGL(void)
{
    if(enable_animation){
        call_back();
      
        if(recording){
            capture_frame(framenum++);
          
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    matrixStack.clear();

    //Creating the lookat and the up vectors for the camera
    //Creating the lookat matrix
    lookat_matrix = glm::lookAt(glm::vec3(c_xpos,c_ypos,c_zpos),glm::vec3(c_tx,c_ty,c_tz),glm::vec3( c_up_x,c_up_y,c_up_z));


    //creating the projection matrix
    if(enable_perspective)
        projection_matrix = glm::frustum(L,R,B,T,N,F);
    else
        projection_matrix = glm::ortho(2*L,2*R,2*B,2*T,N,F);

    view_matrix = projection_matrix*lookat_matrix;
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
    matrixStack.push_back(view_matrix);
    glUniform1f(enableLight1,light1);
    glUniform1f(enableLight2,light2);
    glUniform1f(enableLight3,light3);

    starwars->render();

}

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
    window = glfwCreateWindow(512, 512, "Assignment 4", NULL, NULL);
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

    //Print and see what context got enabled
    std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
    std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
    std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
    std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

    //Keyboard Callback
    glfwSetKeyCallback(window, csX75::key_callback);
    //Framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Initialize GL state
    csX75::initGL();
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

