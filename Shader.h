#pragma once
#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>
#include<GL\glew.h>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CommonValue.h"

 class Shader
{
public:
	Shader();
	void CreateFromString(const char* vertexCode,const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	
	std::string ReadFile(const char* fileLocation); 

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetEyePosition();

	void SetDirectionalLight(DirectionalLight * dLight);
	void SetPointLight(PointLight* pLight, unsigned int lightCount);
	void SetSpotLight(SpotLight* sLight, unsigned int lightCount);

	void UseShader();
	void ClearShader();
	~Shader();


private:
	int pointLightCount;
	int spotLightCount;

	GLuint shaderID, uniformProjection, uniformModel,uniformView,uniformEyePosition,
	uniformSpecularIntensity, uniformShininess;

	// directionalLight struct
	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	}uniformDirectionalLight;

	// PointLight struct
	GLuint uniformPointLightCount;
	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	}uniformPointLight[MAX_POINT_LIGHTS];

	// SpotLight struct
	GLuint uniformSpotLightCount;
	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;

		GLuint uniformDirection;
		GLuint uniformEdge;
	}uniformSpotLight[MAX_SPOT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

 };