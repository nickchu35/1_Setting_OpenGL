#ifndef _GAME_MODELS_H_
#define _GAME_MODELS_H_
 
#pragma once
#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"
#include "VertexFormat.h" //added 3/21/2015
#include <vector>
#include <map>
 
namespace Models
{
	//I explain this structure in Part III
	struct Model
	{
	    unsigned int vao;   // vertex array object, 
	    std::vector<unsigned int> vbos; // vertex buffer objects, how vertices are stored into the GPU memory
	    Model(){}
	};
 
	class GameModels
	{
		public:
		GameModels();
		~GameModels();
		void CreateTriangleModel(const std::string& gameModelName);
		void CreateSphereModel(const std::string& gameModelName, const int num);
		void DeleteModel(const std::string& gameModelName);
		unsigned int GetModel(const std::string& gameModelName);
		private:
		std::map<std::string, Model> GameModelList;//keep our models
	};
}
#endif