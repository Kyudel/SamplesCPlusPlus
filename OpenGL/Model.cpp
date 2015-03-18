/////////////////////////////////////////////////////////////////////
//Copyright © 2013-2015 Ivan Perez
//Author: Ivan Perez
//Linkedin: http://es.linkedin.com/in/ivanperezduran
//Portfolio: http://ivanportfolio.tk/
/////////////////////////////////////////////////////////////////////

#include "Model.hpp"
 
#include <fstream>
#include <sstream>

#include "Utils.hpp"


using std::fstream;
using std::istringstream;

namespace GraphicLibrary
{
	
	Model::Model(string fileName)
	{
		objectLoaded = false;
		this->fileName = fileName;
		contIndex = 0;
		if( fileName != "" )
		{
			loadObject( fileName );
		}

		displayList = 0;

	}

	Model::~Model()
	{
		deleteObjects();
	}

	void Model::render()
	{	 
		Node::render();

		GLubyte color[3] = {0.5f,0.5f,0.5f};
		glColor3ubv (color);

		 if( !objectLoaded )
			return;
		 
		 if( displayList != 0 )
		 {
			 glCallList(displayList);
			 return;
		 }

		 displayList = glGenLists(1);

		 glNewList(displayList, GL_COMPILE_AND_EXECUTE );

		 drawObject(false);
		 drawObject(true);

		 glEndList();

	}


