#ifndef GEOMETRY_H
#define GEOMETRY_H

template <typename T> struct point {
  T x, y;
  point();
  point(int null);
  point(const T x, const T y);
  long double length();
  long double radangle();
  const point operator-();
  point &operator+=(const point &pnt);
  point &operator-=(const point &pnt);
  point &operator*=(const long double q);
  const point operator+(const point &pnt) const;
  const point operator-(const point &pnt) const;
  const point operator*(long double q) const;
  const bool operator==(const point &pnt) const;
  const bool operator!=(const point &pnt) const;
  const T operator*(const point &pnt) const; // Scalar product
  const T operator%(const point &pnt) const; // Cross product
};

template <typename T> std::istream &operator>>(std::istream &is, point<T> &pnt);

template <typename T>
long double radangle(const point<T> &pntA, const point<T> &pntB);

template <typename T>
long double length(const point<T> &pntA, const point<T> &pntB);

template <typename T> long double area(const std::vector<point<T> > &shape);

template <typename T> struct mvector {
  point<T> st, end;
  mvector();
  mvector(const point<T> &end);
  mvector(const point<T> &st, const point<T> &end);
  long double length();
  long double radangle();
  void rotate(const long double angle);
  mvector &operator+=(const mvector &mvec);
  mvector &operator-=(const mvector &mvec);
  mvector &operator*=(const long double q);

  const mvector operator-() const;
  const mvector operator+(const mvector &mvec) const;
  const mvector operator-(const mvector &mvec) const;
  const mvector operator*(long double q) const;
  const bool operator==(const mvector &mvec) const;
  const bool operator!=(const mvector &mvec) const;
  const T operator*(const mvector &mvec);
  const T operator%(const mvector &mvec);
  mvector &operator+=(const point<T> &pnt);
  mvector &operator-=(const point<T> &pnt);
  const mvector operator+(const point<T> &pnt) const;
  const mvector operator-(const point<T> &pnt) const;
};

template <typename T>
long double radangle(mvector<T> &mvecA, mvector<T> &mvecB);

#endif
