void printar_menu ( void );

void cadastro_cliente ( int i ); //a variavel i representa a posicao do cliente dentro do vetor de clientes

void pegarCPF ( int i ); //a variavel i representa a posicao do cliente dentro do vetor de clientes
int verificarCPF (char *CPF);
int isDigit(char letra);
int isNumeric(char *string);
int charToInt(char letra);

void pegarTelefone ( int i ); //a variavel i representa a posicao do cliente dentro do vetor de clientes
int verificar_telefone ( int i ); //a variavel i representa a posicao do cliente dentro do vetor de clientes

#include <stdio.h>
#include <string.h>


//CRIACAO DOS REGISTROS 
typedef struct Data{
    int dia;
    int mes;
    int ano;
}tpdata;


typedef struct Telefone{
    int DDD;
    long int numero;
}tptelefone;


typedef struct Cliente{
    char nome[50];
    char CPF[15];
    tptelefone fone;
    tpdata nascimento;
}tpcliente;


typedef struct Investimento{
    int tipo_aplicacao; // 1, 2 ou 3
    char emissor[50]; //banco
    float taxa_anual;
    char ativo; //[S]im ou [N]ao
}tpinvestimento;


typedef struct Transacao{
    int idTransacao;
    tpcliente cliente;
    tpinvestimento investimento;
    tpdata data_aplicacao;
    float valor_aplicacao;
    tpdata data_resgate;
    float valor_resgate;
}tptransacao;


//PROTOTIPOS DAS FUNCOES
void printar_menu ( void );

void cadastro_cliente ( int i ); //a variavel i representa a posicao do cliente dentro do vetor de clientes

void pegarCPF ( int i ); //a variavel i representa a posicao do cliente dentro do vetor de clientes
int verificarCPF (char *CPF);
int isDigit(char letra);
int isNumeric(char *string);
int charToInt(char letra);

void pegarTelefone ( int i ); //a variavel i representa a posicao do cliente dentro do vetor de clientes
int verificar_telefone ( int i ); //a variavel i representa a posicao do cliente dentro do vetor de clientes

void pegarData ( int i ); //a variavel i representa a posicao do cliente dentro do vetor de clientes
int verificar_data ( int i ); //a variavel i representa a posicao do do cliente dentro do vetor de clientes

void cadastro_investimento ( void );
int lista_investimentos ( void );
int quatidade_de_dias_do_investimento ( int ID );

void fazer_extrato ( void );
float lci_lca (float taxa_anual ,int total_dias ,float investimento );
float cdb (float taxa_anual ,int total_dias ,float investimento);
float fundos (float taxa_anual ,int total_dias ,float investimento);

void lista_clientes (void);

void montante ( void );

int ler_cpf (void); 


//VARIAVEIS GLOBAIS
int i=0; //contador da posicao do cliente no vetor, usada apenas para o cadastro
tpcliente cliente[100];
tpinvestimento investimento[30];
int ninvestimentos = 0;
tptransacao transacao[1000];
int ID = 1;

