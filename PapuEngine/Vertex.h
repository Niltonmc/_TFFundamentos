#pragma once
#include <GL/glew.h>

struct Position {
	float x;
	float y;
};

struct ColorRGBA {
	ColorRGBA(GLubyte R, GLubyte G,
				GLubyte B, GLubyte A)
	{
		set(R, G, B, A);
	}

	ColorRGBA() : r(0), g(0), b(0), a(0) {}
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct UV {
	float u;
	float v;
};

struct Vertex {
	Position position;
	ColorRGBA color;
	UV uv;
	
	void setUV(float u, float v) {
		uv.u = u;
		uv.v = v;
	}
	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

<<<<<<< Updated upstream
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
=======
	void setColorRGBA(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.set(r, g, b, a);
>>>>>>> Stashed changes
	}
};
