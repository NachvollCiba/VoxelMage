#include "Block.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16

#define INITIAL_CHUNK_HEIGHT 256

class Chunk {

	private:
		static const Block _AIR;

		int _height;
		Block* _chunkData;

	public:
		Chunk();

		int height() const;
		const Block* blockAt(int chunkX, int chunkY, int chunkZ) const;

		void setBlockAt(int chunkX, int chunkY, int chunkZ, BlockType type);
		void trim();
};
