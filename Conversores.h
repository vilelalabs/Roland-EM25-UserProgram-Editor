#ifndef _CONVERSORES_H_
#define _CONVERSORES_H_


/*função que junta as matrizes menores formando a
                          matriz de 640 Bytes para inserir no arquivo final  */

/*void CarregaArquivoTotal(DADO &uspr1, DADO &uspr2, DADO &uspr3, DADO &uspr4,
                         DADO &uspr5, DADO &uspr6, DADO &uspr7, DADO &uspr8,
                         DADO &arquivo_de_saida); // & ou * ???  */

//////////////////////////////////////////////////////////////////////////////////////////
/////// Funções para bytes específicos que necessitam de cálculos mais complexos /////////
//////////////////////////////////////////////////////////////////////////////////////////

// função retorna o valor a ser inserido neste byte (58) resposável
                                                //por ligar e desligar os UPPERs UP1 e UP2
DADO calcula_byte_58(bool up1on, bool up2on);
void retorna_byte_58(DADO byte58, bool *up1on, bool *up2on);

//Calcula o valor final para [61], define oitavas de UP1, UP2 e LWR
DADO calcula_byte_61(DADO up1o,DADO up2o,DADO lwro);
void retorna_byte_61(DADO byte61, DADO *up1o,DADO *up2o,DADO *lwro);

//Calcula o valor final para [77], define valores de layer p/ UP2 e Int e Mem p/ LWR  e a função inversa
DADO calcula_byte_77(DADO up2ls, bool lwrint, bool lwrmem);
void retorna_byte_77(DADO byte77, DADO *up2ls, bool *lwrint, bool *lwrmem);

//Calcula o valor final para [78], define se é Lower ou MDrums que está ativado e função inversa
DADO calcula_byte_78(bool lwr_on, bool mdrums_on);
void retorna_byte_78(DADO byte78, bool *lwr_on, bool *mdrums_on);

//Calcula o valor final para [79], define combinações p/ ligar os efeitos  MBassSw, Transp.e K. Vel. e função inversa
DADO calcula_byte_79(bool key_on, bool tr_on, bool mb_on);
void retorna_byte_79(DADO byte79, bool *key_on, bool *tr_on, bool *mb_on);

// inverso das 4 funções de bytes acima: retornam para as variáveis de acordo com o valor do bit





/////////////////////////////////////////////////////////////////////////////////
/////////////////////// FUNÇÃO PRINCIPAL PARA SAVE //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*  coleta todos os dados da tab e faz o processamento, dando retorno  //
//  no ponteiro de matriz "*retorno", ultimo parâmetro da função)      */

void coleta_dados(
/*GroupGeral*/
    bool key_vel_on, DADO tempo, bool transp_on,
    DADO transp_value, bool reverb_on, DADO reverb_value,
    bool chorus_on, DADO chorus_value,
/*GroupUppers*/
    bool up1_on, DADO up1_tone, DADO up1_vol, DADO up1_oct,
    bool up2_on, DADO up2_tone, DADO up2_vol, DADO up2_oct,
    DADO up2_state,
/*GroupLower*/
    bool lower_actv, DADO lower_tone, DADO lower_vol,
    DADO lower_oct,DADO lower_split, bool lower_int,
    bool lower_mem,
/*Group MBass/MDrums*/
    bool mbass_on, DADO mbass_tone, DADO mbass_vol,
    bool mdrums_on, DADO mdrums_kit,
/* Variável que recebe o resultado final com os valores convertidos:*/
    DADO *retorno)
{

    DADO vetor[80];

    vetor[0]  = up1_vol;
    vetor[1]  = up2_vol;
    vetor[2]  = lower_vol;
    vetor[3]  = mbass_vol;
    vetor[4]  = BYTE_PADRAO_04;
    vetor[5]  = BYTE_PADRAO_05;
    vetor[6]  = BYTE_PADRAO_06;

    for(int i = 7;i<=12;i++) vetor[i]  = BYTE_PADRAO_07_A_12;

    vetor[13] = BYTE_PADRAO_13;
    vetor[14] = reverb_value;
    vetor[15] = chorus_value;

    if(chorus_on) vetor[16] = 50; else vetor[16] = 0; //chorus

    vetor[17] = BYTE_PADRAO_17;
    vetor[18] = BYTE_PADRAO_18;
    vetor[19] = BYTE_PADRAO_19;

    if(reverb_on) vetor[20] = 64; else vetor[20] = 0; //reverb

    for(int i = 21;i<=37;i++) vetor[i]  = BYTE_PADRAO_21_A_37;

    vetor[38] = up1_tone;
    vetor[39] = BYTE_PADRAO_39;
    vetor[40] = up2_tone;
    vetor[41] = BYTE_PADRAO_41;
    vetor[42] = lower_tone;
    vetor[43] = BYTE_PADRAO_43;
    vetor[44] = mbass_tone;
    vetor[45] = BYTE_PADRAO_45;
    vetor[46] = mdrums_kit;
    vetor[47] = BYTE_PADRAO_47;
    vetor[48] = BYTE_PADRAO_48;
    vetor[49] = BYTE_PADRAO_49;
    vetor[50] = BYTE_PADRAO_50;
    vetor[51] = tempo;
    vetor[52] = BYTE_PADRAO_52;
    vetor[53] = BYTE_PADRAO_53;
    vetor[54] = BYTE_PADRAO_54;
    vetor[55] = BYTE_PADRAO_55;
    vetor[56] = transp_value;
    vetor[57] = BYTE_PADRAO_57;
    vetor[58] = calcula_byte_58(up1_on,up2_on);
    vetor[59] = BYTE_PADRAO_59;
    vetor[60] = BYTE_PADRAO_60;
    vetor[61] = calcula_byte_61(up1_oct, up2_oct, lower_oct);

    for(int i = 62;i<=73;i++) vetor[i]  = BYTE_PADRAO_62_A_73;

    vetor[74] = BYTE_PADRAO_74;
    vetor[75] = lower_split;
    vetor[76] = BYTE_PADRAO_76;
    vetor[77] = calcula_byte_77(up2_state, lower_int, lower_mem);
    vetor[78] = calcula_byte_78(lower_actv, mdrums_on);
    vetor[79] = calcula_byte_79(key_vel_on, transp_on, mbass_on);

    for(int i=0; i<80; i++)  retorno[i] = vetor[i];

}
///////////////////////////////////////////////////////////////////////////////////
////////////////// FIM DA FUNÇÃO PRINCIPAL DE SAVE/////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


                      /*****************************/

