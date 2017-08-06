#include <iostream>

/**
 * checks assignment to prevent overflow errors
 */
template <class T>
class SafeInteger
{
	T val_;

	public:
	SafeInteger() : val_(0) {}
	
	// do not allow compiler to call it implicitly in operators below
	explicit SafeInteger(T val) : val_(val) {}

	SafeInteger(const SafeInteger<T>& other) : val_(other.val_) {}

	template <typename T2,
		typename std::enable_if<std::is_integral<T2>::value && sizeof(T2) <= sizeof(T), T2>::type* = nullptr>
	SafeInteger<T>& 
	operator = (const T2& aval)
	{ 
		std::cout << sizeof(T) << "," << sizeof(T2) << std::endl;
		val_ = aval; 
		return *this; 
	}

	bool operator == (SafeInteger<T>& other) const { return val_ == other.val_; }
	bool operator != (SafeInteger<T>& other) const { return val_ != other.val_; }
	bool operator < (SafeInteger<T>& other)  const { return val_ < other.val_; }
	bool operator <= (SafeInteger<T>& other) const { return val_ <= other.val_; }
	bool operator > (SafeInteger<T>& other)  const { return val_ > other.val_; }
	bool operator >= (SafeInteger<T>& other) const { return val_ >= other.val_; }

	SafeInteger<T>& operator -- () { val_ --; return *this; }
	SafeInteger<T>& operator -- (int ) { val_ --; return *this; }
	SafeInteger<T>& operator ++ () { val_ ++; return *this; }
	SafeInteger<T>& operator ++ (int ) { val_ ++; return *this; }

	SafeInteger<T>& operator += (const SafeInteger<T>& other) { val_ += other.val_;  return *this;}
	SafeInteger<T>& operator -= (const SafeInteger<T>& other) { val_ -= other.val_;  return *this;}

	template <typename T2,
		typename std::enable_if<std::is_integral<T2>::value && sizeof(T2) <= sizeof(T), T2>::type* = nullptr>
	SafeInteger<T>& operator += (const T2& aval) { val_ += aval;  return *this;}

	template <typename T2,
		typename std::enable_if<std::is_integral<T2>::value && sizeof(T2) <= sizeof(T), T2>::type* = nullptr>
	SafeInteger<T>& operator -= (const T2& aval) { val_ -= aval;  return *this;}

	template <typename T2,
		typename std::enable_if<std::is_integral<T2>::value && sizeof(T2) >= sizeof(T), T2>::type* = nullptr>
	operator T2() const {
		return val_;
	}

	friend std::ostream& operator << (std::ostream& ostr, const SafeInteger<T>& other) {
		ostr << other.val_;
		return ostr;
	}

	friend std::istream& operator >> (std::istream& istr, SafeInteger<T>& other) {
		istr >> other.val_;
		return istr;
	}
};

int main() {
	SafeInteger<int32_t> a;
	a = 4;
	a += 4;
	a -= 2;
	a ++;
	++ a;
	a --;
	-- a;

	std::cout << a;
	std::cin >> a;

	int64_t bigger;
	bigger = a;

	//int16_t smaller;
	//smaller = a;

	int32_t same; // int64_t wont work
	a = same;
	same = a;
}
