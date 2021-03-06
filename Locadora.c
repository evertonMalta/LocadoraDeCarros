#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#define TAM 50 //numero de letras para os campos dos formularios
#define MULTA 10 //porcentagem ao dia
#define IDOSO 60 //idade minima para desc idoso

int data_dia[3];

struct ficha {
	int codigo;
	char carro[TAM];
	char placa[8];
	char categoria[TAM];
	float preco;
	char status;
	int data_locado[3];
	int cod_cliente;
	int ativo;
};

struct cliente {
	int codigo;
	char nome[TAM];
	int idade;
	char cpf[TAM];
	char endereco[TAM];
	char socio;
	char ong;
	int data_devolve[3]; //[DD] [MM] [AAAA]
	int ativo;
};

struct ficha dados;
struct cliente dados1;

FILE *arq;
char resp;
FILE *arq1;
char resp1;

void AbrirArquivo(char carro[])
{
	system("cls");
	arq = fopen(carro, "r+"); // associa ao arq fisico e, se arquivo nao existe, deve ser criado, rb = somente para leitura
	if (arq == NULL) puts("NULL");
	if (arq == NULL)
	arq = fopen(carro, "w+");// abre o arquivo depois - rb = escrita a partir do inicio do arquivo
	puts("ARQUIVO ABERTO.");
	//sleep(1500);
}

void FecharArquivo() {
	system("cls");
	fclose(arq);
	puts("ARQUIVO FECHADO.");
}
void AbrirArquivo1(char cliente[])
{
	system("cls");
	arq1 = fopen(cliente, "r+"); // associa ao arq fisico e, se arquivo nao existe, deve ser criado, rb = somente para leitura
	if (arq1 == NULL) puts("NULL");
	if (arq1 == NULL)
	arq1 = fopen(cliente, "w+");// abre o arquivo depois - rb = escrita a partir do inicio do arquivo
	puts("ARQUIVO ABERTO.");
}

void FecharArquivo1() {
	system("cls");
	fclose(arq1);
	puts("ARQUIVO FECHADO.");
}

//Cria um cabecalho da pagina
void cabecalho(){
    system("cls");
    printf("	Data do sistema: %d Dia %d Mes %d Ano\n", data_dia[0],data_dia[1],data_dia[2]);
    puts("");
}

void constroiDesconto(float total, float descontoIdoso, float descontoSocio, float descontoOng){
    if( dados1.idade >= IDOSO ){
        total = total - descontoIdoso;
        printf("\nIdoso: Sim");
    }else{
        printf("\nIdoso: Nao");
    }
    if( dados1.socio == 'S'){
        total = total - descontoSocio;
        printf("\nSocio: Sim");
    }else{
        printf("\nSocio: Nao");
    }
    if( dados1.ong == 'S'){
        total = total - descontoOng;
        printf("\nOng: Sim\n");
    }else{
        printf("\nOng: Nao\n");
    }
}