//FUNCAO PRINCIPAL
int main(){
    int loop=0;
    int s=0;
    char cpf[15]; //x para posicao do cliente no cadastro do investimento
    int y=0; //y para posicao para fazer o extrato
    int z=0; //z para posicao do cliente para fazer a aplicacao 
    int intcliente = 0;
    int escolha = 0;
    int Tdias = 0;
    
    do{
        
        //menu
        printar_menu (); // a variavel i representa qual cliente esta sendo cadastrado, ex: Cliente 0, Cliente 1, Cliente 2...
        // 1 para Cadastro de Cliente
        // 2 para Cadastro de Investimentos
        // 3 para Fazer Aplicacao
        // 4 para Extrato de todos os clientes
        // 5 para Montante do banco
        // 6 para Lista de clientes
        // 7 para sair
        
        //switch para executar o que o cliente deseja fazer
        scanf ("%d", &s);
        switch (s) {
        case 1: //caso ele escolha se cadastrar 
        cadastro_cliente ( i );
        i++;
        break;
        
        case 2: //caso ele escolha cadastrar investimento 
        cadastro_investimento ();
        break;
        
        case 3: //caso ele escolha fazer uma aplicacao 
        intcliente = ler_cpf ();
        transacao[ID-1].cliente = cliente[intcliente];
        printf ("\nOlá, cliente %s", cliente[intcliente].CPF);
        printf ("\nO ID da sua transação é : %d\n", ID);
        escolha = lista_investimentos ();
        transacao[ID-1].investimento = investimento[escolha];
        printf ("\nTeste : Seu investimento é no %s", investimento[escolha].emissor);
        printf ("\nDigite a data (xx xx xxxx) que você vai fazer a aplicacao do investimento: ");
        scanf ("%d %d %d", &transacao[ID-1].data_aplicacao.dia, &transacao[ID-1].data_aplicacao.mes, &transacao[ID-1].data_aplicacao.ano);
        printf ("\nQual será o valor investido: ");
        scanf ("%f", &transacao[ID-1].valor_aplicacao);
        transacao[ID-1].idTransacao = ID;
        ID++;
        
        break;
        
        case 4: //caso ele escolha ver o extrato
        fazer_extrato ();
        break;
        
        case 5: //caso escolha ver o montante do banco 
        montante ();
        break;
        
        case 6: //caso escolha ver a lista de todos os clientes 
        lista_clientes ();
        break;
        
        case 7: //caso escolha encerrar o codigo
        return 0;
        break;
        }
        
    }while (loop==0);
} //FIM DA FUNCAO PRINCIPAL


//CRIACAO DAS FUNCOES 

//funcao para leitura e validacao da data de nascimento do cliente--> se for valido retorna 1, se nao, retorna 0
int verificar_data ( int i ) {
    
    printf("\nDigite o dia (xx) que voce nasceu...: ");
    scanf("%d",&cliente[i].nascimento.dia);
    printf("\nDigite o mes (xx) que voce nasceu...: ");
    scanf("%d",&cliente[i].nascimento.mes);
    printf("\nDigite o ano (xx) que voce nasceu...: ");
    scanf("%d",&cliente[i].nascimento.ano);
    
    int x = 0;
    if(cliente[i].nascimento.dia>=1 && cliente[i].nascimento.dia<=30){
        if(cliente[i].nascimento.mes>=1 && cliente[i].nascimento.mes<=12){
            if(cliente[i].nascimento.ano>=1900 && cliente[i].nascimento.ano<=2023){
                x=1;
            }
        }
    }
    return x;
}

//funcao para leitura e validacao do telefone (DDD E NUMERO) do cliente--> se for valido retorna 1, se nao, retorna 0
int verificar_telefone ( int i ) { 
    
    printf("\nDigite o DDD (xx) do telefone...: ");
    scanf("%d",&cliente[i].fone.DDD);
    printf("\nDigite o numero (9xxxxxxxx) do telefone...: ");
    scanf("%ld",&cliente[i].fone.numero);
    int x = 0;
    if ( cliente[i].fone.DDD >11 && cliente[i].fone.DDD < 91 ) {
        if( cliente[i].fone.numero>=10000000 && cliente[i].fone.numero<100000000 || (cliente[i].fone.numero>=900000000 && cliente[i].fone.numero<1000000000 )) {
            x = 1;
        }
    }
    return x;
}

//funcao para validacao do cpf --> se for valido retorna 1, se nao, retorna 0
int verificarCPF (char *CPF){

    int saoTodosIguais = 1;
    for (int a = 1; a < 11; a++)
    {
        if (CPF[0] != CPF[a])
        {
            saoTodosIguais = 0;
            break;
        }
    }
    if (saoTodosIguais)
    {
        return 0;
    }

    int digito = 0;
    for (int v = 10, a = 0; v >= 2; v--, a++)
    {
        digito += charToInt(CPF[a]) * v;
    }
    digito = ((digito * 10) % 11) % 10;
    if (digito + '0' != CPF[9])
    {
        return 0;
        // sair cedo se falhar primeiro dígito
    }
    digito = 0;
    for (int v = 11, a = 0; v >= 2; v--, a++)
    {
        digito += charToInt(CPF[a]) * v;
    }
    digito = ((digito * 10) % 11) % 10;
    if (digito + '0' != CPF[10])
    {
        return 0;
    }

    return 1;
}

