#include "Chunk.h"


const Block Chunk::_AIR = Block(AIR);

Chunk::Chunk() : _height(INITIAL_CHUNK_HEIGHT) {
	this->_chunkData = new Block[CHUNK_WIDTH*CHUNK_HEIGHT*INITIAL_CHUNK_HEIGHT];
}

int Chunk::height() const {
	return this->_height;
}

const Block* Chunk::blockAt(int chunkX, int chunkY, int chunkZ) const {
	if (chunkZ < this->_height) {
		return &this->_chunkData[chunkZ*CHUNK_WIDTH*CHUNK_HEIGHT+chunkY*CHUNK_WIDTH+chunkX];
	} else {
		return &_AIR;
	}
}

void Chunk::setBlockAt(int chunkX, int chunkY, int chunkZ, BlockType type) {
	if (chunkZ >= this->_height && type != AIR) {
		// TODO
	} else {
		this->_chunkData[chunkZ*CHUNK_WIDTH*CHUNK_HEIGHT+chunkY*CHUNK_WIDTH+chunkX] = Block(type);
	}
}
