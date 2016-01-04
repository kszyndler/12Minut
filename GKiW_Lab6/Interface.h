#pragma once
class Interface
{
public:
	Interface();
	~Interface();
	void initBackground(float x, float y, float width, float height);
	void draw(float x, float y, void *font, char *string);

private:
	void setOrthographicProjection();
	void restorePerspectiveProjection();
	void renderSpacedBitmapString(float x, float y, int spacing, void *font, char *string);
	void renderVerticalBitmapString(float x, float y, int bitmapHeight, void *font, char *string);
	void renderBitmapString(float x, float y, void *font, char *string);
	GLuint backgroundListId; 

};