/////////////////////////////////////////////////////////////////////////////////
/////////////////////// FUNÇÃO PRINCIPAL PARA LOAD //////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*  coleta todos os dados da tab e faz o processamento, dando retorno  //
//  no ponteiro de matriz "*retorno", ultimo parâmetro da função)      */

void coleta_bytes(
/* Matriz da qual vem os dados*/
    DADO *entrada,

/*GroupGeral*/
    bool *key_vel_on, DADO *tempo, bool *transp_on,
    DADO *transp_value, bool *reverb_on, DADO *reverb_value,
    bool *chorus_on, DADO *chorus_value,
/*GroupUppers*/
    bool *up1_on, DADO *up1_tone, DADO *up1_vol, DADO *up1_oct,
    bool *up2_on, DADO *up2_tone, DADO *up2_vol, DADO *up2_oct,
    DADO *up2_state,
/*GroupLower*/
    bool *lower_actv, DADO *lower_tone, DADO *lower_vol,
    DADO *lower_oct,DADO *lower_split, bool *lower_int,
    bool *lower_mem,
/*Group MBass/MDrums*/
    bool *mbass_on, DADO *mbass_tone, DADO *mbass_vol,
    bool *mdrums_on, DADO *mdrums_kit
    )
{

    DADO vetor[80]; //ok

    for(int i=0; i<80; i++)  vetor[i] = entrada[i]; //ok

    *up1_vol   = vetor[0];
    *up2_vol   = vetor[1];
    *lower_vol = vetor[2];
    *mbass_vol = vetor[3];

    *reverb_value = vetor[14];
    *chorus_value = vetor[15];

    if(vetor[16] == (DADO)50) *chorus_on = true; else *chorus_on = false; //chorus

    if(vetor[20] == (DADO)64) *reverb_on = true; else *reverb_on = false; //reverb

    *up1_tone = vetor[38]; // na hora de passar para  Form, converter de unsigned char para signed char e carregar a lista com "1=A11 Piano..."
    *up2_tone = vetor[40];
    *lower_tone = vetor[42];
    *mbass_tone = vetor[44];
    *mdrums_kit = vetor[46];

    *tempo = vetor[51]; // também converter de unsigned (DADO) para signed (signed char);

    *transp_value = vetor[56];

    retorna_byte_58(vetor[58],up1_on,up2_on);

    retorna_byte_61(vetor[61],up1_oct, up2_oct, lower_oct);

    *lower_split = vetor[75];

    retorna_byte_77(vetor[77], up2_state, lower_int, lower_mem);
    retorna_byte_78(vetor[78], lower_actv, mdrums_on);
    retorna_byte_79(vetor[79], key_vel_on, transp_on, mbass_on);

}
///////////////////////////////////////////////////////////////////////////////////
////////////////// FIM DA FUNÇÃO PRINCIPAL DE LOAD/////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