//Registra o carro no banco de dados
void RegistrarCarro() {
	char opcao;
	do {
	//Faz inclusao dos dados para registra o carro
		cabecalho();
		fseek(arq,0,SEEK_END); // procura de uma certa posicao do arquivo - arq, 0 = qtd bytes para deslocamento do cursor
		//seek_end - comeca do final para o inicio,
		puts("** INCLUSAO DE CARRO ***\n");
		printf("Codigo ......:");
		fflush(stdin);
		scanf("%d",&dados.codigo);
		printf("Carro ..:");
		fflush(stdin);
		gets(dados.carro);
		printf("Placa do carro..:");
		fflush(stdin);
		gets(dados.placa);
		fflush(stdin);
		printf("Categoria..:");
		fflush(stdin);
		gets(dados.categoria);
		fflush(stdin);
		printf("Preco..:\n");
		fflush(stdin);
		scanf("%f", &dados.preco);
		fflush(stdin);
		printf("Status..:\n");
		puts("D = Disponivel");
		puts("L = Locado");
		fflush(stdin);
		dados.status = toupper(getchar());

		if((dados.carro == "") || (dados.carro == NULL)) { // tratamento para nome em branco nao funciona no dev C++
			puts("REGISTRO RESTRINGIDO DEVIDO A DADOS ERRADOS INSERIDOS");
			puts("Deixou o campo CARRO em branco");
			puts("Os dados nao foram registrados no sistema");
		}

		else if(dados.codigo == NULL) { //tratamento para codigo em branco nao funciona para no dev C++
			puts("REGISTRO RESTRINGIDO DEVIDO A DADOS ERRADOS INSERIDOS");
			puts("Deixou o campo CARRO em branco");
			puts("Os dados nao foram registrados no sistema");
		}
//Tratamento do status, restringe o usuario a colocar diferente de D ou L

		else if((dados.status == 'D') || (dados.status == 'L') /*&& (dados.carro != NULL) || (dados.codigo != NULL)*/) {
			dados.ativo = 1;// Ativo = 1 quer dizer que existe, por que na funcao de exclusao, usaremos exclusao logica colocando ativo = 0
			fwrite(&dados,sizeof(struct ficha),1,arq);// escreve todos os dados no arquivo
		}

		else {
			puts("REGISTRO RESTRINGIDO DEVIDO A DADOS ERRADOS INSERIDOS");
			puts("Ou voce inseriu Status digitado errado, Somente digite D = disponivel ou L = locado");
			puts("Deixou alguns dos campos em branco");
			puts("Os dados nao foram registrados no sistema");
		}
// se for errado o status, ele nao registra os dados e de a opcao de fazer uma nova inclusao

		if (ferror(arq))
			puts("ERRO!!");
			printf("\nDESEJA INCLUIR OUTRO CARRO <S/N>? ");
			fflush(stdin);
			opcao = toupper(getchar());
} while (opcao == 'S'); //fim primeiro Do
}

void RegistrarCliente() {
	char opcao;
	do {
	//Faz inclusao dos dados para registra o carro
		cabecalho();
		fseek(arq1,0,SEEK_END); // procura de uma certa posicao do arquivo - arq, 0 = qtd bytes para deslocamento do cursor
		//seek_end - comeca do final para o inicio,
		puts("** INCLUSAO DE Cliente ***\n");
		printf("Codigo ......:");
		fflush(stdin);
		scanf("%d",&dados1.codigo);
		printf("Nome ..: ");
		fflush(stdin);
		gets(dados1.nome);
		printf("Idade..: ");
		fflush(stdin);
		scanf("%d", &dados1.idade);
		printf("CPF..: ");
		fflush(stdin);
		gets(dados1.cpf);
		printf("Endereco..: ");// quantidade de letras de acordo com o define TAM
		fflush(stdin);
		gets(dados1.endereco);
		printf("Socio..:\n");
		puts("S = Socio");
		puts("N = Nao Socio");
		fflush(stdin);
		dados1.socio = toupper(getchar());
        printf("Ong..:\n");
		puts("S = Ong");
		puts("N = Nao Ong");
		fflush(stdin);
		dados1.ong = toupper(getchar());
		if((dados1.nome == "") || (dados1.nome == NULL)) { // tratamento para nome em branco nao funciona no dev C++
			puts("REGISTRO RESTRINGIDO DEVIDO A DADOS ERRADOS INSERIDOS");
			puts("Deixou o campo  em branco");
			puts("Os dados nao foram registrados no sistema");
		}

		else if(dados1.codigo == NULL) { //tratamento para codigo em branco nao funciona para no dev C++
			puts("REGISTRO RESTRINGIDO DEVIDO A DADOS ERRADOS INSERIDOS");
			puts("Deixou o campo NOME em branco");
			puts("Os dados nao foram registrados no sistema");
		}
//Tratamento do status, restringe o usuario a colocar diferente de D ou L

		else if((dados1.socio == 'S') || (dados1.socio == 'N') /*&& (dados.carro != NULL) || (dados.codigo != NULL)*/) {
			dados1.ativo = 1; // Ativo = 1 quer dizer que existe, por que na funcao de exclusao, usaremos exclusao logica colocando ativo = 0
			fwrite(&dados1,sizeof(struct cliente),1,arq1); // escreve todos os dados no arquivo
		}

		else {
			puts("REGISTRO RESTRINGIDO DEVIDO A DADOS ERRADOS INSERIDOS");
			puts("Ou voce inseriu Status digitado errado, Somente digite D = disponivel ou L = locado");
			puts("Deixou alguns dos campos em branco");
			puts("Os dados nao foram registrados no sistema");
		}
// se for errado o status, ele nao registra os dados e da a opcao de fazer uma nova inclusao

		if (ferror(arq1))
			puts("ERRO!!");
			printf("\nDESEJA INCLUIR OUTRO CLIENTE <S/N>? ");
			fflush(stdin);
			opcao = toupper(getchar());
    } while (opcao == 'S'); //fim primeiro Do
}