//funcao auxiliar da validacao do CPF
int isDigit(char letra){
    if (letra >= '0' && letra <= '9')
    {
        return 1;
    }
    return 0;
}

//funcao auxiliar da validacao do CPF
int isNumeric(char *string){
    for (int a = 0; string[a] != '\0'; a++)
    {
        if (!isDigit(string[a]))
        {
            return 0;
        }
    }
    return 1;
}

//funcao auxiliar da validacao do CPF
int charToInt(char letra){
    // retorna -1 se não é número
    if (!isDigit(letra))
    {
        return -1;
    }
    return letra - '0';
}

//funcao para ler e validar o CPF
void pegarCPF ( int i ){
    int count = 0;
    do{
        if (count > 0){
            printf("CPF invalido!\n");
        }
        printf("\nInsira o CPF (xxxxxxxxxxx) do Cliente...: ");
        fgets(cliente[i].CPF, 15, stdin);
        cliente[i].CPF[strlen(cliente[i].CPF)-1] = '\0';
        count++;
    }while(!verificarCPF(cliente[i].CPF));

}

//funcao para calcular a diferenca em dias entre duas datas quaisquer
int Diferenca_de_dias ( tpdata data_inicial, tpdata data_atual ){
    
    int anof=0;
    int mesf=0;
    int diaf=0;
    int total_dias=0;
    
    anof=data_atual.ano-data_inicial.ano;
    mesf=data_atual.mes-data_inicial.mes;
    diaf=data_atual.dia-data_inicial.dia;
    
    if(diaf<0){
        diaf=30+diaf;
        mesf=mesf-1;
    }
    if(mesf<0){
        mesf=12+mesf;
        anof=anof-1;
    }
    total_dias = (anof*360) + (mesf*30) + (diaf);
    
    return total_dias;
}

//funcao para calcular o imposto de renda
float calcular_valor_imposto_de_renda (int total_dias){
    float x = 0;
    float imposto = 0;
    if(0>total_dias && total_dias<=180){
        x=0.225;
        
    }
    if(180>total_dias && total_dias<=360){
        x=0.20;
        
    }
    if(360>total_dias && total_dias<=720){
        x=0.175;
        
    }
    if(720>total_dias){
        x=0.15;
        
    }
    imposto=x;
    return imposto;
}

//funcao para ler o dia de resgate e calcular o total de dias que durou o investimento
int quatidade_de_dias_do_investimento (  int a ){

    //tptransacao ;
    int dif=0;
    
    //entrada de dados sobre a data de resgate do investimento
    printf("\nDigite o dia (xx) que voce vai retirar o investimento...:");
    scanf("%d",&transacao[a].data_resgate.dia);
    printf("\nDigite o mes (xx) que voce vai retirar o investimento...:");
    scanf("%d",&transacao[a].data_resgate.mes);
    printf("\nDigite o ano (xxxx) que voce vai retirar o investimento...:");
    scanf("%d",&transacao[a].data_resgate.ano);
    
    //calculo da quatidade total de dias que durou o investimento
    dif = Diferenca_de_dias ( transacao[a].data_aplicacao, transacao[a].data_resgate );
    return dif;
}

//funcoes para calcular impostos, taxas, lucro e valor a ser resgatado para cada investimento:

