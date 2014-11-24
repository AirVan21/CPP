// Represents complex number
class Complex
{

public:
	// Constructor
	// @param real value of real part 
	// @param img  value of imaginary part
	Complex(int real, int img);

	friend Complex operator*(const Complex &multOne, const Complex &multTwo);
	
	friend Complex& operator*=(Complex &multOne, const Complex &multTwo);

private:
	// Real part of complex number
	int mRe;
	// Imaginary part of complex number
	int mImg;

};

