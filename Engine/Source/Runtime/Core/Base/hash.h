#pragma once
#include<cstddef>
#include<functional>

template<typename T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    seed ^= std::hash<T> {}(v)+0x9e3779b9 + (seed << 6) + (seed >> 2);
    //0x9e3779b9==2654435769≈2^32*(√5-1)/2 (2的32次方乘以黄金分割率)
    //加个0x9e3779b9只是为了让得到的哈希值更均匀地散列到[0,2^32]的范围
    //(seed << 6) + (seed >> 2)只是在洗牌,减小冲突概率
}

template<typename T, typename... Ts>
inline void hash_combine(std::size_t& seed, const T& v, Ts... rest)
{
    hash_combine(seed, v);
    if constexpr (sizeof...(Ts) > 1)
    {
        hash_combine(seed, rest...);
    }
}
