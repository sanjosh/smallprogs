#pragma once

/**
 * http://stackoverflow.com/questions/12413034/shared-map-with-boostinterprocess
 */

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <functional>
#include <utility>

template <class K, class V>
class ShmemMap
{
  typedef K    KeyType;
  typedef V    MappedType;
  typedef std::pair<const KeyType, MappedType> ValueType;
  typedef boost::interprocess::managed_shared_memory BSM;

  typedef boost::interprocess::allocator<ValueType, BSM::segment_manager> ShmemAllocator;

  typedef boost::interprocess::map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MySHMMap;

  public:

  ShmemMap(const std::string& name);
  ShmemMap(const std::string& name, bool create);
  ~ShmemMap();

  void insert(const K& k, const V& v);
  void update(const K& k, const V& v);
  int find(const K& k, V& v);

  private:
  BSM segment_;
  ShmemAllocator allocator_;
  boost::interprocess::offset_ptr<MySHMMap> map_;
  bool wasCreator_ = false;
  const std::string name_;
};


template <class K, class V>
ShmemMap<K, V>::ShmemMap(const std::string& name, bool create)
  : segment_(boost::interprocess::create_only, name.c_str(), 65536)
  , allocator_(segment_.get_segment_manager())
  , name_(name)
  , wasCreator_(true)
{
  map_ = segment_.construct<MySHMMap>(name.c_str())(std::less<K>(), allocator_);
}

template <class K, class V>
ShmemMap<K, V>::ShmemMap(const std::string& name)
  : segment_(boost::interprocess::open_only, name.c_str())
  , allocator_(segment_.get_segment_manager())
  , name_(name)
{
  map_ = segment_.find<MySHMMap>(name).first;
}

template <class K, class V>
ShmemMap<K, V>::~ShmemMap()
{
  if (wasCreator_) {
    boost::interprocess::shared_memory_object::remove(name_.c_str());
  }
}

template <class K, class V>
void ShmemMap<K, V>::insert(const K& k, const V& v)
{
  map_->insert(std::pair<K, V>(k, v));
}

template <class K, class V>
void ShmemMap<K, V>::update(const K& k, const V& v)
{
  auto iter = map_->find();
  iter->second = v;
}

template <class K, class V>
int ShmemMap<K, V>::find(const K& k, V& v)
{
  auto iter = map_->find(k);
  v = iter->second;
  return 0;
}

