#include "ComplexNumber.h"
#include "helper.h"

/* partner: pranay2 */

ComplexNumber::ComplexNumber()
{
    /* Your code here */
    number_type = COMPLEX;
    magnitude = 0.0;
    phase = calculate_phase(0, 0);
    real_component = 0.0;
    imaginary_component = 0.0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    /* Your code here */
    number_type = COMPLEX;
    magnitude = sqrt((rval_real_component * rval_real_component) + (rval_imaginary_component * rval_imaginary_component));
    phase = calculate_phase(rval_real_component, rval_imaginary_component);
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    /* Your code here */
    number_type = COMPLEX;
    magnitude = other.get_magnitude();
    phase = other.get_phase();
    real_component = other.get_real_component();
    imaginary_component = other.get_imaginary_component();
}

void ComplexNumber::set_real_component (double rval)
{
    /* Your code here */
    magnitude = sqrt((rval * rval) + (imaginary_component * imaginary_component));
    phase = calculate_phase(rval, imaginary_component);
    real_component = rval;
}

double ComplexNumber::get_real_component() const
{
    /* Your code here */
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    /* Your code here */
    magnitude = sqrt((real_component * real_component) + (rval * rval));
    phase = calculate_phase(real_component, rval);
    imaginary_component = rval;
}

double ComplexNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double ComplexNumber::get_phase() const{
    /* Your code here */
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component + arg.get_real_component(), imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component - arg.get_real_component(), imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
    double real = real_component * arg.get_real_component();
    real = real - (imaginary_component * arg.get_imaginary_component());

    double imaginary = real_component * arg.get_imaginary_component();
    imaginary = imaginary + (imaginary_component * arg.get_real_component());

    return ComplexNumber(real, imaginary);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    double argreal = arg.get_real_component();
    double argimg = arg.get_imaginary_component();
    double cdsquare = (argreal * argreal) + (argimg * argimg);

    double real = ((real_component * argreal) + (imaginary_component * argimg)) / cdsquare;
    double imaginary = ((imaginary_component * argreal) - (real_component * argimg)) / cdsquare;

    return ComplexNumber(real, imaginary);
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component + arg.get_real_component(), imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component - arg.get_real_component(), imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component * arg.get_real_component(), imaginary_component * arg.get_real_component());
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component / arg.get_real_component(), imaginary_component / arg.get_real_component());
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
    return ComplexNumber(real_component, imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component, imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ComplexNumber(-1 * imaginary_component * arg.get_imaginary_component(), real_component * arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
    double argimg = arg.get_imaginary_component();
    double real = (imaginary_component * argimg) / (argimg * argimg);
    double imaginary = (-1 * real_component * argimg) / (argimg * argimg);
    return ComplexNumber(real, imaginary);
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}