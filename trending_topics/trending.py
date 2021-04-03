#!/usr/bin/python
from collections import deque, defaultdict

class TrendingTopics():

    def __init__(self):
        self._queue =deque()  # of last N elements
        self._key_dict = dict()  # Map : key -> count
        self._count_dict = defaultdict(list)   # Map : count -> list of keys

    def on_new_item(self, new_item):
        if new_item in self._key_dict:
            print('increment ', new_item)
            old_count = self._key_dict[new_item]
            # increment item count
            self._key_dict[new_item] = old_count + 1
            # move to next count bucket
            self._count_dict[old_count].remove(new_item)
            self._count_dict[old_count + 1].append(new_item)
        else:
            print('inserting ', new_item)
            self._key_dict[new_item] = 1
            self._count_dict[1].append(new_item)
        self._queue.append(new_item)

        if len(self._queue) > 5:
            lastk = self._queue.popleft()
            old_count = self._key_dict[lastk]
            print('removing ', lastk, old_count)
            self._count_dict[old_count].remove(lastk)
            if old_count == 1:
                del self._key_dict[lastk]
            else:
                self._key_dict[lastk] = old_count - 1
                self._count_dict[old_count - 1].append(lastk)

    def get_top_k(self):
        print(self._count_dict)
        print(self._key_dict)
        print(self._queue)

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    t = TrendingTopics()
    for item in [1, 2, 1, 3, 1, 4, 1, 5]:
        t.on_new_item('item' + str(item))
    t.get_top_k()
