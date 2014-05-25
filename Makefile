CC = gcc
CPPC = g++
SWIG = swig
PERLVER = 5.18
PERLLIB = /usr/lib/perl/$(PERLVER)/CORE/
MAKE_DIRS = SimpleTrieXS SimpleHashXS

all: SimpleTrie.so SimpleHash.so count tf dist
	@for subdir in $(MAKE_DIRS); do \
		(cd $$subdir && perl Makefile.PL  && make); \
	done
	$(CPPC) -shared -L/usr/local/lib -fstack-protector SimpleTrieXS/SimpleTrieXS.o SimpleTrie.o -o SimpleTrieXS/blib/arch/auto/SimpleTrieXS/SimpleTrieXS.so
	$(CPPC) -shared -L/usr/local/lib -fstack-protector SimpleHashXS/SimpleHashXS.o SimpleHash.o -o SimpleHashXS/blib/arch/auto/SimpleHashXS/SimpleHashXS.so

SimpleTrie.so: SimpleTrie_wrap.o SimpleTrie.o
	$(CC) -g -shared -W -o SimpleTrie.so SimpleTrie.o SimpleTrie_wrap.o -lstdc++
SimpleTrie.o: SimpleTrie.cpp
	$(CPPC) -fPIC -O3 -std=c++11 -c SimpleTrie.cpp
SimpleTrie_wrap.o: SimpleTrie_wrap.cpp
	$(CPPC) -fPIC -I $(PERLLIB) -O3 -c SimpleTrie_wrap.cpp
SimpleTrie_wrap.cpp: SimpleTrie.i SimpleTrie.h
	$(SWIG) -c++ -perl -shadow -o SimpleTrie_wrap.cpp SimpleTrie.i

SimpleHash.so: SimpleHash_wrap.o SimpleHash.o
	$(CC) -g -shared -Wall -o SimpleHash.so SimpleHash_wrap.o SimpleHash.o -lstdc++
SimpleHash.o: SimpleHash.cpp paar.h
	$(CPPC) -fPIC -O3 -std=c++11 -c SimpleHash.cpp
SimpleHash_wrap.o: SimpleHash_wrap.cpp SimpleHash.h
	$(CPPC) -fPIC -I $(PERLLIB) -O3 -c SimpleHash_wrap.cpp
SimpleHash_wrap.cpp: SimpleHash.i SimpleHash.h paar.i
	$(SWIG) -c++ -perl -shadow -o SimpleHash_wrap.cpp SimpleHash.i
paar.i: paar.h
	$(SWIG) -c++ -perl -shadow -o paar_wrap.cpp paar.i

count: count.o SimpleTrie.o SimpleHash.o
	$(CPPC) -o count SimpleTrie.o SimpleHash.o count.o
count.o: count.cpp SimpleHash.h
	$(CPPC) -O3 -c count.cpp
tf: tf.o SimpleTrie.o SimpleHash.o
	$(CPPC) -o tf tf.o SimpleTrie.o SimpleHash.o
tf.o: tf.cpp
	$(CPPC) -O3 -c tf.cpp
dist: dist.o SimpleHash.o
	$(CPPC) -o dist dist.o SimpleHash.o
dist.o: dist.cpp
	$(CPPC) -O3 -std=c++11 -c dist.cpp

clean:
	rm -rf SimpleTrie.so SimpleHash.so count *.o *_wrap.cpp tf dist
	@for subdir in $(MAKE_DIRS) ; do \
		(cd $$subdir && make clean) ;\
	done
