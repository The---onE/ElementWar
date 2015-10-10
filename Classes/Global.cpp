#include "Global.h"

void setSize(Node* s, float size)
{
	s->setScale(DATUM*size / s->getContentSize().height);
}

int randNum(int size, int probability[])
{
	int sum = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += probability[i];
	}
	float r = rand_0_1()*sum;

	sum = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += probability[i];
		if (r < sum)
		{
			return i;
		}
	}
	return -1;
}
