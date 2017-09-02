namespace N {
	class X {
		...
	};

	template<int I> void select(X *);
}

void g(N::X *xp) {
	// can't compile
	select<3>(xp);
}
