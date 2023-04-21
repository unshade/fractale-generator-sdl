//
// Created by Noe Steiner on 21/04/2023.
//

#include "Complex.h"
#include <cmath>


Complex::Complex(double real, double imag) : m_real(real), m_imag(imag) {}

double Complex::real() const {
    return m_real;
}

double Complex::imag() const {
    return m_imag;
}

double Complex::abs() const {
    return sqrt(m_real * m_real + m_imag * m_imag);
}

Complex Complex::operator+(const Complex &other) const {
    return Complex(m_real + other.real(), m_imag + other.imag());
}

Complex Complex::operator-(const Complex &other) const {
    return Complex(m_real - other.real(), m_imag - other.imag());
}

Complex Complex::operator*(const Complex &other) const {
    double real_part = m_real * other.real() - m_imag * other.imag();
    double imag_part = m_real * other.imag() + m_imag * other.real();
    return Complex(real_part, imag_part);
}

Complex Complex::operator/(const Complex &other) const {
    double real_part = (m_real * other.real() + m_imag * other.imag()) /
                       (other.real() * other.real() + other.imag() * other.imag());
    double imag_part = (m_imag * other.real() - m_real * other.imag()) /
                       (other.real() * other.real() + other.imag() * other.imag());
    return Complex(real_part, imag_part);
}

Complex Complex::operator^(int power) const {
    if (power == 0) {
        return Complex(1, 0); // Si la puissance est 0, retourne 1 (sous forme complexe)
    }

    Complex result = *this;
    Complex base = *this;

    for (int i = 1; i < power; i++) {
        result = result * base;
    }

    return result;
}
