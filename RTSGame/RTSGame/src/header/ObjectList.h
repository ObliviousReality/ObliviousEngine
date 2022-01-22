#pragma once
#include "Object.h"
class ObjectList
{
public:
	struct ObjectNode
	{
		Object* object;
		ObjectNode* next;
	};
	static ObjectNode* create();
	static void addItem(ObjectNode* head, Object* object);
	static void removeItem(ObjectNode* head, Object* ob);
	static void clear(ObjectNode* head);
	static void render(ObjectNode* head);
	static int length(ObjectNode* head);
};

