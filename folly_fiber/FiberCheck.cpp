/**
 * Test if coroutine (fiber) api works
 */
#include <folly/fibers/FiberManager.h>
#include <folly/fibers/SimpleLoopController.h>
#include <iostream>


using namespace folly::fibers;

static constexpr size_t MAX = 1000;
static int i = 0;
static int j = 0;

void fiberFunc()
{
  assert (onFiber()); // running as coroutine

  i++;

  // unconditional yield of a fiber
  folly::fibers::yield();

  // conditional yield 
  // fiber get switched out until setValue is called
  auto result = folly::fibers::await(
    [&] (Promise<int> p) {
      j ++;
      p.setValue(j); // this value gets returned by await
    });
}

int main()
{
  FiberManager fiberManager(folly::make_unique<SimpleLoopController>());

  for (int k = 0; k < MAX; k++) {
    fiberManager.addTask(fiberFunc);
  }

  auto& loopController = dynamic_cast<SimpleLoopController&>(fiberManager.loopController());

  loopController.loop([&]() { 
    if (j == MAX) {
      loopController.stop(); 
      std::cout << "final value=" << i << "," << j << std::endl;
    } else {
      std::cout << "intermediate value=" << i << "," << j << std::endl;
    }
  });

  assert(fiberManager.runQueueSize() == 0);
  assert(fiberManager.hasTasks() == false);
  assert(fiberManager.fibersAllocated() == fiberManager.fibersPoolSize());
  assert(fiberManager.hasActiveFiber() == false);

  assert(i == MAX);
  assert(j == MAX);
}
