// fast fourier transform
#include "fft.h"

namespace utils {

    namespace fft {
        // TODO maybe do in sine cos form, 
        // complex numbers require a lot of overhead
        // profile to see which is faster

        /**
        * Returns discrete fourier transform of 0..n
        * (where n is max freq.)
        * fhat (fourier coeff) = SUM j=0 to n-1 (input * e^(-i2PIjk/n))
        */
        std::vector<math::complex>* dft(std::vector<float> &input)
        {
            unsigned long length = input.size();
            if (length == 0) throw std::invalid_argument("length must be > 0"); // placeholder
            //unsigned long maxfq = length / 2;

            std::vector<math::complex>* output =
                new std::vector<math::complex>(length);

            for (unsigned long k = 0; k < length; k++)
            {
                math::complex result = 0;
                for (unsigned long j = 0; j < length; j++)
                {
                    result += math::real_to_complex(input[j])
                        * cis_inv(2 * math::PI * j * k / length);
                }
                (*output)[k] = result;
            }
            return output;
        }

        // TODO power specturm (fhat^2) = conjugate multiply of complex coeff.

        // TODO these...
        // ASSUMES INPUT TO DFT WAS REAL
        /**
        * Returns discrete fourier transform of 0..n
        * (where n is max freq.)
        * j (data) = SUM j=0 to n-1 (fhat * e^(i2PIjk/n))
        */
        std::vector<float>* idft(std::vector<math::complex> &coeffs)
        {
            unsigned long length = coeffs.size();
            //unsigned long length = maxfq * 2;
            if (length == 0) throw std::invalid_argument("length must be > 0"); // placeholder
            std::vector<float>* output =
                new std::vector<float>(length);

            for (unsigned long k = 0; k < length; k++)
            {
                math::complex result = 0;
                for (unsigned long j = 0; j < length; j++)
                {
                    result += coeffs[j]
                        * cis(2 * math::PI * j * k / length);
                }
                (*output)[k] =  result.real() / (float)length;
            }
            return output;
        }


        std::vector<math::complex>* fft(std::vector<float>& input)
        {
            unsigned long length = input.size();
            if (length == 0) throw std::invalid_argument("length must be > 0"); // placeholder
            if (length == 1)
            {
                // base case
                std::vector<math::complex>* ret = new std::vector<math::complex>(1);
                (*ret)[0] = input[0];
                // e^i0=1, return self
                return ret;
            }

            uint64_t pwr2 = uint64_next_pwr2(length);
            input.resize(pwr2, 0);
            length = pwr2;
            // assert pwr2 odd

            // divide (assume padded to even)
            std::vector<float> odds(length/2);
            std::vector<float> evens(length/2);

            for (unsigned long k = 0; k < length/2; k++)
            {
                evens[k] = input[2 * k];
                odds[k] = input[2 * k + 1] ;
            }

            std::vector<math::complex>* ret_evens = fft(evens);
            std::vector<math::complex>* ret_odds = fft(odds);

            for (unsigned long k = 0; k < length/2; k++)
            {
                // twiddle factor
                (*ret_odds)[k] *= cis_inv(2 * math::PI * k / length);
            }
            // merge
            std::vector<math::complex>* ret = new std::vector<math::complex>(length);
            for (unsigned long k = 0; k < length / 2; k++)
            {
                (*ret)[k] = (*ret_evens)[k] + (*ret_odds)[k];
                (*ret)[k+length/2] = (*ret_evens)[k] - (*ret_odds)[k];
            }

            free(ret_evens);
            free(ret_odds);

            return ret;//ret merge
        }

        std::vector<math::complex>* ifft(std::vector<float>& input)
        {
            return NULL;
        }

        std::vector<float>* power_spec(std::vector<math::complex>& input)
        {
            unsigned long length = input.size();
            if (length == 0) throw std::invalid_argument("length must be > 0"); // placeholder
            std::vector<float>* output =
                new std::vector<float>(length);

            for (unsigned long k = 0; k < length; k++)
            {
                math::complex normalize = input[k]  // normalize
                    / sqrt(math::real_to_complex(length));
                (*output)[k] = (normalize * std::conj(normalize)).real();
            }
            return output;
        }

        math::complex eitheta(double theta)
        {
            return std::pow(
                math::EULER,
                math::IMAGINARY_UNIT * math::real_to_complex(theta));
        }

        math::complex cis(double theta)
        {
            return
                math::real_to_complex(cos(theta)) +
                math::IMAGINARY_UNIT * math::real_to_complex(sin(theta));
        }

        // inverse
        math::complex eitheta_inv(double theta)
        {
            return std::pow(
                math::EULER,
                -math::IMAGINARY_UNIT * math::real_to_complex(theta));
        }

        // inverse
        math::complex cis_inv(double theta)
        {
            return
                math::real_to_complex(cos(theta)) -
                math::IMAGINARY_UNIT * math::real_to_complex(sin(theta));
        }
    }
}