//Busca carro pelo codigo e exibe seu status se esta locado ou nao
int Buscar(int codigo) {
	int nreg = -1;
	rewind(arq); //posiciona na primeira estrutura do arquivo
	fread(&dados,sizeof(struct ficha),1,arq);//&dados aponta a estrutura a ser lida
	//sizeof()o tamanho do arquivo, 1 quantidade de buscas, arq = arquivo
	if (!ferror(arq))// se nao retorna erro se der erro, entra no if
	while (!feof(arq))//feof informa se chegou ao fim do arquivo, se for diferente entra no while
	{
		nreg++;
		if ((dados.codigo) == codigo) // compara se o carro digitado tem na lista, se tem ele busca, ao inves de usar == tem que usar =
		return(nreg);
		fread(&dados,sizeof(struct ficha),1,arq); //fread, retorna um numero inteiro correspondente a quantidade de bytes lidos
	}
	else
		puts("ERROR!!");
		return(-1);
}

int BuscarCliente(int codigo) {
	int nreg = -1;
	rewind(arq1); //posiciona na primeira estrutura do arquivo
	fread(&dados1,sizeof(struct cliente),1,arq1);//&dados aponta a estrutura a ser lida
	//sizeof()o tamanho do arquivo, 1 quantidade de buscas, arq = arquivo
	if (!ferror(arq1))// se nao retorna erro se der erro, entra no if
	while (!feof(arq1))//feof informa se chegou ao fim do arquivo, se for diferente entra no while
	{
		nreg++;
		if ((dados1.codigo) == codigo) // compara se o carro digitado tem na lista, se tem ele busca, ao inves de usar == tem que usar =
		return(nreg);
		fread(&dados1,sizeof(struct cliente),1,arq1); //fread, retorna um numero inteiro correspondente a quantidade de bytes lidos
	}
	else
		puts("ERROR!!");
		return(-1);
}

int BuscarPalavra(char categoria[TAM])// funcao de busca para buscar carro por categoria
{
	int nreg = -1;
	rewind(arq); //posiciona na primeira estrutura do arquivo
	fread(&dados,sizeof(struct ficha),1,arq);//&dados aponta a estrutura a ser lida
	//sizeof()o tamanho do arquivo, 1 quantidade de buscas, arq = arquivo
	if (!ferror(arq))// se nao retorna erro se der erro, entra no if
	while (!feof(arq))//feof informa se chegou ao fim do arquivo, se for diferente entra no while
	{
		nreg++;
		if (strcmp(dados.categoria, categoria) == 0) // compara se o carro digitado tem na lista, se tem ele busca, ao inves de usar == tem que usar =
		return(nreg);
		fread(&dados,sizeof(struct ficha),1,arq); //executa a leitura do arquivo
	}
	else
		puts("ERROR!!");
	return(-1);
}

