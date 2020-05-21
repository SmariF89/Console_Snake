#pragma once

#ifndef FRUIT_H
#define FRUIT_H

class Fruit
{
public:
	Fruit();
	~Fruit();

	void spawn();

private:
	void vanish();

	int _score;
	int _timeLeft;

	struct _position
	{
		int x;
		int y;
	};
};

#endif // FRUIT_H