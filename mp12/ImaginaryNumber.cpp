#include "ImaginaryNumber.h"
#include "helper.h"

/* partner: pranay2 */

ImaginaryNumber::ImaginaryNumber()
{
    /* Your code here */
    number_type = IMAGINARY;
    magnitude = 0.0;
    imaginary_component = 0.0;
    phase = calculate_phase(0, imaginary_component);
}

ImaginaryNumber::ImaginaryNumber(double rval)
{
    /* Your code here */
    number_type = IMAGINARY;
    magnitude = sqrt(rval * rval);
    phase = calculate_phase(0, rval);
    imaginary_component = rval;
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
{
    /* Your code here */
    number_type = IMAGINARY;
    magnitude = other.get_magnitude();
    phase = other.get_phase();
    imaginary_component = other.get_imaginary_component();
}

void ImaginaryNumber::set_imaginary_component (double rval)
{
    /* Your code here */
    magnitude = sqrt(rval * rval);
    phase = calculate_phase(0, rval);
    imaginary_component = rval;
}

double ImaginaryNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{
    /* Your code here */
    return phase;
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component + arg.get_imaginary_component());
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component - arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
    return RealNumber(-1 * imaginary_component * arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
    return RealNumber(imaginary_component / arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(-1 * arg.get_real_component(),imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component * arg.get_real_component());
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    double argreal = arg.get_real_component();
    return ImaginaryNumber(imaginary_component * argreal / (argreal * argreal));
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), arg.get_imaginary_component() + imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(-1 * arg.get_real_component(), imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
    double real = -1 * imaginary_component * arg.get_imaginary_component();
    double imaginary = imaginary_component * arg.get_real_component();

    return ComplexNumber(real, imaginary);
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    double argreal = arg.get_real_component();
    double argimg = arg.get_imaginary_component();
    double cdsquare = (argreal * argreal) + (argimg * argimg);

    double real = (imaginary_component * argimg) / cdsquare;
    double imaginary = (imaginary_component * argreal) / cdsquare;

    return ComplexNumber(real, imaginary);
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}