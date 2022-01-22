#pragma once
class Object
{
protected:
	Object();
	~Object();

	virtual void draw();
	virtual void update();

	virtual int getX();
	virtual int getY();
	virtual int getWidth();
	virtual int getHeight();

protected:
	int x, y, w, h;
};

