#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Node {
  int value;
  Node* left;
  Node* right;
  Node(int val): value(val), left(nullptr), right(nullptr) {}
};
class Bst {
private:
  Node* root;
public:
  Bst(const vector<int>& preOrder, const vector<int>& inOrder);
  ~Bst();
  void printPreOrder();
  void printInOrder();
  void printPostOrder();
  void printPreOrderStack();
  void printInOrderStack();
  void printPostOrderStack();
};
//post order
static void iterPost(Node* root)
{
  if(root == nullptr)return;
  iterPost(root->left);
  iterPost(root->right);
  cout << root->value << "\t";
}
void Bst::printPostOrder()
{
  cout << "*************PostOrder************************\n";
  iterPost(root);
  cout << "\n*********************************************\n";
}
void Bst::printPostOrderStack()
{
  cout << "*************PostOrderStack************************\n";
  stack<Node*> st;
  vector<int> nums;
  auto p = root;
  while(!st.empty() || p != nullptr) {
    if(p != nullptr) {
      st.push(p);
      nums.insert(nums.begin(), p->value);
      p = p->right;
    }
    else {
      auto top = st.top();
      st.pop();
      p = top->left;
    }
  }
  for(auto&& n: nums) {
    cout << n << "\t";
  }
  cout << "\n*********************************************\n";
}

//in order
static void iterIn(Node* root)
{
  if(root == nullptr)return;
  iterIn(root->left);
  cout << root->value << "\t";
  iterIn(root->right);
}
void Bst::printInOrder()
{
  cout << "*************InOrder************************\n";
  iterIn(root);
  cout << "\n*********************************************\n";
}
void Bst::printInOrderStack()
{
  cout << "*************InOrderStack************************\n";
  auto p = root;
  stack<Node*> st;
  while(!st.empty() || p != nullptr) {
    if(p != nullptr) {
      st.push(p);
      p = p->left;
    }
    else {
      auto top = st.top();
      cout << top->value << "\t";
      st.pop();
      p = top->right;
    }
  }
  cout << "\n*********************************************\n";
}

//pre order
static void iterPre(Node* root)
{
  if(root == nullptr)return;
  cout << root->value << "\t";
  iterPre(root->left);
  iterPre(root->right);
}
void Bst::printPreOrder()
{
  cout << "*************preOrder************************\n";
  iterPre(root);
  cout << "\n*********************************************\n";
}
void Bst::printPreOrderStack()
{
  cout << "*************preOrderStack************************\n";
  auto p = root;
  stack<Node*> st;
  while(!st.empty() || p != nullptr) {
    if(p != nullptr) {
      st.push(p);
      cout << p->value << "\t";
      p = p->left;
    }
    else {
      p = st.top()->right;
      st.pop();
    }
  }
  cout << "\n*********************************************\n";
}

//build
static int findIndex(const vector<int>& inorder, int l, int h, int val)
{
  for(int i = l; i <= h; ++i) {
    if(inorder[i] == val)return i;
  }
  return -1;
}
static Node* build(const vector<int>& preOrder, int lp, int hp, const vector<int>& inOrder, int li, int hi)
{
  if(lp > hp || li > hi)return nullptr;
  auto root = new Node(preOrder[lp]);
  int len = hp - lp + 1;
  if(len == 1)return root;
  int index = findIndex(inOrder, li, hi, preOrder[lp]);
  int leftLen = index - li;
  if(leftLen > 0) {
    root->left = build(preOrder, lp+1, lp+leftLen, inOrder, li, index-1);
  }
  int rightLen = len - leftLen - 1;
  if(rightLen > 0) {
    root->right = build(preOrder, lp+leftLen+1, hp, inOrder, index+1, hi);
  }
  return root;
}

Bst::Bst(const vector<int>& preOrder, const vector<int>& inOrder)
{
  int n = preOrder.size();
  root = build(preOrder, 0, n-1, inOrder, 0, n-1);
}

//destory with level iterator
Bst::~Bst()
{
  queue<Node*> que;
  if(root != nullptr) {
    que.push(root);
  }
  cout << "*************destory************************\n";
  while(!que.empty()) {
    auto fr = que.front();
    que.pop();
    cout << fr->value << "\t";
    if(fr->left != nullptr)que.push(fr->left);
    if(fr->right != nullptr)que.push(fr->right);
    delete fr;
  }
  cout << endl;
}

int main(int argc, char *argv[])
{
  //vector<int> pre = {7,3,15,9,20};
  //vector<int> in = {3,7,9,15,20};
  vector<int> pre = {8,3,1,6,4,7,10,14,13};
  vector<int> in = {1,3,4,6,7,8,10,13,14};
  Bst tree(pre,in);
  tree.printPreOrder();
  tree.printPreOrderStack();
  tree.printInOrder();
  tree.printInOrderStack();
  tree.printPostOrder();
  tree.printPostOrderStack();
  return 0;
}
