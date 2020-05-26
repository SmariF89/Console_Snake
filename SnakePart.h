#pragma once

#ifndef SNAKEPART_H
#define SNAKEPART_H

#include "Position.h"

struct SnakePart
{
	Position currentPosition;
	Position nextPosition;
};

#endif // SNAKEPART_H