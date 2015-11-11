all: main.o ExpressionTree.o
	g++ -Wall -o expre main.o ExpressionTree.o
main.o: main.cc ExpressionTree.h
	g++ -Wall -c main.cc
ExpressionTree.o: ExpressionTree.cc ExpressionTree.h TreeNode.h
	g++ -Wall -c ExpressionTree.cc