///////////////// IMPLEMENTAÇÃO DAS FUNÇÕES PROTOTIPADAS NO INICIO ////////////////////
/*///////////////////////////////////////////////////////////////////////////////////*/
// função retorna o valor a ser inserido neste byte (58) resposável
//por ligar e desligar os UPPERs UP1 e UP2
DADO calcula_byte_58(bool up1on, bool up2on)
{
   int val = -81;

   if(up1on) val += 16 ;

   if(up2on) val += 64 ;

   return DADO(val);
}

//-------------------------------------------------------------------------------------
//função inversa para o byte 58, retornamos os dados para "reconstruir" o Form
void retorna_byte_58(DADO byte58, bool *up1on, bool *up2on)
{
    if(byte58 == -81)       { *up1on = false; *up2on = false; }
    else if(byte58 == -17)  { *up1on = false; *up2on = true;  }
    else if(byte58 == -65)  { *up1on = true;  *up2on = false; }
    else                    { *up1on = true;  *up2on = true;  }

}

/*///////////////////////////////////////////////////////////////////////////////////*/
//Calcula o valor final para [61], define oitavas de UP1, UP2 e LWR
DADO calcula_byte_61(DADO up1o,DADO up2o,DADO lwro)
{
    int val = 64;   //  valor se todos -1 OCTAVE

    //abaixo, para cada variável que tenha valor 0 OCTAVE, acrescenta-se um valor à
    // variável que será retornada (val), e o dobro do mesmo valor para +1 OCTAVE
    if(up1o == 0) val+=1;
    else if(up1o == 1) val+=2;

    if(up2o == 0) val+=4;
    else if(up2o == 1) val+=8;


    if(lwro == 0) val+=16;
    else if(lwro == 1) val+=32;

    return Shortint(val);
}

//-------------------------------------------------------------------------------------
//função inversa para o byte 61, retornamos os dados para "reconstruir" o Form
void retorna_byte_61(DADO byte61, DADO *up1o,DADO *up2o,DADO *lwro)
{
    DADO val = (DADO)(byte61 -64);


    if(val >= 32)       {*lwro = 1; val -=(DADO)32;}
    else if (val >=16)  {*lwro = 0; val -=(DADO)16;}
    else                 *lwro = -1;

    if(val >= 8)       {*up2o = 1; val -=(DADO)8;}
    else if (val >=4)  {*up2o = 0; val -=(DADO)4;}
    else                *up2o = -1;

    if(val >= 2)       {*up1o = 1; val -=(DADO)2;}
    else if (val >=1)  {*up1o = 0; val -=(DADO)1;}
    else                *up1o = -1;

    return;
}


/*///////////////////////////////////////////////////////////////////////////////////*/
//Calcula o valor final para [77], define valores de layer p/ UP2 e Int e Mem p/ LWR
DADO calcula_byte_77(DADO up2ls, bool lwrint, bool lwrmem)
{
    int val = 1;

    if(lwrint) val += 16;

    if(lwrmem) val += 32;

    if(up2ls == UP2_MEL_INT) val += 128;
    else if(up2ls == UP2_LAYER) val += 64;

    return DADO(val);
}
//-------------------------------------------------------------------------------------

//faz função inversa, converte o byte 77 em dados ue podem ser usados para "reconstruir" o Form.
void retorna_byte_77(DADO byte77, DADO *up2ls, bool *lwrint, bool *lwrmem)
{
    // define up2-layer
    DADO val = byte77;

    //ShowMessage(val);// -  DEBUG

     if(val <= (DADO)-79)
     {
        *up2ls = (DADO)UP2_MEL_INT;    // na hora de passar p/ form verificar o valor e ativar o
                                // RadioButton correspondente
        val += (DADO)128;
     }
     else if(val >= (DADO)64 )    // valoers maiores que 128 sempre são maiores que 64
     {                          // porem só entra neste 'if' se já não for > que 128
        *up2ls = (DADO)UP2_LAYER;
        val -= (DADO)64;
     }
     else
        *up2ls = (DADO)UP2_DESATIVADO;

     //ShowMessage(val);// -  DEBUG

     //define LOWER MEMORY

     if (val >= (DADO)32)
     {
        *lwrmem = true;
        //ShowMessage("lower mem"); -  DEBUG
        val -= (DADO)32;
     }
     else
       *lwrmem = false;

     //define LOWER INTELLIGENCE

     if (val >= (DADO)16)
     {
        *lwrint = true;
        //ShowMessage("lower int") -  DEBUG
        val -= (DADO)16;
     }
     else
       *lwrint = false;

     //ShowMessage(val);// -  DEBUG
    return ;
}

