#pragma once

/**
 * This is an inefficient matrix library!
 * Consider using a different library!
 *
 * This library, while small, lacks most features
 * of a good matrix library. Additionally, some features
 * don't work for integer types.
 */

#include <initializer_list>
#include <iostream>
#include <utility>
#include <sstream>
#include <functional>
#include <math.h>

template<typename T, unsigned int width = 2, unsigned int height = 2>
class Matrix
{
public:
    T data[width * height];

    const unsigned int _width = width;
    const unsigned int _height = height;

    Matrix();
    Matrix(std::initializer_list<T> initialData);
    Matrix(const Matrix<T, width, height>& other);

    const Matrix<T, width, height>& operator=(const Matrix<T, width, height>& other);

    inline const T& getAt(unsigned int x, unsigned int y) const;
    inline void setAt(unsigned int x, unsigned int y, T);

    void multiplyRowByConstant(unsigned int y, T constant);
    void addConstantMultpileOfRow(unsigned int sourceRow, unsigned int destinationRow, T constantMultpilier);
    void swapRows(unsigned int y1, unsigned int y2);
    void operator*=(const Matrix<T, height, width>& other);

    bool invert();
    void toIdentity();
    void zero();

    void fill(std::function<T(unsigned int, unsigned int)>);
};

namespace MatrixControl
{
    template<typename T>
    Matrix<T, 2, 2> createRotationMatrix(T theta);

    template<typename T>
    void toRotationMatrix(T theta, Matrix<T, 2, 2>& mat);
}

template<typename T, unsigned int width, unsigned int height>
Matrix<T, height, height> operator*(const Matrix<T, width, height>& left, const Matrix<T, height, width>& right);

template<typename T, unsigned int width, unsigned int height>
std::ostream& operator<<(std::ostream& left, const Matrix<T, width, height>& right);

template<typename T, unsigned int width, unsigned int height>
bool operator==(const Matrix<T, width, height>&, const Matrix<T, width, height>&);

template<typename T>
std::pair<T, T> operator*(const std::pair<T, T>& left, const Matrix<T, 2, 2>& right);

// Implementation

template<typename T, unsigned int width, unsigned int height>
Matrix<T, height, height> operator*(const Matrix<T, width, height>& left, const Matrix<T, height, width>& right)
{
    Matrix<T, height, height> result;
    T currentSum = 0.0;
    unsigned int y1, x1, h;

    for (y1 = 0; y1 < left._height; y1++)
    {
        for (x1 = 0; x1 < right._width; x1++)
        {
            currentSum = 0.0;
            for (h = 0; h < left._width; h++)
            {
                currentSum += left.getAt(h, y1) * right.getAt(x1, h);
            }

            result.setAt(x1, y1, currentSum);
        }
    }

    return result;
}

template<typename T, unsigned int width, unsigned int height>
std::ostream& operator<<(std::ostream& output, const Matrix<T, width, height>& right)
{
    output << '[' << std::endl;

    std::string currentValue, otherValue;
    std::stringstream conversionStream;

    unsigned int x, y, y2;
    unsigned int endingSpaces = 0;

    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            conversionStream << right.getAt(x, y) << " ";
            conversionStream >> currentValue;

            output << currentValue;

            if(x < width - 1)
            {
                // Add appropriate spaces.
                endingSpaces = 1;
                output << " ";
                for(y2 = 0; y2 < height; y2++)
                {
                    conversionStream << right.getAt(x, y2) << " ";
                    conversionStream >> otherValue;

                    while(otherValue.size() + 1 > currentValue.size() + endingSpaces)
                    {
                        endingSpaces++;
                        output << " ";
                    }
                }
            }
        }
        output << std::endl;
    }

    output << ']';

    return output;
}

template<typename T, unsigned int w1, unsigned int h1, unsigned int w2, unsigned int h2>
bool operator==(const Matrix<T, w1, h1>& left, const Matrix<T, w2, h2>& right)
{
    if (left._width != right._width || left._height != right._height)
    {
        return false;
    }

    for (unsigned int x = 0; x < left._width; x++)
    {
        for (unsigned int y = 0; y < left._height; y++)
        {
            if (left.getAt(x, y) != right.getAt(x, y))
            {
                return false;
            }
        }
    }

    return true;
}

template<typename T, unsigned int w1, unsigned int h1, unsigned int w2, unsigned int h2>
bool operator!=(const Matrix<T, w1, h1>& left, const Matrix<T, w2, h2>& right)
{
    return !operator==<T, w1, h1, w2, h2>(left, right);
}

template<typename T>
std::pair<T, T> operator*(const std::pair<T, T>& left, const Matrix<T, 2, 2>& right)
{
    std::pair<T, T> result (std::get<0>(left) * right.getAt(0, 0) + std::get<1>(left) * right.getAt(0, 1),
            std::get<0>(left) * right.getAt(1, 0) + std::get<1>(left) * right.getAt(1, 1));
    return result;
}

namespace MatrixControl
{
    template<typename T>
    Matrix<T, 2, 2> createRotationMatrix(T theta)
    {
        Matrix<T, 2, 2> result {cos(theta), -sin(theta),
            sin(theta), cos(theta)};
        return result;
    }

    template<typename T>
    void toRotationMatrix(T theta, Matrix<T, 2, 2>& mat)
    {
        mat.data[0] = cos(theta);
        mat.data[1] = -sin(theta);
        mat.data[2] = sin(theta);
        mat.data[3] = cos(theta);
    }
}

