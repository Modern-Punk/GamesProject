#include "Light.h"
void Material::SetAmbient(float r, float g, float b, float a) {
	mAmbient[0] = r;
	mAmbient[1] = g;
	mAmbient[2] = b;
	mAmbient[3] = a;
}
void Material::SetDiffuse(float r, float g, float b, float a) {
	mDiffuse[0] = r;
	mDiffuse[1] = g;
	mDiffuse[2] = b;
	mDiffuse[3] = a;
}
void Material::SetSpecular(float r, float g, float b, float a) {
	mSpecular[0] = r;
	mSpecular[1] = g;
	mSpecular[2] = b;
	mSpecular[3] = a;
}
void Material::SetSpecularShininess(float shininess) {
	mShininess = shininess;
}
void Material::Update() {
	glMaterialfv(GL_FRONT, GL_AMBIENT, mAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, mShininess);
}
void Light::SetAmbientColor(float r, float g, float b, float a) {
	mAmbientColor[0] = r;
	mAmbientColor[1] = g;
	mAmbientColor[2] = b;
	mAmbientColor[3] = a;
}

void Light::SetDiffuseColor(float r, float g, float b, float a) {
	mDiffuseColor[0] = r;
	mDiffuseColor[1] = g;
	mDiffuseColor[2] = b;
	mDiffuseColor[3] = a;
}

void Light::SetSpecularColor(float r, float g, float b, float a) {
	mSpecularColor[0] = r;
	mSpecularColor[1] = g;
	mSpecularColor[2] = b;
	mSpecularColor[3] = a;
}

void Light::Update() {
	glEnable(mLightIdentifier);
	glLightfv(mLightIdentifier, GL_AMBIENT, mAmbientColor);
	glLightfv(mLightIdentifier, GL_DIFFUSE, mDiffuseColor);
	glLightfv(mLightIdentifier, GL_SPECULAR, mSpecularColor);
}

void Light::SetPosition(float x, float y, float z) {
	mPosition[0] = x;
	mPosition[1] = y;
	mPosition[2] = z;
}

void DirectionLight::Update() {
	Light::Update();
	float position[] = { mPosition[0],mPosition[1],mPosition[2],0.0f };
	glLightfv(mLightIdentifier, GL_POSITION, position);
}

void PointLight::Update() {
	Light::Update();
	float position[] = { mPosition[0],mPosition[1],mPosition[2],1.0f };
	glLightfv(mLightIdentifier, GL_POSITION, position);
	glLightf(mLightIdentifier, GL_CONSTANT_ATTENUATION, mSetting[0]);
	glLightf(mLightIdentifier, GL_LINEAR_ATTENUATION, mSetting[1]);
	glLightf(mLightIdentifier, GL_QUADRATIC_ATTENUATION, mSetting[2]);
}

void PointLight::SetAttenuation(float constant, float linear, float quadratic) {
	mSetting[0] = constant;
	mSetting[1] = linear;
	mSetting[2] = quadratic;
}

void SpotLight::SetExponent(float v) {
	mSetting1[0] = v;
}
void SpotLight::SetCutoff(float v) {
	mSetting1[1] = v;
}
void SpotLight::SetDirection(float x, float y, float z) {
	mDirection[0] = x;
	mDirection[1] = y;
	mDirection[2] = z;
}
void SpotLight::Update() {
	Light::Update();
	float position[] = { mPosition[0],mPosition[1],mPosition[2],1.0f };
	glLightfv(mLightIdentifier, GL_POSITION, position);
	glLightf(mLightIdentifier, GL_CONSTANT_ATTENUATION, mSetting[0]);
	glLightf(mLightIdentifier, GL_LINEAR_ATTENUATION, mSetting[1]);
	glLightf(mLightIdentifier, GL_QUADRATIC_ATTENUATION, mSetting[2]);
	glLightf(mLightIdentifier, GL_SPOT_EXPONENT, mSetting1[0]);
	glLightf(mLightIdentifier, GL_SPOT_CUTOFF, mSetting1[1]);
	glLightfv(mLightIdentifier, GL_SPOT_DIRECTION, mDirection);
}


