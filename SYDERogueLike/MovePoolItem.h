#pragma once
#include "Move.h"
#include <vector>
#include <string>
#include <memory>

class MovePoolItem {
public:

	MovePoolItem() {}
	MovePoolItem(std::shared_ptr<Move> m, int c) { m_Move = m; m_Cost = c;}

	std::shared_ptr<Move> getMove() { return m_Move; }
	int getCost() { return m_Cost; }

private:
	std::shared_ptr<Move> m_Move;
	int m_Cost;
};