void Locar() {
	int codigo,codigo1;
	int nreg;
	cabecalho();
	puts("** LOCAR CARRO ***\n");
	printf("Digite o codigo do carro para registrar a locacao ......:");
	fflush(stdin);
	scanf("%d",&codigo);
	printf("Digite o codigo do cliente para registrar a locacao ......:");
	fflush(stdin);
	scanf("%d",&codigo1);
	nreg = Buscar(codigo);
	if ( nreg >=0 ) // se a busca for maior do que 0 ele achou e apresentar os dados achados e mudar o status automaticamente
	{
		if(dados.status != 'L')
		{
			//registra dia que foi alugado
			dados.data_locado[2] = data_dia[2];
			dados.data_locado[1] = data_dia[1];
			dados.data_locado[0] = data_dia[0];

			puts("Digite a data de devolucao:");
			printf("Dia: ");
			fflush(stdin);
			scanf("%d", &dados1.data_devolve[0]);
			printf("Mes: ");
			fflush(stdin);
			scanf("%d", &dados1.data_devolve[1]);
			printf("Ano: ");
			fflush(stdin);
			scanf("%d", &dados1.data_devolve[2]);
			if((dados1.data_devolve[0]  <= data_dia[0] && dados1.data_devolve[1]  <= data_dia[1] && dados1.data_devolve[2]  <= data_dia[2]) || dados1.data_devolve[2]  < data_dia[2]) {
				puts("Data de Devolucao Invalida!");
				puts("ERROR!!");
			}
			else {
                printf("%d/%d/%d\n", dados1.data_devolve[0],dados1.data_devolve[1],dados1.data_devolve[2]);
				printf("Status ..: %c\n",dados.status);
				fflush(stdin);
				dados.status = 'L';
				printf("Novo Status..= %c: \n", dados.status);
				puts("Status L = locado\n");
				// Posiciona novamente o cursor sobre o registro desejado.
				fseek(arq,sizeof(struct ficha) * nreg, SEEK_SET);//seek_set comeca da posicao corrente
				fwrite(&dados, sizeof(dados), 1, arq);//escreve os novos dados no arquivo
				fwrite(&dados1,sizeof(struct cliente),1,arq1);
				if (!ferror(arq))//se nao der erro
				{
					puts("");
					puts("LOCACAO REALIZADA");
				}
				else
				{
					puts("ERROR!!");
				}
			}
		}//fim if que filtra se nao esta locado
	else
	{
		puts("");
		puts("Carro ja se encontra em status L = Locado");
		puts("Clique em enter para voltar ao menu principal");
	}
		system("pause");
	}
	else
		puts("CARRO NAO ESTA CADASTRADO OU NAO ESTA DISPONIVEL");
	fflush(stdin);
	getchar();
}