/*///////////////////////////////////////////////////////////////////////////////////*/
//Calcula o valor final para [78], define se é Lower ou MDrums que está ativado;
DADO calcula_byte_78(bool lwr_on, bool mdrums_on)
{
    if(lwr_on)          return DADO(2);
    else if (mdrums_on) return DADO(4);
    else                return 0;
}

//-------------------------------------------------------------------------------------
//função inversa para o byte 78, retornamos os dados para "reconstruir" o Form
void retorna_byte_78(DADO byte78, bool *lwr_on, bool *mdrums_on)
{
    if(byte78 == 2)         { *lwr_on = true;  *mdrums_on = false; }
    else if (byte78 == 4)   { *lwr_on = false; *mdrums_on = true;  }
    else                    { *lwr_on = false; *mdrums_on = false; }

}

/*///////////////////////////////////////////////////////////////////////////////////*/

//Calcula o valor final para [79], define comb.
// p/ ligar os efeitos  MBassSw, Transp.e K. Vel.
DADO calcula_byte_79(bool key_on, bool tr_on, bool mb_on)
{
    int val = 0;

    if(key_on) val += 1;

    if(tr_on) val +=2;

    if(mb_on) val +=16;

    return DADO(val);
}

//-------------------------------------------------------------------------------------
//função inversa para o byte 79, retornamos os dados para "reconstruir" o Form

void retorna_byte_79(DADO byte79, bool *key_on, bool *tr_on, bool *mb_on)
{
    int val = byte79;

    if(val >= 16) {*mb_on = true;  val -=16;} else *mb_on = false;

    if(val >= 2)  {*tr_on = true;  val -=2; } else *tr_on = false;

    if(val)       {*key_on = true; val -=1; } else *key_on = false;

    return;
}


/*///////////////////////////////////////////////////////////////////////////////////*/

void SalvaArquivoTotal(DADO *uspr1, DADO *uspr2, DADO *uspr3, DADO *uspr4,
                         DADO *uspr5, DADO *uspr6, DADO *uspr7, DADO *uspr8,
                         DADO *arquivo_de_saida)
{
    int i;
    const int tam = 80; //tamanho de cada "sub-matriz"

    for(i=0;i<640;i++)
    {
        if(i<tam)           arquivo_de_saida[i] = uspr1[i];
        else if (i<tam*2)   arquivo_de_saida[i] = uspr2[i-tam];
        else if (i<tam*3)   arquivo_de_saida[i] = uspr3[i-tam*2];
        else if (i<tam*4)   arquivo_de_saida[i] = uspr4[i-tam*3];
        else if (i<tam*5)   arquivo_de_saida[i] = uspr5[i-tam*4];
        else if (i<tam*6)   arquivo_de_saida[i] = uspr6[i-tam*5];
        else if (i<tam*7)   arquivo_de_saida[i] = uspr7[i-tam*6];
        else if (i<tam*8)   arquivo_de_saida[i] = uspr8[i-tam*7];

        //ShowMessage("tam = " + (String)tam + "\n\ni = " + (String)i + "\n\ni-tam = " + (String)(i-tam));
    }
    return;
}

//----------------------------------------------------------------------------------------

void CarregaArquivoTotal(DADO *arquivo_de_entrada, DADO *uspr1, DADO *uspr2, DADO *uspr3, DADO *uspr4,
                         DADO *uspr5, DADO *uspr6, DADO *uspr7, DADO *uspr8)
{
    int i;
    const int tam = 80; //tamanho de cada "sub-matriz"


    for(i=0;i<640;i++)
    {
        if(i<tam)           uspr1[i]       = arquivo_de_entrada[i];
        else if (i<tam*2)   uspr2[i-tam]   = arquivo_de_entrada[i];
        else if (i<tam*3)   uspr3[i-tam*2] = arquivo_de_entrada[i];
        else if (i<tam*4)   uspr4[i-tam*3] = arquivo_de_entrada[i];
        else if (i<tam*5)   uspr5[i-tam*4] = arquivo_de_entrada[i];
        else if (i<tam*6)   uspr6[i-tam*5] = arquivo_de_entrada[i];
        else if (i<tam*7)   uspr7[i-tam*6] = arquivo_de_entrada[i];
        else if (i<tam*8)   uspr8[i-tam*7] = arquivo_de_entrada[i];
    }
    return;
}



#endif