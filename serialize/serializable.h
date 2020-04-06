#ifndef IWTBAM_SERIALIZABLE_H
#define IWTBAM_SERIALIZABLE_H

#include <string>
#include <sstream>
#include <type_traits>
#include <utility>

using std::string;
using std::stringstream;
using std::enable_if_t;
using std::is_scalar;
using std::is_void;
using std::move;

namespace iwtbam {
namespace serialize {

template<class T>
class Serializable {
public:
    virtual std::string serialize(T) = 0;
    virtual T deserialize(const std::string&) = 0;
};



template<class T, class = void>
class BaseSerializeUtil;

/*
    基础类型的序列化
*/

template<class T>
class BaseSerializeUtil<T, enable_if_t<is_scalar<T>::value>>:
     Serializable<T> {
public:
    std::string serialize(T data){
        stringstream ss;
        ss << data;
        return ss.str();
    }

    T deserialize(const std::string& raw_data){
        stringstream ss(raw_data);
        T data;
        ss >> data;
        return data;
    }
};


/*
    可迭代类型的顺序容器序列化
*/

template<class T>
class BaseSerializeUtil<T, enable_if_t<!is_void<typename T::iterator>::value>>:
    Serializable<T>{
public:

    using value_type = typename T::value_type;
    using iter_type  = typename T::iterator;
    std::string serialize(T data){
        stringstream ss;
        size_t size = data.size();
        ss << size;
        for(auto iter = data.begin(); iter != data.end(); iter++)
            ss << " " << (*iter);
        return ss.str();
    }

    T deserialize(const std::string& raw_data){
        stringstream ss(raw_data);
        size_t size;
        ss >> size;
        T data(size);
        for(auto iter = data.begin(); iter != data.end(); iter++)
            ss >> (*iter);
        return move(data);
    }
};

/*
    
*/

// template<class T>
// class BaseSerializeUtil : Serializable<T, U = std::enable_if_t<is_container_v<T>, T>> {
// public:
    

//     std::string serialize(U data){

//     }

//     U deserialize(const std::string& raw_data){

//     }
// };




//namesapce end
}
}

#endif