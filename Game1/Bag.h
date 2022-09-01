#pragma once

struct InBagItem
{
	string name;
	ItemType type;
	float damage;
};

class Bag : public OnScreen
{
	InBagItem bagitem;

	Bag();
	~Bag();

};

