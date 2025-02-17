#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	// Create circle
	std::vector<vector3 > vertex;
	GLfloat theta = 0;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(theta) * a_fRadius, sin(theta) * a_fRadius, 0.0f);
		theta += delta;
		vertex.push_back(temp);
	}

	// Create base and triangle sides
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(ZERO_V3, vertex[(i + 1) % a_nSubdivisions], vertex[i]);
		AddTri(vector3(0.0f, 0.0f, a_fHeight), vertex[i], vertex[(i + 1) % a_nSubdivisions]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	// Create circle
	std::vector<vector3 > vertex;
	GLfloat theta = 0;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(theta) * a_fRadius, sin(theta) * a_fRadius, 0.0f);
		theta += delta;
		vertex.push_back(temp);
	}

	// Create 2 circle bases and quad sides based on base vertices
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float tempVertex = vertex[i].z + a_fHeight;
		float tempVertex_Sub = vertex[(i + 1) % a_nSubdivisions].z + a_fHeight;
		AddTri(ZERO_V3, vertex[(i + 1) % a_nSubdivisions], vertex[i]);
		AddQuad(vertex[i], 
			vertex[(i + 1) % a_nSubdivisions], 
			vector3(vertex[i].x, vertex[i].y, tempVertex), 
			vector3(vertex[(i + 1) % a_nSubdivisions].x, vertex[(i + 1) % a_nSubdivisions].y, tempVertex_Sub));
		AddTri(vector3(0.0f, 0.0f, a_fHeight), 
			vector3(vertex[i].x, vertex[i].y, tempVertex), 
			vector3(vertex[(i + 1) % a_nSubdivisions].x, vertex[(i + 1) % a_nSubdivisions].y, tempVertex_Sub));
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	std::vector<vector3 > vertexOuter;
	std::vector<vector3 > vertexInner;
	GLfloat theta = 0;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	// Create vertices based off of circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 tempOuter = vector3(cos(theta) * a_fOuterRadius, sin(theta) * a_fOuterRadius, 0.0f);
		vector3 tempInner = vector3(cos(theta) * a_fInnerRadius, sin(theta) * a_fInnerRadius, 0.0f);
		theta += delta;
		vertexOuter.push_back(tempOuter);
		vertexInner.push_back(tempInner);
	}

	// Create outer sides
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float tempVertex = vertexOuter[i].z + a_fHeight;
		float tempVertex_Sub = vertexOuter[(i + 1) % a_nSubdivisions].z + a_fHeight;
		AddQuad(vertexOuter[i], 
			vertexOuter[(i + 1) % a_nSubdivisions], 
			vector3(vertexOuter[i].x, vertexOuter[i].y, tempVertex), 
			vector3(vertexOuter[(i + 1) % a_nSubdivisions].x, vertexOuter[(i + 1) % a_nSubdivisions].y, tempVertex_Sub));
	}

	// Create inner sides
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float tempVertex = vertexInner[i].z + a_fHeight;
		float tempVertex_Sub = vertexInner[(i + 1) % a_nSubdivisions].z + a_fHeight;
		AddQuad(vector3(vertexInner[i].x, vertexInner[i].y, tempVertex), 
			vector3(vertexInner[(i + 1) % a_nSubdivisions].x, vertexInner[(i + 1) % a_nSubdivisions].y, tempVertex_Sub), 
			vertexInner[i], 
			vertexInner[(i + 1) % a_nSubdivisions]);
	}

	// Create connection between outer and inner sides
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		float tempVertex_O = vertexOuter[i].z + a_fHeight;
		float tempVertex_Sub_O = vertexOuter[(i + 1) % a_nSubdivisions].z + a_fHeight;
		float tempVertex_I = vertexInner[i].z + a_fHeight;
		float tempVertex_Sub_I = vertexInner[(i + 1) % a_nSubdivisions].z + a_fHeight;
		AddQuad(vector3(vertexOuter[i].x, vertexOuter[i].y, tempVertex_O), 
			vector3(vertexOuter[(i + 1) % a_nSubdivisions].x, vertexOuter[(i + 1) % a_nSubdivisions].y, tempVertex_Sub_O), 
			vector3(vertexInner[i].x, vertexInner[i].y, tempVertex_I), 
			vector3(vertexInner[(i + 1) % a_nSubdivisions].x, vertexInner[(i + 1) % a_nSubdivisions].y, tempVertex_Sub_I));
		AddQuad(vertexInner[i], 
			vertexInner[(i + 1) % a_nSubdivisions], 
			vertexOuter[i], 
			vertexOuter[(i + 1) % a_nSubdivisions]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	// NOTE: THIS DOES NOT WORK
	// Got help from "Computer Graphics Programming in OpenGL With C++"

	std::vector<vector3> vertex;
	
	// Calculate first ring
	for (int i = 0; i < a_nSubdivisionsB; i++)
	{
		glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), ((i * 360.0f) / a_nSubdivisionsB), glm::vec3(0.0f, 0.0f, 1.0f));
		vector3 position(rotateMat * vector4(a_fOuterRadius, 0.0f, 0.0f, 1.0f));
		vertex.push_back(vector3(position + vector3(a_fInnerRadius, 0.0f, 0.0f)));
	}

	// Rotate ring to get other rings
	for (int i = 1; i < a_nSubdivisionsB + 1; i++)
	{
		glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), ((i * 360.0f) / a_nSubdivisionsB), glm::vec3(0.0f, 0.0f, 1.0f));
		//vertex[i * (a_nSubdivisionsB + 1) + i] = (vector3(rotateMat * vector4(vertex[i], 0.0f)));
	}

	// Calculate sides of torus
	for (int i = 0; i < a_nSubdivisionsB; i++)
	{
		AddTri(vertex[i], vertex[(i + 1) % a_nSubdivisionsB], vertex[i]);
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	// NOTE: THIS DOES NOT WORK
	// Got help from https://www.songho.ca/opengl/gl_sphere.html#webgl_sphere

	std::vector<vector3> vertex;
	std::vector<vector3> normalVertex;
	std::vector<float> textVertex;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));
	float sectorAngle;

	// Build vertices
	for (int i = 0; i <= a_nSubdivisions; i++)
	{
		// Create angle
		sectorAngle = 2.0f * PI - i * delta;
		float xy = cosf(sectorAngle) * a_fRadius;
		float z = sinf(sectorAngle) * a_fRadius;

		for (int j = 0; j <= a_nSubdivisions; j++)
		{
			// vertex position
			sectorAngle = j * delta;
			float x = xy * cosf(sectorAngle);
			float y = xy * sinf(sectorAngle);
			vector3 temp = vector3(x, y, z);
			vertex.push_back(temp);

			// normal vertices
			//float length = 1.0f / a_fRadius;
			//float nx = x * length;
			//float ny = y * length;
			//float nz = z * length;
			//vector3 normalTemp = vector3(nx, ny, nz);
			//normalVertex.push_back(normalTemp);

			// text corrdinates
			//float s = (float)j / a_nSubdivisions;
			//float t = (float)i / a_nSubdivisions;
			//textVertex.push_back(s);
			//textVertex.push_back(t);
		}
	}

	// Create triangles to fill circle
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 tempVertex = vertex[i + 1];
		vector3 tempVertex_Sub = vertex[((i + 1) % a_nSubdivisions) + 1];

		for (int j = 0; j < a_nSubdivisions; j++)
		{
			if (i != 0)
			{
				AddTri(vertex[j], vertex[(j + 1) % a_nSubdivisions], tempVertex);
			}

			if (i != (a_nSubdivisions - 1))
			{
				AddTri(tempVertex, vertex[(j + 1) % a_nSubdivisions], tempVertex_Sub);
			}
		}
	}

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}