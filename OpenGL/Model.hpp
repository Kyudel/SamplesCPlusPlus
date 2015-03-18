/////////////////////////////////////////////////////////////////////
//Copyright © 2013-2015 Ivan Perez
//Author: Ivan Perez
//Linkedin: http://es.linkedin.com/in/ivanperezduran
//Portfolio: http://ivanportfolio.tk/
/////////////////////////////////////////////////////////////////////

#ifndef MODEL_HEADER
#define MODEL_HEADER

#include <SFML/OpenGL.hpp>
#include <SFML\System\Vector3.hpp>
#include <string>
#include <vector>

using sf::Vector3f;
using std::string;
using std::vector;

#include "Node.hpp"
#include "Texture.hpp"

namespace GraphicLibrary
{
	

	/** The class model rende and gives give functionality. */
	class Model : public Node
	{
	private:

		/** List of objects. */
		vector<GroupObject *> objects;

		/** List of vertices. */
		vector<Vector3f *> vertices;

		/** List of normals. */
		vector<Vector3f *> normals;

		/** List of UVWs. */
		vector<Vector3f *> UVWs;

		/** List of the different materials of a object. */
		vector<Material *> materials;

		/** Radius of the object. */
		float radius;

		/** Center of the object. */
		Vector3f center;

		/** Is a object loaded. */
		bool objectLoaded;

		GLuint displayList;

		/** Path of the 3D object. */
		string fileName;

		/** Cont of indeces. */
		int contIndex;

	public:
		
		/**
		* Constructor Model.
		* @param fileName - name of the 3D object .obj
		*/
		Model(string filename);

		/** Destructor Model. */
		~Model();
	public:

		/** Render a specified 3D model. */
		void drawObject(bool transparency);

		/**
		* Draw one of the faces of a 3D object.
		* @param face - face to render
		*/
		void drawFace(Face &face);

		/** Delete the objects. */
		void deleteObjects();

		/**
		* Load a 3D object.
		* @param filename - path of the object
		* @return true if the model was loaded successfully
		*/
		bool loadObject(const string& filename);

		/**
		* Load the materials of a object.
		* @param filename - path of the object
		* @return true if the materials were loaded successfully
		*/
		bool loadMaterials(const string& filename);

		/**
		* Get the radius.
		* @return radius
		*/
		float getRadius() const;

		/**
		* Get the center.
		* @return pointer center
		*/
		Vector3f getCenter() const;

		/**
		* Get the path.
		* @return get the path
		*/
		string getPath() const;
	public:
		/** Render the model 3D. */
		void render();
	};

	/** The struct Material is a group of properties of a 3d object used to render. */
	struct Material
	{
		float Ka[4];
		float Kd[4];
		float Ks[4];
		float Ke[4];

		float shininess;
		float alpha;
		float illum;

		Texture *ambientMap;
		Texture *diffuseMap;
		Texture *specularMap;
		Texture *emissionMap;
		Texture *shininessMap;
		Texture *transparencyMap;
		Texture *bumpMap;

		string name;

		Material()
		{
			float defaultAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			float defaultDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
			float defaultSpecular[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			float defaultEmission[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

			memcpy(Ka, defaultAmbient, sizeof(float)* 4);
			memcpy(Kd, defaultDiffuse, sizeof(float)* 4);
			memcpy(Ks, defaultSpecular, sizeof(float)* 4);
			memcpy(Ke, defaultEmission, sizeof(float)* 4);

			ambientMap = 0;
			diffuseMap = 0;
			specularMap = 0;
			emissionMap = 0;
			shininessMap = 0;
			transparencyMap = 0;
			bumpMap = 0;
		}
	};

	/** The struct face has information such as normals, vertices, material,... */
	struct Face
	{
		sf::Vector3f **vertices;
		int numVertices;

		sf::Vector3f **normals;
		int numNormals;

		sf::Vector3f **UVWs;
		int numUVWs;

		Material *material;

		sf::Vector3f faceCenter;

		sf::Vector3f faceNormal;

		Face()
		{
			normals = 0;
			vertices = 0;
			UVWs = 0;

			material = 0;
		}
	};

	/** Group of objects. */
	struct GroupObject
	{
		vector<Face *>	faces;
		string			objectName;
		string			groupName;
	};
}

#endif