template<typename T, unsigned int width, unsigned int height>
Matrix<T, width, height>::Matrix(std::initializer_list<T> initialData)
{
    unsigned int initialDataSize = initialData.size();

    unsigned int index = 0;
    for (auto item : initialData)
    {
        data[index] = item;
        index++;

        if (index >= width * height)
        {
            break;
        }
    }
}

template<typename T, unsigned int width, unsigned int height>
Matrix<T, width, height>::Matrix()
{
    zero();
}

template<typename T, unsigned int width, unsigned int height>
Matrix<T, width, height>::Matrix(const Matrix<T, width, height>& other)
{
    for(unsigned int i = 0; i < width * height; i++)
    {
        data[i] = other.data[i];
    }
}

template<typename T, unsigned int width, unsigned int height>
const Matrix<T, width, height>& Matrix<T, width, height>::operator=(const Matrix<T, width, height>& other)
{
    Matrix<T, width, height>::Matrix(other);

    return *this;
}

template<typename T, unsigned int width, unsigned int height>
void Matrix<T, width, height>::zero()
{
    for(unsigned int i = 0; i < width * height; i++)
    {
        data[i] = 0;
    }
}

// This will only work for square matricies!
template<typename T, unsigned int width, unsigned int height>
void Matrix<T, width, height>::operator*=(const Matrix<T, height, width>& other)
{
    Matrix<double, height, height> result = operator*<T, width, height>(*this, other);

    for(unsigned int i = 0; i < height * height && i < width * height; i++)
    {
        data[i] = result.data[i];
    }
}

template<typename T, unsigned int width, unsigned int height>
const T& Matrix<T, width, height>::getAt(unsigned int x, unsigned int y) const
{
    return data[y * width + x];
}

template<typename T, unsigned int width, unsigned int height>
void Matrix<T, width, height>::setAt(unsigned int x, unsigned int y, T setTo)
{
    data[y * width + x] = setTo;
}

template<typename T, unsigned int width, unsigned int height>
void Matrix<T, width, height>::multiplyRowByConstant(unsigned int y, T constant)
{
    for(unsigned int x = 0; x < width; x++)
    {
        data[y * width + x] *= constant;
    }
}

template<typename T, unsigned int width, unsigned int height>
void Matrix<T, width, height>::addConstantMultpileOfRow(unsigned int srcY, unsigned int dstY, T constant)
{
    for(unsigned int x = 0; x < width; x++)
    {
        data[dstY * width + x] += data[srcY * width + x] * constant;
    }
}

template<typename T, unsigned int width, unsigned int height>
void Matrix<T, width, height>::swapRows(unsigned int y1, unsigned int y2)
{
    T temp;
    for(unsigned int x = 0; x < width; x++)
    {
        temp = data[y1 * width + x];
        data[y1 * width + x] = data[y2 * width + x];
        data[y2 * width + x] = temp;
    }
}

template<typename T, unsigned int width, unsigned int height>
void Matrix<T, width, height>::toIdentity()
{
    unsigned int y;
    T setTo;
    for(unsigned int x = 0; x < width; x++)
    {
        for(y = 0; y < height; y++)
        {
            if(x == y)
            {
                setTo = 1;
            }
            else
            {
                setTo = 0;
            }

            setAt(x, y, setTo);
        }
    }
}

template<typename T, unsigned int width, unsigned int height>
bool Matrix<T, width, height>::invert()
{
    /**
     * Apply the method of elementary row operators.
     * Each row can be multiplied by a constant, swapped with another,
     * or have a constant multiple of another added to it.
     *
     * Will fail in the case of integers.
     */

    Matrix copy = Matrix(*this);

    this->toIdentity();

    unsigned int piviotY;
    unsigned int y;
    unsigned int incrementCount = 1;
    T constantMultiple;
    T piviotValue;
    bool success = true;

    for (unsigned int x = 0; x < width; x++)
    {
        piviotY = x;

        if (piviotY >= height)
        {
            success = false;
            break;
        }

        piviotValue = copy.getAt(x, piviotY);

        if (piviotValue == 0)
        {
            if(piviotY + incrementCount < height)
            {
                swapRows(piviotY, piviotY + incrementCount);
                copy.swapRows(piviotY, piviotY + incrementCount);
                incrementCount++;
                x --;
                continue;
            }
            else
            {
                success = false;
                break;
            }
        }

        // Make the piviot's value 1.
        copy.multiplyRowByConstant(piviotY, 1/piviotValue);
        multiplyRowByConstant(piviotY, 1/piviotValue);


        // Make everything else in the row 0.
        for (y = 0; y < height; y++)
        {
            if (y != piviotY)
            {
                constantMultiple = -copy.getAt(x, y);
                addConstantMultpileOfRow(piviotY, y, constantMultiple);
                copy.addConstantMultpileOfRow(piviotY, y, constantMultiple);
            }
        }
    }

    return success;
}

template<typename T, unsigned int width, unsigned int height>
void Matrix<T, width, height>::fill(std::function<T(unsigned int, unsigned int)> generator)
{
    unsigned int y;
    for(unsigned int x = 0; x < width; x++)
    {
        for(y = 0; y < height; y++)
        {
            setAt(x, y, generator(x, y));
        }
    }
}


void testMatricies();

