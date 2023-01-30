#pragma once

#include <bitset>
#include <iostream>

namespace ctm
{
	namespace utility
	{
		template<size_t N, template<size_t> class BAType = std::bitset>
		class bigint_base
		{
		private:
			BAType<N> bitarray;
		public:

			void print(void)
			{
				std::cout << bitarray << std::endl;
			}

			template<std::integral T>
			bigint_base(T val);

			bigint_base(void) = default;
			bigint_base(const bigint_base& other) = default;
			bigint_base(bigint_base&& other) = default;
			bigint_base& operator=(const bigint_base& rhs) = default;
			bigint_base& operator=(bigint_base&& rhs) = default;

			bigint_base operator|(const bigint_base& a) const;
			bigint_base operator&(const bigint_base& a) const;
			bigint_base operator^(const bigint_base& a) const;
			bigint_base operator<<(size_t st) const;
			bigint_base operator>>(size_t st) const;

			bigint_base& operator|=(const bigint_base& a);
			bigint_base& operator&=(const bigint_base& a);
			bigint_base& operator^=(const bigint_base& a);
			bigint_base& operator<<=(size_t st);
			bigint_base& operator>>=(size_t st);

			bigint_base operator~(void) const;

			operator bool() const;

			bigint_base operator++(int);
			bigint_base& operator++(void);

			bigint_base operator+(const bigint_base& a) const;
			bigint_base operator-(void) const;
			bigint_base operator-(const bigint_base& a) const;
			
			bigint_base& operator+=(const bigint_base& a);
			bigint_base& operator-=(const bigint_base& a);

			bigint_base operator*(const bigint_base& a) const;
			bigint_base operator/(const bigint_base& a) const;

			std::strong_ordering operator<=>(const bigint_base& a) const;

			friend std::istream& operator>>(std::istream& in, bigint_base& a)
			{
				char c = in.get();
				bool neg = false;
				if (c == '-')
					neg = true;
				else
					in.putback(c);
				a = bigint_base<N, BAType>();
				for (c = in.get(); c != EOF && '0' <= c && c <= '9'; c = in.get()) {
					a = (a << size_t(3)) + (a << size_t(1)) + bigint_base<N, BAType>(c - '0');
				}
				in.putback(c);
				if (neg)
					a = -a;
				return in;
			}

			friend std::ostream& operator<<(std::ostream& out, bigint_base& a)
			{

			}
		};

