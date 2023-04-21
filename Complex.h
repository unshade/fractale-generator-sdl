//
// Created by Noe Steiner on 21/04/2023.
//

#ifndef FRACTALE_GENERATOR_COMPLEX_H
#define FRACTALE_GENERATOR_COMPLEX_H


class Complex {

public:
    Complex(double real = 0.0, double imag = 0.0);

    double real() const;
    double imag() const;
    double abs() const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;
    Complex operator^(int power) const;



private:
    double m_real;
    double m_imag;
};


#endif //FRACTALE_GENERATOR_COMPLEX_H