void DevolucaoCarro() {
	int codigo,dia=0,mes=0,ano=0, atraso=0,tdias=0,i,j,k;
	int nreg, nregcli;
	float total=0,multa=0,descontoIdoso=0,descontoSocio=0,descontoOng = 0;

	int totalDiasLocacao = 0, totalDiasDevolucao = 0, totalDiasAtual = 0;


	cabecalho();
	puts("** DEVOLUCAO DO CARRO ***\n");
	printf("Digite o codigo do carro para registar a devolucao......:");
	fflush(stdin);
	scanf("%d",&codigo);
	nreg = Buscar(codigo);
	if ( nreg >=0 ) //if principal de busca se tem na lista o codigo digitado
	{
		if(dados.status != 'D')
		{//if que filtra quem nao esta disponivel para devolver
			nregcli = BuscarCliente(dados.cod_cliente);
            printf("Nome do cliente: %s\n",dados1.nome);
			printf("Nome do carro: %s\n",dados.carro);
			puts("Total a pagar:");
			printf("Valor da diaria: %.2f \n", dados.preco);
			//calculo atraso iteracao

			totalDiasLocacao = dados.data_locado[0] + (dados.data_locado[1] * 30) + (dados.data_locado[2] * 365);
			totalDiasAtual = data_dia[0] + (data_dia[1] * 30) + (data_dia[2] * 365);
			totalDiasDevolucao = dados1.data_devolve[0] + (dados1.data_devolve[1] * 30) + (dados1.data_devolve[2] * 365);

			if(totalDiasDevolucao < totalDiasAtual){
                atraso = 1;
                tdias = totalDiasAtual - totalDiasLocacao;
			}else{
                atraso = 0;
                tdias = totalDiasAtual - totalDiasLocacao;
                if(tdias < 0){
                    tdias = 1;
                }
			}

			total = dados.preco * ((float) tdias); //total a pagar sem multa e sem desconto
			descontoIdoso= ((total * 10.0) /100.0);//Desconto Idoso
			descontoSocio=  ((total * 5.0) /100.0);//Desconto Socio
            descontoOng = ((total* 5.0)/100.0);//Desconto Ong
			//multa= ((total* MULTA) / 100.0); //calculo da multa

			if(atraso == 0) {
				constroiDesconto(total,descontoIdoso,descontoSocio,descontoOng);

				printf("R$ %.2f\n", total);
			}
			else {
				total= total * 1.3;
				puts("Devido ao atraso de:");
				printf(" %d dia(s)", totalDiasDevolucao - totalDiasAtual);
				printf("Multa.: %.2f", total * 0.3);

				constroiDesconto(total,descontoIdoso,descontoSocio,descontoOng);
				printf("Total a pagar: %.2f \n", total);
			}

			printf("Status ..: %c\n",dados.status);
			fflush(stdin);
			dados.status = 'D';
			printf("Novo Status..: %c -> Disponivel\n", dados.status);
			puts("");
			// Posiciona novamente o cursor sobre o registro desejado.
			fseek(arq,sizeof(struct ficha) * nreg, SEEK_SET);// seek_set procura da posicao corrente o cursor
			fwrite(&dados, sizeof(dados), 1, arq);
			if (!ferror(arq))
			{
				puts("DEVOLUCAO REALIZADA");
			}
			else
			{
				puts("ERROR!!");
			}
		}		//fim if que filtra que nao esta devolvido para mudar o status
		else
		{
			puts("");
			puts("Carro ja se encontra em status D = Disponivel ou Devolvido");
			puts("Clique em enter para voltar ao menu principal");
		}
		system("pause");
	}//fim if principal de busca se tem na lista o codigo digitado
	else
	{
	puts("CARRO NAO ESTA CADASTRADO OU NAO ESTA DISPONIVEL");
	fflush(stdin);
	getchar();
	}
}

void ExcluirCarro() {
	char opcao;
	int codigo;
	int nreg;
	cabecalho();
	puts("** EXCLUSAO DE CARRO ***");
	printf("Codigo do carro......:");
	fflush(stdin);
	scanf("%d",&codigo);
	nreg = Buscar(codigo);
	if ( nreg >=0 ) {
		printf("num %d\n",nreg);
		printf("Nome do carro..: %s\n",dados.carro);
		printf("CONFIRMA EXCLUSAO DO CARRO <S/N>?");
		fflush(stdin);
		opcao = toupper(getchar());
		if (opcao == 'S') {
			fseek(arq,sizeof(struct ficha) * nreg, SEEK_SET);//procura os dados da posicao corrente (seek_set)
			// Exclusao Logica
			dados.ativo = 0;// quando ativo = 0, ele  excluido logicamente
			fwrite(&dados, sizeof(dados), 1, arq);//registra novos dados
			if (!ferror(arq))
				puts("CARRO EXCLUIDO.");
			else
			puts("ERRO!!");
		}
	}
	else
		puts("CARRO NAO ENCONTRADO.");
	fflush(stdin);
	getchar();
}

