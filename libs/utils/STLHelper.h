/**
 *  
 *
 *  @author xujun
 *  @since  2012-8-1
 */
#ifndef _STLHelper_2012_8_1_h__
#define _STLHelper_2012_8_1_h__

#include <map>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

namespace utils
{
    template <typename Key, typename Value>
    Value getMapValue(const map<Key, Value>& m, const Key& key, const Value& defautV = Value())
    {
        typename map<Key, Value>::const_iterator iter = m.find(key);
        if (iter != m.end())
        {
            return iter->second;
        }
        return defautV;
    }

    template <typename Key, typename Value>
    Value getMapValue(const std::unordered_map<Key, Value>& m, const Key& key, const Value& defautV = Value())
    {
        typename std::unordered_map<Key, Value>::const_iterator iter = m.find(key);
        if (iter != m.end())
        {
            return iter->second;
        }
        return defautV;
    }

    template <typename Key, typename Value>
    Value& getMapValueRef(map<Key, Value>& m, const Key& key)
    {
        typename map<Key, Value>::iterator iter = m.find(key);
        if (iter != m.end())
        {
            return iter->second;
        } else {
            static Value d;
            return d;
        }
    }

    template <typename Key, typename Value>
    Value& getMapValueRef(std::unordered_map<Key, Value>& m, const Key& key)
    {
        typename std::unordered_map<Key, Value>::iterator iter = m.find(key);
        if (iter != m.end())
        {
            return iter->second;
        }
        else {
            static Value d;
            return d;
        }
    }

    template <typename Key, typename Value>
    const Value& getMapValueConstRef(const map<Key, Value>& m, const Key& key)
    {
        typename map<Key, Value>::const_iterator iter = m.find(key);
        if (iter != m.end())
        {
            return iter->second;
        }
        else {
            static Value d;
            return d;
        }
    }

    template <typename Key, typename Value>
    const Value& getMapValueConstRef(const std::unordered_map<Key, Value>& m, const Key& key)
    {
        typename std::unordered_map<Key, Value>::const_iterator iter = m.find(key);
        if (iter != m.end())
        {
            return iter->second;
        }
        else {
            static Value d;
            return d;
        }
    }

    template <typename Key, typename Value>
    bool remove(map<Key, Value>& m, const Key& key)
    {
        typename map<Key, Value>::iterator iter = m.find(key);
        if (iter != m.end())
        {
            m.erase(iter);
            return true;
        } else {
            return false;
        }
    }

    template <typename Key, typename Value>
    bool remove(std::unordered_map<Key, Value>& m, const Key& key)
    {
        typename std::unordered_map<Key, Value>::iterator iter = m.find(key);
        if (iter != m.end())
        {
            m.erase(iter);
            return true;
        }
        else {
            return false;
        }
    }

    template <typename T>
    bool remove(std::set<T>& m, const T& key)
    {
        typename set<T>::iterator iter = m.find(key);
        if (iter != m.end())
        {
            m.erase(iter);
            return true;
        } else {
            return false;
        }
    }

    template <typename T>
    bool remove(vector<T>& m, const T& key)
    {
        bool removed = false;
        for (typename vector<T>::iterator iter = m.begin(); iter != m.end(); )
        {
            if (*iter == key)
            {
                iter = m.erase(iter);
                removed = true;
            }
            else
            {
                ++iter;
            }
        }
        return removed;        
    }

    template <typename T>
    bool remove(list<T>& m, const T& key)
    {
        bool removed = false;
        for (typename list<T>::iterator iter = m.begin(); iter != m.end(); )
        {
            if (*iter == key)
            {
                iter = m.erase(iter);
                removed = true;
            }
            else
            {
                ++iter;
            }
        }
        return removed;
    }

    template <typename T>
    bool removeOne(list<T>& m, const T& key)
    {
        typename list<T>::iterator iter = find(m.begin(), m.end(), key);
        if (iter != m.end())
        {
            m.erase(iter);
            return true;
        } else {
            return false;
        }
    }

    template <typename T>
    bool removeOne(vector<T>& m, const T& key)
    {
        typename vector<T>::iterator iter = find(m.begin(), m.end(), key);
        if (iter != m.end())
        {
            m.erase(iter);
            return true;
        } else {
            return false;
        }
    }

    template <typename T>
    bool contain(const set<T>& m, const T& key)
    {
        typename set<T>::const_iterator iter = m.find(key);
        return iter != m.end();
    }

    template <typename T>
    bool contain(const vector<T>& m, const T& key)
    {
        typename vector<T>::const_iterator iter = std::find(m.begin(), m.end(), key);
        return iter != m.end();
    }

    template <typename T>
    bool contain(const list<T>& m, const T& key)
    {
        typename list<T>::const_iterator iter = std::find(m.begin(), m.end(), key);
        return iter != m.end();
    }

    template <typename Key, typename Value>
    bool contain(const map<Key, Value>& m, const Key& key)
    {
        typename map<Key, Value>::const_iterator iter = m.find(key);
        return iter != m.end();
    }

    template <typename Key, typename Value>
    bool contain(const std::unordered_map<Key, Value>& m, const Key& key)
    {
        typename std::unordered_map<Key, Value>::const_iterator iter = m.find(key);
        return iter != m.end();
    }