//funcao para calcular lCI/LCA
float lci_lca (float taxa_anual ,int total_dias ,float investimento ){
    float taxa_diario1 = 0, 
          taxa_investimento = 0, 
          quantia_que_lucrou = 0, 
          quantia_soma = 0,
          taxatotal= 0;
    taxa_diario1 = taxa_anual / 100.0;
    taxatotal = taxa_diario1 / 360.0;
    quantia_soma  = taxatotal * total_dias * investimento;
    quantia_que_lucrou = quantia_soma + investimento;
    
    return quantia_que_lucrou;
}

//funcao para calcular CDB
float cdb (float taxa_anual ,int total_dias ,float investimento){
    float taxa_diario1 = 0, 
          taxa_investimento = 0, 
          quantia_que_lucrou = 0, 
          quantia_soma = 0, 
          deducao_imposto = 0,
          imposto = 0,
          TOTAL = 0;
          
    taxa_diario1 = (taxa_anual /100) / 360;
    quantia_soma  = (taxa_diario1 * total_dias) * investimento;
    imposto = calcular_valor_imposto_de_renda ( total_dias);
    deducao_imposto = quantia_soma * imposto;
    quantia_que_lucrou = quantia_soma - deducao_imposto;
    TOTAL = quantia_que_lucrou + investimento;
    
    return TOTAL;
}

//funcao para calcular fundos
float fundos (float taxa_anual ,int total_dias ,float investimento){
    float taxa_diario1 = 0, 
          taxa_investimento = 0, 
          quantia_que_lucrou = 0, 
          quantia_soma = 0, 
          quantia_que_lucrou_fundos = 0, 
          deducao_imposto = 0,
          impostos_Fundos = 0,
          imposto = 0,
          TOTAL = 0;
          
    impostos_Fundos = (1 / 360 ) * total_dias;
    taxa_diario1 = (taxa_anual /100) / 360;
    quantia_soma  = (taxa_diario1 * total_dias) * investimento;
    imposto = calcular_valor_imposto_de_renda ( total_dias);
    deducao_imposto = quantia_soma * imposto * impostos_Fundos;
    quantia_que_lucrou = deducao_imposto - investimento;
    TOTAL = quantia_que_lucrou + investimento;
    
    return TOTAL;
}

//funcao para printar o menu de opcoes
void printar_menu ( void ){
    printf ("\n***************************************************\n");
    printf ("           O QUE DESEJA FAZER?\n           ");
    if( i>0 ){
        printf ("\nDigite 1 para Cadastro do proximo Cliente\n");
    }
    else{
        printf ("\nDigite 1 para Cadastro do Cliente\n");
    }
    printf ("Digite 2 para Cadastro de Investimentos\n");
    printf ("Digite 3 para Fazer uma Aplicacao\n");
    printf ("Digite 4 para mostrar o Extrato do Cliente\n");
    printf ("Digite 5 para mostrar o Montante dos Investimentos\n");
    printf ("Digite 6 para mostrar a Lista de Clientes\n");
    printf ("Digite 7 para sair\n");
    printf ("***************************************************\n");
}

//funcao para fazer o cadastro do Cliente
void cadastro_cliente ( int i ){
    int xnasci = 2;
    // nome
    getchar();
    printf("***************************************************\n");
    printf("Digite o nome do Cliente...: ");
    fgets ( cliente[i].nome , 50 , stdin );
    cliente[i].nome[ strlen(cliente[i].nome) -1 ] = '\0';
            
    // cpf
    pegarCPF( i );
            
    // telefone
    pegarTelefone ( i );
            
    // nascimento
    pegarData ( i );
    
    printf("\n***************************************************\n\n");
    printf("             Parabéns, cadastro concluído!            \n");
}