void ConsultarCarro(){
	int codigo;
	int nreg;
	cabecalho();
	puts("** CONSULTA DE CARROS ***\n");
	printf("Codigo do Carro ......:");
	fflush(stdin);
	scanf("%d",&codigo);
	nreg = Buscar(codigo);
	if ( nreg >= 0 ) // se nao atingou -1, ele achou um codigo correspondente, e imprimir o conteudo, usado pelo funcao buscar
	{
		if(dados.status == 'D')
		{
			printf("num %d\n",nreg);
			printf("Codigo: %d\n Carro ..: %s\n Categoria: %s\n Placa: %s \n Status: %c -> Disponivel\n", dados.codigo, dados.carro, dados.categoria, dados.placa, dados.status);
		}
	else {
		printf("num %d\n",nreg);
		printf("Codigo: %d\n Carro ..: %s\n Categoria: %s\n Placa: %s \n Status: %c -> Locado\n", dados.codigo, dados.carro, dados.categoria, dados.placa, dados.status);
	}
	}
	else
		puts("CARRO NAO ENCONTRADO.");
	fflush(stdin);
	getchar();
}

void listarCategorias()	{
	//Funcao que mostra categorias, sendo usadas como funcao estava dando erro, logo colocamos todo o codigo aqui dentro da funcao ListarCarroCategoria
	rewind(arq); //posiciona na primeira linha do arquivo // inicia funcao mostra categoria
	fread(&dados,sizeof(struct ficha),1,arq); //le os dados
	puts("Categorias registradas para fazer a busca");
	puts("");
	if (!ferror(arq)) //se nao der erro pela funcao ferror
	while (!feof(arq)) //feof informa se chegou ao fim do arquivo, se for diferente entra continua no loop do while
	{
		//if (dados.ativo)// o if identifica se o valor  verdadeiro automaticamente que  1, se 1 ele existe, se 0,
		//nao existe, na funcao de exclusao, ter carro que estarao com ativo = 0 e nao aparecerao na listagem
		printf("%s \n",dados.categoria);
		fread(&dados,sizeof(struct ficha),1,arq); //le os dados selecionados
	}
	else {
		puts("ERROR!!");
		fflush(stdin);
		getchar();
	}
	puts("");
	//Fim funcao mostra categorias
}
void ListarCarroCategoria(){
	char categoria[TAM];// variavel categoria para comparar durante a busca e imprimir caso seja condizente
	cabecalho();
	puts("***** LISTA DE CARROS POR CATEGORIA*****\n");
	// listarCategorias();
	listarCategorias();//Funcao lista categorias registradas para facilitar a busca
	puts("Digite a categoria de filmes");
	scanf("%s",&categoria);
	rewind(arq); //posiciona na primeira linha do arquivo, para comecar a busca do comeco
	fread(&dados,sizeof(struct ficha),1,arq);
	if (!ferror(arq)) // se for diferente de erro da funcao ferror
		while (!feof(arq)) //feof informa se chegou ao fim do arquivo, se for diferente entra continua no loop do while
		{
			if (strcmp(dados.categoria, categoria) == 0)// comparando pelo strcmp se for igual, imprime os dados da struct que o cursor esta buscando dados
			printf("Codigo: %d \n Carro: %s: \n Categoria: %s\n Preco: %.2f\n Status: %c\n Ativo: %d \n\n",dados.codigo,dados.carro,dados.categoria,dados.preco,dados.status,dados.ativo);
			fread(&dados,sizeof(struct ficha),1,arq); //fread, retorna um numero inteiro correspondente a quantidade de bytes lidos
		}
	else
		puts("ERROR!!");
	fflush(stdin);
	getchar();
}

void ListarCliente() {
	cabecalho();
	puts("***** LISTA DE Clientes *****\n");
	rewind(arq1); //posiciona na primeira linha do arquivo
	fread(&dados1,sizeof(struct cliente),1,arq1); //le os dados
	if (!ferror(arq1)) //se nao der erro pela funcao ferror
	while (!feof(arq1)) //feof informa se chegou ao fim do arquivo, se for diferente entra continua no loop do while
	{
		printf("Codigo: %d \n Nome: %s \n Idade: %d \n CPF: %s \n Endereco: %s\n Socio: %c\n Ong: %c\n\n",dados1.codigo,dados1.nome,dados1.idade,dados1.cpf,dados1.endereco,dados1.socio,dados1.ong);
		fread(&dados1,sizeof(struct cliente),1,arq1); //le os dados selecionados
	}
	else
		puts("ERROR!!");
	fflush(stdin);
	getchar();
}

