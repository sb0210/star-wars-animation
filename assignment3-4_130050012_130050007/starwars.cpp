//cuboid
//disk


#ifndef _GL_FRAMEWORK_CPP_
#define _GL_FRAMEWORK_CPP_

#include "starwars.hpp"
#include <vector>
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <cmath>
#include "texture.hpp"

glm::vec4 white=glm::vec4(1.0,1.0,1.0,1.0);
glm::vec4 red=glm::vec4(1.0,0,0,1.0);
glm::vec4 blue=glm::vec4(0,0,1.0,1.0);
glm::vec4 green=glm::vec4(0,1.0,0,1.0);
const int num_vertices = 36;
extern float L,R,T,B,N,F;
extern float c_xpos,c_ypos, c_zpos, c_xrot,c_yrot,c_zrot,c_up_x,c_up_y,c_up_z;
extern GLuint vPosition,vColor,vNormal,vTex,uModelViewMatrix,viewMatrix,normalMatrix,b,is_cone;
extern glm::mat4 view_matrix;

/*Starwars*/
	Starwars::Starwars(){
		humanoidBot = new Humanoid();
		nonHumanoidBot = new NonHumanoid();
		background = new BackGround();
		land =  new Land();
		cone = new Cone();
		curr_node = humanoidBot->parentNode;
		currentBot=0;
	}

	void Starwars::CurrentNode(std::string node){
		if(currentBot==0)
			curr_node=humanoidBot->getNode(node);
		else
			curr_node=nonHumanoidBot->getNode(node);
	}

	void Starwars::toggle_texture(){
		(humanoidBot->parentNode)->toggle_texture();
		(nonHumanoidBot->parentNode)->toggle_texture();
	}
	void Starwars::render(){

		glUniform1f(is_cone,-1);
		glUniform1f(b,1);
		background->render();
		glUniform1f(b,-1);
		glUniform1f(is_cone,1);
		land->render();
		cone->render();
		glUniform1f(is_cone,-1);
		humanoidBot->render();
		nonHumanoidBot->render();


	}
	void Starwars::store_key_frames(std::ofstream & outfile){
		(humanoidBot->parentNode)->store_key_frames(outfile);
		(nonHumanoidBot->parentNode)->store_key_frames(outfile);
	}

	void Starwars::load_key_frames(std::ifstream & infile){
		(humanoidBot->parentNode)->load_key_frames(infile);
		(nonHumanoidBot->parentNode)->load_key_frames(infile);
	}

	void Starwars::moveBot(GLfloat x, GLfloat y, GLfloat z){
		if(currentBot==0)
			humanoidBot->move_bot(x,y,z);
		else
			nonHumanoidBot->move_bot(x,y,z);
	}
