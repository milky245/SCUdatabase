/**
 * LRU implementation
 */
#include "buffer/lru_replacer.h"
#include "page/page.h"

namespace scudb {

template <typename T> LRUReplacer<T>::LRUReplacer():Size(0) 
{
	Head = new node();
	Tail = Head;
}

template <typename T> LRUReplacer<T>::~LRUReplacer() = default;


/*
 * Insert value into LRU
 */
template <typename T> void LRUReplacer<T>::Insert(const T &value)
{
    std::lock_guard<std::mutex> lock(Mutex);
    auto it = Table.find(value);
    if (it == Table.end()) 
    {
        Tail->next = new node(value, Tail);
        Tail = Tail->next;
        Table.emplace(value, Tail);
        ++Size;
    }
    else 
    {
        if (it->second != Tail) 
        {
            node* pre = it->second->pre;
            node* cur = pre->next;
            pre->next = std::move(cur->next);
            pre->next->pre = pre;
            cur->pre = Tail;
            Tail->next = std::move(cur);
            Tail = Tail->next;
        }
    }
}
/* If LRU is non-empty, pop the head member from LRU to argument "value", and
 * return true. If LRU is empty, return false
 */
template <typename T> bool LRUReplacer<T>::Victim(T &value) 
{
    std::lock_guard<std::mutex> lock(Mutex);
    if (Size == 0) 
    {
        return false;
    }
    value = Head->next->data;
    Head->next = Head->next->next;
    if (Head->next != nullptr)
    {
        Head->next->pre = Head;
    }
    Table.erase(value);
    if (--Size == 0) 
    {
        Tail = Head;
    }
    return true;
}
/*
 * Remove value from LRU. If removal is successful, return true, otherwise
 * return false
 */
template <typename T> bool LRUReplacer<T>::Erase(const T &value) {
    std::lock_guard<std::mutex> lock(Mutex);
    auto it = Table.find(value);
    if (it != Table.end()) 
    {
        if (it->second != Tail) 
        {
            node* pre = it->second->pre;
            node* cur = pre->next;
            pre->next = std::move(cur->next);
            pre->next->pre = pre;
        }
        else 
        {
            Tail = Tail->pre;
            delete Tail->next;
        }
        Table.erase(value);
        if (--Size == 0) 
        {
            Tail = Head;
        }
        return true;
    }

    return false;
}

template <typename T> size_t LRUReplacer<T>::Size() 
{
    std::lock_guard<std::mutex> lock(Mutex);
    return Size;
}

template class LRUReplacer<Page *>;
// test only
template class LRUReplacer<int>;

} // namespace scudb