	void Model::drawObject(bool transparency)
	{	 
		Material *lastMaterial = 0;

		for( int i = 0; i< (int)objects.size(); i++ )
		{
			GroupObject *object = objects[i];
			for( int n = 0;n<(int) object->faces.size();n++ )
			{
				Face *face = object->faces[n];
				
				Material *material = face->material;

				if( material != lastMaterial )
				{
					if( transparency == false && material->alpha < 1.0f )
					{
						continue;
					}
					material->Kd[4] = material->alpha;
					glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ( GLfloat * )material->Ka );
					glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, ( GLfloat * )material->Kd );
					glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, ( GLfloat * )material->Ks );
					glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, ( GLfloat * )material->Ke );
					glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, material->shininess );

					if( material->diffuseMap != 0 )
					{
						glEnable( GL_TEXTURE_2D );
						glBindTexture( GL_TEXTURE_2D, material->diffuseMap->texID );
					}
					else
					{
						glDisable( GL_TEXTURE_2D );
					}

					lastMaterial = material;
				}

				drawFace(*face);
			}
		}
	}	 
	void Model::drawFace(Face &face)
	{	 
		if( (int) face.numVertices <=3 )
			glBegin(GL_TRIANGLES);
		else
			glBegin(GL_POLYGON);

		for( int v = 0; v<(int) face.numVertices; v++ )
		{
			if( (int)face.numUVWs > v && face.UVWs != 0)
			{
				glTexCoord2f( face.UVWs[v]->x, face.UVWs[v]->y );
			}
			if( (int)face.numVertices > v && face.vertices != 0)
			{
				glVertex3d( face.vertices[v]->x, face.vertices[v]->y, face.vertices[v]->z);
			}
			if( (int)face.numNormals > v && face.normals != 0)
			{
				glNormal3d( face.normals[v]->x, face.normals[v]->y, face.normals[v]->z);
			}
			
		}
		
		glEnd();
	}	 
		 
	void Model::deleteObjects()
	{	 
		for( int m =0; m < (int)materials.size() ;m++ )
		{
			if( materials[m]->ambientMap != 0 )
			{
				delete materials[m]->ambientMap;
			}
			if( materials[m]->diffuseMap != 0 )
			{
				delete materials[m]->diffuseMap;
			}
			if( materials[m]->ambientMap != 0 )
			{
				delete materials[m]->ambientMap;
			}
			if( materials[m]->specularMap != 0 )
			{
				delete materials[m]->specularMap;
			}
			if( materials[m]->shininessMap != 0 )
			{
				delete materials[m]->shininessMap;
			}
			if( materials[m]->transparencyMap != 0 )
			{
				delete materials[m]->transparencyMap;
			}
			if( materials[m]->bumpMap != 0 )
			{
				delete materials[m]->bumpMap;
			}
 
			delete materials[m];
		}

		for( int m =0; m < (int)vertices.size() ;m++ )
		{
			delete vertices[m];
		}

		for( int m =0; m < (int)normals.size() ;m++ )
		{
			delete normals[m];
		}

		for( int m =0; m < (int)UVWs.size() ;m++ )
		{
			delete UVWs[m];
		}

		for( int i = 0; i < (int)objects.size(); i++ )
		{
			GroupObject *object = objects[i];

			for( int f = 0; f< (int)object->faces.size(); f++ )
			{
			delete object->faces[f]->vertices;
			delete object->faces[f]->normals;
			delete object->faces[f]->UVWs;

			delete object->faces[f];
			}
		}

		UVWs.clear();
		normals.clear();
		vertices.clear();
		objects.clear();
		materials.clear();
	}	 
		 
	bool Model::loadObject(const string& filename)
	{	 
		this->fileName = fileName;

		fstream is( filename.data() );
		if( !is )
		{
			char line[256];
			is.getline(line,256);
			istringstream newLine(line, istringstream::in);
			string test;
			newLine >> test;
		}

		fstream istr( filename.data() );
		if( !istr)
			return false;

		deleteObjects();

		displayList = 0;
		objectLoaded = false;

		GroupObject *defaultObject = new GroupObject();
		GroupObject *currentGroup = defaultObject;

		objects.push_back( defaultObject );

		char path[256];
		strcpy(path, fileName.data());

		for( int i = (int)filename.length(); path[i] != '\\' && path[i] != '/' && i >= 0 ;i-- )
			path[i] = 0;

		Material *currentMaterial = 0;
		char line[256];
		int countF = 0;

		//Loop which looks each letter of every line
		while( istr.getline(line, 256) )
		{
			istringstream newLine(line, istringstream::in);

			string firstWord;

			newLine >> firstWord;

			if( firstWord == "#")
			{
				
			}
			else if( firstWord == "mtllib" )
			{
				string materialFilename;
				
				//Load materials
				while (newLine >> materialFilename )
				{
					loadMaterials( string(path) +  materialFilename );
					string s = string(path) +  materialFilename;
				}
			}
			else if( firstWord == "usemtl" )
			{
				string materialName;
				newLine >> materialName;

				for( int i= 0; i < (int)materials.size(); i++)
				{
					if( materials[i]->name == materialName )
					{
						currentMaterial = materials[i];
						break;
					}
				}
			}
			else if( firstWord == "v" )
			{
				Vector3f *vertex = new Vector3f();

				newLine >> vertex->x >> vertex->y >> vertex->z;

				vertices.push_back(vertex);
			}
			else if( firstWord == "vt" )
			{
				Vector3f *uvw = new Vector3f();

				newLine >> uvw->x >> uvw->y >> uvw->z;

				UVWs.push_back(uvw);
			}
			else if( firstWord == "vn" )
			{
				Vector3f *normal = new Vector3f();

				newLine >> normal->x >> normal->y >> normal->z;

				normals.push_back(normal);
			}
			else if( firstWord == "g" )
			{
				string objectName;

				newLine >> objectName;

				if( objectName == "default" )
				{
					currentGroup == defaultObject;
				}
				else
				{
					GroupObject *object = new GroupObject();

					object->objectName = objectName;
					newLine >> object->groupName;

					currentGroup = object;

					objects.push_back(object);
				}
			}
			else if( firstWord == "f" )
			{
				contIndex += 3;
				Face *newFace = new Face();

				newFace->material = currentMaterial;

				currentGroup->faces.push_back(newFace);

				countF++;
				
				vector<Vector3f *> tempVertices;
				vector<Vector3f *> tempUVWs;
				vector<Vector3f *> tempNormals;

				int cont = 0;
				while( !newLine.eof() && cont < 3)
				{
					cont++;
					int normal	= 0;
					int vertex	= 0;
					int uvw		= 0;


					bool noUV = false;

					char temp;

					if( (int)vertices.size() > 0 )
					{
						newLine >> vertex;

						while( newLine.get(temp) )
							if( temp == '/' || temp == ' ' )
								break;

						newLine.get(temp);

						if( temp == '/' )
							noUV = true;
						else
							newLine.unget();

						tempVertices.push_back( vertices[--vertex] );
					}

					if( (int)UVWs.size() > 0 && !noUV )
					{
						newLine >> uvw;

						while( newLine.get(temp) )
							if( temp == '/' || temp == ' ' )
								break;

						tempUVWs.push_back(UVWs[--uvw]);

					}

					if( (int)normals.size() > 0 )
					{
						newLine >> normal;

						while( newLine.get(temp) )
							if( temp == '/' || temp == ' ' )
								break;

						tempNormals.push_back( normals[--normal]);
					}
				}

				newFace->numVertices	= (int)tempVertices.size();
				newFace->numNormals		= (int)tempNormals.size();
				newFace->numUVWs		= (int)tempUVWs.size();

				newFace->vertices	= new Vector3f *[newFace->numVertices];
				newFace->normals	= new Vector3f *[newFace->numNormals];
				newFace->UVWs		= new Vector3f *[newFace->numUVWs];

				for( int v = 0; v < newFace->numVertices; v++ )
					newFace->vertices[v] = tempVertices[v];

				for( int v = 0; v < newFace->numNormals; v++ )
					newFace->normals[v] = tempNormals[v];

				for( int v = 0; v < newFace->numUVWs; v++ )
					newFace->UVWs[v] = tempUVWs[v];


				for( int v = 0; v < newFace->numUVWs; v++ )
					newFace->faceCenter += (*tempVertices[v]);

				newFace->faceCenter /= (float)newFace->numVertices;

				if( newFace->numVertices >= 3 )
				{
					Vector3f vector1 = Normalize( (*newFace->vertices[0]) - (*newFace->vertices[1]) );
					Vector3f vector2 = Normalize( (*newFace->vertices[0]) - (*newFace->vertices[2]) );

					newFace->faceNormal = CrossProduct(vector1, vector2);
				}
				
			}

		}

		float xmin, xmax;
		float ymin, ymax;
		float zmin, zmax;

		center = Vector3f(0, 0, 0);
		for( int n = 0; n < (int)vertices.size(); n++ )
		{
			if( n == 0 )
			{
				xmin = xmax = vertices[n]->x;
				ymin = ymax = vertices[n]->y;
				zmin = zmax = vertices[n]->z;
				continue;
			}
			//x
			if( vertices[n]->x < xmin )
			{
				xmin = vertices[n]->x;
			}
			if( vertices[n]->x > xmax )
			{
				xmax = vertices[n]->x;
			}
			//y
			if( vertices[n]->y < ymin )
			{
				ymin = vertices[n]->y;
			}
			if( vertices[n]->y > ymax )
			{
				ymax = vertices[n]->y;
			}
			//z
			if( vertices[n]->z < zmin )
			{
				zmin = vertices[n]->z;
			}
			if( vertices[n]->z > zmax )
			{
				zmax = vertices[n]->z;
			}
			
			center += (*vertices[n]);

		}

		center /= (float)vertices.size();

		radius = Magnitude( Vector3f(xmax, ymax, zmax) - Vector3f(xmin, ymin, zmin) )/2;

		objectLoaded = true;

		return true;
	}	 
	bool Model::loadMaterials(const string& filename)
	{
		fstream istr(filename.data());

		if( !istr )
			return false;

		char path[256];
		strcpy(path, fileName.data());

		for( int i = (int)filename.length(); path[i] != '\\' && path[i] != '/';i-- )
			path[i] = 0;

		Material *material = 0;

		char line[256];

		while( istr.getline(line, 256) )
		{
			istringstream newLine( line, istringstream::in );

			string firstWord;

			newLine >> firstWord;

			if( firstWord == "newmtl" )
			{
				material = new Material();

				materials.push_back(material);

				string name;

				newLine >> material->name;
			}
			else if( firstWord == "illum" )
			{
				newLine >> material->illum;
			}
			else if( firstWord == "Ka" )
			{
				newLine >> material->Ka[0] >> material->Ka[1] >> material->Ka[2];
			}
			else if( firstWord == "Kd" )
			{
				newLine >> material->Kd[0] >> material->Kd[1] >> material->Kd[2];
			}
			else if( firstWord == "Ks" )
			{
				newLine >> material->Ks[0] >> material->Ks[1] >> material->Ks[2];
			}
			else if( firstWord == "Ke" )
			{
				newLine >> material->Ke[0] >> material->Ke[1] >> material->Ke[2];
			}
			else if( firstWord == "Ns" )
			{
				newLine >> material->shininess;
			}
			else if( firstWord == "d" || firstWord == "Tr")
			{
				newLine >> material->alpha;
			}
			else if( firstWord == "Tf")
			{
				Vector3f color = Vector3f();

				newLine >> color.x >> color.y >> color.z;
				material->alpha = (color.x + color.y + color.z) / 3.0f;
			}
			else if( firstWord == "map_Ka")
			{
				
				string filename;
				newLine >> filename;

				Texture *map = new Texture( string(path) + filename, "" );
				
				material->ambientMap = map;
			}
			else if( firstWord == "map_Kd")
			{
				
				string filename;
				newLine >> filename;

				Texture *map = new Texture( string(path) + filename, "" );
				
				material->diffuseMap = map;
			}
			else if( firstWord == "map_Ks")
			{
				
				string filename;
				newLine >> filename;

				Texture *map = new Texture( string(path) + filename, "" );
				
				material->specularMap = map;
			}
			else if( firstWord == "map_Ke")
			{
				
				string filename;
				newLine >> filename;

				Texture *map = new Texture( string(path) + filename, "" );
				
				material->emissionMap = map;
			}
			else if( firstWord == "map_Ns")
			{
				
				string filename;
				newLine >> filename;

				Texture *map = new Texture( string(path) + filename, "" );
				
				material->shininessMap = map;
			}
			else if( firstWord == "map_d")
			{
				
				string filename;
				newLine >> filename;

				Texture *map = new Texture( string(path) + filename, "" );
				
				material->transparencyMap = map;
			}
			else if( firstWord == "map_Bump")
			{
				
				string filename;
				newLine >> filename;

				Texture *map = new Texture( string(path) + filename, "" );
				
				material->bumpMap = map;
			}
		}
	}


	float Model::getRadius() const
	{
		return radius;
	}

	Vector3f Model::getCenter() const
	{
		return center;
	}
	string Model::getPath() const
	{
		return fileName;
	}

}