/*
 * extendible_hash.h : implementation of in-memory hash table using extendible
 * hashing
 *
 * Functionality: The buffer pool manager must maintain a page table to be able
 * to quickly map a PageId to its corresponding memory location; or alternately
 * report that the PageId does not match any currently-buffered page.
 */

#pragma once

#include <cstdlib>
#include <vector>
#include <string>
#include <mutex>
#include <map>
#include <memory>
#include <iostream>

#include "hash/hash_table.h"

namespace scudb {

template <typename K, typename V>
class ExtendibleHash : public HashTable<K, V> 
{
	class Bucket
	{
		size_t mSize{};
		int depth;
	public:
		std::map<K, V> vals;
		explicit Bucket(size_t s, int d) :st_mSize(s), depth(d) {};
		bool b_find(K key);
		bool b_remove(K key);
		bool b_insert(K key, V value);
		int getDepth();
		bool isFull();
		bool isEmpty();
	};
	using Buckets = std::vector<std::shared_ptr<Bucket>>;
public:
  // constructor
  ExtendibleHash(size_t size);
  // helper function to generate hash addressing
  size_t HashKey(const K &key);
  // helper function to get global & local depth
  int GetGlobalDepth() const;
  int GetLocalDepth(int bucket_id) const;
  int GetNumBuckets() const;
  // lookup and modifier
  V GetV(const K& key) override;
  int getSize();
  bool Find(const K &key, V &value) override;
  bool Remove(const K &key) override;
  void Insert(const K &key, const V &value) override;

private:
  // add your own member variables here
	int globalDepth;
	size_t BucketSize;
	size_t size{};
	std::recursive_mutex mutex;
	Buckets exHashTable;
	void increase();
	int getHashIndex(const K& key) const;
	void split(const std::shared_ptr<Bucket>& tarBucket);
};
} // namespace scudb
