DIRS := \
	1 \
	10 \
	13 \
	14 \
	15 \
	16 \
	17 \
	2 \
	24 \
	27 \
	37 \
	4 \
	5 \
	7

all :
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE}); done

clean :
	@ for dir in ${DIRS}; do (cd $${dir}; ${MAKE} clean); done
