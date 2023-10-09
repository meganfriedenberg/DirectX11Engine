#include "stdafx.h"
#include "assetManager.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "rapidjson\include\rapidjson\rapidjson.h"
#include "rapidjson\include\rapidjson\document.h"
#include <fstream>
#include <sstream>
#include "stringUtil.h"
#include "jsonUtil.h"



Material::Material()
{
	Graphics* pGraphics = Graphics::Get();
	materialShader = new Shader();
	matBuff = pGraphics->CreateGraphicsBuffer(&matConst, sizeof(matConst), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);
	matConst.c_diffuseColor = Vector3::Zero;
	matConst.c_specularColor = Vector3::Zero;
	matConst.c_specularPower = 0;
	matConst.padding = 0.0f;

	for (int i = 0; i < Graphics::TEXTURE_SLOT_TOTAL; i++)
	{
		textures[i] = nullptr;
	}
}

Material::~Material()
{
	matBuff->Release(); // Release the buffer, but do not delete the shader or textures
}

void Material::SetActive()
{
	materialShader->SetActive();

	Graphics* mGraphics = Graphics::Get();
	mGraphics->UploadBuffer(matBuff, &matConst, sizeof(matConst));
	mGraphics->GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_MATERIAL, 1, &matBuff);
	mGraphics->GetDeviceContext()->PSSetConstantBuffers(Graphics::CONSTANT_BUFFER_MATERIAL, 1, &matBuff);

	for (int i = 0; i < Graphics::TEXTURE_SLOT_TOTAL; i++)
	{
		if (textures[i] != nullptr)
		{
			//textures[i]->SetActive(Graphics::TEXTURE_SLOT_DIFFUSE);
			textures[i]->SetActive(i);
		}
	}
	
}

void Material::SetShader(const Shader* shader)
{
	materialShader = shader;
}
void Material::SetTexture(int slot, const Texture* texture)
{
	textures[slot] = texture; // I think?
}
void Material::SetDiffuseColor(const Vector3& color)
{
	matConst.c_diffuseColor = color;
}
void Material::SetSpecularColor(const Vector3& color)
{
	matConst.c_specularColor = color;
}
void Material::SetSpecularPower(float power)
{
	matConst.c_specularPower = power;
}

Material* Material::StaticLoad(const WCHAR* fileName, AssetManager* pManager)
{
	
	Material* m = new Material();

	if (false == m->Load(fileName, pManager))
	{
		return m;
	}
	return m; // Return a new material if the load fails
	

}
bool Material::Load(const WCHAR* fileName, AssetManager* pAssetManager)
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
		DbgAssert(false, "Unable to open Material file");
		return false;
	}

	std::string str = doc["metadata"]["type"].GetString();
	int ver = doc["metadata"]["version"].GetInt();

	// Check the metadata
	if (!doc["metadata"].IsObject() ||
		str != "itpmat" ||
		ver != 1)
	{
		DbgAssert(false, "Material File Incorrect Version");
		return false;
	}

	// Load shader
	std::wstring matName;
	GetWStringFromJSON(doc, "shader", matName);
	SetShader(pAssetManager->GetShader(matName));

	// Load the texture
	const rapidjson::Value& textFormat = doc["textures"];
	if (!textFormat.IsArray() || textFormat.Size() < 1)
	{
		DbgAssert(false, "Material File Invalid Textures Format");
		return false;
	}
	for (int i = 0; i < textFormat.Size(); i++)
	{
		std::wstring textureName;
		const rapidjson::Value& ind = textFormat[i];
		std::string text = (static_cast<std::string>(ind.GetString()));
		StringUtil::String2WString(textureName, text);

		SetTexture(i, pAssetManager->LoadTexture(textureName));
	}

	Vector3 diffColor;
	GetVectorFromJSON(doc, "diffuseColor", diffColor);

	SetDiffuseColor(diffColor);

	Vector3 specColor;
	GetVectorFromJSON(doc, "specularColor", specColor);
	SetSpecularColor(specColor);

	float specularPower = 0;
	GetFloatFromJSON(doc, "specularPower", specularPower);
	SetSpecularPower(specularPower);

	return true;
}