void ListarCarro() {
	cabecalho();
	puts("***** LISTA DE CARROS*****\n");
	rewind(arq); //posiciona na primeira linha do arquivo
	fread(&dados,sizeof(struct ficha),1,arq); //le os dados
	if (!ferror(arq)) //se nao der erro pela funcao ferror
	while (!feof(arq)) //feof informa se chegou ao fim do arquivo, se for diferente entra continua no loop do while
	{
		if (dados.ativo)// o if identifica se o valor e verdadeiro automaticamente que e 1, se 1 ele existe, se 0,
		//nao existe, na funcao de exclusao, ter carro que estarao com ativo = 0 e nao aparecerao na listagem
		printf("Codigo: %d \n Carro: %s: \n Placa: %s \n Categoria: %s\n Status: %c\n Ativo: %d \n\n",dados.codigo,dados.carro,dados.placa,dados.categoria,dados.status,dados.ativo);
		fread(&dados,sizeof(struct ficha),1,arq); //le os dados selecionados
	}
	else
		puts("ERROR!!");
	fflush(stdin);
	getchar();
}
void mudaDataSistema(){
	puts("Digite uma nova data para o sistema:");
	printf("Dia: ");
	fflush(stdin);
	scanf("%d", &data_dia[0]);
	printf("Mes: ");
	fflush(stdin);
	scanf("%d", &data_dia[1]);
	printf("Ano: ");
	fflush(stdin);
	scanf("%d", &data_dia[2]);
}


void Menu() {
	cabecalho();
	puts("***** PROGRAMA DE CONTROLE DE LOCADORA *****\n");
	puts("1. Inclusao Carros");
	puts("2. Inclusao Cliente");
	puts("3. Consulta Carros por Codigo");
	//puts("4. Consulta Cliente por Codigo");
	puts("4. Listar Clientes");
	puts("5. Locar um Carro.");
	puts("6. Devolver um Carro.");
	puts("7. Listar Carros");
	puts("8. Consulta Carros por Categoria");
	puts("9. Excluir Carro");
	puts("10. Mudar data do Sitema");
	puts("0. Sair\n");
}

void opcoes() {
	int opcao;
	do {
		//printf("Data do sistema: %d Dia %d Mes %d Ano\n", data_dia[0],data_dia[1],data_dia[2]);
		Menu();
		printf("Selecione uma opcao: ");
		scanf("%d", &opcao);
		switch(opcao)
		//usando switch case, chamamos as funcoes de acordo com as opcoes escolhidas
		{
			case 1: RegistrarCarro(); break;
			case 2: RegistrarCliente(); break;
			case 3: ConsultarCarro(); break;
			case 4: ListarCliente(); break;
			case 5: Locar(); break;
			case 6: DevolucaoCarro(); break;
			case 7: ListarCarro(); break;
			case 8: ListarCarroCategoria();break;
			case 9: ExcluirCarro(); break;
			case 10: mudaDataSistema(); break;
			case 0: puts("Programa finalizado"); break;
			default:
				puts("Opcao Invalida");
		}
	} while (opcao != 0);
	sleep(1000);
}

main() {
	//Atualiza a data do programa
	puts("Digite a data do sistema:");
	printf("Dia: ");
	fflush(stdin);
	scanf("%d", &data_dia[0]);
	printf("Mes: ");
	fflush(stdin);
	scanf("%d", &data_dia[1]);
	printf("Ano: ");
	fflush(stdin);
	scanf("%d", &data_dia[2]);

	system("cls");
	AbrirArquivo("CARROS.DAT");//dentro da funcao AbrirArquivo colocaremos o nome do arquivo, no caso foi CARROS.DAT e deve ter a extensao .DAT
	AbrirArquivo1("CLIENTES.DAT");
	opcoes();
	FecharArquivo();
	FecharArquivo1();
	system("pause");
}
