#include "StdAfx.h"


CWall::CWall(vec3 a, vec3 b, vec3 c, vec3 d, string texture) : CSceneObject(), Colliding(1)
 {
	_displayListId = -1; 
	v.resize(4);
	v[0] = a;
	v[1] = b;
	v[2] = c;
	v[3] = d;

	collide(v, 0, this);

	vec3::Cross((c-b), (a-b), n); //wektor normalny sciany
	n.Normalize(); 
	textureName = texture; 
}


CWall::~CWall(void)
{
}

void CWall::Initialize(void)
{
	_displayListId = glGenLists(1);
	
	glNewList(_displayListId, GL_COMPILE);
		glBegin(GL_QUADS);
		
			// Wektor normalny jest taki sam dla wszystkich wierzcho³ków.
			glNormal3f( n.x, n.y, n.z);

			glTexCoord2f( 1.0f, 0.0f );
			glVertex3f(v[0].x, v[0].y, v[0].z);
				
			glTexCoord2f( 1.0f, 1.0f );
			glVertex3f(v[1].x, v[1].y, v[1].z);
			
			glTexCoord2f( 0.0f, 1.0f );
			glVertex3f(v[2].x, v[2].y, v[2].z);

			glTexCoord2f( 0.0f, 0.0f );
			glVertex3f(v[3].x, v[3].y, v[3].z);
			
		glEnd();
	glEndList();

	string texPath("Resources\\tex\\" + textureName);
	char *cstr = new char[texPath.length() + 1];
	strcpy(cstr, texPath.c_str());
	_wallTexture = new CTexture(cstr, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_wallTexture->Load(true);
	delete[] cstr;

}

void CWall::Update(void)
{
}

void CWall::Render(void)
{
	glPushMatrix();

	float mA[] = { 1.0f, 1.0f, 1.0f };
	float mS[] = { 0.0f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mA);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mS);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _wallTexture->GetId(true));
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glCallList(_displayListId);

	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
}
