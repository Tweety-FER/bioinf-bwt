DSASampling.o: DSASampling.cpp DSASampling.h lpermutation.h linkedTree.h \
 customTree.h types.h rbtree.h sbvtree.h lfMappable.h
DynamicSuffixArray.o: DynamicSuffixArray.cpp DynamicSuffixArray.h types.h \
 gRankS.h sbvtree.h rbtree.h intTree.h customTree.h DSASampling.h \
 lpermutation.h linkedTree.h lfMappable.h
customTree.o: customTree.cpp customTree.h types.h rbtree.h
gRankS.o: gRankS.cpp gRankS.h types.h sbvtree.h rbtree.h
intTree.o: intTree.cpp intTree.h customTree.h types.h rbtree.h
lpermutation.o: lpermutation.cpp lpermutation.h linkedTree.h customTree.h \
 types.h rbtree.h
rbtree.o: rbtree.cpp rbtree.h types.h
run.o: run.cpp DynamicSuffixArray.h types.h gRankS.h sbvtree.h rbtree.h \
 intTree.h customTree.h DSASampling.h lpermutation.h linkedTree.h \
 lfMappable.h
sbvtree.o: sbvtree.cpp sbvtree.h rbtree.h types.h
test.o: test.cpp DynamicSuffixArray.h types.h gRankS.h sbvtree.h rbtree.h \
 intTree.h customTree.h DSASampling.h lpermutation.h linkedTree.h \
 lfMappable.h catch.hpp
utils.o: utils.cpp utils.h types.h
