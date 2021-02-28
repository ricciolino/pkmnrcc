#ifndef TUPLE2_H
#define TUPLE2_H

template <typename T>
class Tuple2 {
    public:
        T x;
        T y;
        Tuple2() { }
        Tuple2(const T& _x, const T& _y) : x(_x), y(_y) { }
       
};

#endif
