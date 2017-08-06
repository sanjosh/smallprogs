//
// See stroustrup article on Wrappers
//
#include <iostream>
#include <type_traits>
#include <string.h>

typedef int (*FileTranslatorFunc)(const char* old_name, size_t old_length, char* new_name);

template <typename F>
struct Wrapper {

  F f;

  template <typename... T>
  auto operator()(T&&... args) -> typename std::result_of<F(T...)>::type 
  {
    std::cout << "calling f with " << sizeof...(args) << " arguments.\n";
    return f(std::forward<T>(args)...);
  }
};

template <typename F>
Wrapper<F> wrap(F&& f) 
{
  return {std::forward<F>(f)};
}

int myfunc(const char* old, size_t len, char* newname)
{
  strncpy(newname, old, len);
  return 3;
}

struct ABC
{
  typedef Wrapper<FileTranslatorFunc> FuncWrapper;
  FuncWrapper mywrap;
};

int main() {
  ABC a;
  a.mywrap = wrap(&myfunc);
  //auto f = wrap(myfunc);

  char newname[10];
  newname[0] = '\0';
  std::cout << a.mywrap("abc", 3, newname) << std::endl;
  std::cout << newname << std::endl;

  return 0;
}


