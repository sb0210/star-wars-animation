#include "hierarchy_node.hpp"

#include <iostream>
 
extern GLuint vPosition,vColor,vNormal,vTex,uModelViewMatrix,viewMatrix,normalMatrix,b,diffuse,ambient,specular,shininess, enableTexture;
extern std::vector<glm::mat4> matrixStack;
float pi= 180;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, std::vector<glm::vec4> a_vertices, std::vector<glm::vec4> a_colours,std::vector<glm::vec4> a_normals, std::size_t v_size, std::size_t c_size, std::size_t n_size,bool e_tex,std::vector<glm::vec2> a_texture, std::string filename, int width, int height){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		normal_buffer_size= n_size;
		enable_texture= e_tex;
		if(enable_texture)
			texture_buffer_size=a_texture.size()*sizeof(glm::vec2);
		else
			texture_buffer_size=0;


		// initialize vao and vbo of the object;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		if(enable_texture){
			mytex=LoadTexture(filename.c_str(),width,height);
		}

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + normal_buffer_size + texture_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, &a_vertices[0] );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, &a_colours[0] );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, color_buffer_size, &a_normals[0] );
		if(enable_texture)
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + color_buffer_size, texture_buffer_size, &a_texture[0] );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));
		
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(2*vertex_buffer_size));

		if(enable_texture){
			glEnableVertexAttribArray( vTex );
			glVertexAttribPointer( vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3*vertex_buffer_size));
		}

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;
		jx=jy=jz=0;
		minx=miny=minz=-pi;
		maxx=maxy=maxz=pi;

		update_matrices();

		my_diffuse = glm::vec4(0.5, 0.5, 0.5, 1.0); 
		my_ambient = glm::vec4(0.1, 0.05, 0.05, 1.0);
		my_specular = glm::vec4(0.2, 0.2, 0.2, 1.0);
		my_shininess = 0.05;
	}

	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::apply_texture(){
		if(enable_texture){
			glBindTexture(GL_TEXTURE_2D, mytex);
		}
	}

	void HNode::toggle_texture(){
		enable_texture=!enable_texture;
		for(int i=0;i<children.size();i++){
			children[i]->toggle_texture();
		}
	}

	void HNode::store_key_frames(std::ofstream & outfile){
		outfile<<tx<<" "<<ty<<" "<<tz<<" "<<rx<<" "<<ry<<" "<<rz<<" "<<enable_texture<<std::endl;
		for(int i=0;i<children.size();i++){
			children[i]->store_key_frames(outfile);
		}
	}
	void HNode::load_key_frames(std::ifstream & infile){
		infile>>tx>>ty>>tz>>rx>>ry>>rz>>enable_texture;
		update_matrices();
		for(int i=0;i<children.size();i++){
			children[i]->load_key_frames(infile);
		}
	}
	void HNode::change_joint(GLfloat ajx, GLfloat ajy, GLfloat ajz){
		jx = ajx;
		jy = ajy;
		jz = ajz;

	}
	void HNode::change_only_angles(GLfloat arx, GLfloat ary, GLfloat arz){
		rx=rx+arx;
		ry=ry+ary;
		rz=rz+arz;
		update_matrices();
	}
	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);

		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		// std::cout<<glm::to_string(*ms_mult)<<std::endl;

		// normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix)));
  		glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(glm::mat3(*ms_mult)))));
  		glUniform4f(diffuse,my_diffuse[0],my_diffuse[1],my_diffuse[2],my_diffuse[3]);
  		glUniform4f(ambient,my_ambient[0],my_ambient[1],my_ambient[2],my_ambient[3]);
  		glUniform4f(specular,my_specular[0],my_specular[1],my_specular[2],my_specular[3]);
  		glUniform1f(shininess,my_shininess);
		

		if(enable_texture){
	  	  	glUniform1f( enableTexture,1);
			apply_texture();
		}
		else{
	  		glUniform1f( enableTexture,-1);
	  	}
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(glm::translate(glm::mat4(1.0f),glm::vec3(jx,jy,jz)));
		matrixStack.push_back(rotation);
		matrixStack.push_back(glm::translate(glm::mat4(1.0f),glm::vec3(-jx,-jy,-jz)));

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		rx=rx+15;
		if(rx<minx)
			rx=minx;
		if(rx>maxx)
			rx=maxx;
		update_matrices();
	}


	void HNode::inc_ry(){
		ry=ry+15;
		if(ry<miny)
			ry=miny;
		if(ry>maxy)
			ry=maxy;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz=rz+15;
		if(rz<minz)
			rz=minz;
		if(rz>maxz)
			rz=maxz;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx=rx-15;
		if(rx<minx)
			rx=minx;
		if(rx>maxx)
			rx=maxx;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry=ry-15;
		if(ry<miny)
			ry=miny;
		if(ry>maxy)
			ry=maxy;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz=rz-15;
		if(rz<minz)
			rz=minz;
		if(rz>maxz)
			rz=maxz;
		update_matrices();
	}

	void HNode::change_angle_parameters(GLfloat a_minx,GLfloat a_maxx,GLfloat a_miny,GLfloat a_maxy,GLfloat a_minz,GLfloat a_maxz){
		minx=a_minx;
		maxx=a_maxx;
		miny=a_miny;
		maxy=a_maxy;
		minz=a_minz;
		maxz=a_maxz;
	}

	void HNode::move_bot(GLfloat x, GLfloat y, GLfloat z){
		tx = tx + x;
		ty = ty + y;
		tz = tz + z;
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}