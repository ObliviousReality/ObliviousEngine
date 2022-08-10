#include "pch.h"
#include "..\header\ObjectList.h"

ObjectList::ObjectNode* ObjectList::create()
{
	ObjectNode* head = new ObjectNode;
	head->next = nullptr;
	head->object = nullptr;
	return head;
}

void ObjectList::addItem(ObjectNode* head, Object* object)
{
	if (head->object == nullptr)
	{
		head->object = object;
	}
	else
	{
		ObjectNode* newNode = new ObjectNode;
		newNode->object = object;
		newNode->next = nullptr;
		ObjectNode* node = head;
		while (node->next != nullptr)
		{
			node = node->next;
		}
		node->next = newNode;
	}

}

void ObjectList::removeItem(ObjectNode* head, Object* ob)
{
	if (head->object == nullptr)
	{
		return;
	}
	ObjectNode* node = head;
	while (node->next->object != ob)
	{
		if (node->next == nullptr)
		{
			return;
		}
		node = node->next;
		if (node->next == nullptr)
		{
			return;
		}
	}
	node->next = node->next->next;
}

void ObjectList::clear(ObjectNode* head)
{
	head->next = nullptr;
	head->object = nullptr;
}

void ObjectList::render(ObjectNode* head)
{
	if (!head)
	{
		return;
	}
	ObjectList::ObjectNode* temp = head;
	while (temp)
	{
		temp->object->update();
		temp->object->draw();
		temp = temp->next;
	}
}

int ObjectList::length(ObjectNode* head)
{
	if (!head)
	{
		return 0;
	}
	ObjectList::ObjectNode* temp = head;
	int count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return count;
}
