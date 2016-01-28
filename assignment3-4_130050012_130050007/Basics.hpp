#include <iostream>
#include "include.hpp"
#define pi 3.1415


void tr(std::vector<glm::vec4> & vec, float rot_x,float rot_y, float rot_z, float tra_x, float tra_y, float tra_z, std::vector<glm::vec4> &norm);

class Basics{
public:

	static void quad1(int a, int b, int c, int d, glm::vec4 color,int face, glm::vec4* positions, std::vector<std::vector<glm::vec2> > t_coords ,
		 std::vector<glm::vec4> &v_positions,std::vector<glm::vec4> &v_colors,std::vector<glm::vec2> &tex_coords,int & tri_idx);
   static void quad(int a, int b, int c, int d,  glm::vec4* positions, glm::vec4* colors, std::vector<glm::vec4> &v_positions,std::vector<glm::vec4> &v_colors,int & tri_idx);

	static std::vector<glm::vec4> drawCube(
		float l,
		// std::vector<glm::vec4> &normals,
		std::vector<glm::vec2> &tex_coords
		);
	static std::vector<glm::vec4> drawCuboid(
		float len,
		float wid,
		float height,
		std::vector<glm::vec4> &normals
		);
	static std::vector<glm::vec4> drawFrustum(
		float radius_small,
		float radius_big,
		float height,
		int iteration,
		std::vector<glm::vec4> &normals,
		float initial_angle
		);
	static std::vector<glm::vec4> drawCylinder(
		float radius,
		float height,
		std::vector<glm::vec4> &normals
		);
	static std::vector<glm::vec4> drawCone(
		float radius,
		float height,
		std::vector<glm::vec4> &normals
		);
	static std::vector<glm::vec4> drawFrustumCone(
		float radius_small,
		float radius_big,
		float height,
		std::vector<glm::vec4> &normals
		);
	static std::vector<glm::vec4> drawSphere(
		float radius,
		std::vector<glm::vec4> &normals
		);
	static std::vector<glm::vec4> drawDisk(
		float radius,
		int iteration,
		float start_angle,
		float end_angle,
		std::vector<glm::vec4> &normals
		);		
	static std::vector<glm::vec4> drawArc(
		float radius,
		float start_theta,
		float end_theta,
		float start_phi,
		float end_phi,
		std::vector<glm::vec4> &normals
	);
	static std::vector<glm::vec4> drawEllipsoid(
		float radius_small,
		float radius_big,
		float start_theta,
		float end_theta,
		float start_phi,
		float end_phi,
		std::vector<glm::vec4> &normals
	);
	static std::vector<glm::vec4> drawNeck(
		float outerRadius,
		float innerRadius,
		float height,
		std::vector<glm::vec4> &normals
	);
	static std::vector<glm::vec4>drawArcCylinder(
		float radius,
		float height,
		float start_angle,
		float end_angle,
		std::vector<glm::vec4> &normals
	);
	static std::vector<glm::vec4> getColor(
		std::vector<glm::vec4> & vec,
		glm::vec4 color
	);
	static glm::vec2 calcUV( glm::vec4 p);
	static std::vector<glm::vec2> calcUVsphere(std::vector<glm::vec4> sphere);
	static glm::vec2 calcUVhem( glm::vec4 p);
	static std::vector<glm::vec2> calcUVhemisphere(std::vector<glm::vec4> sphere);
	static std::vector<glm::vec4> drawSquare(float length, std::vector<glm::vec4> & v);
	static std::vector<glm::vec2> calcUVSquare();
	static std::vector<glm::vec4> drawThickArc();
};
