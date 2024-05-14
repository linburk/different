#include <cmath>
#include <geometry.hpp>
#include <iostream>
#include <vector>

template <typename T> point<T>::point() {}

template <typename T> point<T>::point(int null) : x(0), y(0) {}

template <typename T> point<T>::point(const T x, const T y) : x(x), y(y) {}

template <typename T> long double point<T>::length() {
  return std::hypot(x, y);
}

template <typename T> long double point<T>::radangle() {
  return std::atan2(y, x);
}

template <typename T> const point<T> point<T>::operator-() {
  return point(-(this->x), -(this->y));
}

template <typename T> point<T> &point<T>::operator+=(const point<T> &pnt) {
  x += pnt.x, y += pnt.y;
  return *this;
}
template <typename T> point<T> &point<T>::operator-=(const point<T> &pnt) {
  x -= pnt.x, y -= pnt.y;
  return *this;
}

template <typename T> point<T> &point<T>::operator*=(const long double q) {
  x *= q, y *= q;
  return *this;
}

template <typename T>
const point<T> point<T>::operator+(const point &pnt) const {
  return point(*this) += pnt;
}
template <typename T>
const point<T> point<T>::operator-(const point &pnt) const {
  return point(*this) -= pnt;
}

template <typename T> const point<T> point<T>::operator*(long double q) const {
  return point(*this) *= q;
}

template <typename T> const bool point<T>::operator==(const point &pnt) const {
  return (pnt.x == (this->x) && pnt.y == (this->y));
}

template <typename T> const bool point<T>::operator!=(const point &pnt) const {
  return !(pnt == *this);
}

template <typename T> const T point<T>::operator*(const point &pnt) const {
  return (this->x) * pnt.x + (this->y) * pnt.y;
}

template <typename T> const T point<T>::operator%(const point &pnt) const {
  return (this->x) * pnt.y - (this->y) * pnt.x;
}

template <typename T> std::istream &operator>>(std::istream &is, point<T> &A) {
  is >> A.x >> A.y;
  return is;
}

template <typename T>
long double radangle(const point<T> &pntA, const point<T> &pntB) {
  return atan2(pntA % pntB, pntA * pntB);
}

template <typename T> long double length(point<T> &pntA, point<T> &pntB) {
  return std::hypot((pntA.x - pntB.x), (pntA.y - pntB.y));
}

template <typename T> long double area(const std::vector<point<T>> &shape) {
  long long S = 0;
  for (size_t i = 0; i < shape.size(); i++) {
    S += shape[i] % shape[(i + 1) % shape.size()];
  }
  return (long double)std::abs(S) / 2;
}

template <typename T> mvector<T>::mvector() {}

template <typename T>
mvector<T>::mvector(const point<T> &pnt) : st(0), end(pnt) {}

template <typename T>
mvector<T>::mvector(const point<T> &pntA, const point<T> &pntB)
    : st(pntA), end(pntB) {}

template <typename T> long double mvector<T>::length() {
  return ::length(st, end);
}

template <typename T> long double mvector<T>::radangle() {
  return ::radangle(st, end);
}

template <typename T> void mvector<T>::rotate(const long double angle) {
  long double newX, newY;
  end -= st;
  newX = end.x * cos(angle) - end.y * sin(angle);
  newY = end.x * sin(angle) + end.y * cos(angle);
  end.x = newX;
  end.y = newY;
  end += st;
}

template <typename T> mvector<T> &mvector<T>::operator+=(const point<T> &pnt) {
  st += pnt;
  end += pnt;
  return *this;
}

template <typename T>
mvector<T> &mvector<T>::operator+=(const mvector<T> &mvec) {
  point<T> tEndSt = end - st, tMvecEndSt = mvec.end - mvec.st;
  end = tEndSt + tMvecEndSt + st;
  return *this;
}

template <typename T> mvector<T> &mvector<T>::operator-=(const point<T> &pnt) {
  st -= pnt, end -= pnt;
  return *this;
}
template <typename T>
mvector<T> &mvector<T>::operator-=(const mvector<T> &mvec) {
  point<T> tEndSt = end - st, tMvecEndSt = mvec.end - mvec.st;
  end = tEndSt - tMvecEndSt + st;
  return *this;
}

template <typename T> mvector<T> &mvector<T>::operator*=(const long double q) {
  end -= st;
  end *= q;
  end += st;
  return *this;
}

template <typename T> const mvector<T> mvector<T>::operator-() const {
  return mvector(*this) *= -1;
}

template <typename T>
const mvector<T> mvector<T>::operator+(const point<T> &pnt) const {
  return mvector(*this) += pnt;
}

template <typename T>
const mvector<T> mvector<T>::operator+(const mvector<T> &mvec) const {
  return mvector(*this) += mvec;
}

template <typename T>
const mvector<T> mvector<T>::operator-(const point<T> &pnt) const {
  return mvector(*this) -= pnt;
}

template <typename T>
const mvector<T> mvector<T>::operator-(const mvector<T> &mvec) const {
  return mvector(*this) -= mvec;
}

template <typename T>
const mvector<T> mvector<T>::operator*(long double q) const {
  return mvector(*this) *= q;
}

template <typename T>
const bool mvector<T>::operator==(const mvector<T> &mvec) const {
  const point<T> tEndSt = end - st;
  const point<T> tMvecStEnd = mvec.end - mvec.st;
  return tEndSt == tMvecStEnd;
}

template <typename T>
const bool mvector<T>::operator!=(const mvector<T> &mvec) const {
  return !(mvec == (*this));
}

template <typename T> const T mvector<T>::operator*(const mvector<T> &mvec) {
  const point<T> tEndSt = end - st;
  const point<T> tMvecEndSt = mvec.end - mvec.st;
  return tEndSt * tMvecEndSt;
}

template <typename T> const T mvector<T>::operator%(const mvector<T> &mvec) {
  const point<T> tEndSt = end - st;
  const point<T> tMvecEndSt = mvec.end - mvec.st;
  return tEndSt % tMvecEndSt;
}

template <typename T>
long double radangle(mvector<T> &mvecA, mvector<T> &mvecB) {
  const point<T> tEndStA = mvecA.end - mvecA.st;
  const point<T> tEndStB = mvecB.end - mvecA.st;
  return radangle(tEndStA, tEndStB);
}

template class point<long long>;
template class point<long double>;
template class mvector<long long>;
template class mvector<long double>;