/*humanoid*/
	Humanoid::Humanoid(){
		initHip();
		initThigh();
		initLowerLeg();
		initFoot();
		initTorso();
		initUpperArm();
		initLowerArm();
		initPalm();
		initNeck();
		initHead();
		parentNode=hip;
		return;
	}
	void Humanoid::render(){
		parentNode->render_tree();
		return;
	}
	void Humanoid::initHip(){
		std::vector<glm::vec4> temp,temp_c, temp_n;
		std::vector<glm::vec4> pos_draw=Basics::drawArcCylinder(0.75,5,-pi/2,pi/2,temp_n);
		temp=Basics::drawDisk(0.75,100,-pi/2,pi/2,temp_n);
		tr(temp,0,0,0,0,2.5,0, temp_n);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		temp=Basics::drawDisk(0.75,100,pi/2,3*pi/2, temp_n);
		tr(temp,0,0,pi,0,-2.5,0, temp_n);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		temp=Basics::drawCuboid(1,5,1.5,temp_n);
		temp_n.insert(temp_n.end(),temp.begin(),temp.end());
		tr(temp,0,0,0,-0.5,0,0,temp_n);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		tr(pos_draw,0,0,pi/2,0,0,0,temp_n);
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,white);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		hip = new csX75::HNode(NULL,pos_draw.size(),pos_draw,col_draw,temp_n,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		hip->change_parameters(0,8.75,0,0,0,0);
	}
	void Humanoid::initThigh(){
		std::vector<glm::vec4> temp,temp_c,nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawFrustumCone(0.75,0.6,3,nor_draw);
		temp=Basics::drawArc(0.75,0,pi,0,pi,nor_draw);
		tr(temp,0,0,0,0,1.5,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		temp=Basics::drawArc(0.6,pi,2*pi,0,pi,nor_draw);
		tr(temp,0,0,0,0,-1.5,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,red);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		lThigh = new csX75::HNode(hip,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,600);
		rThigh = new csX75::HNode(hip,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,600);
		lThigh->change_parameters(-1.25,-2.5,0,0,0,0);
		lThigh->change_joint(0,1.5,0);
		rThigh->change_parameters(1.25,-2.5,0,0,0,0);
		rThigh->change_joint(0,1.5,0);
	}
	void Humanoid::initLowerLeg(){
		std::vector<glm::vec4> temp,temp_c,nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawFrustumCone(0.6,0.5,3,nor_draw);
		temp=Basics::drawArc(0.6,0,pi,0,pi,nor_draw);
		tr(temp,0,0,0,0,1.5,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		temp=Basics::drawArc(0.5,pi,2*pi,0,pi,nor_draw);
		tr(temp,0,0,0,0,-1.5,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,blue);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		lLowerLeg = new csX75::HNode(lThigh,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		rLowerLeg = new csX75::HNode(rThigh,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		lLowerLeg->change_parameters(0,-3,0,0,0,0);
		lLowerLeg->change_joint(0,1.5,0);
		rLowerLeg->change_parameters(0,-3,0,0,0,0);
		rLowerLeg->change_joint(0,1.5,0);
		lLowerLeg->change_angle_parameters(0,180,0,0,0,0);
		rLowerLeg->change_angle_parameters(0,180,0,0,0,0);
	}
	void Humanoid::initTorso(){
		std::vector<glm::vec4> temp,temp_c,nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawCuboid(4.5,5,1.5,nor_draw);
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,green);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		torso = new csX75::HNode(hip,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		torso->change_parameters(0,2.5,0,0,0,0);
		torso->change_joint(0,-2.5,0);
	}
	void Humanoid::initNeck(){
		std::vector<glm::vec4> nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawNeck(0.75,0.65,2,nor_draw);
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,green);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		neck = new csX75::HNode(torso,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		neck->change_parameters(0,3.25,0,0,0,0);
		neck->change_joint(0,-1,0);
	}
	void Humanoid::initUpperArm(){
		std::vector<glm::vec4> temp,temp_c,nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawFrustumCone(0.5,0.4,2,nor_draw);
		temp=Basics::drawArc(0.5,0,pi,0,pi,nor_draw);
		tr(temp,0,0,0,0,1,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		temp=Basics::drawArc(0.4,pi,2*pi,0,pi,nor_draw);
		tr(temp,0,0,0,0,-1,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,red);
		tr(pos_draw,0,0,3*pi/2,0,0,0,nor_draw);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		lUpperArm = new csX75::HNode(torso,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		tr(pos_draw,0,0,pi,0,0,0,nor_draw);
		rUpperArm = new csX75::HNode(torso,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		lUpperArm->change_parameters(-3.25,1.5,0,0,0,0);
		lUpperArm->change_joint(1,0,0);
		rUpperArm->change_parameters(3.25,1.5,0,0,0,0);
		rUpperArm->change_joint(-1,0,0);
	}
	void Humanoid::initLowerArm(){
		std::vector<glm::vec4> temp,temp_c,nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawFrustumCone(0.4,0.3,2,nor_draw);
		temp=Basics::drawArc(0.4,0,pi,0,pi,nor_draw);
		tr(temp,0,0,0,0,1,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		temp=Basics::drawArc(0.3,pi,2*pi,0,pi,nor_draw);
		tr(temp,0,0,0,0,-1,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,red);
		tr(pos_draw,0,0,pi/2,0,0,0,nor_draw);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		lLowerArm = new csX75::HNode(lUpperArm,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		tr(pos_draw,0,0,pi,0,0,0,nor_draw);
		rLowerArm = new csX75::HNode(rUpperArm,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		lLowerArm->change_parameters(-2,0,0,0,0,0);
		lLowerArm->change_joint(1,0,0);
		rLowerArm->change_parameters(2,0,0,0,0,0);
		rLowerArm->change_joint(-1,0,0);
		lLowerArm->change_angle_parameters(0,0,0,0,-180,0);
		rLowerArm->change_angle_parameters(0,0,0,0,0,180);
	}
	void Humanoid::initPalm(){
		std::vector<glm::vec4> nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawSphere(0.5,nor_draw);
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,white);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		lPalm = new csX75::HNode(lLowerArm,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		rPalm = new csX75::HNode(rLowerArm,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		lPalm->change_parameters(-1.5,0,0,0,0,0);
		lPalm->change_joint(0.5,0,0);
		rPalm->change_parameters(1.5,0,0,0,0,0);
		rPalm->change_joint(-0.5,0,0);
	}
	void Humanoid::initHead(){
		std::vector<glm::vec4> nor_draw,temp_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawEllipsoid(1,1.25,0,2*pi,0,pi,nor_draw);
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,white);
		tr(pos_draw,pi/2,0,0,0,0,0,nor_draw);
		std::vector<glm::vec4> temp_pos_draw=Basics::drawEllipsoid(0.1,0.2,0,2*pi,0,pi,temp_draw);
		std::vector<glm::vec4> col1_draw=Basics::getColor(temp_pos_draw,glm::vec4(0,0,0,1.0));
		tr(temp_pos_draw,0,pi/2,0,0.5,0.75,0.8,temp_draw);
		pos_draw.insert(pos_draw.end(),temp_pos_draw.begin(),temp_pos_draw.end());
		nor_draw.insert(nor_draw.end(),temp_draw.begin(),temp_draw.end());
		col_draw.insert(col_draw.end(),col1_draw.begin(),col1_draw.end());
		
		tr(temp_pos_draw,0,0,0,-1,0,0,temp_draw);
		pos_draw.insert(pos_draw.end(),temp_pos_draw.begin(),temp_pos_draw.end());
		nor_draw.insert(nor_draw.end(),temp_draw.begin(),temp_draw.end());
		col_draw.insert(col_draw.end(),col1_draw.begin(),col1_draw.end());

		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		head = new csX75::HNode(neck,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		head->change_parameters(0,1.625,0,0,0,0);
		head->change_joint(0,-1.25,0);
	}
	void Humanoid::initFoot(){
		std::vector<glm::vec4> temp,temp_c,nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawFrustumCone(0.3,0.5,1.5,nor_draw);
		temp=Basics::drawArc(0.3,0,pi,0,pi,nor_draw);
		tr(temp,0,0,0,0,0.75,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		temp=Basics::drawDisk(0.5,100,0,2*pi,nor_draw);
		tr(temp,0,0,0,0,-0.75,0,nor_draw);
		pos_draw.insert(pos_draw.end(),temp.begin(),temp.end());
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,white);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		lFoot = new csX75::HNode(lLowerLeg,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		rFoot = new csX75::HNode(rLowerLeg,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/all_humanoid.bmp",600,400);
		lFoot->change_parameters(0,-2.55,0,0,0,0);
		lFoot->change_joint(0,1.05,0);
		rFoot->change_parameters(0,-2.55,0,0,0,0);
		rFoot->change_joint(0,1.05,0);
	}
	void Humanoid::move_bot(GLfloat x, GLfloat y, GLfloat z){
		parentNode->move_bot(x,y,z);
	}
	csX75::HNode* Humanoid::getNode(std::string node){
		if(node=="hip")
			return hip;
		if(node=="lThigh")
			return lThigh;
		if(node=="rThigh")
			return rThigh;
		if(node=="lLowerLeg")
			return lLowerLeg;
		if(node=="rLowerLeg")
			return rLowerLeg;
		if(node=="lFoot")
			return lFoot;
		if(node=="rFoot")
			return rFoot;
		if(node=="lUpperArm")
			return lUpperArm;
		if(node=="rUpperArm")
			return rUpperArm;
		if(node=="lLowerArm")
			return lLowerArm;
		if(node=="rLowerArm")
			return rLowerArm;
		if(node=="lPalm")
			return lPalm;
		if(node=="rPalm")
			return rPalm;
		if(node=="head")
			return head;
		if(node=="neck")
			return neck;
		if(node=="torso")
			return torso;
		if(node=="parent")
			return parentNode;
		return parentNode;
	}
/* Non Humanoid -------------------------------------------------------------------------------*/

	NonHumanoid::NonHumanoid(){
		initNeck();
		initHead();
		initBody();
		parentNode=neck;
	}
	void NonHumanoid::initBody(){

		std::vector<glm::vec4> temp,temp_n;
		std::vector<glm::vec4> nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawSphere(2,nor_draw);
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,red);
		std::vector<glm::vec2> tex_draw = Basics::calcUVsphere(pos_draw);
		body = new csX75::HNode(neck,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),nor_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/body_nonhumanoid.bmp",294,252);
		body->change_parameters(0,-2,0,0,0,0);
	}
	void NonHumanoid::initNeck(){
		std::vector<glm::vec4> temp,temp_n;
		std::vector<glm::vec4> nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawSphere(0,nor_draw);
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,white);
		neck = new csX75::HNode(NULL,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),nor_draw.size()*sizeof(glm::vec4));
		neck->change_parameters(5,4,0,0,0,0);
	}
	void NonHumanoid::initHead(){
		std::vector<glm::vec4> temp,temp_n;
		std::vector<glm::vec4> nor_draw;
		std::vector<glm::vec4> pos_draw=Basics::drawArc(1.5,0,pi,0,pi,nor_draw);
		std::vector<glm::vec4> col_draw=Basics::getColor(pos_draw,blue);
		std::vector<glm::vec2> tex_draw = Basics::calcUVhemisphere(pos_draw);
		head = new csX75::HNode(neck,pos_draw.size(),pos_draw,col_draw,nor_draw,pos_draw.size()*sizeof(glm::vec4),pos_draw.size()*sizeof(glm::vec4),nor_draw.size()*sizeof(glm::vec4),1,tex_draw,"images/head_nonhumanoid.bmp",1300,1117);
		head->change_angle_parameters(-30,30,-180,180,-30,30);
	}
	csX75::HNode* NonHumanoid::getNode(std::string node){
		if(node=="body")
			return body;
		if(node=="neck")
			return neck;
		if(node=="head")
			return head;
		return parentNode;
	}
	void NonHumanoid::render(){
		parentNode->render_tree();
	}
	void NonHumanoid::move_bot(GLfloat x, GLfloat y, GLfloat z){
		parentNode->move_bot(x,y,z);
		GLfloat dx=x*60,dy=y*60,dz=z*60;
		body->change_only_angles(dz,dy,-dx);
	}	
/* background */
	BackGround::BackGround(){

		num_vertices=36;
		// Load Textures 
		tex=LoadTexture("images/spherical.bmp",1024,512);
		glBindTexture(GL_TEXTURE_2D, tex);

		//Ask GL for two Vertex Attribute Objects (vao) , one for the sphere and one for the wireframe
		glGenVertexArrays (1, &vao);
		//Ask GL for two Vertex Buffer Object (vbo)    
		glGenBuffers (1, &vbo);

		//Set 0 as the current array to be used by binding it
		glBindVertexArray (vao);    
		//Set 0 as the current buffer to be used by binding it
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		std::vector<glm::vec4> v_norms;
		std::vector<glm::vec4> v_positions = Basics::drawSphere(70,v_norms);
		std::vector<glm::vec2> tex_coords = Basics::calcUVsphere(v_positions);


		//Copy the points into the current buffer
		glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec4)*(v_positions).size() + sizeof(glm::vec2)*tex_coords.size() , NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0,sizeof(glm::vec4)*(v_positions).size(), &v_positions[0] );
		glBufferSubData( GL_ARRAY_BUFFER, sizeof(glm::vec4)*(v_positions).size(), sizeof(glm::vec2)*tex_coords.size(), &tex_coords[0]);
		// glBufferSubData( GL_ARRAY_BUFFER, sizeof(tex_coords)+sizeof(v_positions), sizeof(v_normals), &v_normals[0] );

		// set up vertex array
		//Position
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		//Textures
		glEnableVertexAttribArray( vTex );
		glVertexAttribPointer( vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4)*(v_positions).size()));
		num_vertices=v_positions.size();
	}
	void BackGround::render(){


		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glBindVertexArray (vao);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);
		
	}
/* land */
	Land::Land(){
		num_vertices=36;

		// Load Textures 
		tex=LoadTexture("images/asteroid.bmp",2560,2029);
		glBindTexture(GL_TEXTURE_2D, tex);

		//Ask GL for two Vertex Attribute Objects (vao) , one for the sphere and one for the wireframe
		glGenVertexArrays (1, &vao);
		//Ask GL for two Vertex Buffer Object (vbo)    
		glGenBuffers (1, &vbo);

		//Set 0 as the current array to be used by binding it
		glBindVertexArray (vao);    
		//Set 0 as the current buffer to be used by binding it
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		std::vector<glm::vec4> v_norms;
		std::vector<glm::vec4> v_positions = Basics::drawDisk(30,100,0,2*pi,v_norms);
		std::vector<glm::vec2> tex_coords = Basics::calcUVsphere(v_positions);



		//Copy the points into the current buffer
		glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size()*2+sizeof(glm::vec2)*tex_coords.size() , NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER,0,sizeof(glm::vec4)*(v_positions).size(), &v_positions[0] );
		glBufferSubData( GL_ARRAY_BUFFER,sizeof(glm::vec4)*(v_positions).size(),sizeof(glm::vec4)*(v_norms).size(), &v_norms[0] );
		glBufferSubData( GL_ARRAY_BUFFER,sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size(),sizeof(glm::vec4)*v_norms.size(), &v_norms[0]);
		glBufferSubData( GL_ARRAY_BUFFER,sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size()*2,sizeof(glm::vec2)*tex_coords.size(), &tex_coords[0]);
		// glBufferSubData( GL_ARRAY_BUFFER, sizeof(tex_coords)+sizeof(v_positions), sizeof(v_normals), &v_normals[0] );

		// set up vertex array
		//Position
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4)*(v_positions).size()));

		//Textures
		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size()));

		//Textures
		glEnableVertexAttribArray( vTex );
		glVertexAttribPointer( vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size()*2));
		num_vertices=v_positions.size();
	}

	void Land::render(){

		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(glm::mat3(view_matrix)))));
		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glBindVertexArray (vao);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);
		
	}
