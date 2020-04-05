#include "Block.h"

Block::Block(const BlockType type) : _type(type) {}

BlockType Block::type() const {
	return this->_type;
}
