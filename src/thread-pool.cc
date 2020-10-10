#include <iostream>
#include <thread>
#include <functional>
#include <vector>

using namespace std;
typedef std::function<void()> Task;

enum TaskStatus {
  INIT,
  RUNNING,
  FINISHED
};
class ThreadPool {
  bool start = true;
  volatile int curGet = 0;
  volatile int curPut = 0;
  volatile int curSz = 0;
  int poolSz;
  int queSz;
  Task* taskQue;
  vector<thread> pool;
  void run() {
    while(start) {
      while(curSz == 0){
        this_thread::yield();
      }
      Task t;
      {
        lock_guard lg;
        if(curSz == 0)continue;
        t = move(taskQue[curGet]);
        curGet = (curGet + 1) % queSz;
        --curSz;
      }
      t();
    }
  }
public:
  ThreadPool(int queSz, int threadSz): poolSz(threadSz), queSz(queSz) {
    taskQue = new Task[queSz];
  }
  void start() {
    for(int i = 0; i < poolSz; ++i) {
      pool.push_back(thread(run()));
    }
  }
  bool put(Task&& t) {
    if(curSz == queSz)return false;
    {
      lock_guard lg;
      if(curSz == queSz)return false;
      taskQue[curPut] = move(t);
      curPut = (curPut + 1) % queSz;
      ++curSz;
    }
    return true;
  }
  ~Thread() {
    for(auto&& t: pool) {
      t.join();
    }
    delete[] taskQue;
  }
};
int main(int argc, char *argv[])
{
  return 0;
}
