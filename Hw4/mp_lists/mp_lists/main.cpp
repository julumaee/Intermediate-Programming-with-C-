#include "List.h"

int main() {

  List<int> list;
  
  std::cout << "Main: Reached line: " << __LINE__ << std::endl;

  for (unsigned i = 0; i < 6; i++) {
      list.insertBack(i);
  }

  list.tripleRotate();

  std::cout << "Main: Reached line: " << __LINE__ << std::endl;

  return 0;
}