//funcao para fazer o cadastro de um investimento
void cadastro_investimento ( void ){
    
    printf ("\n***************************************************\n");
    printf ("\n          Qual o tipo do seu investimento?         \n");
    printf ("Digite 1 para LCI/LCA\n");
    printf ("Digite 2 para CDB\n");
    printf ("Digite 3 para FUNDOS\n");
    printf ("\nDigite aqui...: ");
    scanf ("%d",&investimento[ninvestimentos].tipo_aplicacao);
            
    switch ( investimento[ninvestimentos].tipo_aplicacao ){
        
        case 1: //se for LCI
        printf("Digite do nome do banco emissor...: ");
        getchar();
        fgets(investimento[ninvestimentos].emissor, 50, stdin );
        investimento[ninvestimentos].emissor[strlen(investimento[ninvestimentos].emissor)-1]='\0';
        printf("\n\nDigite a taxa anual...: ");
        scanf("%f",&investimento[ninvestimentos].taxa_anual);
        getchar();
        printf("\n\nDigite S se for ativo ou digite N se nao for ativo...: ");
        getchar();
        scanf("%c",&investimento[ninvestimentos].ativo);
        break;
                
        case 2: //se for CDB
        printf("Digite do nome do banco emissor...: ");
        getchar();
        fgets(investimento[ninvestimentos].emissor, 50, stdin );
        investimento[ninvestimentos].emissor[strlen(investimento[ninvestimentos].emissor)-1]='\0';
        printf("\n\nDigite a taxa anual...: ");
        scanf("%f",&investimento[ninvestimentos].taxa_anual);
        getchar();
        printf("\n\nDigite S se for ativo ou digite N se nao for ativo...: ");
        getchar();
        scanf("%c",&investimento[ninvestimentos].ativo);
        break;
                
        case 3: //se for fundos
        printf("Digite do nome do banco emissor...: ");
        getchar();
        fgets(investimento[ninvestimentos].emissor, 50, stdin );
        investimento[ninvestimentos].emissor[strlen(investimento[ninvestimentos].emissor)-1]='\0';
        printf("\n\nDigite a taxa anual...: ");
        scanf("%f",&investimento[ninvestimentos].taxa_anual);
        getchar();
        printf("\n\nDigite S se for ativo ou digite N se nao for ativo...: ");
        scanf("%c",&investimento[ninvestimentos].ativo);
        getchar();
        break;
    }
    ninvestimentos++;
}

//funcao para verificar o telefone ate que esteja correto
void pegarTelefone ( int i ){
    int count = 0;
    do{
        if (count > 0){
            printf("Telefone invalido!\n");
        }
        count++;
    }while(!verificar_telefone ( i ) );

}

//funcao para verificar a data ate que esteja correto
void pegarData ( int i ) {
    int count = 0;
    do{
        if (count > 0){
            printf ("Data Inválida!\n");
        }
        count++;
    } while ( !verificar_data ( i ));
}

//funcao par fazer o extrato de um cliente
void fazer_extrato () {
    int posicao = 0,
        a = 0,
        cont = 0,
        tdias = 0;
    float tlci = 0,
          tcdb = 0,
          tfundos = 0;
    
    posicao = ler_cpf ();
    
    //apresentacao da lista de investimentos disponiveis para o cliente escolher
    printf ("\n*******************************************\n");
    printf ("            LISTA DE INVESTIMETOS            \n");

    for ( cont = 0 ; cont <= transacao[ID-1].idTransacao ; cont++ ) {
        if (strcmp(transacao[cont].cliente.CPF, cliente[posicao].CPF) == 0) {
            printf ("%d. Banco: %s Tipo: %s  Capital inicial: %.1f\n", transacao[cont].idTransacao, transacao[cont].investimento.emissor, transacao[cont].investimento.tipo_aplicacao==1?"LCI/LCA":( transacao[cont].investimento.tipo_aplicacao==2?"CDB":"FUNDOS") ,transacao[cont].valor_aplicacao);
        }
    }
    
    //aqui ele escolhe em qual dos investimentos ele vai querer fazer uma transacao
    printf("\nDigite o ID da transacao...: ");
    scanf("%d",&a);
    a = a-1;
    
    //calculo do total de dias
    tdias = quatidade_de_dias_do_investimento ( a );
    if ( transacao[a].investimento.tipo_aplicacao == 1 ) {
        tlci = lci_lca ( transacao[a].investimento.taxa_anual , tdias , transacao[a].valor_aplicacao );
        printf ("\nO valor de retirada é %.2f", tlci);
    } else {
        if ( transacao[a].investimento.tipo_aplicacao == 2 ) {
            tcdb = cdb ( transacao[a].investimento.taxa_anual , tdias , transacao[a].valor_aplicacao);
            printf ("O valor de retirada é %.2f", tcdb);
        } else {
            tfundos = fundos ( transacao[a].investimento.taxa_anual , tdias , transacao[a].valor_aplicacao);
            printf ("O valor de retirada é %.2f", tfundos);
        }
    }
}

