#ifndef _HNODE_HPP_
#define _HNODE_HPP_

#include "include.hpp"
#include "texture.hpp"
#include <fstream>
namespace csX75	 { 

	// A simple class that represents a node in the hierarchy tree
	class HNode {
		//glm::vec4 * vertices;
		//glm::vec4 * colors;
		GLfloat tx,ty,tz,rx,ry,rz,jx,jy,jz;
		GLfloat minx,miny,minz,maxx,maxy,maxz;

		std::size_t vertex_buffer_size;
		std::size_t color_buffer_size;
		std::size_t normal_buffer_size;
		std::size_t texture_buffer_size;

		GLuint num_vertices;
		GLuint vao,vbo;

		glm::mat4 rotation;
		glm::mat4 translation;
		
		std::vector<HNode*> children;
		HNode* parent;
		bool enable_texture;
		GLuint mytex;



		glm::vec4 my_diffuse; 
		glm::vec4 my_ambient;
		glm::vec4 my_specular;
		float my_shininess;


		void update_matrices();

	  public:
		HNode (HNode*, GLuint, std::vector<glm::vec4>,  std::vector<glm::vec4>, std::vector<glm::vec4>, std::size_t,  std::size_t, std::size_t,bool e_tex=0,std::vector<glm::vec2> a_texture = std::vector<glm::vec2>(), std::string filename="images/all.bmp", int width=512,int height=512);

		//HNode (HNode* , glm::vec4*,  glm::vec4*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		
		void add_child(HNode*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void change_joint(GLfloat ajx, GLfloat ajy, GLfloat ajz);
		void render_tree();
		void apply_texture();
		void toggle_texture();
		void change_angle_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void change_only_angles(GLfloat arx, GLfloat ary, GLfloat arz);
		void move_bot(GLfloat x, GLfloat y, GLfloat z);
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
		void store_key_frames(std::ofstream & outfile);
		void load_key_frames(std::ifstream & infile);
	};

	glm::mat4* multiply_stack(std::vector <glm::mat4> );
};	

#endif