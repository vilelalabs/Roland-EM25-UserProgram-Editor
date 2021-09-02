#ifndef _MANIPULA_ARQUIVO_FINAL_H_
#define _MANIPULA_ARQUIVO_FINAL_H_

int SalvaArquivo(DADO *dados, AnsiString nome_arq)
{
    FILE *arquivo;
    char *str;  // str = nome do arquivo recebido do SaveDialog

    /* converte AnsiString em *char[] */
    str = nome_arq.c_str();

	if (!(arquivo = fopen(str,"wb")))  /* Caso ocorra algum erro na abertura do arquivo..*/
  	{                                  /* a função manda mensagem e aborta*/
        ShowMessage("Erro ao criar o novo arquivo!");
        return 0;
  	}

    for(int i = 0; i<640; i++)
        fprintf(arquivo,"%c",dados[i]);       //salva no arquivo byte a byte


    fclose(arquivo); // fecha arquivo lido

    //Debug
    //[DEBUG] ShowMessage("Arquivo Salvo com Sucesso");
    return 1;
}

//--------------------------------------------------------------------------------
int CarregaArquivo(DADO *dados, AnsiString nome_arq)
{
    FILE *arquivo;
    char *str;  // str = nome do arquivo recebido do SaveDialog

    /* converte AnsiString em *char[] */
    str = nome_arq.c_str();

	if (!(arquivo = fopen(str,"rb")))  /* Caso ocorra algum erro na abertura do arquivo..*/
  	{                                  /* a função manda mensagem e aborta*/
        //ShowMessage("Erro ao criar o novo arquivo!");
        return 0; //retorna sem fazer nada
  	}

    for(int i = 0; i<640; i++)
        fscanf(arquivo,"%c",&dados[i]);       //salva no arquivo byte a byte


    fclose(arquivo); // fecha arquivo lido

    //Debug
    //[DEBUG] ShowMessage("Arquivo Carregado com Sucesso");

    return 1;
}

#endif
