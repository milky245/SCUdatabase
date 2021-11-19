/**
 * lru_replacer.h
 *
 * Functionality: The buffer pool manager must maintain a LRU list to collect
 * all the pages that are unpinned and ready to be swapped. The simplest way to
 * implement LRU is a FIFO queue, but remember to dequeue or enqueue pages when
 * a page changes from unpinned to pinned, or vice-versa.
 */

#pragma once

#include "buffer/replacer.h"
#include "hash/extendible_hash.h"
#include <unordered_map>
#include <mutex>
#include <memory>

namespace scudb {
	
template <typename T> class LRUReplacer : public Replacer<T> {
	struct node
	{
		T data;
		node* pre = nullptr;
		node* next = nullptr;
		node() = default;
		explicit node(T d, node* p = nullptr) :data(d), pre(p) {};
	};
public:
  // do not change public interface
  LRUReplacer();

  ~LRUReplacer();

  void Insert(const T &value);

  bool Victim(T &value);

  bool Erase(const T &value);

  size_t Size();

private:
  // add your member variables here
	mutable std::mutex Mutex;
	size_t Size;
	std::unordered_map<T, node*> lruMap;
	node* Head;
	node* Tail;
};

} // namespace scudb