/*Cone*/
	Cone::Cone(){
		num_vertices=36;

		// Load Textures 
		tex=LoadTexture("images/asteroid.bmp",2560,2029);
		glBindTexture(GL_TEXTURE_2D, tex);

		//Ask GL for two Vertex Attribute Objects (vao) , one for the sphere and one for the wireframe
		glGenVertexArrays (1, &vao);
		//Ask GL for two Vertex Buffer Object (vbo)    
		glGenBuffers (1, &vbo);

		//Set 0 as the current array to be used by binding it
		glBindVertexArray (vao);    
		//Set 0 as the current buffer to be used by binding it
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		std::vector<glm::vec4> v_norms;
		std::vector<glm::vec4> v_positions =Basics::drawFrustum(30,0,45,100,v_norms,0);
		tr(v_positions,0,0,0,0,-22.5,0,v_norms);
		std::vector<glm::vec2> tex_coords = Basics::calcUVsphere(v_positions);



		//Copy the points into the current buffer
		glBufferData (GL_ARRAY_BUFFER, sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size()*2+sizeof(glm::vec2)*tex_coords.size() , NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER,0,sizeof(glm::vec4)*(v_positions).size(), &v_positions[0] );
		glBufferSubData( GL_ARRAY_BUFFER,sizeof(glm::vec4)*(v_positions).size(),sizeof(glm::vec4)*(v_norms).size(), &v_norms[0] );
		glBufferSubData( GL_ARRAY_BUFFER,sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size(),sizeof(glm::vec4)*v_norms.size(), &v_norms[0]);
		glBufferSubData( GL_ARRAY_BUFFER,sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size()*2,sizeof(glm::vec2)*tex_coords.size(), &tex_coords[0]);
		// glBufferSubData( GL_ARRAY_BUFFER, sizeof(tex_coords)+sizeof(v_positions), sizeof(v_normals), &v_normals[0] );

		// set up vertex array
		//Position
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
		
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4)*(v_positions).size()));

		//Textures
		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size()));

		//Textures
		glEnableVertexAttribArray( vTex );
		glVertexAttribPointer( vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(glm::vec4)*(v_positions).size()+sizeof(glm::vec4)*(v_norms).size()*2));
		num_vertices=v_positions.size();
	}

	void Cone::render(){

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glBindVertexArray (vao);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);
		
	}

#endif

