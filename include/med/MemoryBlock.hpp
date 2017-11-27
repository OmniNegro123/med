#include <vector>

#include "med/MedTypes.hpp"
#include "med/Bytes.hpp"

using namespace std;

class MemoryBlock : public Bytes {
public:
  MemoryBlock();
  MemoryBlock(Byte* data, int size);
  virtual ~MemoryBlock();

  void setDataWithAddress(Byte* data, int size, MemAddr address);
  void setAddress(MemAddr address);
  MemAddr getAddress();

private:
  MemAddr address;
};

class MemoryBlocks {
public:
  MemoryBlocks(); // Do not destruct by freeing the memory. Free on demand
  void free();
  void push(MemoryBlock block);
  void clear();
  int getSize();

  vector<MemoryBlock> getData();
private:
  vector<MemoryBlock> data;
};