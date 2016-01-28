#ifndef _STARWARS_HPP_
#define _STARWARS_HPP_

#include <iostream>
#include "hierarchy_node.hpp"
#include "Basics.hpp"
#include <fstream>
class Humanoid{
	int n;
	csX75::HNode* hip;

	csX75::HNode* lThigh;
	csX75::HNode* lLowerLeg;
	csX75::HNode* lFoot;

	csX75::HNode* rThigh;
	csX75::HNode* rLowerLeg;
	csX75::HNode* rFoot;

	csX75::HNode* torso;

	csX75::HNode* lUpperArm;
	csX75::HNode* lLowerArm;
	csX75::HNode* lPalm;

	csX75::HNode* rUpperArm;
	csX75::HNode* rLowerArm;
	csX75::HNode* rPalm;

	csX75::HNode *neck;
	csX75::HNode *head;
	
public:
	csX75::HNode* parentNode;
	Humanoid();
	
	csX75::HNode* getNode(std::string node);
	void render();

	void initHip();
		
	void initThigh();
	void initLowerLeg();
	void initFoot();

	void initTorso();
	void initNeck();
	void initHead();
	
	void initUpperArm();
	void initLowerArm();
	void initPalm();
	void move_bot(GLfloat x, GLfloat y, GLfloat z);

};

class NonHumanoid{
	csX75::HNode* head;
	csX75::HNode* neck;
	csX75::HNode* body;

public:
	csX75::HNode *parentNode;
	NonHumanoid();
	csX75::HNode* getNode(std::string node);
	
	void initHead();
	void initNeck();
	void initBody();

	void render();
	void move_bot(GLfloat x, GLfloat y, GLfloat z);

};

class BackGround{
	int num_vertices;
	GLuint vao,vbo;
	// GLuint shaderProgramBG;
	GLuint tex;

	// glm::mat4 rotation_matrixBG;
	// glm::mat4 projection_matrixBG;
	// glm::mat4 c_rotation_matrixBG;
	// glm::mat4 lookat_matrixBG;

	// glm::mat4 model_matrixBG;
	// glm::mat4 view_matrixBG;


	// glm::mat4 modelview_matrixBG;
	// glm::mat3 normal_matrixBG;

	// GLuint uModelViewMatrixBG;
	// GLuint viewMatrixBG;
	// GLuint normalMatrixBG;

public:
	BackGround();
	void render();
};

class Land{
private:
	int num_vertices;
	GLuint vao, vbo;
	GLuint tex;
public:
	Land();
	void render();	
};

class Cone{
private:
	int num_vertices;
	GLuint vao, vbo;
	GLuint tex;
public:
	Cone();
	void render();	
};

class Starwars{
private:
	Humanoid* humanoidBot;
	NonHumanoid* nonHumanoidBot;
	BackGround* background;
	Land* land;
	Cone* cone;
public:
	csX75::HNode* curr_node;
	int currentBot;
	Starwars();
	void CurrentNode(std::string node);
	void render();
	void toggle_texture();

	void store_key_frames(std::ofstream & outfile);
	void load_key_frames(std::ifstream & infile);
	void moveBot(GLfloat x, GLfloat y, GLfloat z);

};
#endif




