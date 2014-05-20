swig -c++ -perl -shadow -o SimpleTrie_wrap.cpp SimpleTrie.i
g++ -fPIC -c SimpleTrie.cpp SimpleTrie_wrap.cpp -I /usr/lib/perl/5.18/CORE/ -O3
gcc -g -shared -W -o SimpleTrie.so SimpleTrie.o SimpleTrie_wrap.o -lstdc++

swig -c++ -perl -shadow -o MapTrie_wrap.cpp MapTrie.i
g++ -fPIC -c MapTrie.cpp MapTrie_wrap.cpp -I /usr/lib/perl/5.18/CORE/ -O3
gcc -g -shared -W -o MapTrie.so MapTrie.o MapTrie_wrap.o -lstdc++

swig -c++ -perl -shadow -o SimpleHash_wrap.cpp SimpleHash.i
g++ -fPIC -c SimpleHash.cpp SimpleHash_wrap.cpp -I /usr/lib/perl/5.18/CORE/ -O3
gcc -g -shared -W -o SimpleHash.so SimpleHash.o SimpleHash_wrap.o -lstdc++

g++ -c -O3 count.cpp 
g++ -o count SimpleHash.o SimpleTrie.o MapTrie.o count.o
