#include <iostream>
#include <deque>

int main ()
{
  unsigned int i;

  // constructors used in the same order as described above:
  std::deque<int> first;                                // empty deque of ints
  std::deque<int> second (4,100);                       // four ints with value 100
  std::deque<int> third (second.begin(),second.end());  // iterating through second
  std::deque<int> fourth (third);                       // a copy of third
  third.push_back(999);
  // the iterator constructor can be used to copy arrays:
  int myints[] = {16,2,77,29};
  std::deque<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of third are:";
  for (std::deque<int>::iterator it = third.begin(); it!=third.end(); ++it)
    std::cout << ' ' << *it;

  std::cout << "The contents of fourth are:";
  for (std::deque<int>::iterator it = fourth.begin(); it!=fourth.end(); ++it)
    std::cout << ' ' << *it;


  std::cout << '\n';

  return 0;
}