		template<size_t N, template<size_t> class BAType>
		template<std::integral T>
		bigint_base<N, BAType>::bigint_base(T val)
		{
			bitarray = BAType<N>(val);
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator|(const bigint_base<N, BAType>& a) const
		{
			bigint_base<N, BAType> res;
			res.bitarray = bitarray | a.bitarray;
			return res;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator&(const bigint_base<N, BAType>& a) const
		{
			bigint_base<N, BAType> res;
			res.bitarray = bitarray & a.bitarray;
			return res;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator^(const bigint_base<N, BAType>& a) const
		{
			bigint_base<N, BAType> res;
			res.bitarray = bitarray ^ a.bitarray;
			return res;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator<<(size_t st) const
		{
			bigint_base<N, BAType> res;
			res.bitarray = bitarray << st;
			return res;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator>>(size_t st) const
		{
			bigint_base<N, BAType> res;
			res.bitarray = bitarray >> st;
			return res;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType>& bigint_base<N, BAType>::operator|=(const bigint_base<N, BAType>& a)
		{
			bitarray |= a.bitarray;
			return *this;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType>& bigint_base<N, BAType>::operator&=(const bigint_base<N, BAType>& a)
		{
			bitarray &= a.bitarray;
			return *this;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType>& bigint_base<N, BAType>::operator^=(const bigint_base<N, BAType>& a)
		{
			bitarray ^= a.bitarray;
			return *this;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType>& bigint_base<N, BAType>::operator<<=(size_t st)
		{
			bitarray <<= st;
			return *this;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType>& bigint_base<N, BAType>::operator>>=(size_t st)
		{
			bitarray >>= st;
			return *this;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator~(void) const
		{
			bigint_base<N, BAType> res;
			res.bitarray = ~bitarray;
			return res;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType>::operator bool() const
		{
			for (size_t i = 0; i < N; i++) {
				if (bitarray[i])
					return true;
			}
			return false;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator++(int)
		{
			bigint_base<N, BAType> res(*this);
			for (size_t i = 0; i < N; i++) {
				bitarray[i] = !bitarray[i];
				if (bitarray[i])
					break;
			}
			return res;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType>& bigint_base<N, BAType>::operator++(void)
		{
			for (size_t i = 0; i < N; i++) {
				bitarray[i] = !bitarray[i];
				if (bitarray[i])
					break;
			}
			return *this;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator+(const bigint_base<N, BAType>& a) const
		{
			bigint_base<N, BAType> res(*this ^ a);
			bigint_base<N, BAType> carry((*this & a) << size_t(1));
			bigint_base<N, BAType> tmp;
			while (carry) {
				tmp = res;
				res ^= carry;
				carry &= tmp;
				carry <<= 1;
			}
			return res;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator-(void) const
		{
			return ++~(*this);
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator-(const bigint_base<N, BAType>& a) const
		{
			return *this + -a;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType>& bigint_base<N, BAType>::operator+=(const bigint_base<N, BAType>& a)
		{
			bigint_base<N, BAType> carry((*this & a) << size_t(1));
			*this ^= a;
			bigint_base<N, BAType> tmp;
			while (carry) {
				tmp = *this;
				*this ^= carry;
				carry &= tmp;
				carry <<= 1;
			}
			return *this;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType>& bigint_base<N, BAType>::operator-=(const bigint_base<N, BAType>& a)
		{
			return (*this += -a);
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator*(const bigint_base<N, BAType>& a) const
		{
			bigint_base<N, BAType> res;
			for (size_t i = 0; i < N; i++) {
				if (bitarray[i])
					res += a << i;
			}
			return res;
		}

		template<size_t N, template<size_t> class BAType>
		std::strong_ordering bigint_base<N, BAType>::operator<=>(const bigint_base<N, BAType>& a) const
		{
			if (bitarray[N - 1] != a.bitarray[N - 1])
				return a.bitarray[N - 1] <=> bitarray[N - 1];
			if (bitarray[N - 1]) {
				for (size_t i = N; i > 0; i--) {
					size_t j = i - 1;
					if (bitarray[j] != a.bitarray[j])
						return a.bitarray[j] <=> bitarray[j];
				}
			}
			else {
				for (size_t i = N; i > 0; i--) {
					size_t j = i - 1;
					if (bitarray[j] != a.bitarray[j])
						return bitarray[j] <=> a.bitarray[j];
				}
			}
			return std::strong_ordering::equal;
		}

		template<size_t N, template<size_t> class BAType>
		bigint_base<N, BAType> bigint_base<N, BAType>::operator/(const bigint_base<N, BAType>& a) const
		{
			bool neg = false;
			if (bitarray[N - 1] != a.bitarray[N - 1])
				neg = true;
			bigint_base<N, BAType> A = *this;
			if (A.bitarray[N - 1])
				A = -A;
			A.bitarray[N - 1] = 0;
			bigint_base<N, BAType> B = a;
			if (B.bitarray[N - 1])
				B = -B;
			B.bitarray[N - 1] = 0;
			size_t start = N - 1;
			for (size_t i = 0; i < N - 1; i++) {
				if (B.bitarray[i])
					start = N - 1 - i;
			}
			bigint_base<N, BAType> res;
			for (size_t i = start; i > 0; i--) {
				size_t j = i - 1;
				if (A - (B << j) >= bigint_base<N, BAType>()) {
					A -= B << j;
					res.bitarray[j] = 1;
				}
			}
			if (neg)
				return -res;
			return res;
		}

	}
}