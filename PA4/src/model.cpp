//
// Created by alex on 9/20/17.
//

#include "model.h"

Model* Model::load(std::string filename) {
	Model* newModel = new Model();
	std::string line;
	
	static std::unordered_map<std::string, Model*> loadedModels;
	
	if(loadedModels.find(filename) != loadedModels.end()) {
		return loadedModels[filename];
	}
	
	std::ifstream inFile(filename);
	if(!inFile.is_open()) return NULL;
	
	while(true) {
		getline(inFile, line, ' ');
		if(inFile.eof()) break;
		
		while(std::isspace(line[0])) {
			line.erase(0, 1);
		}
		
		//std::cout << "Looking at: " << line << std::endl;
		
		if(line == "#") {
			//Skip line - comment
			getline(inFile, line);
		} else if(line == "v") {
			//New vertex - add it into the list
			//v # # #
			Vertex newVertex = {{0.0, 0.0, 0.0}, {((float) rand()) / RAND_MAX, ((float) rand()) / RAND_MAX, ((float) rand()) / RAND_MAX}};
			inFile >> newVertex.vertex.x;
			inFile >> newVertex.vertex.y;
			inFile >> newVertex.vertex.z;

			newModel->_vertices.push_back(newVertex);
		} else if(line == "f") {
			//New face
			//f #/#/# #/#/# #/#/#
			unsigned int faceVertex;
			std::string nextArg;
			
			for(int i = 0; i < 3; i++) {
				//Just take the first number, we don't need to know texture mapping or normals
				inFile >> nextArg;
				faceVertex = strtol(nextArg.c_str(), NULL, 10);
				newModel->_indices.push_back(faceVertex);
			}
		} else if(line == "mtllib") {
			//Material file
			//mtllib <filename>
			inFile >> line;
			loadMaterials(newModel, "models/" + line);
		} else if(line == "usemtl") {
			//Use this material for the next few faces
			//usemtl <material name>
			std::string mtlName;
			inFile >> mtlName;
			
			if(newModel->materialList.find(mtlName) == newModel->materialList.end())  {
				std::cout << "Material \"" << mtlName << "\" not found!" << std::endl;
				return NULL;
			}
			
			newModel->material = newModel->materialList[mtlName];
		} else {
			getline(inFile, line);
		}
	}
	
	//Debug Code
	/*std::cout << "Vertex 1: " << newModel->_vertices[0].vertex.x << ", " << newModel->_vertices[0].vertex.y << ", " << newModel->_vertices[0].vertex.z << std::endl;
	std::cout << "Vertices: " << newModel->_vertices.size() << std::endl;
	std::cout << "Faces: " << newModel->_indices.size() << std::endl;*/
	
	for (unsigned int &Indice : newModel->_indices) {
		Indice = Indice - 1;
	}
	
	
	loadedModels[filename] = newModel;
	
	return newModel;
}

void Model::loadMaterials(Model* model, std::string filename) {
	Model::Material newMaterial;
	std::string line;
	std::string currentName;
	
	std::ifstream inFile(filename);
	if(!inFile.is_open()) {
		std::cout << "Could not open material file \"" << filename << "\"" << std::endl;
		return;
	}
	
	std::cout << "Loading material from " << filename << std::endl;
	
	while(true) {
		getline(inFile, line, ' ');
		if(inFile.eof()) break;
		
		while(std::isspace(line[0])) {
			line.erase(0, 1);
		}
		
		if(line == "#") {
			//Skip line - comment
			getline(inFile, line);
		} else if(line == "newmtl") {
			//New material
			//newmtl <name>
			if(currentName != "") {
				model->materialList[currentName] = newMaterial;
			}
			
			inFile >> line;
			currentName = line;
		} else if(line == "Ns") {
			//Specular exponent / shininess
			//Ns #
			float shininess;
			
			inFile >> line;
			shininess = strtod(line.c_str(), NULL);
			
			newMaterial.shininess = shininess;
		} else if(line == "Ka") {
			//Ambient
			//Ka # # #
			inFile >> newMaterial.ambient.r;
			inFile >> newMaterial.ambient.g;
			inFile >> newMaterial.ambient.b;
		} else if(line == "Kd") {
			//Diffuse
			//Kd # # #
			inFile >> newMaterial.diffuse.r;
			inFile >> newMaterial.diffuse.g;
			inFile >> newMaterial.diffuse.b;
		} else if(line == "Ks") {
			//Specular
			//Ks # # #
			inFile >> newMaterial.specular.r;
			inFile >> newMaterial.specular.g;
			inFile >> newMaterial.specular.b;
		} else if(line == "d") {
			//Opacity
			//d #
			float opacity;
			
			inFile >> opacity;
			
			newMaterial.ambient.a = opacity;
			newMaterial.diffuse.a = opacity;
			newMaterial.specular.a = opacity;
		} else if(line == "Tr") {
			//Transparency
			//Tr #
			float opacity;
			
			inFile >> opacity;
			
			newMaterial.ambient.a = 1.0f - opacity;
			newMaterial.diffuse.a = 1.0f - opacity;
			newMaterial.specular.a = 1.0f - opacity;
		} else {
			getline(inFile, line);
		}
	}
	
	if(currentName != "") {
		model->materialList[currentName] = newMaterial;
	}
}

Model::Model(){}