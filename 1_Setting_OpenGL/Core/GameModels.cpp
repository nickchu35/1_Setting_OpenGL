#include "GameModels.h"
#include <string>
#include <map>
// for M_PI use
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Models;
 
GameModels::GameModels()
{

}
 
GameModels::~GameModels()
{
	std::map<std::string, Model>::iterator it;
	for (it = GameModelList.begin(); it != GameModelList.end(); ++it)
	{
		//delete VAO and VBOs (if many)
		unsigned int* p = &it->second.vao;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	GameModelList.clear();
}

void GameModels::DeleteModel(const std::string& gameModelName)
{
	Model model = GameModelList[gameModelName];
    unsigned int p = model.vao;
    glDeleteVertexArrays(1, &p);
    glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
    model.vbos.clear();
    GameModelList.erase(gameModelName); 
}
 
unsigned int GameModels::GetModel(const std::string& gameModelName)
{
	return GameModelList[gameModelName].vao;
}
 
void GameModels::CreateTriangleModel(const std::string& gameModelName)
{
	unsigned int vao;
    unsigned int vbo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3( 0.25, -0.25, 0.0),
                                 glm::vec4( 1, 0, 0, 1))); //red
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0),
                                 glm::vec4( 0, 1, 0, 1))); //green
	vertices.push_back(VertexFormat(glm::vec3( 0.0, 0.433-0.25, 0.0),
                                 glm::vec4( 0, 0, 1, 1))); //blue

 
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	// on qualifier 0 (first param), send 3 (second param), floats (third param) non normalized (forth param), 
	// knowing that the next vertex appears every sizeof(VertexFormat) (fifth param, called stride) and the 
	// offset of the first element from VertexFormat (x from position) is 0.

	// call glEnableVertexAttribArray() and glVertexAttribPointer() methods again for the color attribute.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);

    Model myModel;                            //is allocated on Stack
    myModel.vao = vao;                        //add vao
    myModel.vbos.push_back(vbo);              //add vbo
    GameModelList[gameModelName] = myModel;  //add to std::map
}

void GameModels::CreateRectangleModel(const std::string& gameModelName)
{
	unsigned int vao;
    unsigned int vbo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
    std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3( 0.25, -0.25, 0.0),
                                 glm::vec4( 1, 0, 0, 1))); //red
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0),
                                 glm::vec4( 0, 1, 0, 1))); //green
	vertices.push_back(VertexFormat(glm::vec3(-0.25, 0.25,  0.0),
                                 glm::vec4( 0, 0, 1, 1))); //blue
	vertices.push_back(VertexFormat(glm::vec3( 0.25, 0.25,  0.0),
                                 glm::vec4( 0, 0, 1, 1))); //blue

 
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

	// call glEnableVertexAttribArray() and glVertexAttribPointer() methods again for the color attribute.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);  // three floates for position, 12 is correct

    Model myModel;                            //is allocated on Stack
    myModel.vao = vao;                        //add vao
    myModel.vbos.push_back(vbo);              //add vbo
    GameModelList[gameModelName] = myModel;  //add to std::map
}

void GameModels::CreateSphereModel(const std::string& gameModelName)
{

	unsigned int vao;
    unsigned int vbo;
 
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
 
	std::vector<VertexFormat> vertices;

	for(int i = 1; i <= 40; i++)
	{
		// latitude is an angle, ½n«×
		double lat0 = M_PI * (-0.5 + (double) (i - 1) / 40); // start from -90
		//double z0  = sin(lat0);
		double y0 = sin(lat0);
		//double zr0 = cos(lat0);
		double smallR0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double) i / 40); // 180 , start from -89 => upper
		//double z1 = sin(lat1);
		double y1 = sin(lat1);
		//double zr1 = cos(lat1);
		double smallR1 = cos(lat1);

		for(int j = 0; j <= 40; j++)
		{
			// longitude = ¸g«×
	        double lng = 2 * M_PI * (double) j/40; // 0 ~ 360 degrees
			double x = cos(lng); // 1 ~ 0 ~ 1 ~ 0
			double z = sin(lng); // 0 ~ 1 ~ 0 ~ 1
			vertices.push_back(VertexFormat(glm::vec3( x * smallR0, y0, z * smallR0),
                                 glm::vec4( 0, 0, 1, 1))); //blue
			vertices.push_back(VertexFormat(glm::vec3( x * smallR1, y1, z * smallR1),
                                 glm::vec4( 0, 1, 0, 1))); //green
		}
	}
 
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3200, &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

	// call glEnableVertexAttribArray() and glVertexAttribPointer() methods again for the color attribute.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);

    Model myModel;                            //is allocated on Stack
    myModel.vao = vao;                        //add vao
    myModel.vbos.push_back(vbo);              //add vbo
    GameModelList[gameModelName] = myModel;  //add to std::map
}
