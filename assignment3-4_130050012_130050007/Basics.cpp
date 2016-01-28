#include "Basics.hpp"

void tr(std::vector<glm::vec4> & vec, float rot_x,float rot_y, float rot_z, float tra_x, float tra_y, float tra_z, std::vector<glm::vec4> &norm){
	float mat_x[16]={
		1,0,0,0,
		0,cos(rot_x),-sin(rot_x),0,
		0,sin(rot_x),cos(rot_x),0,
		0,0,0,1
	};
	float mat_y[16]={
		cos(rot_y),0,sin(rot_y),0,
		0,1,0,0,
		-sin(rot_y),0,cos(rot_y),0,
		0,0,0,1
	};
	float mat_z[16]={
		cos(rot_z),-sin(rot_z),0,0,
		sin(rot_z),cos(rot_z),0,0,
		0,0,1,0,
		0,0,0,1
	};
	float mat[16]={
		1,0,0,tra_x,
		0,1,0,tra_y,
		0,0,1,tra_z,
		0,0,0,1
	};
	glm::mat4 matrix = glm::transpose(glm::make_mat4(mat_x)*glm::make_mat4(mat_y)*glm::make_mat4(mat_z)*glm::make_mat4(mat));
	glm::mat4 norm_matrix= glm::transpose(glm::inverse(matrix));
	for(int i=0;i<vec.size();i++){
		vec[i]=matrix*vec[i];
		norm[norm.size()-vec.size()+i]=norm_matrix*norm[norm.size()-vec.size()+i];
	}
	return;
}
// Basics::quad generates two triangles for each face and assigns colors to the vertices
void Basics::quad(int a, int b, int c, int d,  glm::vec4* positions, glm::vec4* colors, std::vector<glm::vec4> &v_positions,std::vector<glm::vec4> &v_colors,int & tri_idx){
	v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
	v_colors[tri_idx] = colors[b]; v_positions[tri_idx] = positions[b]; tri_idx++;
	v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
	v_colors[tri_idx] = colors[a]; v_positions[tri_idx] = positions[a]; tri_idx++;
	v_colors[tri_idx] = colors[c]; v_positions[tri_idx] = positions[c]; tri_idx++;
	v_colors[tri_idx] = colors[d]; v_positions[tri_idx] = positions[d]; tri_idx++;
}

void Basics::quad1(int a, int b, int c, int d, glm::vec4 color,int face, glm::vec4* positions, std::vector<std::vector<glm::vec2> > t_coords ,
		 std::vector<glm::vec4> &v_positions,std::vector<glm::vec4> &v_colors,std::vector<glm::vec2> &tex_coords,int & tri_idx)
{
  face=face+1;
  // face=0;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[a]; 
  // v_normals[tri_idx] = normals[a]; 
  tex_coords[tri_idx] = t_coords[face][3];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[b];
  // v_normals[tri_idx] = normals[b]; 
  tex_coords[tri_idx] = t_coords[face][1];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[c]; 
  // v_normals[tri_idx] = normals[c]; 
  tex_coords[tri_idx] = t_coords[face][0];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[a]; 
  // v_normals[tri_idx] = normals[a]; 
  tex_coords[tri_idx] = t_coords[face][3];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[c]; 
  // v_normals[tri_idx] = normals[c]; 
  tex_coords[tri_idx] = t_coords[face][0];
  tri_idx++;
  v_colors[tri_idx] = color; v_positions[tri_idx] = positions[d]; 
  // v_normals[tri_idx] = normals[d]; 
  tex_coords[tri_idx] = t_coords[face][2];
  tri_idx++;
 }
