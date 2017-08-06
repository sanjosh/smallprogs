#include <iostream>
#include <vector>
#include <functional>


class BufferedFunctionCaller
{
  // queue of bound functions 
  std::vector<std::function<void()>> tasks;

  public:
    template<class F, class... Args>
    void defer(F f, Args&&... args) {
      // TODO if queue empty, arm timer
        tasks.push_back(std::bind(f, std::forward<Args>(args)...));
        // call all the funcs in queue
        if (tasks.size() == 10) {
          flush();
        }
    }

    void flush() {
      for (auto& elem : tasks) {
        elem();
      }
      tasks.clear();
    }
};

void f1(int a, int b) {
  std::cout << a << "," << b << std::endl;
}

void f2(int a, int b, int c) {
  std::cout << a << "," << b << "," << c << std::endl;
}

int main()
{
    BufferedFunctionCaller c;

    for (int i = 0; i < 100; i++) {
      c.defer(f1, i, i + 10);
    }

    for (int i = 0; i < 100; i++) {
      c.defer(f2, i, i + 10, i + 20);
    }

    c.flush();
}
