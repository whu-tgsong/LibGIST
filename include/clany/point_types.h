#ifndef CLANY_POINT_TYPES_HPP
#define CLANY_POINT_TYPES_HPP

#include <vector>
#include <iterator>
#include <iostream>
#include <memory>
#include "clany_macros.h"

_CLANY_BEGIN
#define  CLANY_ADD_RGB \
union \
{ \
    struct \
    { \
        uchar b; \
        uchar g; \
        uchar r; \
    }; \
    uchar rgb[3]; \
}; \


#define CLANY_ADD_POINT3D \
union \
{ \
    T data[3]; \
    struct \
    { \
        T x; \
        T y; \
        T z; \
    }; \
}; \


#define CLANY_ADD_NORMAL3D \
union \
{ \
    T data_n[3]; \
    T normal[3]; \
    struct \
    { \
        T normal_x; \
        T normal_y; \
        T normal_z; \
    }; \
}; \


struct PixelRGB
{
    CLANY_ADD_RGB;

    PixelRGB() : b(0), g(0), r(0) {}

    PixelRGB(uchar r_, uchar g_, uchar b_) : b(b_), g(g_), r(r_) {}
};


template<typename T>
struct Point3D
{
    CLANY_ADD_POINT3D;

    Point3D() : x(0), y(0), z(0) {}

    Point3D(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
};
using Point3f = Point3D<float>;
using Point3d = Point3D<double>;


template<typename T>
struct Normal
{
    CLANY_ADD_NORMAL3D;

    Normal() : normal_x(0), normal_y(0), normal_z(0) {}

    Normal(T n_x, T n_y, T n_z) : normal_x(n_x), normal_y(n_y), normal_z(n_z) {}
};
using Normal3f = Normal<float>;
using Normal3d = Normal<double>;


template<typename T>
struct PointNormal
{
    CLANY_ADD_POINT3D;
    CLANY_ADD_NORMAL3D;

    PointNormal() : x(0), y(0), z(0), normal_x(0), normal_y(0), normal_z(0) {}

    PointNormal(T x_, T y_, T z_, T n_x, T n_y, T n_z)
        : x(x_), y(y_), z(z_), normal_x(n_x), normal_y(n_y), normal_z(n_z) {}
};
using Point3fNormal = PointNormal<float>;
using Point3dNormal = PointNormal<double>;


template<typename T>
struct PointRGB
{
    CLANY_ADD_POINT3D;
    CLANY_ADD_RGB;

    inline PointRGB() : x(0), y(0), z(0), b(0), g(0), r(0) {}

    inline PointRGB(T x_, T y_, T z_, uchar r_, uchar g_, uchar b_)
        : x(x_), y(y_), z(z_), b(b_), g(g_), r(r_) {}
};
using Point3fRGB = PointRGB<float>;
using Point3dRGB = PointRGB<double>;


inline std::ostream& operator<<(std::ostream& os, const PixelRGB& p)
{
    os << p.r << " " << p.g << " " << p.b;
    return (os);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Point3D<T>& p)
{
    os << p.x << " " << p.y << " " << p.z;
    return (os);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Normal<T>& p)
{
    os << p.normal_x << " " << p.normal_y << " " << p.normal_z;
    return (os);
}


template<typename PointT>
class PointCloud
{
public:
    typedef PointT PointType;
    typedef vector<PointCloud<PointT>> CloudVectorType;
    typedef shared_ptr<PointCloud<PointT>> Ptr;
    typedef shared_ptr<const PointCloud<PointT>> ConstPtr;

    typedef typename vector<PointT>::iterator iterator;
    typedef typename vector<PointT>::const_iterator const_iterator;

    PointCloud() : points(), width(0), height(0) {}

    PointCloud(int width_, int height_ = 1, const PointT& value_ = PointT())
        : points(width_*height_, value_), width(width_), height(height_)
    {}

    PointCloud& operator+=(const PointCloud& rhs)
    {
        size_t old_size = this->size();
        size_t new_size = old_size + rhs.size();
        points.resize(new_size);
        copy(rhs.begin(), rhs.end(), this->begin() + old_size);

        width = new_size;
        height = 1;

        return (*this);
    }

    PointCloud operator+(const PointCloud& rhs)
    {
        return (PointCloud<PointT>(*this) += rhs);
    }

    iterator begin() { return (points.begin()); }
    iterator end()   { return (points.end()); }
    const_iterator begin() const { return (points.begin()); }
    const_iterator end() const   { return (points.end()); }

    inline size_t size() const { return (points.size()); }
    inline void reserve(size_t n) { points.reserve(n); }
    inline bool empty() const { return points.empty(); }
    inline void resize(size_t n)
    {
        points.resize(n);
        if (width * height != n) {
            width = n;
            height = 1;
        }
    }

    const PointT& operator[] (size_t n) const { return (points[n]); }
    PointT& operator[] (size_t n) { return (points[n]); }
    const PointT& at(size_t n) const { return (points.at(n)); }
    PointT& at(size_t n) { return (points.at(n)); }
    const PointT& front() const { return (points.front()); }
    PointT& front() { return (points.front()); }
    const PointT& back() const { return (points.back()); }
    PointT& back() { return (points.back()); }

    void push_back(const PointT& pt) { points.push_back(pt); }
    void pop_back() { points.pop_back(); }

    void swap(PointCloud<PointT>& rhs)
    {
        this->points.swap(rhs.points);
        std::swap(width, rhs.width);
        std::swap(height, rhs.height);
    }

    void clear()
    {
        points.clear();
        width = height = 0;
    }

public:
    vector<PointT> points;

    int width;
    int height;
};
_CLANY_END

#endif
