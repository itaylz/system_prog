#pragma once

#include <iostream>
#include <cmath>

class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0) : real(real), imag(imag) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }

    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
                       (imag * other.real - real * other.imag) / denominator);
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    bool operator<(const Complex& other) const {
        return magnitude() < other.magnitude();
    }

    bool operator<=(const Complex& other) const {
        return magnitude() <= other.magnitude();
    }

    bool operator>(const Complex& other) const {
        return magnitude() > other.magnitude();
    }

    bool operator>=(const Complex& other) const {
        return magnitude() >= other.magnitude();
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& complex) {
        os << complex.real << " + " << complex.imag << "i";
        return os;
    }

private:
    double real;
    double imag;
};

