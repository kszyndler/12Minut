#pragma once

// Tekstura.
class CTexture
{
public:
	bool IsLoaded;

	CTexture(char *, GLuint);
	CTexture(char *);
	CTexture(char *, int, int);
	~CTexture(void);
	bool Load(bool);
	GLuint GetId(bool);

protected:
	int _magFilter;
	int _minFilter;
	char * _file;
	GLuint _id;
};

