#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include <vector>

template<class type> class polynomial {
    public:
        polynomial() {}
        polynomial(type c)
        {
            this->set(0, c);
        }

        void set(typename std::vector<type>::size_type j, type coefficient)
        {
            if(j + 1 >= coefficients.size())
            {
                if(coefficient != 0)
                {
                    coefficients.resize(j + 1);
                    coefficients[j] = coefficient;
                }
            }
            else
            {
                coefficients[j] = coefficient;
                resize();
            }
        }

        type get(typename std::vector<type>::size_type j) const
        {
            if(j < coefficients.size())
            {
                return coefficients[j];
            }
            return 0;
        }

        polynomial operator+(const polynomial &other) const
        {
            polynomial ret;

            typename std::vector<type>::size_type s = (degree() > other.degree() ? degree() + 1 : other.degree() + 1);
            for(typename std::vector<type>::size_type i = 0;i < s;i++)
            {
                ret.set(i, this->get(i) + other.get(i));
            }

            ret.resize();

            return ret;
        }

        polynomial operator+(const type &other) const
        {
            polynomial ret = *this;

            ret.set(0, ret.get(0) + other);

            ret.resize();

            return ret;
        }

        friend polynomial operator+(const type &lhs, const polynomial &rhs)
        {
            polynomial ret = rhs;

            ret.set(0, lhs + ret.get(0));

            ret.resize();

            return ret;
        }

        polynomial operator-(const polynomial &other) const
        {
            polynomial ret;

            typename std::vector<type>::size_type s = (degree() > other.degree() ? degree() + 1 : other.degree() + 1);
            for(typename std::vector<type>::size_type i = 0;i < s;i++)
            {
                ret.set(i, this->get(i) - other.get(i));
            }

            ret.resize();

            return ret;
        }

        polynomial operator-(const type &other) const
        {
            polynomial ret = *this;

            ret.set(0, ret.get(0) - other);

            ret.resize();

            return ret;
        }

        friend polynomial operator-(const type &lhs, const polynomial &rhs)
        {
            polynomial ret = rhs;

            ret.set(0, lhs - ret.get(0));

            ret.resize();

            return ret;
        }

        polynomial operator*(const polynomial &other) const
        {
            polynomial ret;

            typename std::vector<type>::size_type s1 = degree() + 1;
            typename std::vector<type>::size_type s2 = other.degree() + 1;
            for(typename std::vector<type>::size_type i = 0;i < s1;i++)
            {
                for(typename std::vector<type>::size_type j = 0;j < s2;j++)
                {
                    double tmp = ret.get(i + j);
                    ret.set(i + j, tmp + this->get(i) * other.get(j));
                }
            }

            ret.resize();

            return ret;
        }

        polynomial operator*(const type &other) const
        {
            polynomial ret;

            typename std::vector<type>::size_type s1 = degree() + 1;
            for(typename std::vector<type>::size_type i = 0;i < s1;i++)
            {
                ret.set(i, this->get(i) * other);
            }

            ret.resize();

            return ret;
        }

        friend polynomial operator*(const type &lhs, const polynomial &rhs)
        {
            polynomial ret;

            typename std::vector<type>::size_type s1 = rhs.degree() + 1;
            for(typename std::vector<type>::size_type i = 0;i < s1;i++)
            {
                ret.set(i, lhs * rhs.get(i));
            }

            ret.resize();

            return ret;
        }

        polynomial indefinite_integral() const
        {
            polynomial ret;

            for(typename std::vector<type>::size_type i = 0;i < coefficients.size();i++)
            {
                ret.set(i + 1, this->get(i) / ((type)i + 1));
            }

            ret.resize();

            return ret;
        }

        polynomial differentiate() const
        {
            polynomial ret;

            if(coefficients.size() > 0)
            {
                for(typename std::vector<type>::size_type i = 0;i < coefficients.size() - 1;i++)
                {
                    ret.set(i, (type)(i + 1) * this->get(i + 1));
                }

                ret.resize();
            }

            return ret;
        }

        std::vector<double>::size_type degree() const
        {
            // TODO: degree -inf
            if(coefficients.size() == 0) return 0;
            return coefficients.size() - 1;
        }

        friend std::ostream &operator<<(std::ostream& out, const polynomial &pol)
        {
            if(pol.coefficients.size() > 0)
            {
                for(typename std::vector<type>::size_type i = 0;i < pol.degree();i++)
                {
                    if(pol.get(i) != 0) out << pol.get(i) << "*x^" << i << " + ";
                }

                out << pol.coefficients[pol.degree()] << "*x^" << pol.degree();
            }

            return out;
        }

        type eval_at(type x)
        {
            if(coefficients.size() > 0)
            {
                type ret = 0;

                for(typename std::vector<type>::size_type i = coefficients.size() - 1;i > 0;i--)
                {
                    ret = this->get(i) + x * ret;
                }

                ret = this->get(0) + x * ret;

                return ret;
            }

            return 0;
        }


    private:
        typename std::vector<type> coefficients;

        void resize()
        {
            typename std::vector<type>::size_type s = coefficients.size();
            if(s > 0)
            {
                bool non_zero_coeff = false;
                for(typename std::vector<type>::size_type i = s - 1;i > 0;i--)
                {
                    if(coefficients[i] == 0)
                    {
                        coefficients.resize(i);
                    }
                    else
                    {
                        non_zero_coeff = true;
                        break;
                    }
                }

                if(!non_zero_coeff)
                {
                    if(coefficients[0] == 0)
                    {
                        coefficients.resize(0);
                    }
                }
            }
        }
};

#endif

