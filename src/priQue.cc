#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class PriQue {
  vector<int> ele;

public:
  void push(int e) {
    int pos = ele.size();
    ele.push_back(e);
    while(pos != 0) {
      auto parent = (pos - 1) / 2;
      if(ele[parent] >= ele[pos])break;
      swap(ele[parent], ele[pos]);
      pos = parent;
    }
  }

  int pop() {
    int res = ele[0];
    int sz = ele.size();
    swap(ele[0], ele[sz-1]);
    ele.pop_back();
    int parent = 0;
    int child = 2 * parent + 1;
    --sz;
    while(child < sz) {
      if(child + 1 < sz && ele[child] < ele[child+1])++child;
      if(ele[parent] >= ele[child])break;
      swap(ele[parent], ele[child]);
      parent = child;
      child = 2 * parent + 1;
    }
    return res;
  }
  bool empty() const {
    return ele.empty();
  }
};

int main(int argc, char *argv[])
{
  const int MAX = atoi(argv[1]);
  PriQue que;
  vector<int> nums;
  for(int i = 0; i < MAX; ++i) {
    int n = rand() % MAX;
    que.push(n);
    nums.push_back(n);
  }
  sort(nums.begin(), nums.end());
  for(int i = MAX - 1; i >= 0; --i) {
    if(nums[i] != que.pop()) {
      cout << "WRONG\t";
      break;
    }
  }
  cout << "ENDS\n";
  return 0;
}
