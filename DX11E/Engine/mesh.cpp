#include "stdafx.h"
#include "mesh.h"
#include "assetManager.h"
#include "jsonUtil.h"
#include "material.h"
#include "Shader.h"
#include "stringUtil.h"
#include "vertexBuffer.h"
#include "rapidjson\include\rapidjson\rapidjson.h"
#include "rapidjson\include\rapidjson\document.h"
#include <fstream>
#include <sstream>


Mesh::Mesh(const VertexBuffer* vertexBuffer, Material* material)
{
	mMaterial = material;
	mVertexBuffer = vertexBuffer;
}

Mesh::~Mesh()
{
	delete mVertexBuffer;
}

void Mesh::Draw() const
{
	mMaterial->SetActive();
	mVertexBuffer->Draw();
}

bool Mesh::Load(const WCHAR* fileName, AssetManager* pAssetManager)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		DbgAssert(false, "Unable to open Mesh file");
		return false;
	}

	std::string str = doc["metadata"]["type"].GetString();
	int ver = doc["metadata"]["version"].GetInt();

	// Check the metadata
	if (!doc["metadata"].IsObject() ||
		str != "itpmesh" ||
		ver != 3)
	{
		DbgAssert(false, "Mesh File Incorrect Version");
		return false;
	}

	// Check if it's a skinned mesh
	GetBoolFromJSON(doc, "skinned", mIsSkinned);

	// Load Material
	std::wstring matName;
	GetWStringFromJSON(doc, "material", matName);
	mMaterial = pAssetManager->LoadMaterial(matName);

	// Read the vertex format
	const rapidjson::Value& vertFormat = doc["vertexformat"];
	if (!vertFormat.IsArray() || vertFormat.Size() < 1)
	{
		DbgAssert(false, "Mesh File Invalid Vertex Format");
		return false;
	}

	uint32_t vertSize = 0;
	uint32_t vertNumValues = 0;
	std::string inputLayoutName;
	for (rapidjson::SizeType i = 0; i < vertFormat.Size(); i++)
	{
		if (!vertFormat[i].IsObject())
		{
			DbgAssert(false, "Mesh File Invalid Vertex Format");
			return false;
		}

		inputLayoutName += vertFormat[i]["name"].GetString();

		std::string vertType = vertFormat[i]["type"].GetString();
		uint32_t elementSize = 0;
		if (vertType == "float")
			elementSize = 4;
		else
			elementSize = 1;

		vertNumValues += vertFormat[i]["count"].GetUint();
		vertSize += elementSize * vertFormat[i]["count"].GetUint();
	}

	if (vertNumValues < 3)
	{
		DbgAssert(false, "Mesh File Invalid Vertex Format");
		return false;
	}

	// Load in the vertices
	const rapidjson::Value& vertsJson = doc["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		DbgAssert(false, "Mesh File Invalid Vertex Format");
		return false;
	}

	union VertPacked
	{
		float f;
		uint8_t b[4];
	};
	uint32_t numVerts = vertsJson.Size();
	std::vector<VertPacked> vertices;
	vertices.reserve(numVerts * vertSize);
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray() || vert.Size() != vertNumValues)
		{
			DbgAssert(false, "Mesh File Invalid Vertex Format");
			return false;
		}

		// Now stuff all the vertices into the vertex buffer
		if (mIsSkinned)
		{   //special case for skinned
			VertPacked temp;
			// Position/Normal
			for (rapidjson::SizeType j = 0; j < 6; j++)
			{
				temp.f = vert[j].GetDouble();
				vertices.emplace_back(temp);
			}

			// Uints for bones and weights
			for (rapidjson::SizeType j = 6; j < 14; j += 4)
			{
				temp.b[0] = vert[j].GetUint();
				temp.b[1] = vert[j + 1].GetUint();
				temp.b[2] = vert[j + 2].GetUint();
				temp.b[3] = vert[j + 3].GetUint();
				vertices.emplace_back(temp);
			}

			// Last two texture coordinates
			for (rapidjson::SizeType j = 14; j < vert.Size(); j++)
			{
				temp.f = vert[j].GetDouble();
				vertices.emplace_back(temp);
			}
		}
		else
		{
			for (rapidjson::SizeType j = 0; j < vert.Size(); j++)
			{
				VertPacked temp;
				temp.f = vert[j].GetDouble();
				vertices.emplace_back(temp);
			}
		}
	}

	// Load in the indices
	const rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		DbgAssert(false, "Mesh File Invalid Index Format");
		return false;
	}

	std::vector<uint16_t> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
			DbgAssert(false, "Mesh File Invalid Index Format");
			return false;
		}

		indices.emplace_back(static_cast<uint16_t>(ind[0].GetUint()));
		indices.emplace_back(static_cast<uint16_t>(ind[1].GetUint()));
		indices.emplace_back(static_cast<uint16_t>(ind[2].GetUint()));
	}

	// Now create a vertex array
	mVertexBuffer = new VertexBuffer(
		vertices.data(), numVerts, vertSize,
		indices.data(), (uint32_t)indices.size(), sizeof(uint16_t)
	);

	return true;	// everything went fine
}

Mesh* Mesh::StaticLoad(const WCHAR* fileName, AssetManager* pAssetManager)
{
	Mesh* pMesh = new Mesh(nullptr, nullptr);
	if (false == pMesh->Load(fileName, pAssetManager))
	{
		delete pMesh;
		return nullptr;
	}
	return pMesh;
}