//funcao para apresentar a lista de clientes
void lista_clientes (void) {
    int k=0;
    // Ordenar os clientes por CPF
    for (int k = 1; k < i; k++) {
        tpcliente temp = cliente[k];
        int j = k - 1;
        while (j >= 0 && strcmp(cliente[j].nome, temp.nome) > 0) {
            cliente[j + 1] = cliente[j];
            j--;
        }
        cliente[j + 1] = temp;
    }

    // Imprimir os clientes ordenados
    printf("Lista de clientes ordenados por CPF:\n");
    for (int k = 0; k < i; k++) {
        printf("\n***************************************************\n");
        printf("Cliente %d\n", k + 1);
        printf("Nome: %s\n", cliente[k].nome);
        printf("CPF: %s\n", cliente[k].CPF);
        printf("Telefone: (%d) %ld\n", cliente[k].fone.DDD, cliente[k].fone.numero);
        printf("Data de Nascimento: %d/%d/%d", cliente[k].nascimento.dia, cliente[k].nascimento.mes, cliente[k].nascimento.ano);
        printf("\n***************************************************\n");
    }
}

//funcao para ler o CPF para identificacao do usuario
int ler_cpf (void){
    char comparacao[15];
    int cont=0;
    printf("Digite seu CPF (xxxxxxxxxxx) para identificacao...: ");
    getchar();
    fgets(comparacao, 15, stdin);
    comparacao[strlen(comparacao)-1]='\0';
    while(cont<i){
        if(strcmp(comparacao,cliente[cont].CPF)==0){
            return cont;
        }
        cont++;
    }
}

//funcao para apresentar a lista de todos os investimentos cadastrados 
int lista_investimentos ( void ) {
    int cont = 0,
        escolha = 0,
        TIPO = 0,
        intretorno = 0;
    
    printf ("\n***************************************************\n");
    printf ("\nTipos de investimento\n");
    printf ("1. LCI/LCA\n");
    printf ("2. CDB\n");
    printf ("3. FUNDOS\n");
    printf ("\nEscolha um tipo de investimento: \n");
    scanf("%d", &TIPO);
    printf ("\n*******************************************\n");
    printf ("            LISTA DE INVESTIMETOS            \n");
    for ( cont = 0 ; cont <= ninvestimentos ; cont++ ) {
        if ( TIPO == investimento[cont].tipo_aplicacao) {
            printf ("%d.%s %.1f\n", cont+1, investimento[cont].emissor, investimento[cont].taxa_anual);
        }    
    }
    printf ("\nEscolha um investimento: ");
    scanf("%d", &escolha);
    intretorno = escolha - 1;
return intretorno;
}

//funcao para apresentar o montante dos bancos para cada tipo de investimento
void montante () {
    int TIPO = 0,
        cont = 0;
    float soma = 0;
    
    printf ("\n***************************************************\n");
    printf ("\nTipos de investimento\n");
    printf ("1. LCI/LCA\n");
    printf ("2. CDB\n");
    printf ("3. FUNDOS\n");
    printf ("\nDigite o numero do tipo de investimento que deseja fazer: \n");
    scanf("%d", &TIPO);
    for ( cont = 0 ; cont < ninvestimentos ; cont++ ) {
        if ( TIPO == investimento[cont].tipo_aplicacao) {
            soma += transacao[cont].valor_aplicacao;
        }
    printf ("%s %.2f\n", investimento[cont].emissor, soma);   
    }
}