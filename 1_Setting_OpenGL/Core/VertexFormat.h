#ifndef VertexFormat_H_
#define VertexFormat_H_
 
#include "..\Dependencies\glm\glm.hpp"
 
struct VertexFormat
{
	glm::vec3 position;//our first vertex attribute
	glm::vec4 color;

	VertexFormat(const glm::vec3 &pos, const glm::vec4 &iColor)
	{
		position = pos;
		color = iColor;
	}
};
 
#endif