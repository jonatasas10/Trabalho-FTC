afdtool: main.o complemento.o gerarAFD.o minimizacao.o produto.o reconhecer.o
	cc -o afdtool main.o complemento.o gerarAFD.o minimizacao.o produto.o reconhecer.o
main.o: main.c
	cc -c main.c
complemento.o: complemento.c complemento.h
	cc -c complemento.c
gerarAFD.o: gerarAFD.c gerarAFD.h
	cc -c gerarAFD.c
minimizacao.o: minimizacao.c minimizacao.h
	cc -c minimizacao.c
produto.o: produto.c produto.h
	cc -c produto.c
reconhecer.o: reconhecer.c reconhecer.h
	cc -c reconhecer.c
clean:
	rm *.o afdtool
