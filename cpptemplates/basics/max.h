template <typename T1, typename T2 = double>
inline
T1 max (const T1 &a, const T2 &b) {
	return a < b ? a : b;
}