/*Basics*/
	std::vector<glm::vec4> Basics::drawCube(
		float l,
		// std::vector<glm::vec4> &normals,
		std::vector<glm::vec2> &tex_coords
		)
	{

		std::vector<glm::vec4> vec(36);
		std::vector<glm::vec4> vec_c(36);
		tex_coords.resize(36);

		const int num_vertices = 36;

		// glm::vec4 texCoordinates[8];
		//Eight vertices in homogenous coordinates
		float len=l;
		glm::vec4 positions[8] = {
		  glm::vec4(-len, -len, len, 1.0),
		  glm::vec4(-len, len, len, 1.0),
		  glm::vec4(len, len, len, 1.0),
		  glm::vec4(len, -len, len, 1.0),
		  glm::vec4(-len, -len, -len, 1.0),
		  glm::vec4(-len, len, -len, 1.0),
		  glm::vec4(len, len, -len, 1.0),
		  glm::vec4(len, -len, -len, 1.0)
		};
		glm::vec4 normals[8] = {
		  glm::vec4(-len, -len, len, 1.0),
		  glm::vec4(-len, len, len, 1.0),
		  glm::vec4(len, len, len, 1.0),
		  glm::vec4(len, -len, len, 1.0),
		  glm::vec4(-len, -len, -len, 1.0),
		  glm::vec4(-len, len, -len, 1.0),
		  glm::vec4(len, len, -len, 1.0),
		  glm::vec4(len, -len, -len, 1.0)
		};
		//RGBA colors
		glm::vec4 colors[8] = {
		  glm::vec4(0.0, 0.0, 0.0, 1.0),
		  glm::vec4(1.0, 0.0, 0.0, 1.0),
		  glm::vec4(1.0, 1.0, 0.0, 1.0),
		  glm::vec4(0.0, 1.0, 0.0, 1.0),
		  glm::vec4(0.0, 0.0, 1.0, 1.0),
		  glm::vec4(1.0, 0.0, 1.0, 1.0),
		  glm::vec4(1.0, 1.0, 1.0, 1.0),
		  glm::vec4(0.0, 1.0, 1.0, 1.0)
		};
		  float   delta=0.05  ;  
		std::vector<std::vector<glm::vec2> > t_coords(7); 
		for(int i=0;i<7;i++){
			t_coords[i].resize(4);
		}
			int i=0;
		  t_coords[i][0] = glm::vec2( 0.0, 0.0); 
		  t_coords[i][1] = glm::vec2( 0.0, 1.0);
		  t_coords[i][2] = glm::vec2( 1.0, 0.0);
		  t_coords[i][3] = glm::vec2( 1.0, 1.0);
			i++;
		  
		  t_coords[i][0] = glm::vec2( 0.0+ delta, 0.3333333);
		  t_coords[i][1] = glm::vec2( 0.0+ delta, 0.6666666);
		  t_coords[i][2] = glm::vec2( 0.25+ delta, 0.3333333);
		  t_coords[i][3] = glm::vec2( 0.25+ delta, 0.6666666);
		  i++;
		  
		  t_coords[i][0] = glm::vec2( 0.25+ delta, 0.3333333);
		  t_coords[i][1] = glm::vec2( 0.25+ delta, 0.6666666);
		  t_coords[i][2] = glm::vec2( 0.5+ delta, 0.3333333);
		  t_coords[i][3] = glm::vec2( 0.5+ delta, 0.6666666);
		  i++;
		  
		  t_coords[i][0] = glm::vec2( 0.5+ delta, 0.3333333);
		  t_coords[i][1] = glm::vec2( 0.5+ delta, 0.6666666);
		  t_coords[i][2] = glm::vec2( 0.75+ delta, 0.3333333);
		  t_coords[i][3] = glm::vec2( 0.75+ delta, 0.6666666);
		  i++;
		  
		  t_coords[i][0] = glm::vec2( 0.75+ delta, 0.3333333);
		  t_coords[i][1] = glm::vec2( 0.75+ delta, 0.6666666);
		  t_coords[i][2] = glm::vec2( delta, 0.3333333);
		  t_coords[i][3] = glm::vec2( delta, 0.6666666);
		  i++;
		  
		  t_coords[i][0] = glm::vec2( 0.25+ delta, 0.0);
		  t_coords[i][1] = glm::vec2( 0.25+ delta, 0.3333333);
		  t_coords[i][2] = glm::vec2( 0.5+ delta, 0.0);
		  t_coords[i][3] = glm::vec2( 0.5+ delta, 0.3333333);
		  i++;
		  
		  t_coords[i][0] = glm::vec2( 0.25+ delta, 0.6666666);
		  t_coords[i][1] = glm::vec2( 0.25+ delta, 1.0);
		  t_coords[i][2] = glm::vec2( 0.5+ delta, 0.6666666);
		  t_coords[i][3] = glm::vec2( 0.5+ delta, 1.0);
		  i++;

		int tri_idx=0;

		Basics::quad1( 2, 1, 0, 3, glm::vec4(1.0,0.0,0.0,1.0),1,positions,t_coords,vec,vec_c,tex_coords,tri_idx  );
		Basics::quad1( 6, 2, 3, 7, glm::vec4(0,1.0,0,1.0),2,positions,t_coords,vec,vec_c,tex_coords,tri_idx);
		Basics::quad1( 3, 0, 4, 7, glm::vec4(1.0,1.0,1.0,1.0),4,positions,t_coords,vec,vec_c,tex_coords,tri_idx);
		Basics::quad1( 6, 5, 1,2, glm::vec4(1.0,0.0,0.0,1.0),5,positions,t_coords,vec,vec_c,tex_coords,tri_idx);
		Basics::quad1( 5, 6, 7, 4, glm::vec4(0.0,0.0,1.0,1.0),3,positions,t_coords,vec,vec_c,tex_coords,tri_idx);
		Basics::quad1( 1, 5, 4, 0, glm::vec4(0.0,0.0,1.0,1.0), 0,positions,t_coords,vec,vec_c,tex_coords,tri_idx);
		return vec;
	}

	std::vector<glm::vec4> Basics::drawCuboid(
		float l,
		float h,
		float w,
		std::vector<glm::vec4> &normals
		)
	{	
		l=l/2;
		h=h/2;
		w=w/2;
		std::vector<glm::vec4> vec(36);
		std::vector<glm::vec4> vec_c(36);
		glm::vec4 positions[8] = {
			glm::vec4(-l,h, -w,1.0),
			glm::vec4(-l,h, w, 1.0),
			glm::vec4(l,h, w, 1.0),
			glm::vec4(l,h, -w, 1.0),
			glm::vec4(-l,-h, -w, 1.0),
			glm::vec4(-l,-h, w, 1.0),
			glm::vec4(l,-h, w, 1.0),
			glm::vec4(l,-h, -w, 1.0)
		};

		glm::vec4 colors[8] = {
			glm::vec4(0.0, 0.0, 0.0, 1.0),
			glm::vec4(1.0, 0.0, 0.0, 1.0),
			glm::vec4(1.0, 1.0, 0.0, 1.0),
			glm::vec4(0.0, 1.0, 0.0, 1.0),
			glm::vec4(0.0, 0.0, 1.0, 1.0),
			glm::vec4(1.0, 0.0, 1.0, 1.0),
			glm::vec4(1.0, 1.0, 1.0, 1.0),
			glm::vec4(0.0, 1.0, 1.0, 1.0)
		};

		//To generate cuboid
		int t=0;
		Basics::quad( 0, 1, 2, 3, positions,colors,vec,vec_c,t );
	    Basics::quad( 2, 6, 7, 3, positions,colors,vec,vec_c,t );
	    Basics::quad( 3, 7, 4, 0, positions,colors,vec,vec_c,t );
	    Basics::quad( 6, 2, 1, 5, positions,colors,vec,vec_c,t );
	    Basics::quad( 4, 7, 6, 5, positions,colors,vec,vec_c,t );
	    Basics::quad( 5, 1, 0, 4, positions,colors,vec,vec_c,t );


	    for(int i=0;i<6;i++){//+y
	    	normals.push_back(glm::vec4(0,1,0,1));
	    }
	    for(int i=0;i<6;i++){//+x
	    	normals.push_back(glm::vec4(1,0,0,1));
	    }
	    for(int i=0;i<6;i++){//-z
	    	normals.push_back(glm::vec4(0,0,-1,1));
	    }
	    for(int i=0;i<6;i++){//+z
	    	normals.push_back(glm::vec4(0,0,1,1));
	    }
	    for(int i=0;i<6;i++){//-y
	    	normals.push_back(glm::vec4(0,-1,0,1));
	    }
	    for(int i=0;i<6;i++){//-x
	    	normals.push_back(glm::vec4(-1,0,0,1));
	    }

		return vec;
	}

	// Draw Frustum
	std::vector<glm::vec4> Basics::drawFrustum(
		float radius_small,
		float radius_big,
		float height,
		int iterations,
		std::vector<glm::vec4> &normals,
		float initial_angle=0
	){
		std::vector<glm::vec4> vec;
		float angle=2*pi/iterations;
		for(int i=0;i<iterations;i++){
			float x1=radius_big*cos(i*angle+initial_angle);
			float y1=radius_big*sin(i*angle+initial_angle);
			float x2=radius_small*cos(i*angle+initial_angle);
			float y2=radius_small*sin(i*angle+initial_angle);
			float nz1=radius_big*(radius_big - radius_small)/height;
			i=i+1;
			float x3=radius_big*cos(i*angle+initial_angle);
			float y3=radius_big*sin(i*angle+initial_angle);
			float x4=radius_small*cos(i*angle+initial_angle);
			float y4=radius_small*sin(i*angle+initial_angle);
			i=i-1;
			float h=height/2;
			vec.push_back(
				glm::vec4(x1,-h,y1,1.0)
				);
			vec.push_back(
				glm::vec4(x3,-h,y3,1.0)
				);
			vec.push_back(
				glm::vec4(x2,h,y2,1.0)
				);
			vec.push_back(
				glm::vec4(x2,h,y2,1.0)
				);
			vec.push_back(
				glm::vec4(x3,-h,y3,1.0)
				);
			vec.push_back(
				glm::vec4(x4,h,y4,1.0)
				);
			// nz1=0.0;
			normals.push_back(glm::vec4(x1,nz1,y1,1.0));
			normals.push_back(glm::vec4(x3,nz1,y3,1.0));
			normals.push_back(glm::vec4(x1,nz1,y1,1.0));
			normals.push_back(glm::vec4(x1,nz1,y1,1.0));
			normals.push_back(glm::vec4(x3,nz1,y3,1.0));
			normals.push_back(glm::vec4(x3,nz1,y3,1.0));
		}
		
		return vec;
	}

	std::vector<glm::vec4> Basics::drawDisk(float radius,int iterations,float start_angle,float end_angle, std::vector<glm::vec4> & normals){
		std::vector<glm::vec4> vec;
		float angle=(end_angle-start_angle)/iterations;
		for(int i=0;i<iterations;i++){
			float x1=radius*cos(i*angle+start_angle);
			float z1=radius*sin(i*angle+start_angle);
			i++;
			float x2=radius*cos(i*angle+start_angle);
			float z2=radius*sin(i*angle+start_angle);
			i--;
			vec.push_back(glm::vec4(x1,0,z1,1.0));
			vec.push_back(glm::vec4(x2,0,z2,1.0));
			vec.push_back(glm::vec4(0,0,0,1.0));
			normals .push_back(glm::vec4(0,1.0,0,1.0));
			normals .push_back(glm::vec4(0,1.0,0,1.0));
			normals .push_back(glm::vec4(0,1.0,0,1.0));
		}
		return vec;
	}
	std::vector<glm::vec4> Basics::drawArcCylinder(float radius,float height,float start_angle,float end_angle, std::vector<glm::vec4> & normals){
		int iterations=100;
		std::vector<glm::vec4> vec;
		float angle=(end_angle-start_angle)/iterations;
		for(int i=0;i<iterations;i++){
			float x1=radius*cos(i*angle+start_angle);
			float y1=radius*sin(i*angle+start_angle);
			float x2=radius*cos(i*angle+start_angle);
			float y2=radius*sin(i*angle+start_angle);
			i=i+1;
			float x3=radius*cos(i*angle+start_angle);
			float y3=radius*sin(i*angle+start_angle);
			float x4=radius*cos(i*angle+start_angle);
			float y4=radius*sin(i*angle+start_angle);
			i=i-1;
			float h=height/2;
			vec.push_back(
				glm::vec4(x1,-h,y1,1.0)
				);
			vec.push_back(
				glm::vec4(x3,-h,y3,1.0)
				);
			vec.push_back(
				glm::vec4(x2,h,y2,1.0)
				);
			vec.push_back(
				glm::vec4(x2,h,y2,1.0)
				);
			vec.push_back(
				glm::vec4(x3,-h,y3,1.0)
				);
			vec.push_back(
				glm::vec4(x4,h,y4,1.0)
				);
			normals.push_back(glm::vec4(x1,0,y1,1.0));
			normals.push_back(glm::vec4(x3,0,y3,1.0));
			normals.push_back(glm::vec4(x1,0,y1,1.0));
			normals.push_back(glm::vec4(x1,0,y1,1.0));
			normals.push_back(glm::vec4(x3,0,y3,1.0));
			normals.push_back(glm::vec4(x3,0,y3,1.0));
		}
		return vec;
	}
	std::vector<glm::vec4> Basics::drawCylinder(float radius,float height, std::vector<glm::vec4> & normals){
		return Basics::drawFrustum(radius,radius,height,100,normals);
	}

	std::vector<glm::vec4> Basics::drawCone(float radius,float height, std::vector<glm::vec4> & normals){
		return Basics::drawFrustum(0,radius,height,100,normals);
	}

	std::vector<glm::vec4> Basics::drawFrustumCone(float radius_small,float radius_big,	float height,std::vector<glm::vec4> & normals){
		return Basics::drawFrustum(radius_small,radius_big,height,100,normals);
	}


	std::vector<glm::vec4> Basics::drawSphere(float radius,std::vector<glm::vec4> & normals){
		int iterations=100;
		float theta=0;
		float phi=0;
		float deltaTheta=2*pi/iterations;
		float deltaPhi=pi/iterations;
		std::vector<glm::vec4> vec;
		for(int i=0;i<iterations;i++)
			for(int j=0;j<iterations;j++){
				float x1 = radius*cos(i*deltaTheta)*sin(j*deltaPhi);
				float y1 = radius*sin(i*deltaTheta)*sin(j*deltaPhi);
				float z1 = radius*cos(j*deltaPhi);
				i++;
				float x2 = radius*cos(i*deltaTheta)*sin(j*deltaPhi);
				float y2 = radius*sin(i*deltaTheta)*sin(j*deltaPhi);
				float z2 = radius*cos(j*deltaPhi);
				i--;
				j++;
				float x3 = radius*cos(i*deltaTheta)*sin(j*deltaPhi);
				float y3 = radius*sin(i*deltaTheta)*sin(j*deltaPhi);
				float z3 = radius*cos(j*deltaPhi);
				i++;
				float x4 = radius*cos(i*deltaTheta)*sin(j*deltaPhi);
				float y4 = radius*sin(i*deltaTheta)*sin(j*deltaPhi);
				float z4 = radius*cos(j*deltaPhi);

				vec.push_back(glm::vec4(x1,y1,z1,1.0));
				vec.push_back(glm::vec4(x3,y3,z3,1.0));
				vec.push_back(glm::vec4(x2,y2,z2,1.0));
				vec.push_back(glm::vec4(x2,y2,z2,1.0));
				vec.push_back(glm::vec4(x3,y3,z3,1.0));
				vec.push_back(glm::vec4(x4,y4,z4,1.0));
				normals.push_back(glm::vec4(x1,y1,z1,1.0));
				normals.push_back(glm::vec4(x3,y3,z3,1.0));
				normals.push_back(glm::vec4(x2,y2,z2,1.0));
				normals.push_back(glm::vec4(x2,y2,z2,1.0));
				normals.push_back(glm::vec4(x3,y3,z3,1.0));
				normals.push_back(glm::vec4(x4,y4,z4,1.0));
				i--;
				j--;
			}
		return vec;	
	}

	std::vector<glm::vec4> Basics::drawArc(float radius, float start_theta, float end_theta, float start_phi, float end_phi,std::vector<glm::vec4> & normals){
		int iterations=100;
		float theta=0;
		float phi=0;
		float deltaTheta=(end_theta-start_theta)/iterations;
		float deltaPhi=(end_phi-start_phi)/iterations;
		std::vector<glm::vec4> vec;
		for(int i=0;i<iterations;i++)
			for(int j=0;j<iterations;j++){
				float x1 = radius*cos(start_theta+i*deltaTheta)*sin(start_phi+j*deltaPhi);
				float y1 = radius*sin(start_theta+i*deltaTheta)*sin(start_phi+j*deltaPhi);
				float z1 = radius*cos(start_phi+j*deltaPhi);
				i++;
				float x2 = radius*cos(start_theta+i*deltaTheta)*sin(start_phi+j*deltaPhi);
				float y2 = radius*sin(start_theta+i*deltaTheta)*sin(start_phi+j*deltaPhi);
				float z2 = radius*cos(start_phi+j*deltaPhi);
				i--;
				j++;
				float x3 = radius*cos(start_theta + i*deltaTheta)*sin(start_phi+j*deltaPhi);
				float y3 = radius*sin(start_theta + i*deltaTheta)*sin(start_phi+j*deltaPhi);
				float z3 = radius*cos(start_phi + j*deltaPhi);
				i++;
				float x4 = radius*cos(start_theta + i*deltaTheta)*sin(start_phi+j*deltaPhi);
				float y4 = radius*sin(start_theta + i*deltaTheta)*sin(start_phi+j*deltaPhi);
				float z4 = radius*cos(start_phi + j*deltaPhi);

				vec.push_back(glm::vec4(x1,y1,z1,1.0));
				vec.push_back(glm::vec4(x3,y3,z3,1.0));
				vec.push_back(glm::vec4(x2,y2,z2,1.0));
				vec.push_back(glm::vec4(x2,y2,z2,1.0));
				vec.push_back(glm::vec4(x3,y3,z3,1.0));
				vec.push_back(glm::vec4(x4,y4,z4,1.0));
				normals.push_back(glm::vec4(x1,y1,z1,1.0));
				normals.push_back(glm::vec4(x3,y3,z3,1.0));
				normals.push_back(glm::vec4(x2,y2,z2,1.0));
				normals.push_back(glm::vec4(x2,y2,z2,1.0));
				normals.push_back(glm::vec4(x3,y3,z3,1.0));
				normals.push_back(glm::vec4(x4,y4,z4,1.0));
				i--;
				j--;
			}
		return vec;		
	}

	std::vector<glm::vec4> Basics::drawEllipsoid(
		float radius_small,
		float radius_big,
		float start_theta,
		float end_theta,
		float start_phi,
		float end_phi,
		std::vector<glm::vec4> & normals
	){
		std::vector<glm::vec4> vec = Basics::drawArc(1,start_theta,end_theta,start_phi,end_phi,normals);
		float mat[16] = {
			radius_small,0,0,0,
			0,radius_small,0,0,
			0,0,radius_big,0,
			0,0,0,1
		};
		glm::mat4 matrix = glm::transpose(glm::make_mat4(mat));
		glm::mat4 norm_matrix= glm::transpose(glm::inverse(matrix));
		for(int i=0;i<vec.size();i++){
			vec[i]=matrix*vec[i];
			normals[normals.size()-vec.size()+i]=norm_matrix*normals[normals.size()-vec.size()+i];
		}
		return vec;
	}

	std::vector<glm::vec4> Basics::getColor(std::vector<glm::vec4> & vec,glm::vec4 color){
		std::vector<glm::vec4> v(vec.size(),color);
		return v; 
	}
	std::vector<glm::vec4> Basics::drawNeck(
		float outerRadius,
		float innerRadius,
		float height,
		std::vector<glm::vec4> &normals
	){
		std::vector<glm::vec4> vec;
		float d=outerRadius-innerRadius;
		float h=height/2;
		float B=(d*d+h*h)/(2*d);
		float phi=asin(h/B);
		int iterations=100;
		float deltaTheta = 2*pi/iterations;
		float deltaPhi=2*phi/iterations;
		for(int i=0;i<iterations;i++)
			for(int j=-iterations/2;j<iterations/2;j++){
				float r1 = innerRadius+B*(1-cos(j*deltaPhi));
				float x1 = r1*cos(i*deltaTheta);
				float y1 = B*sin(j*deltaPhi);
				float z1 = r1*sin(i*deltaTheta);
				float cx1 = (B+innerRadius)*cos(i*deltaTheta);
				float cz1 = (B+innerRadius)*sin(i*deltaTheta);
				float cy1 = 0;
				i++;
				float r2 = innerRadius+B*(1-cos(j*deltaPhi));
				float x2 = r2*cos(i*deltaTheta);
				float y2 = B*sin(j*deltaPhi);
				float z2 = r2*sin(i*deltaTheta);
				float cx2 = (B+innerRadius)*cos(i*deltaTheta);
				float cz2 = (B+innerRadius)*sin(i*deltaTheta);
				float cy2 = 0;
				i--;
				j++;
				float r3 = innerRadius+B*(1-cos(j*deltaPhi));
				float x3 = r3*cos(i*deltaTheta);
				float y3 = B*sin(j*deltaPhi);
				float z3 = r3*sin(i*deltaTheta);
				float cx3 = (B+innerRadius)*cos(i*deltaTheta);
				float cz3 = (B+innerRadius)*sin(i*deltaTheta);
				float cy3 = 0;
				i++;
				float r4 = innerRadius+B*(1-cos(j*deltaPhi));
				float x4 = r4*cos(i*deltaTheta);
				float y4 = B*sin(j*deltaPhi);
				float z4 = r4*sin(i*deltaTheta);
				float cx4 = (B+innerRadius)*cos(i*deltaTheta);
				float cz4 = (B+innerRadius)*sin(i*deltaTheta);
				float cy4 = 0;
				i--;
				j--;				
				vec.push_back(glm::vec4(x1,y1,z1,1.0));
				vec.push_back(glm::vec4(x3,y3,z3,1.0));
				vec.push_back(glm::vec4(x2,y2,z2,1.0));
				vec.push_back(glm::vec4(x2,y2,z2,1.0));
				vec.push_back(glm::vec4(x3,y3,z3,1.0));
				vec.push_back(glm::vec4(x4,y4,z4,1.0));
				normals.push_back(glm::vec4(cx1-x1,cy1-y1,cz1-z1,1.0));
				normals.push_back(glm::vec4(cx3-x3,cy3-y3,cz3-z3,1.0));
				normals.push_back(glm::vec4(cx2-x2,cy2-y2,cz2-z2,1.0));
				normals.push_back(glm::vec4(cx2-x2,cy2-y2,cz2-z2,1.0));
				normals.push_back(glm::vec4(cx3-x3,cy3-y3,cz3-z3,1.0));
				normals.push_back(glm::vec4(cx4-x4,cy4-y4,cz4-z4,1.0));
			}
		return vec;	
	}

	glm::vec2 Basics::calcUV( glm::vec4 p)
	{
	    p = glm::normalize(p);

	    const float PI = 3.1415926f;

	    float u = ((atan2(p.x, p.y) / PI) + 1.0f) * 0.5f;
	    float v = (asin(p.z) / PI) + 0.5f;

	    return glm::vec2(u,v);
	}

	std::vector<glm::vec2> Basics::calcUVsphere(std::vector<glm::vec4> sphere){
		std::vector<glm::vec2> res;
		for(int i=0;i<sphere.size();i++){
			res.push_back(Basics::calcUV(sphere[i]));
		}	
		return res;
	}

	glm::vec2 Basics::calcUVhem( glm::vec4 p)
	{
	    p = glm::normalize(p);

	    const float PI = 3.1415926f;

	    float u = ((atan2(p.x, p.y) / PI));
	    float v = (asin(p.z) / PI) + 0.5f;

	    return glm::vec2(u,v);
	}

	std::vector<glm::vec2> Basics::calcUVhemisphere(std::vector<glm::vec4> sphere){
		std::vector<glm::vec2> res;
		for(int i=0;i<sphere.size();i++){
			res.push_back(Basics::calcUVhem(sphere[i]));
		}	
		return res;
	}
	std::vector<glm::vec4> Basics::drawSquare(float length, std::vector<glm::vec4> & norms ){
		std::vector<glm::vec4> v;
		v.push_back(glm::vec4(-length,0,-length,1.0));
		v.push_back(glm::vec4(length,0,-length,1.0));
		v.push_back(glm::vec4(-length,0,length,1.0));
		v.push_back(glm::vec4(length,0,-length,1.0));
		v.push_back(glm::vec4(-length,0,length,1.0));
		v.push_back(glm::vec4(length,0,length,1.0));
		std::vector<glm::vec4> v2;
		v2.push_back(glm::vec4(0,1,0,1.0));
		v2.push_back(glm::vec4(0,1,0,1.0));
		v2.push_back(glm::vec4(0,1,0,1.0));
		v2.push_back(glm::vec4(0,1,0,1.0));
		v2.push_back(glm::vec4(0,1,0,1.0));
		v2.push_back(glm::vec4(0,1,0,1.0));
		norms= v2;
		return v;
	}
	std::vector<glm::vec2> Basics::calcUVSquare(){
		std::vector<glm::vec2> v;
		v.push_back(glm::vec2(0,1));
		v.push_back(glm::vec2(1,1));
		v.push_back(glm::vec2(0,0));
		v.push_back(glm::vec2(1,1));
		v.push_back(glm::vec2(0,0));
		v.push_back(glm::vec2(1,0));
		return v;
	}