    template <typename Key, typename Value>
    vector<Key> keys(const map<Key, Value>& m)
    {
        vector<Key> ret;
        if (!m.empty())
        {
            ret.reserve(m.size());
            for (typename map<Key, Value>::const_iterator iter = m.begin(); iter != m.end(); ++iter)
            {
                ret.push_back(iter->first);
            }
        }
        return ret;
    }

    template <typename Key, typename Value>
    vector<Key> keys(const std::unordered_map<Key, Value>& m)
    {
        vector<Key> ret;
        if (!m.empty())
        {
            ret.reserve(m.size());
            for (typename std::unordered_map<Key, Value>::const_iterator iter = m.begin(); iter != m.end(); ++iter)
            {
                ret.push_back(iter->first);
            }
        }
        return ret;
    }

    template <typename Key, typename Value>
    vector<Value> values(const map<Key, Value>& m)
    {
        vector<Value> ret;
        if (!m.empty())
        {
            ret.reserve(m.size());
            for (typename map<Key, Value>::const_iterator iter = m.begin(); iter != m.end(); ++iter)
            {
                ret.push_back(iter->second);
            }
        }
        return ret;
    }

    template <typename Key, typename Value>
    vector<Value> values(const std::unordered_map<Key, Value>& m)
    {
        vector<Value> ret;
        if (!m.empty())
        {
            ret.reserve(m.size());
            for (typename std::unordered_map<Key, Value>::const_iterator iter = m.begin(); iter != m.end(); ++iter)
            {
                ret.push_back(iter->second);
            }
        }
        return ret;
    }

    template <typename Key, typename Value>
    vector<Value> values(const multimap<Key, Value>& m)
    {
        vector<Value> ret;
        if (!m.empty())
        {
            ret.reserve(m.size());
            for (typename multimap<Key, Value>::const_iterator iter = m.begin(); iter != m.end(); ++iter)
            {
                ret.push_back(iter->second);
            }
        }
        return ret;
    }

    template< class CurElement>
    inline static void ExcludeDuplicates(vector< CurElement >& val)
    {
        set< CurElement > tempSet;
        sort(val.begin(), val.end());
        tempSet.insert(val.begin(), val.end());
        val.resize(tempSet.size());
        int i = 0;
        for (typename set< CurElement >::iterator iter = tempSet.begin(); iter != tempSet.end(); ++iter)
        {
            val[i] = *iter;
            ++i;
        }
        tempSet.clear();
    }


    template <typename Key, typename Value>
    void replace(std::map<Key, Value>& m, const Key& key, const Value& value)
    {
        std::pair<typename std::map<Key, Value>::iterator, bool> iret = m.insert(make_pair(key, value));
        if (!iret.second)
        {
            iret.first->second = value;
        }
    }


    template <typename Key, typename Value>
    void replacePtr(std::map<Key, std::shared_ptr<Value> >& m, const Key& key, const Value& value)
    {
        std::shared_ptr<Value> ptrValue = utils::getMapValue(m, key);
        if (NULL != ptrValue)
        {
            *ptrValue = value;
        } else {
            replace(m, key, std::shared_ptr<Value>(new Value(value)));
        }
    }

    template <typename Key, typename Value>
    bool tryReplace(map<Key, Value>& m, const Key& key, const Value& value)
    {
        pair<typename map<Key, Value>::iterator, bool> ret = m.insert(make_pair(key, value));
        return ret.second;
    }

    template <typename Key, typename Base, typename Extend>
    void dynamic_pointer_cast(const map<Key, std::shared_ptr<Base> >& raw, map<Key, std::shared_ptr<Extend> >& ret)
    {
        for (typename map<Key, std::shared_ptr<Base> >::const_iterator iter = raw.begin(); iter != raw.end(); ++iter)
        {
            if (NULL != iter->second)
            {
                ret.insert(make_pair(iter->first, std::dynamic_pointer_cast<Extend>(iter->second)));
            }
        }
    }

    template <typename Key, typename Value>
    void compareMap(const map<Key, Value>& rawMap, const map<Key, Value>& newMap, vector<Key>& added, vector<Key>& removed, vector<Key>& changed)
    {
        added.reserve(newMap.size());
        removed.reserve(rawMap.size());
        changed.reserve(rawMap.size());

        typename map<Key, Value>::const_iterator rawIter = rawMap.begin();
        typename map<Key, Value>::const_iterator newIter = newMap.begin();
        while (rawIter != rawMap.end() && newIter != newMap.end())
        {
            if (rawIter->first == newIter->first)
            {
                if (rawIter->second != newIter->second)
                {
                    changed.push_back(rawIter->first);
                }

                ++rawIter;
                ++newIter;
            }
            else if (rawIter->first > newIter->first)
            {
                added.push_back(newIter->first);
                ++newIter;
            }
            else
            {
                removed.push_back(rawIter->first);
                ++rawIter;
            }           
        }

        for (; rawIter != rawMap.end(); ++rawIter)
        {
            removed.push_back(rawIter->first);
        }

        for (; newIter != newMap.end(); ++newIter)
        {
            added.push_back(newIter->first);
        }
    }

    //template <typename Base, typename Extend>
    //vector<std::shared_ptr<Extend> > dynamic_pointer_cast(const vector<std::shared_ptr<Base> >& raw)
    //{
    //    vector<std::shared_ptr<Extend> > ret(raw.size());
    //    for (size_t i = 0; i < raw.size(); ++i)
    //    {
    //        ret[i] = std::dynamic_pointer_cast<Extend>(raw[i]);
    //    }
    //    return ret;
    //}


}

#endif // STLHelper_h__