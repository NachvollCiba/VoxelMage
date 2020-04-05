
enum BlockType {
	AIR=0, 
	GRASS=1, 
	DIRT=2, 
	STONE=3
};

class Block {
	private:
		BlockType _type;
	public:
		Block(BlockType type=AIR);

		BlockType type() const;
};
