#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

/**
 * Vector bidimensional genérico.
 */
template<typename T = float>
class Vector2D
{

public:
	Vector2D<T>(T a, T l) : x(a), y(l)
	{ }
	Vector2D() : Vector2D(0, 0) { }

	// Coordenadas del vector
	const T& getX() const { return x; }
	const T& getY() const { return y; }
	
	// Operadores
	/*Vector2D operator+(const Vector2D& otro) const {
		return {x + otro.x, y + otro.y};
	}*/

	// TODO: completar
	Vector2D<T> operator+(Vector2D<T> v) const { return Vector2D<T>(this->x + v.x, this->y + v.y); }
	Vector2D<T> operator-(Vector2D<T> v) const { return Vector2D<T>(this->x - v.x, this->y - v.y); }
	int operator*(Vector2D<T> v) const { return (this->x * v.x) + (this->y * v.y); }
	Vector2D<T> operator*(int v) const { return Vector2D<T>(this->x * v, this->y * v); }

	// Operadores de entrada/salida
	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
		return out << '{' << v.x << ", " << v.y << '}';
	}
private:
	T x, y;
};

#endif // VECTOR2D_H

using Point2D = Vector2D<float>;

