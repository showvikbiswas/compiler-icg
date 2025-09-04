flex 1805068_scanner.l
bison -d 1805068_parser.y
g++ lex.yy.c 1805068_parser.tab.c -w
./a.out