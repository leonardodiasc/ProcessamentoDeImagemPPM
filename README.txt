Funcionalidades implementadas:
	Filtros: 
	-Blur
	-Sharpen
	-Deteccao de bordas.
	-Tresholding(Binarizacao).

	Transformacoes:
	-Reduzir
	-Ampliar(o método usado utiliza interpolacao para a criação dos novos pixels, deixando a imagem com maior qualidade comparado ao método simples de apenas multiplicar os pixels antigos).
	-Rotacionar(90o, 180o, ou 270o)

Funcionalidades nao implementadas:
	Todas as funcionalidades básicas foram implementadas, porem eu não consegui achar nenhuma ferramenta de C que eu conseguisse adaptar o código facilmente para criação da interface gráfica, principalmente porque eu comecei a fazer o código para rodar pelo terminal, teria sido mais fácil se eu ja tivesse começado a fazer ja usando alguma ferramenta .

O que seria feito diferentemente:
	Planejar o funcionamento do código em avanço teria facilitado, tive problemas de quando finalmente consigo imaginar um algoritmo e ao testa-lo me deparo com erros inesperados, colocar no papel teria ajudado. De inicio eu não estava preocupado com a indentação e organizacao, o que acabou prejudicando a leitura do código, no final eu consegui limpar e organizar o código, ter feito isso de inicio teria me evitado problemas.

Como compilar:
	Exemplo utilizando o gcc:
		“gcc main.c filters.c -o main”
		“./main lena.ppm” //sendo lena.ppm a imagem a ser transformada

	Ou seja, executável + caminho para a imagem desejada.
	Os arquivos usados são main.c, filters.c, e filters.h