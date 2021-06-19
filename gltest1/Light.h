#pragma once
#include <stdio.h>
#include<GL/glut.h>

class Material {
public:
	float mAmbient[4], mDiffuse[4], mSpecular[4];
	float mShininess;
	void SetAmbient(float r, float g, float b, float a);
	void SetDiffuse(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);
	void SetSpecularShininess(float shininess);
	void Update();
};
class Light {
public:
	GLenum mLightIdentifier;
	float mAmbientColor[4], mDiffuseColor[4], mSpecularColor[4];
	float mPosition[3];
	Light(GLenum identifier) :mLightIdentifier(identifier) {}
	virtual void SetPosition(float x, float y, float z);
	void SetAmbientColor(float r, float g, float b, float a);
	void SetDiffuseColor(float r, float g, float b, float a);
	void SetSpecularColor(float r, float g, float b, float a);
	virtual void Update();
};

class DirectionLight :public Light {
public:
	DirectionLight(GLenum identifier) :Light(identifier) {}
	void Update();
};
class PointLight :public Light {
public:
	float mSetting[3];//�������
	PointLight(GLenum identifier) :Light(identifier) {}
	void SetAttenuation(float constant, float linear, float quadratic);//����˥��,����������Ӧ��˥��ϵ��������˥��ϵ����ƽ����˥��ϵ��
	void Update();
};
class SpotLight :public PointLight {
public:
	float mSetting1[3];
	float mDirection[3];
	SpotLight(GLenum identifier) :PointLight(identifier) {}
	void Update();
	void SetDirection(float x, float y, float z);
	void SetExponent(float v);//�������ߵ��ǽǶ�
	void SetCutoff(float v);//���������ĽǶ�

};

