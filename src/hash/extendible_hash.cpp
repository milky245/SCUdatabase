#include <list>

#include "hash/extendible_hash.h"
#include "page/page.h"

namespace scudb {

	template <typename K, typename V> 
	bool ExtendibleHash<K, V>::Bucket::b_find(K key)
	{
		return vals.find(key) != vals.end();
	}
	template <typename K, typename V>
	bool ExtendibleHash<K, V>::Bucket::b_remove(K key)
	{
		if (this->b_find(key))
		{
			vals.erase(key);
			return true;
		}
		else
		{
			return false;
		}
	}
	template <typename K, typename V>
	bool ExtendibleHash<K, V>::Bucket::b_insert(K key,V value)
	{
		if (isFull())
		{
			return false;
		}
		else
		{
			vals[key] = value;
			return true;
		}
	}
	template <typename K, typename V>
	bool ExtendibleHash<K, V>::Bucket::find(K key)
	{
		return vals.find(key) != vals.end();
	}
	template <typename K, typename V>
	bool ExtendibleHash<K, V>::Bucket::isFull()
	{
		return vals.size() == mSize;
	}
	template <typename K, typename V>
	bool ExtendibleHash<K, V>::Bucket::isEmpty()
	{
		return vals.size() == 0;
	}
	template <typename K, typename V>
	bool ExtendibleHash<K, V>::Bucket::getDepth()
	{
		return depth;
	}

/*
 * constructor
 * array_size: fixed array size for each bucket
 */
template <typename K, typename V>
ExtendibleHash<K, V>::ExtendibleHash(size_t size) :globalDepth(1), BucketSize{Size}
{
	for (int i = 0; i < 1 << globalDepth; i++)
	{
		exHashTable.push_back(std::make_shared<Bucket>(1, BucketSize));
	}
}

/*
 * helper function to calculate the hashing address of input key
 */
template <typename K, typename V>
size_t ExtendibleHash<K, V>::HashKey(const K &key) {
	return std::hash<K>{}(key);
}

/*
 * helper function to return global depth of hash table
 * NOTE: you must implement this function in order to pass test
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::GetGlobalDepth() const {
	return globalDepth;
}

/*
 * helper function to return local depth of one specific bucket
 * NOTE: you must implement this function in order to pass test
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::GetLocalDepth(int bucket_id) const {
	return exHashTable[bucket_id]->getDepth();
}

/*
 * helper function to return current number of bucket in hash table
 */
template <typename K, typename V>
int ExtendibleHash<K, V>::GetNumBuckets() const {
	return 1 << globalDepth;
}

template <typename K, typename V>
int ExtendibleHash<K, V>::getHashIndex(const K& key) const 
{
	return HashKey(key) & ((1 << globalDepth) - 1);
}
template <typename K, typename V>
V ExtendibleHash<K, V>::GetV(const K& key)
{
	std::lock_guard<std::recursive_mutex> guard(mutex);
	V val;
	Find(key, val);
	return val;
}
template <typename K, typename V> 
int ExtendibleHash<K, V>::getSize()
{
	return size;
}
template <typename K, typename V>
void ExtendibleHash<K, V>::increase() 
{
	for (int i = 0; i < 1 << globalDepth; i++) {
		exHashTable.push_back(exHashTable[i]);
	}
	globalDepth++;
}
/*
 * lookup function to find value associate with input key
 */
template <typename K, typename V>
bool ExtendibleHash<K, V>::Find(const K &key, V &value) {
	std::lock_guard<std::recursive_mutex> guard(mutex);
	int index = getHashIndex(key);
	std::shared_ptr<Bucket> theBuck = exHashTable[index];
	if (theBuck->vals.find(key) != theBuck->vals.end())
	{
		value = theBuck->vals[key];
		return true;
	}
	return false;
}

/*
 * delete <key,value> entry in hash table
 * Shrink & Combination is not required for this project
 */
template <typename K, typename V>
bool ExtendibleHash<K, V>::Remove(const K &key) {
	std::lock_guard<std::recursive_mutex> guard(mutex);
	int index = getHashIndex(key);
	if (exHashTable[index]->b_remove(key)) 
	{
		size--;
		return true;
	}
	return false;
}

/*
 * insert <key,value> entry in hash table
 * Split & Redistribute bucket when there is overflow and if necessary increase
 * global depth
 */
template <typename K, typename V>
void ExtendibleHash<K, V>::Insert(const K &key, const V &value)
{
	std::lock_guard<std::recursive_mutex> guard(mutex);
	int index = getHashIndex(key);
	auto targetBucket = exHashTable[index];
	if (targetBucket->isFull()) 
	{
		split(targetBucket);
		Insert(key, value);
	}
	else 
	{
		targetBucket->b_insert(key, value);
		size++;
	}
}
template <typename K, typename V>
void ExtendibleHash<K, V>::split(const std::shared_ptr<Bucket>& targetBucket) {

	int oldIndex = targetBucket->getDepth();
	if (oldIndex == globalDepth) 
	{
		increase();
	}
	int maskIndex = 1 << oldIndex;
	auto firstBucket = std::make_shared<Bucket>(oldIndex + 1, BucketSize);
	auto secondBucket = std::make_shared<Bucket>(oldIndex + 1, BucketSize);
	
	for (const auto& item : targetBucket->vals)
	{
		size_t newIndex = getHashIndex(item.first);
		if (newIndex & maskIndex)
		{
			firstBucket->vals.insert(item);
		}
		else 
		{
			secondBucket->vals.insert(item);
		}
	}
	for (size_t i = 0; i < exHashTable.size(); i++) 
	{
		if (exHashTable[i] == targetBucket) 
		{
			if (i & maskIndex) 
			{
				exHashTable[i] = firstBucket;
			}
			else 
			{
				exHashTable[i] = secondBucket;
			}
		}
	}
}
template class ExtendibleHash<page_id_t, Page *>;
template class ExtendibleHash<Page *, std::list<Page *>::iterator>;
// test purpose
template class ExtendibleHash<int, std::string>;
template class ExtendibleHash<int, std::list<int>::iterator>;
template class ExtendibleHash<int, int>;
} // namespace scudb
