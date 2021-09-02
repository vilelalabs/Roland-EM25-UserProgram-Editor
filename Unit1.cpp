//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

/******************************************************************************/
/*********** INICIALIZAÇÕES PERSONALIZADAS & VARIÁVEIS GLOBAIS ****************/

////Bibliotecas Antigas para Salvar e Carregar o Arquivo Binário////////////////
#include <iostream.h>                                           ////////////////
#include <stdlib.h>                                             ////////////////
#include <stdio.h>                                              ////////////////
using namespace std;                                            ////////////////
////////////////////////////////////////////////////////////////////////////////

typedef Shortint DADO; // cria tipo de dados DADO, (signed char)
// constantes para uso da função "void __fastcall matriz_para_uspr();"

#define USER_ALL 0     // todos user programs
#define USER_P_1 1     // apenas uspr 1,
#define USER_P_2 2     // apenas uspr 2, etc...
#define USER_P_3 3
#define USER_P_4 4
#define USER_P_5 5
#define USER_P_6 6
#define USER_P_7 7
#define USER_P_8 8

//Constantes para uso do Layer/ Mel. Int do Upper 2 (Conversores.h usam essas variaveis também)
#define UP2_DESATIVADO 0
#define UP2_MEL_INT    1
#define UP2_LAYER      2

#include "BytesPadroes.h"           //Bytes inseridos diretamente na matriz final para preencher as lacunas
                                    // de dados "não-importante" para está aplicação

#include "ListasEM25.h"             //Listas "enum" e definições de valores Rev, Chr etc...

#include "Conversores.h"            //Função que converte dados do Formulário nos valores
                                    // nos valores a serem gravados no arquivo final

#include "ManipulaArquivoFinal.h"   // Diminui código "antigo" neste Unit1.cpp inserindo funcções facilitadas
                                    // para salvar os arquivos em formato binário

////////////////////////////////Variaveis Globais///////////////////////////////

// guardarão o estado inicial de UPPER2, Desativado, Melodia inteligente ou Layer

DADO up2state_1 = UP2_DESATIVADO,up2state_2 = UP2_DESATIVADO,up2state_3 = UP2_DESATIVADO,
     up2state_4 = UP2_DESATIVADO, up2state_5 = UP2_DESATIVADO,up2state_6 = UP2_DESATIVADO,
     up2state_7 = UP2_DESATIVADO,up2state_8 = UP2_DESATIVADO;

    DADO USPR_1[80]; //  Estas Matrizes Armazenam dados dos UserPrograms
    DADO USPR_2[80]; //  individualmente. Para inserir no arquivo final,
    DADO USPR_3[80]; //  deve-se carregá-los sequencialmente em um Array
    DADO USPR_4[80]; //  ou diretamente no arquivo.
    DADO USPR_5[80]; //
    DADO USPR_6[80]; //
    DADO USPR_7[80]; //
    DADO USPR_8[80]; //

    DADO USPRL_1[80]; //  <> Do mesmo modo que as anteriores, porem representam
    DADO USPRL_2[80]; //       arquivos carregados para serem transferidos ao Form.
    DADO USPRL_3[80]; //  <> usado para operações inversas às realizadas com
    DADO USPRL_4[80]; //       as variaveis acima.
    DADO USPRL_5[80]; //  <> formato do nome USPR(L)OAD_X
    DADO USPRL_6[80]; //
    DADO USPRL_7[80]; //
    DADO USPRL_8[80]; //

    DADO USPR_NEW[80]; // <> durante toda a execução contém o USPR Inicial, para carregar nos
                       // <> outros USPRs quando clicado em [NEW] no menu principal
                       // <> Usado também para a opção USPR Reset do menu Editar

    DADO USPR_MEM[80]; // Usado para procedimentos Copiar->Colar , usado como "ClipBoard"


    int tabfocus = 1;   // verifica qual a Tab aberta atualmente
                        // para auxiliar nas funções de copiar e colar


// variáveis utilizadas para troca de linguagem nas mensagens gerais de saída e avisos

//  <<criar variáveis>>
    String msg_sair = MSG_SAIR_ENG;
    String msg_transp = MSG_TRANSP_ENG;
    String msg_novo = MSG_NOVO_ENG;
    String msg_about = MSG_ABOUT_ENG;
    String msg_open_err = MSG_OPEN_ENG;
    String msg_sobreescrever = MSG_SOBREESCREVER_ENG;
// as mensagens "constantes" estão contidas no arquivo "ListasEM25.h"


// funções extras utilizadas - declaradas no arquivo "Unit.h" em "public declarations"
    //void matriz_para_uspr();
    //void CorrigeTempos();

/******************************************************************************/
/******************************************************************************/

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPrincipal *FormPrincipal;
//---------------------------------------------------------------------------
__fastcall TFormPrincipal::TFormPrincipal(TComponent* Owner)
    : TForm(Owner)
{
/****************************************************************************/
/*****Carrega Lista de Sons em todos os Combos de todos os User Programs****/
/****************************************************************************/

    //Upper1//
    ComboUP1_1->Items->LoadFromFile("_tonelist.dat");
    ComboUP1_2->Items->LoadFromFile("_tonelist.dat");
    ComboUP1_3->Items->LoadFromFile("_tonelist.dat");
    ComboUP1_4->Items->LoadFromFile("_tonelist.dat");
    ComboUP1_5->Items->LoadFromFile("_tonelist.dat");
    ComboUP1_6->Items->LoadFromFile("_tonelist.dat");
    ComboUP1_7->Items->LoadFromFile("_tonelist.dat");
    ComboUP1_8->Items->LoadFromFile("_tonelist.dat");

    //Upper2//
    ComboUP2_1->Items->LoadFromFile("_tonelist.dat");
    ComboUP2_2->Items->LoadFromFile("_tonelist.dat");
    ComboUP2_3->Items->LoadFromFile("_tonelist.dat");
    ComboUP2_4->Items->LoadFromFile("_tonelist.dat");
    ComboUP2_5->Items->LoadFromFile("_tonelist.dat");
    ComboUP2_6->Items->LoadFromFile("_tonelist.dat");
    ComboUP2_7->Items->LoadFromFile("_tonelist.dat");
    ComboUP2_8->Items->LoadFromFile("_tonelist.dat");

    //Lower//
    ComboLower_1->Items->LoadFromFile("_tonelist.dat");
    ComboLower_2->Items->LoadFromFile("_tonelist.dat");
    ComboLower_3->Items->LoadFromFile("_tonelist.dat");
    ComboLower_4->Items->LoadFromFile("_tonelist.dat");
    ComboLower_5->Items->LoadFromFile("_tonelist.dat");
    ComboLower_6->Items->LoadFromFile("_tonelist.dat");
    ComboLower_7->Items->LoadFromFile("_tonelist.dat");
    ComboLower_8->Items->LoadFromFile("_tonelist.dat");

    //Manual Bass Switch//
    ComboMBass_1->Items->LoadFromFile("_tonelist.dat");
    ComboMBass_2->Items->LoadFromFile("_tonelist.dat");
    ComboMBass_3->Items->LoadFromFile("_tonelist.dat");
    ComboMBass_4->Items->LoadFromFile("_tonelist.dat");
    ComboMBass_5->Items->LoadFromFile("_tonelist.dat");
    ComboMBass_6->Items->LoadFromFile("_tonelist.dat");
    ComboMBass_7->Items->LoadFromFile("_tonelist.dat");
    ComboMBass_8->Items->LoadFromFile("_tonelist.dat");

    //Manual Drums//
    ComboMDrums_1->Items->LoadFromFile("_drumlist.dat");
    ComboMDrums_2->Items->LoadFromFile("_drumlist.dat");
    ComboMDrums_3->Items->LoadFromFile("_drumlist.dat");
    ComboMDrums_4->Items->LoadFromFile("_drumlist.dat");
    ComboMDrums_5->Items->LoadFromFile("_drumlist.dat");
    ComboMDrums_6->Items->LoadFromFile("_drumlist.dat");
    ComboMDrums_7->Items->LoadFromFile("_drumlist.dat");
    ComboMDrums_8->Items->LoadFromFile("_drumlist.dat");

/****************************************************************************/

/****************************************************************************/
/***************Inicializa as informações (Labels) dos ScrollBars************/
/*******************(*mesma declaração no evento OnScroll)*******************/
/****************************************************************************/

    //TRANSPOSE
    LabelTransp_1->Caption = ScrollTransp_1->Position;
    LabelTransp_2->Caption = ScrollTransp_2->Position;
    LabelTransp_3->Caption = ScrollTransp_3->Position;
    LabelTransp_4->Caption = ScrollTransp_4->Position;
    LabelTransp_5->Caption = ScrollTransp_5->Position;
    LabelTransp_6->Caption = ScrollTransp_6->Position;
    LabelTransp_7->Caption = ScrollTransp_7->Position;
    LabelTransp_8->Caption = ScrollTransp_8->Position;

    //Reverb
    LabelReverb_1->Caption = ReverbName(ScrollReverb_1->Position);
    LabelReverb_2->Caption = ReverbName(ScrollReverb_2->Position);
    LabelReverb_3->Caption = ReverbName(ScrollReverb_3->Position);
    LabelReverb_4->Caption = ReverbName(ScrollReverb_4->Position);
    LabelReverb_5->Caption = ReverbName(ScrollReverb_5->Position);
    LabelReverb_6->Caption = ReverbName(ScrollReverb_6->Position);
    LabelReverb_7->Caption = ReverbName(ScrollReverb_7->Position);
    LabelReverb_8->Caption = ReverbName(ScrollReverb_8->Position);

    //Chorus
    LabelChorus_1->Caption = ChorusName(ScrollChorus_1->Position);
    LabelChorus_2->Caption = ChorusName(ScrollChorus_2->Position);
    LabelChorus_3->Caption = ChorusName(ScrollChorus_3->Position);
    LabelChorus_4->Caption = ChorusName(ScrollChorus_4->Position);
    LabelChorus_5->Caption = ChorusName(ScrollChorus_5->Position);
    LabelChorus_6->Caption = ChorusName(ScrollChorus_6->Position);
    LabelChorus_7->Caption = ChorusName(ScrollChorus_7->Position);
    LabelChorus_8->Caption = ChorusName(ScrollChorus_8->Position);

    //UP1Vol
    LabelUP1Vol_1->Caption = ScrollUP1Vol_1->Position;
    LabelUP1Vol_2->Caption = ScrollUP1Vol_2->Position;
    LabelUP1Vol_3->Caption = ScrollUP1Vol_3->Position;
    LabelUP1Vol_4->Caption = ScrollUP1Vol_4->Position;
    LabelUP1Vol_5->Caption = ScrollUP1Vol_5->Position;
    LabelUP1Vol_6->Caption = ScrollUP1Vol_6->Position;
    LabelUP1Vol_7->Caption = ScrollUP1Vol_7->Position;
    LabelUP1Vol_8->Caption = ScrollUP1Vol_8->Position;

    //UP2Vol
    LabelUP2Vol_1->Caption = ScrollUP2Vol_1->Position;
    LabelUP2Vol_2->Caption = ScrollUP2Vol_2->Position;
    LabelUP2Vol_3->Caption = ScrollUP2Vol_3->Position;
    LabelUP2Vol_4->Caption = ScrollUP2Vol_4->Position;
    LabelUP2Vol_5->Caption = ScrollUP2Vol_5->Position;
    LabelUP2Vol_6->Caption = ScrollUP2Vol_6->Position;
    LabelUP2Vol_7->Caption = ScrollUP2Vol_7->Position;
    LabelUP2Vol_8->Caption = ScrollUP2Vol_8->Position;

    //LowerVol
    LabelLowerVol_1->Caption = ScrollLowerVol_1->Position;
    LabelLowerVol_2->Caption = ScrollLowerVol_2->Position;
    LabelLowerVol_3->Caption = ScrollLowerVol_3->Position;
    LabelLowerVol_4->Caption = ScrollLowerVol_4->Position;
    LabelLowerVol_5->Caption = ScrollLowerVol_5->Position;
    LabelLowerVol_6->Caption = ScrollLowerVol_6->Position;
    LabelLowerVol_7->Caption = ScrollLowerVol_7->Position;
    LabelLowerVol_8->Caption = ScrollLowerVol_8->Position;

    //MBassVol
    LabelMBassVol_1->Caption = ScrollMBassVol_1->Position;  ///ScrollMBassVol_1
    LabelMBassVol_2->Caption = ScrollMBassVol_2->Position;  ///LabelMBassVol_1
    LabelMBassVol_3->Caption = ScrollMBassVol_3->Position;
    LabelMBassVol_4->Caption = ScrollMBassVol_4->Position;
    LabelMBassVol_5->Caption = ScrollMBassVol_5->Position;
    LabelMBassVol_6->Caption = ScrollMBassVol_6->Position;
    LabelMBassVol_7->Caption = ScrollMBassVol_7->Position;
    LabelMBassVol_8->Caption = ScrollMBassVol_8->Position;

    //UP1Oct
    LabelUP1Oct_1->Caption = ScrollUP1Oct_1->Position;
    LabelUP1Oct_2->Caption = ScrollUP1Oct_2->Position;
    LabelUP1Oct_3->Caption = ScrollUP1Oct_3->Position;
    LabelUP1Oct_4->Caption = ScrollUP1Oct_4->Position;
    LabelUP1Oct_5->Caption = ScrollUP1Oct_5->Position;
    LabelUP1Oct_6->Caption = ScrollUP1Oct_6->Position;
    LabelUP1Oct_7->Caption = ScrollUP1Oct_7->Position;
    LabelUP1Oct_8->Caption = ScrollUP1Oct_8->Position;

    //UP2Oct
    LabelUP2Oct_1->Caption = ScrollUP2Oct_1->Position;
    LabelUP2Oct_2->Caption = ScrollUP2Oct_2->Position;
    LabelUP2Oct_3->Caption = ScrollUP2Oct_3->Position;
    LabelUP2Oct_4->Caption = ScrollUP2Oct_4->Position;
    LabelUP2Oct_5->Caption = ScrollUP2Oct_5->Position;
    LabelUP2Oct_6->Caption = ScrollUP2Oct_6->Position;
    LabelUP2Oct_7->Caption = ScrollUP2Oct_7->Position;
    LabelUP2Oct_8->Caption = ScrollUP2Oct_8->Position;

    //LowerOct
    LabelLowerOct_1->Caption = ScrollLowerOct_1->Position;
    LabelLowerOct_2->Caption = ScrollLowerOct_2->Position;
    LabelLowerOct_3->Caption = ScrollLowerOct_3->Position;
    LabelLowerOct_4->Caption = ScrollLowerOct_4->Position;
    LabelLowerOct_5->Caption = ScrollLowerOct_5->Position;
    LabelLowerOct_6->Caption = ScrollLowerOct_6->Position;
    LabelLowerOct_7->Caption = ScrollLowerOct_7->Position;
    LabelLowerOct_8->Caption = ScrollLowerOct_8->Position;

    //*SplitPoint: insere a nota C3, padrão, o calculo real está em OnChange
    LabelSplitLowerNote_1->Caption = "C3";
    LabelSplitLowerNote_2->Caption = "C3";
    LabelSplitLowerNote_3->Caption = "C3";
    LabelSplitLowerNote_4->Caption = "C3";
    LabelSplitLowerNote_5->Caption = "C3";
    LabelSplitLowerNote_6->Caption = "C3";
    LabelSplitLowerNote_7->Caption = "C3";
    LabelSplitLowerNote_8->Caption = "C3";


/****************************************************************************/
/*******************Carrega Matriz Padrão de User Programs*******************/
/****************************************************************************/
coleta_dados(CheckKey_1->Checked, DADO(StrToInt(EditTempo_1->Text)), CheckTransp_1->Checked,
    DADO(ScrollTransp_1->Position), CheckReverb_1->Checked, DADO(ScrollReverb_1->Position),
    CheckChorus_1->Checked, DADO(ScrollChorus_1->Position), CheckUP1_1->Checked,
    DADO(ComboUP1_1->Items->IndexOf(ComboUP1_1->Text)), DADO(ScrollUP1Vol_1->Position),
    DADO(ScrollUP1Oct_1->Position), CheckUP2_1->Checked, DADO(ComboUP2_1->Items->IndexOf(ComboUP2_1->Text)),
    DADO(ScrollUP2Vol_1->Position), DADO(ScrollUP2Oct_1->Position), up2state_1,
    CheckLower_1->Checked, DADO(ComboLower_1->Items->IndexOf(ComboLower_1->Text)),
    DADO(ScrollLowerVol_1->Position), DADO(ScrollLowerOct_1->Position), DADO(ScrollSplitLower_1->Position),
    CheckLowerInt_1->Checked,CheckLowerMem_1->Checked, CheckMBass_1->Checked, DADO(ComboMBass_1->Items->IndexOf(ComboMBass_1->Text)),
    DADO(ScrollMBassVol_1->Position), CheckMDrums_1->Checked, DADO(ComboMDrums_1->Items->IndexOf(ComboMDrums_1->Text)),
    USPR_NEW);

    //faz com que todas matrizes contenham a mesma informação na inicialização do programa
    for(int i=0;i<80;i++)
    {
        USPR_1[i] = USPR_NEW[i];
        USPR_2[i] = USPR_NEW[i];
        USPR_3[i] = USPR_NEW[i];
        USPR_4[i] = USPR_NEW[i];
        USPR_5[i] = USPR_NEW[i];
        USPR_6[i] = USPR_NEW[i];
        USPR_7[i] = USPR_NEW[i];
        USPR_8[i] = USPR_NEW[i];
    }
/****************************************************************************/


//coloca foco no User Program 1
            PagePrincipal->ActivePage = TabUSPR_1;
}
//---------------------------------------------------------------------------
//////////////////////////// SCROLL TRANSPOSE /////////////////////////////////
void __fastcall TFormPrincipal::ScrollTransp_1Change(TObject *Sender)
{
    LabelTransp_1->Caption = ScrollTransp_1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_2Change(TObject *Sender)
{
    LabelTransp_2->Caption = ScrollTransp_2->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_3Change(TObject *Sender)
{
    LabelTransp_3->Caption = ScrollTransp_3->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_4Change(TObject *Sender)
{
    LabelTransp_4->Caption = ScrollTransp_4->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_5Change(TObject *Sender)
{
    LabelTransp_5->Caption = ScrollTransp_5->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_6Change(TObject *Sender)
{
    LabelTransp_6->Caption = ScrollTransp_6->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_7Change(TObject *Sender)
{
    LabelTransp_7->Caption = ScrollTransp_7->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_8Change(TObject *Sender)
{
    LabelTransp_8->Caption = ScrollTransp_8->Position;
}
//---------------------------------------------------------------------------
////////////////////////////   LABEL REVERB  /////////////////////////////////
void __fastcall TFormPrincipal::ScrollReverb_1Change(TObject *Sender)
{
    LabelReverb_1->Caption = ReverbName(ScrollReverb_1->Position);    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollReverb_2Change(TObject *Sender)
{
    LabelReverb_2->Caption = ReverbName(ScrollReverb_2->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollReverb_3Change(TObject *Sender)
{
    LabelReverb_3->Caption = ReverbName(ScrollReverb_3->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollReverb_4Change(TObject *Sender)
{
    LabelReverb_4->Caption = ReverbName(ScrollReverb_4->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollReverb_5Change(TObject *Sender)
{
    LabelReverb_5->Caption = ReverbName(ScrollReverb_5->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollReverb_6Change(TObject *Sender)
{
    LabelReverb_6->Caption = ReverbName(ScrollReverb_6->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollReverb_7Change(TObject *Sender)
{
    LabelReverb_7->Caption = ReverbName(ScrollReverb_7->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollReverb_8Change(TObject *Sender)
{
    LabelReverb_8->Caption = ReverbName(ScrollReverb_8->Position);
}
//---------------------------------------------------------------------------
////////////////////////////   LABEL CHORUS  /////////////////////////////////
void __fastcall TFormPrincipal::ScrollChorus_1Change(TObject *Sender)
{
    LabelChorus_1->Caption = ChorusName(ScrollChorus_1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollChorus_2Change(TObject *Sender)
{
    LabelChorus_2->Caption = ChorusName(ScrollChorus_2->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollChorus_3Change(TObject *Sender)
{
    LabelChorus_3->Caption = ChorusName(ScrollChorus_3->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollChorus_4Change(TObject *Sender)
{
    LabelChorus_4->Caption = ChorusName(ScrollChorus_4->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollChorus_5Change(TObject *Sender)
{
    LabelChorus_5->Caption = ChorusName(ScrollChorus_5->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollChorus_6Change(TObject *Sender)
{
    LabelChorus_6->Caption = ChorusName(ScrollChorus_6->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollChorus_7Change(TObject *Sender)
{
    LabelChorus_7->Caption = ChorusName(ScrollChorus_7->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollChorus_8Change(TObject *Sender)
{
    LabelChorus_8->Caption = ChorusName(ScrollChorus_8->Position);
}
//---------------------------------------------------------------------------
//////////////////////////// SCROLL UPPER1 VOL /////////////////////////////////
void __fastcall TFormPrincipal::ScrollUP1Vol_1Change(TObject *Sender)
{
    LabelUP1Vol_1->Caption = ScrollUP1Vol_1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Vol_2Change(TObject *Sender)
{
    LabelUP1Vol_2->Caption = ScrollUP1Vol_2->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Vol_3Change(TObject *Sender)
{
    LabelUP1Vol_3->Caption = ScrollUP1Vol_3->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Vol_4Change(TObject *Sender)
{
    LabelUP1Vol_4->Caption = ScrollUP1Vol_4->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Vol_5Change(TObject *Sender)
{
    LabelUP1Vol_5->Caption = ScrollUP1Vol_5->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Vol_6Change(TObject *Sender)
{
    LabelUP1Vol_6->Caption = ScrollUP1Vol_6->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Vol_7Change(TObject *Sender)
{
    LabelUP1Vol_7->Caption = ScrollUP1Vol_7->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Vol_8Change(TObject *Sender)
{
    LabelUP1Vol_8->Caption = ScrollUP1Vol_8->Position;
}
//---------------------------------------------------------------------------
//////////////////////////// SCROLL UPPER2 VOL /////////////////////////////////
void __fastcall TFormPrincipal::ScrollUP2Vol_1Change(TObject *Sender)
{
    LabelUP2Vol_1->Caption = ScrollUP2Vol_1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Vol_2Change(TObject *Sender)
{
    LabelUP2Vol_2->Caption = ScrollUP2Vol_2->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Vol_3Change(TObject *Sender)
{
    LabelUP2Vol_3->Caption = ScrollUP2Vol_3->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Vol_4Change(TObject *Sender)
{
    LabelUP2Vol_4->Caption = ScrollUP2Vol_4->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Vol_5Change(TObject *Sender)
{
    LabelUP2Vol_5->Caption = ScrollUP2Vol_5->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Vol_6Change(TObject *Sender)
{
    LabelUP2Vol_6->Caption = ScrollUP2Vol_6->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Vol_7Change(TObject *Sender)
{
    LabelUP2Vol_7->Caption = ScrollUP2Vol_7->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Vol_8Change(TObject *Sender)
{
    LabelUP2Vol_8->Caption = ScrollUP2Vol_8->Position;
}
//---------------------------------------------------------------------------
//////////////////////////// SCROLL LOWER VOL /////////////////////////////////
void __fastcall TFormPrincipal::ScrollLowerVol_1Change(TObject *Sender)
{
    LabelLowerVol_1->Caption = ScrollLowerVol_1->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerVol_2Change(TObject *Sender)
{
    LabelLowerVol_2->Caption = ScrollLowerVol_2->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerVol_3Change(TObject *Sender)
{
    LabelLowerVol_3->Caption = ScrollLowerVol_3->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerVol_4Change(TObject *Sender)
{
    LabelLowerVol_4->Caption = ScrollLowerVol_4->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerVol_5Change(TObject *Sender)
{
    LabelLowerVol_5->Caption = ScrollLowerVol_5->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerVol_6Change(TObject *Sender)
{
    LabelLowerVol_6->Caption = ScrollLowerVol_6->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerVol_7Change(TObject *Sender)
{
    LabelLowerVol_7->Caption = ScrollLowerVol_7->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerVol_8Change(TObject *Sender)
{
    LabelLowerVol_8->Caption = ScrollLowerVol_8->Position;
}
//---------------------------------------------------------------------------

//////////////////////////// SCROLL MBASS VOL /////////////////////////////////
void __fastcall TFormPrincipal::ScrollMBassVol_1Change(TObject *Sender)
{
    LabelMBassVol_1->Caption = ScrollMBassVol_1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollMBassVol_2Change(TObject *Sender)
{
    LabelMBassVol_2->Caption = ScrollMBassVol_2->Position;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollMBassVol_3Change(TObject *Sender)
{
    LabelMBassVol_3->Caption = ScrollMBassVol_3->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollMBassVol_4Change(TObject *Sender)
{
    LabelMBassVol_4->Caption = ScrollMBassVol_4->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollMBassVol_5Change(TObject *Sender)
{
    LabelMBassVol_5->Caption = ScrollMBassVol_5->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollMBassVol_6Change(TObject *Sender)
{
    LabelMBassVol_6->Caption = ScrollMBassVol_6->Position;
}
//---------------------------------------------------------------------------


void __fastcall TFormPrincipal::ScrollMBassVol_7Change(TObject *Sender)
{
    LabelMBassVol_7->Caption = ScrollMBassVol_7->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollMBassVol_8Change(TObject *Sender)
{
    LabelMBassVol_8->Caption = ScrollMBassVol_8->Position;
}
//---------------------------------------------------------------------------
/////////////////////////////SCROLL UPPER1 OCT/////////////////////////////////
void __fastcall TFormPrincipal::ScrollUP1Oct_1Change(TObject *Sender)
{
    LabelUP1Oct_1->Caption = ScrollUP1Oct_1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Oct_2Change(TObject *Sender)
{
    LabelUP1Oct_2->Caption = ScrollUP1Oct_2->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Oct_3Change(TObject *Sender)
{
    LabelUP1Oct_3->Caption = ScrollUP1Oct_3->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Oct_4Change(TObject *Sender)
{
    LabelUP1Oct_4->Caption = ScrollUP1Oct_4->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Oct_5Change(TObject *Sender)
{
    LabelUP1Oct_5->Caption = ScrollUP1Oct_5->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Oct_6Change(TObject *Sender)
{
    LabelUP1Oct_6->Caption = ScrollUP1Oct_6->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Oct_7Change(TObject *Sender)
{
    LabelUP1Oct_7->Caption = ScrollUP1Oct_7->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP1Oct_8Change(TObject *Sender)
{
    LabelUP1Oct_8->Caption = ScrollUP1Oct_8->Position;
}
//---------------------------------------------------------------------------
/////////////////////////////SCROLL UPPER2 OCT/////////////////////////////////
void __fastcall TFormPrincipal::ScrollUP2Oct_1Change(TObject *Sender)
{
    LabelUP2Oct_1->Caption = ScrollUP2Oct_1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Oct_2Change(TObject *Sender)
{
    LabelUP2Oct_2->Caption = ScrollUP2Oct_2->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Oct_3Change(TObject *Sender)
{
    LabelUP2Oct_3->Caption = ScrollUP2Oct_3->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Oct_4Change(TObject *Sender)
{
    LabelUP2Oct_4->Caption = ScrollUP2Oct_4->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Oct_5Change(TObject *Sender)
{
    LabelUP2Oct_5->Caption = ScrollUP2Oct_5->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Oct_6Change(TObject *Sender)
{
    LabelUP2Oct_6->Caption = ScrollUP2Oct_6->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Oct_7Change(TObject *Sender)
{
    LabelUP2Oct_7->Caption = ScrollUP2Oct_7->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollUP2Oct_8Change(TObject *Sender)
{
    LabelUP2Oct_8->Caption = ScrollUP2Oct_8->Position;
}
//---------------------------------------------------------------------------
/////////////////////////////SCROLL LOWER OCT/////////////////////////////////
void __fastcall TFormPrincipal::ScrollLowerOct_1Change(TObject *Sender)
{
    LabelLowerOct_1->Caption = ScrollLowerOct_1->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerOct_2Change(TObject *Sender)
{
    LabelLowerOct_2->Caption = ScrollLowerOct_2->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerOct_3Change(TObject *Sender)
{
    LabelLowerOct_3->Caption = ScrollLowerOct_3->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerOct_4Change(TObject *Sender)
{
    LabelLowerOct_4->Caption = ScrollLowerOct_4->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerOct_5Change(TObject *Sender)
{
    LabelLowerOct_5->Caption = ScrollLowerOct_5->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerOct_6Change(TObject *Sender)
{
    LabelLowerOct_6->Caption = ScrollLowerOct_6->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerOct_7Change(TObject *Sender)
{
    LabelLowerOct_7->Caption = ScrollLowerOct_7->Position;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollLowerOct_8Change(TObject *Sender)
{
    LabelLowerOct_8->Caption = ScrollLowerOct_8->Position;
}
//---------------------------------------------------------------------------
/////////////////////////////SCROLL SPLIT LOWER/////////////////////////////////
void __fastcall TFormPrincipal::ScrollSplitLower_1Change(TObject *Sender)
{
LabelSplitLowerNote_1->Caption = LowerSplitNote(ScrollSplitLower_1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollSplitLower_2Change(TObject *Sender)
{
LabelSplitLowerNote_2->Caption = LowerSplitNote(ScrollSplitLower_2->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollSplitLower_3Change(TObject *Sender)
{
LabelSplitLowerNote_3->Caption = LowerSplitNote(ScrollSplitLower_3->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollSplitLower_4Change(TObject *Sender)
{
LabelSplitLowerNote_4->Caption = LowerSplitNote(ScrollSplitLower_4->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollSplitLower_5Change(TObject *Sender)
{
LabelSplitLowerNote_5->Caption = LowerSplitNote(ScrollSplitLower_5->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollSplitLower_6Change(TObject *Sender)
{
LabelSplitLowerNote_6->Caption = LowerSplitNote(ScrollSplitLower_6->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollSplitLower_7Change(TObject *Sender)
{
LabelSplitLowerNote_7->Caption = LowerSplitNote(ScrollSplitLower_7->Position);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollSplitLower_8Change(TObject *Sender)
{
LabelSplitLowerNote_8->Caption = LowerSplitNote(ScrollSplitLower_8->Position);
}
//---------------------------------------------------------------------------

////////////////////////////////////CHECK LOWER/////////////////////////////////
void __fastcall TFormPrincipal::CheckLower_1Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_1->Checked && CheckMDrums_1->Checked) CheckMDrums_1->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckLower_2Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_2->Checked && CheckMDrums_2->Checked) CheckMDrums_2->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckLower_3Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_3->Checked && CheckMDrums_3->Checked) CheckMDrums_3->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckLower_4Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_4->Checked && CheckMDrums_4->Checked) CheckMDrums_4->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckLower_5Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_5->Checked && CheckMDrums_5->Checked) CheckMDrums_5->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckLower_6Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_6->Checked && CheckMDrums_6->Checked) CheckMDrums_6->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckLower_7Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_7->Checked && CheckMDrums_7->Checked) CheckMDrums_7->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckLower_8Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_8->Checked && CheckMDrums_8->Checked) CheckMDrums_8->Checked = false;
}
//---------------------------------------------------------------------------
////////////////////////////////////CHECK MDRUMS/////////////////////////////////
void __fastcall TFormPrincipal::CheckMDrums_1Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_1->Checked && CheckMDrums_1->Checked) CheckLower_1->Checked = false;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckMDrums_2Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_2->Checked && CheckMDrums_2->Checked) CheckLower_2->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckMDrums_3Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_3->Checked && CheckMDrums_3->Checked) CheckLower_3->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckMDrums_4Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_4->Checked && CheckMDrums_4->Checked) CheckLower_4->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckMDrums_5Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_5->Checked && CheckMDrums_5->Checked) CheckLower_5->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckMDrums_6Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_6->Checked && CheckMDrums_6->Checked) CheckLower_6->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckMDrums_7Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_7->Checked && CheckMDrums_7->Checked) CheckLower_7->Checked = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::CheckMDrums_8Click(TObject *Sender)
{
    //Lower e MDrums não podem ser ativados ao mesmo tempo
    if(CheckLower_8->Checked && CheckMDrums_8->Checked) CheckLower_8->Checked = false;
}
//---------------------------------------------------------------------------
////////////////////////////////////EDIT TEMPO KEYPRESS/////////////////////////////////
void __fastcall TFormPrincipal::EditTempo_1KeyPress(TObject *Sender,
      char &Key)
{
    //Evita caracteres além de números e Backspace, substitui-os por ENTER (sem efeito)
    if((Key < '0' || Key > '9') && !(Key == VK_BACK)) Key = VK_RETURN;

    // Essa mesma função, por não fazer referência à objetos específicos,
                                    // é reutilizada por todos os EditTempo_N; //

}
//---------------------------------------------------------------------------
/////////////////////////////////EDIT TEMPO EXIT //////////////////////////////

void __fastcall TFormPrincipal::EditTempo_1Exit(TObject *Sender)
{
    //Verifica se valor está entre 20 e 250, valores aceitos  pelo EM-25
    if (EditTempo_1->Text == "") EditTempo_1->Text = "98";
    else if(StrToInt(EditTempo_1->Text) < 20) EditTempo_1->Text = "20";
    else if (StrToInt(EditTempo_1->Text) > 250) EditTempo_1->Text = "250";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::EditTempo_2Exit(TObject *Sender)
{
    if (EditTempo_2->Text == "") EditTempo_2->Text = "98";
    else if(StrToInt(EditTempo_2->Text) < 20) EditTempo_2->Text = "20";
    else if (StrToInt(EditTempo_2->Text) > 250) EditTempo_2->Text = "250";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::EditTempo_3Exit(TObject *Sender)
{
    if (EditTempo_3->Text == "") EditTempo_3->Text = "98";
    else if(StrToInt(EditTempo_3->Text) < 20) EditTempo_3->Text = "20";
    else if (StrToInt(EditTempo_3->Text) > 250) EditTempo_3->Text = "250";
}
//---------------------------------------------------------------------------


void __fastcall TFormPrincipal::EditTempo_4Exit(TObject *Sender)
{
    if (EditTempo_4->Text == "") EditTempo_4->Text = "98";
    else if(StrToInt(EditTempo_4->Text) < 20) EditTempo_4->Text = "20";
    else if (StrToInt(EditTempo_4->Text) > 250) EditTempo_4->Text = "250";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::EditTempo_5Exit(TObject *Sender)
{
    if (EditTempo_5->Text == "") EditTempo_5->Text = "98";
    else if(StrToInt(EditTempo_5->Text) < 20) EditTempo_5->Text = "20";
    else if (StrToInt(EditTempo_5->Text) > 250) EditTempo_5->Text = "250";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::EditTempo_6Exit(TObject *Sender)
{
    if (EditTempo_6->Text == "") EditTempo_6->Text = "98";
    else if(StrToInt(EditTempo_6->Text) < 20) EditTempo_6->Text = "20";
    else if (StrToInt(EditTempo_6->Text) > 250) EditTempo_6->Text = "250";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::EditTempo_7Exit(TObject *Sender)
{
    if (EditTempo_7->Text == "") EditTempo_7->Text = "98";
    else if(StrToInt(EditTempo_7->Text) < 20) EditTempo_7->Text = "20";
    else if (StrToInt(EditTempo_7->Text) > 250) EditTempo_7->Text = "250";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::EditTempo_8Exit(TObject *Sender)
{
    if (EditTempo_8->Text == "") EditTempo_8->Text = "98";
    else if(StrToInt(EditTempo_8->Text) < 20) EditTempo_8->Text = "20";
    else if (StrToInt(EditTempo_8->Text) > 250) EditTempo_8->Text = "250";
}
//---------------------------------------------------------------------------

/////////////////////////SCROLL TRANSPOSE EXIT //////////////////////////////

void __fastcall TFormPrincipal::ScrollTransp_1Exit(TObject *Sender)
{
    if(ScrollTransp_1->Position == 0)
        {
            ShowMessage(msg_transp);
            ScrollTransp_1->Position = 1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_2Exit(TObject *Sender)
{
    if(ScrollTransp_2->Position == 0)
        {
            ShowMessage(" O valor do Transpose não pode ser \"0\","
                        "Valor Padrão 1");
            ScrollTransp_2->Position = 1;
        }    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_3Exit(TObject *Sender)
{
    if(ScrollTransp_3->Position == 0)
        {
            ShowMessage(" O valor do Transpose não pode ser \"0\","
                        "Valor Padrão 1");
            ScrollTransp_3->Position = 1;
        }    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_4Exit(TObject *Sender)
{
    if(ScrollTransp_4->Position == 0)
        {
            ShowMessage(" O valor do Transpose não pode ser \"0\","
                        "Valor Padrão 1");
            ScrollTransp_4->Position = 1;
        }    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_5Exit(TObject *Sender)
{
    if(ScrollTransp_5->Position == 0)
        {
            ShowMessage(" O valor do Transpose não pode ser \"0\","
                        "Valor Padrão 1");
            ScrollTransp_5->Position = 1;
        }    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_6Exit(TObject *Sender)
{
    if(ScrollTransp_6->Position == 0)
        {
            ShowMessage(" O valor do Transpose não pode ser \"0\","
                        "Valor Padrão 1");
            ScrollTransp_6->Position = 1;
        }    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_7Exit(TObject *Sender)
{
    if(ScrollTransp_7->Position == 0)
        {
            ShowMessage(" O valor do Transpose não pode ser \"0\","
                        "Valor Padrão 1");
            ScrollTransp_7->Position = 1;
        }    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::ScrollTransp_8Exit(TObject *Sender)
{
    if(ScrollTransp_8->Position == 0)
        {
            ShowMessage(" O valor do Transpose não pode ser \"0\","
                        "Valor Padrão 1");
            ScrollTransp_8->Position = 1;
        }
}
//---------------------------------------------------------------------------


///////////////////// RADIO UP2 STATE UP2_DESATIVADO //////////////////////////

void __fastcall TFormPrincipal::RadioUP2Desativado_1Click(TObject *Sender)
{
    up2state_1 = UP2_DESATIVADO;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Desativado_2Click(TObject *Sender)
{
    up2state_2 = UP2_DESATIVADO;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Desativado_3Click(TObject *Sender)
{
    up2state_3 = UP2_DESATIVADO;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Desativado_4Click(TObject *Sender)
{
    up2state_4 = UP2_DESATIVADO;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Desativado_5Click(TObject *Sender)
{
    up2state_5 = UP2_DESATIVADO;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Desativado_6Click(TObject *Sender)
{
    up2state_6 = UP2_DESATIVADO;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Desativado_7Click(TObject *Sender)
{
    up2state_7 = UP2_DESATIVADO;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Desativado_8Click(TObject *Sender)
{
    up2state_8 = UP2_DESATIVADO;
}
//---------------------------------------------------------------------------
/////////////////////// RADIO UP2 STATE UP2_MEL_INT /////////////////////////////
void __fastcall TFormPrincipal::RadioUP2MelInt_1Click(TObject *Sender)
{
    up2state_1 = UP2_MEL_INT;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2MelInt_2Click(TObject *Sender)
{
    up2state_2 = UP2_MEL_INT;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2MelInt_3Click(TObject *Sender)
{
    up2state_3 = UP2_MEL_INT;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2MelInt_4Click(TObject *Sender)
{
    up2state_4 = UP2_MEL_INT;
}
//---------------------------------------------------------------------------


void __fastcall TFormPrincipal::RadioUP2MelInt_5Click(TObject *Sender)
{
    up2state_5 = UP2_MEL_INT;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2MelInt_6Click(TObject *Sender)
{
    up2state_6 = UP2_MEL_INT;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2MelInt_7Click(TObject *Sender)
{
    up2state_7 = UP2_MEL_INT;    
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2MelInt_8Click(TObject *Sender)
{
    up2state_8 = UP2_MEL_INT;
}
//---------------------------------------------------------------------------

//////////////////////// RADIO UP2 STATE UP2_LAYER //////////////////////////////
void __fastcall TFormPrincipal::RadioUP2Layer_1Click(TObject *Sender)
{
    up2state_1 = UP2_LAYER;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Layer_2Click(TObject *Sender)
{
    up2state_2 = UP2_LAYER;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Layer_3Click(TObject *Sender)
{
    up2state_3 = UP2_LAYER;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Layer_4Click(TObject *Sender)
{
    up2state_4 = UP2_LAYER;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Layer_5Click(TObject *Sender)
{
    up2state_5 = UP2_LAYER;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Layer_6Click(TObject *Sender)
{
    up2state_6 = UP2_LAYER;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Layer_7Click(TObject *Sender)
{
    up2state_7 = UP2_LAYER;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::RadioUP2Layer_8Click(TObject *Sender)
{
    up2state_8 = UP2_LAYER;
}
//---------------------------------------------------------------------------





void __fastcall TFormPrincipal::PagePrincipalChange(TObject *Sender)
{
    if(PagePrincipal->ActivePage == TabUSPR_1)
    {
        tabfocus = 1;
    }
    else if(PagePrincipal->ActivePage == TabUSPR_2)
    {
        tabfocus = 2;
    }
    else if(PagePrincipal->ActivePage == TabUSPR_3)
    {
        tabfocus = 3;
    }
    else if(PagePrincipal->ActivePage == TabUSPR_4)
    {
        tabfocus = 4;
    }
    else if(PagePrincipal->ActivePage == TabUSPR_5)
    {
        tabfocus = 5;
    }
    else if(PagePrincipal->ActivePage == TabUSPR_6)
    {
        tabfocus = 6;
    }
    else if(PagePrincipal->ActivePage == TabUSPR_7)
    {
        tabfocus = 7;
    }
    else if(PagePrincipal->ActivePage == TabUSPR_8)
    {
        tabfocus = 8;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuCloseClick(TObject *Sender)
{
       Close(); //Fecha o programa
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuOpenClick(TObject *Sender)
{
    DADO ARQUIVO[640];
    AnsiString nome_arquivo;

    if (OpenDialog-> Execute())
    {
        nome_arquivo = OpenDialog->FileName;

        //procedimento que garante que a extensão não seja omitida ao carregar arquivos evitando erros
        if(nome_arquivo.SubString(nome_arquivo.Length()-3,4) != ".UP0")
            nome_arquivo.Insert(".UP0",nome_arquivo.Length());


        // Carrega o arquivo para um ARRAY de 640 Bytes
        if(!CarregaArquivo(ARQUIVO,nome_arquivo))
        {
            ShowMessage(msg_open_err);
        }
        else
        {
            //Caminho_Abrir atribuída com caminho do último arquivo aberto
            Caminho_Abrir = OpenDialog->FileName;
            //atribui Caminho_Abrir para Caminho_Salvar (para ficarem iguais)
            Caminho_Salvar = Caminho_Abrir;

            //divide o arquivo em 8 USERPROGRAMS diferentes;
            CarregaArquivoTotal(ARQUIVO, USPRL_1, USPRL_2, USPRL_3, USPRL_4, USPRL_5, USPRL_6, USPRL_7, USPRL_8);

            //coloca os dados na tela (nos objetos do FormPrincipal->PagePrincipal)
            matriz_para_uspr(USER_ALL);

            //coloca foco em todas paginas para atualizar a matriz, e volta no User Program 1
            PagePrincipal->ActivePage = TabUSPR_1;
            /*PagePrincipal->ActivePage = TabUSPR_2;
            PagePrincipal->ActivePage = TabUSPR_3;
            PagePrincipal->ActivePage = TabUSPR_4;
            PagePrincipal->ActivePage = TabUSPR_5;
            PagePrincipal->ActivePage = TabUSPR_6;
            PagePrincipal->ActivePage = TabUSPR_7;
            PagePrincipal->ActivePage = TabUSPR_8;
            PagePrincipal->ActivePage = TabUSPR_1; */
         }

    }

    
    //else { ShowMessage("Erro ao abrir o arquivo!"); return; }
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuSaveAsClick(TObject *Sender)
{

    //força a função "PagePrincipalChanging", que verifica por mudança nas Tabs
    // assim, gravando também dados modificados na Tab Atual
    if(PagePrincipal->ActivePage != NULL) PagePrincipalChanging(Sender, NULL);

    DADO ARQUIVO[640];
    if (SaveDialog -> Execute())
    {
        //separa o nome do arquivo
        AnsiString nome_arquivo = SaveDialog->FileName;

        //procedimento que garante que a extensão não seja omitida ao carregar arquivos evitando erros
        if(nome_arquivo.SubString(nome_arquivo.Length()-3,4) != ".UP0")
            nome_arquivo.Insert(".UP0",nome_arquivo.Length());

        if(FileExists(nome_arquivo))
            if (MessageBox(NULL, msg_sobreescrever.c_str(),NULL, MB_OKCANCEL) == IDCANCEL)
                return;



        // une os dados de todos User Programs em um só arquivo
        SalvaArquivoTotal(USPR_1, USPR_2, USPR_3, USPR_4, USPR_5, USPR_6, USPR_7, USPR_8, ARQUIVO);

        //procedimento que verifica se a extensão não vai ser repetida ao criar o novo arquivo
        if(nome_arquivo.SubString(nome_arquivo.Length()-3,4) == ".UP0")
            nome_arquivo.Delete(nome_arquivo.Length()-3,4);

        // Salva o arquivo com o conteúdo de um ARRAY de 640 Bytes.
        SalvaArquivo(ARQUIVO,(nome_arquivo+".UP0"));

        // Caminho_Salvar atribuída com caminho do último arquivo salvo
        Caminho_Salvar = SaveDialog->FileName;
        // atribui Caminho_Salvar para Caminho_Abrir (para ficarem iguais)
        Caminho_Abrir = Caminho_Salvar;

        //[DEBUG] ShowMessage("Arquivo Salvo com Sucesso!");
    }
    //else  ShowMessage("Erro ao abrir o arquivo!");
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuSaveClick(TObject *Sender)
{
    //força a função "PagePrincipalChanging", que verifica por mudança nas Tabs
    // assim, gravando também dados modificados na Tab Atual
    if(PagePrincipal->ActivePage != NULL) PagePrincipalChanging(NULL, NULL);

     // se o arquivo aberto já foi salvo ...
     if((Caminho_Abrir == Caminho_Salvar) && (Caminho_Salvar != ""))
     {
         DADO ARQUIVO[640];
        // une os dados de todos User Programs em um só arquivo
        SalvaArquivoTotal(USPR_1, USPR_2, USPR_3, USPR_4, USPR_5, USPR_6, USPR_7, USPR_8, ARQUIVO);
        //separa o nome do arquivo
        AnsiString nome_arquivo = Caminho_Salvar;

        // o arquivo será salvo sem chamar a caixa Salvar Como
        // Salva o arquivo com o conteúdo de um ARRAY de 640 Bytes.
        SalvaArquivo(ARQUIVO,(nome_arquivo));

     }
     else    // a caixa de diálogos Salvar Como será Chamada
             MenuSaveAsClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::PagePrincipalChanging(TObject *Sender,
      bool &AllowChange)
{
  //  if(PagePrincipal->ActivePage == TabUSPR_1)
  //  {
       coleta_dados(CheckKey_1->Checked, DADO(StrToInt(EditTempo_1->Text)), CheckTransp_1->Checked,
                    DADO(ScrollTransp_1->Position), CheckReverb_1->Checked, DADO(ScrollReverb_1->Position),
                    CheckChorus_1->Checked, DADO(ScrollChorus_1->Position), CheckUP1_1->Checked,
                    DADO(ComboUP1_1->Items->IndexOf(ComboUP1_1->Text)), DADO(ScrollUP1Vol_1->Position),
                    DADO(ScrollUP1Oct_1->Position), CheckUP2_1->Checked, DADO(ComboUP2_1->Items->IndexOf(ComboUP2_1->Text)),
                    DADO(ScrollUP2Vol_1->Position), DADO(ScrollUP2Oct_1->Position), up2state_1,
                    CheckLower_1->Checked, DADO(ComboLower_1->Items->IndexOf(ComboLower_1->Text)),
                    DADO(ScrollLowerVol_1->Position), DADO(ScrollLowerOct_1->Position), DADO(ScrollSplitLower_1->Position),
                    CheckLowerInt_1->Checked,CheckLowerMem_1->Checked, CheckMBass_1->Checked, DADO(ComboMBass_1->Items->IndexOf(ComboMBass_1->Text)),
                    DADO(ScrollMBassVol_1->Position), CheckMDrums_1->Checked, DADO(ComboMDrums_1->Items->IndexOf(ComboMDrums_1->Text)),
                    USPR_1);

       //DEBUG
       //for(int i=0; i<80; i++) ShowMessage(String(USPR_1[i]));

   // }
   // else if(PagePrincipal->ActivePage == TabUSPR_2)
   // {
       coleta_dados(CheckKey_2->Checked, DADO(StrToInt(EditTempo_2->Text)), CheckTransp_2->Checked,
                    DADO(ScrollTransp_2->Position), CheckReverb_2->Checked, DADO(ScrollReverb_2->Position),
                    CheckChorus_2->Checked, DADO(ScrollChorus_2->Position), CheckUP1_2->Checked,
                    DADO(ComboUP1_2->Items->IndexOf(ComboUP1_2->Text)), DADO(ScrollUP1Vol_2->Position),
                    DADO(ScrollUP1Oct_2->Position), CheckUP2_2->Checked, DADO(ComboUP2_2->Items->IndexOf(ComboUP2_2->Text)),
                    DADO(ScrollUP2Vol_2->Position), DADO(ScrollUP2Oct_2->Position), up2state_2,
                    CheckLower_2->Checked, DADO(ComboLower_2->Items->IndexOf(ComboLower_2->Text)),
                    DADO(ScrollLowerVol_2->Position), DADO(ScrollLowerOct_2->Position), DADO(ScrollSplitLower_2->Position),
                    CheckLowerInt_2->Checked,CheckLowerMem_2->Checked, CheckMBass_2->Checked, DADO(ComboMBass_2->Items->IndexOf(ComboMBass_2->Text)),
                    DADO(ScrollMBassVol_2->Position), CheckMDrums_2->Checked, DADO(ComboMDrums_2->Items->IndexOf(ComboMDrums_2->Text)),
                    USPR_2);
   // }
   // else if(PagePrincipal->ActivePage == TabUSPR_3)
   // {
       coleta_dados(CheckKey_3->Checked, DADO(StrToInt(EditTempo_3->Text)), CheckTransp_3->Checked,
                    DADO(ScrollTransp_3->Position), CheckReverb_3->Checked, DADO(ScrollReverb_3->Position),
                    CheckChorus_3->Checked, DADO(ScrollChorus_3->Position), CheckUP1_3->Checked,
                    DADO(ComboUP1_3->Items->IndexOf(ComboUP1_3->Text)), DADO(ScrollUP1Vol_3->Position),
                    DADO(ScrollUP1Oct_3->Position), CheckUP2_3->Checked, DADO(ComboUP2_3->Items->IndexOf(ComboUP2_3->Text)),
                    DADO(ScrollUP2Vol_3->Position), DADO(ScrollUP2Oct_3->Position), up2state_3,
                    CheckLower_3->Checked, DADO(ComboLower_3->Items->IndexOf(ComboLower_3->Text)),
                    DADO(ScrollLowerVol_3->Position), DADO(ScrollLowerOct_3->Position), DADO(ScrollSplitLower_3->Position),
                    CheckLowerInt_3->Checked,CheckLowerMem_3->Checked, CheckMBass_3->Checked, DADO(ComboMBass_3->Items->IndexOf(ComboMBass_3->Text)),
                    DADO(ScrollMBassVol_3->Position), CheckMDrums_3->Checked, DADO(ComboMDrums_3->Items->IndexOf(ComboMDrums_3->Text)),
                    USPR_3);
   // }
   // else if(PagePrincipal->ActivePage == TabUSPR_4)
   // {
       coleta_dados(CheckKey_4->Checked, DADO(StrToInt(EditTempo_4->Text)), CheckTransp_4->Checked,
                    DADO(ScrollTransp_4->Position), CheckReverb_4->Checked, DADO(ScrollReverb_4->Position),
                    CheckChorus_4->Checked, DADO(ScrollChorus_4->Position), CheckUP1_4->Checked,
                    DADO(ComboUP1_4->Items->IndexOf(ComboUP1_4->Text)), DADO(ScrollUP1Vol_4->Position),
                    DADO(ScrollUP1Oct_4->Position), CheckUP2_4->Checked, DADO(ComboUP2_4->Items->IndexOf(ComboUP2_4->Text)),
                    DADO(ScrollUP2Vol_4->Position), DADO(ScrollUP2Oct_4->Position), up2state_4,
                    CheckLower_4->Checked, DADO(ComboLower_4->Items->IndexOf(ComboLower_4->Text)),
                    DADO(ScrollLowerVol_4->Position), DADO(ScrollLowerOct_4->Position), DADO(ScrollSplitLower_4->Position),
                    CheckLowerInt_4->Checked,CheckLowerMem_4->Checked, CheckMBass_4->Checked, DADO(ComboMBass_4->Items->IndexOf(ComboMBass_4->Text)),
                    DADO(ScrollMBassVol_4->Position), CheckMDrums_4->Checked, DADO(ComboMDrums_4->Items->IndexOf(ComboMDrums_4->Text)),
                    USPR_4);
   // }
   // else if(PagePrincipal->ActivePage == TabUSPR_5)
   // {
       coleta_dados(CheckKey_5->Checked, DADO(StrToInt(EditTempo_5->Text)), CheckTransp_5->Checked,
                    DADO(ScrollTransp_5->Position), CheckReverb_5->Checked, DADO(ScrollReverb_5->Position),
                    CheckChorus_5->Checked, DADO(ScrollChorus_5->Position), CheckUP1_5->Checked,
                    DADO(ComboUP1_5->Items->IndexOf(ComboUP1_5->Text)), DADO(ScrollUP1Vol_5->Position),
                    DADO(ScrollUP1Oct_5->Position), CheckUP2_5->Checked, DADO(ComboUP2_5->Items->IndexOf(ComboUP2_5->Text)),
                    DADO(ScrollUP2Vol_5->Position), DADO(ScrollUP2Oct_5->Position), up2state_5,
                    CheckLower_5->Checked, DADO(ComboLower_5->Items->IndexOf(ComboLower_5->Text)),
                    DADO(ScrollLowerVol_5->Position), DADO(ScrollLowerOct_5->Position), DADO(ScrollSplitLower_5->Position),
                    CheckLowerInt_5->Checked,CheckLowerMem_5->Checked, CheckMBass_5->Checked, DADO(ComboMBass_5->Items->IndexOf(ComboMBass_5->Text)),
                    DADO(ScrollMBassVol_5->Position), CheckMDrums_5->Checked, DADO(ComboMDrums_5->Items->IndexOf(ComboMDrums_5->Text)),
                    USPR_5);
   // }
  //  else if(PagePrincipal->ActivePage == TabUSPR_6)
   // {
       coleta_dados(CheckKey_6->Checked, DADO(StrToInt(EditTempo_6->Text)), CheckTransp_6->Checked,
                    DADO(ScrollTransp_6->Position), CheckReverb_6->Checked, DADO(ScrollReverb_6->Position),
                    CheckChorus_6->Checked, DADO(ScrollChorus_6->Position), CheckUP1_6->Checked,
                    DADO(ComboUP1_6->Items->IndexOf(ComboUP1_6->Text)), DADO(ScrollUP1Vol_6->Position),
                    DADO(ScrollUP1Oct_6->Position), CheckUP2_6->Checked, DADO(ComboUP2_6->Items->IndexOf(ComboUP2_6->Text)),
                    DADO(ScrollUP2Vol_6->Position), DADO(ScrollUP2Oct_6->Position), up2state_6,
                    CheckLower_6->Checked, DADO(ComboLower_6->Items->IndexOf(ComboLower_6->Text)),
                    DADO(ScrollLowerVol_6->Position), DADO(ScrollLowerOct_6->Position), DADO(ScrollSplitLower_6->Position),
                    CheckLowerInt_6->Checked,CheckLowerMem_6->Checked, CheckMBass_6->Checked, DADO(ComboMBass_6->Items->IndexOf(ComboMBass_6->Text)),
                    DADO(ScrollMBassVol_6->Position), CheckMDrums_6->Checked, DADO(ComboMDrums_6->Items->IndexOf(ComboMDrums_6->Text)),
                    USPR_6);
   // }
  //  else if(PagePrincipal->ActivePage == TabUSPR_7)
  //  {
       coleta_dados(CheckKey_7->Checked, DADO(StrToInt(EditTempo_7->Text)), CheckTransp_7->Checked,
                    DADO(ScrollTransp_7->Position), CheckReverb_7->Checked, DADO(ScrollReverb_7->Position),
                    CheckChorus_7->Checked, DADO(ScrollChorus_7->Position), CheckUP1_7->Checked,
                    DADO(ComboUP1_7->Items->IndexOf(ComboUP1_7->Text)), DADO(ScrollUP1Vol_7->Position),
                    DADO(ScrollUP1Oct_7->Position), CheckUP2_7->Checked, DADO(ComboUP2_7->Items->IndexOf(ComboUP2_7->Text)),
                    DADO(ScrollUP2Vol_7->Position), DADO(ScrollUP2Oct_7->Position), up2state_7,
                    CheckLower_7->Checked, DADO(ComboLower_7->Items->IndexOf(ComboLower_7->Text)),
                    DADO(ScrollLowerVol_7->Position), DADO(ScrollLowerOct_7->Position), DADO(ScrollSplitLower_7->Position),
                    CheckLowerInt_7->Checked,CheckLowerMem_7->Checked, CheckMBass_7->Checked, DADO(ComboMBass_7->Items->IndexOf(ComboMBass_7->Text)),
                    DADO(ScrollMBassVol_7->Position), CheckMDrums_7->Checked, DADO(ComboMDrums_7->Items->IndexOf(ComboMDrums_7->Text)),
                    USPR_7);
  //  }
   // else if(PagePrincipal->ActivePage == TabUSPR_8)
   // {
       coleta_dados(CheckKey_8->Checked, DADO(StrToInt(EditTempo_8->Text)), CheckTransp_8->Checked,
                    DADO(ScrollTransp_8->Position), CheckReverb_8->Checked, DADO(ScrollReverb_8->Position),
                    CheckChorus_8->Checked, DADO(ScrollChorus_8->Position), CheckUP1_8->Checked,
                    DADO(ComboUP1_8->Items->IndexOf(ComboUP1_8->Text)), DADO(ScrollUP1Vol_8->Position),
                    DADO(ScrollUP1Oct_8->Position), CheckUP2_8->Checked, DADO(ComboUP2_8->Items->IndexOf(ComboUP2_8->Text)),
                    DADO(ScrollUP2Vol_8->Position), DADO(ScrollUP2Oct_8->Position), up2state_8,
                    CheckLower_8->Checked, DADO(ComboLower_8->Items->IndexOf(ComboLower_8->Text)),
                    DADO(ScrollLowerVol_8->Position), DADO(ScrollLowerOct_8->Position), DADO(ScrollSplitLower_8->Position),
                    CheckLowerInt_8->Checked,CheckLowerMem_8->Checked, CheckMBass_8->Checked, DADO(ComboMBass_8->Items->IndexOf(ComboMBass_8->Text)),
                    DADO(ScrollMBassVol_8->Position), CheckMDrums_8->Checked, DADO(ComboMDrums_8->Items->IndexOf(ComboMDrums_8->Text)),
                    USPR_8);
       //DEBUG
       //for(int i=0; i<80; i++) ShowMessage(String(USPR_8[i]));

}
//---------------------------------------------------------------------------


void __fastcall TFormPrincipal::matriz_para_uspr(int qual_uspr)
{

  typedef unsigned char UNSIG; // para variáveis signed char que estouram os valores, retornarem aos valores positivos

//variáveis independentes para receber os valores da matriz antes de repassá-los aos objetos

/*GroupGeral*/
    bool key_vel_on; DADO tempo; bool transp_on;
    DADO transp_value; bool reverb_on; DADO reverb_value;
    bool chorus_on; DADO chorus_value;
/*GroupUppers*/
    bool up1_on; DADO up1_tone; DADO up1_vol; DADO up1_oct;
    bool up2_on; DADO up2_tone; DADO up2_vol; DADO up2_oct;
    DADO up2_state;
/*GroupLower*/
    bool lower_actv; DADO lower_tone; DADO lower_vol;
    DADO lower_oct;DADO lower_split; bool lower_int;
    bool lower_mem;
/*Group MBass/MDrums*/
    bool mbass_on; DADO mbass_tone; DADO mbass_vol;
    bool mdrums_on; DADO mdrums_kit;


// ------------------- Transfere dados para a tab USER PROGRAM_1 ------------------------

if(qual_uspr == USER_ALL || qual_uspr == USER_P_1)
{

    coleta_bytes(USPRL_1, &key_vel_on, &tempo, &transp_on, &transp_value,
                  &reverb_on, &reverb_value, &chorus_on, &chorus_value,
                  &up1_on, &up1_tone, &up1_vol, &up1_oct,
                  &up2_on, &up2_tone, &up2_vol, &up2_oct, &up2_state,
                  &lower_actv, &lower_tone, &lower_vol, &lower_oct,
                  &lower_split, &lower_int, &lower_mem,
                  &mbass_on, &mbass_tone, &mbass_vol,
                  &mdrums_on, &mdrums_kit);

    //passa variáveis para os objetos:

    CheckKey_1->Checked             = key_vel_on;
    EditTempo_1->Text               = IntToStr((UNSIG)tempo);
    CheckTransp_1->Checked          = transp_on;
    ScrollTransp_1->Position        = transp_value;
    CheckReverb_1->Checked          = reverb_on;
    ScrollReverb_1->Position        = reverb_value;
    CheckChorus_1->Checked          = chorus_on;
    ScrollChorus_1->Position        = chorus_value;

    CheckUP1_1->Checked             = up1_on;
    CheckUP2_1->Checked             = up2_on;
    CheckLower_1->Checked           = lower_actv;
    CheckMBass_1->Checked           = mbass_on;
    CheckMDrums_1->Checked          = mdrums_on;

    //procedimento para carregar os nomes dos Tones para às ComboBoxes  ---inicio---

    //carrega arquivo com as values no formato: 0=A11 Pian...
    ComboUP1_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboUP2_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboLower_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMBass_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMDrums_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumvalues.dat");

    ComboUP1_1->Text = (ComboUP1_1->Items->Values[(UNSIG)up1_tone]);
    ComboUP2_1->Text = (ComboUP2_1->Items->Values[(UNSIG)up2_tone]);
    ComboLower_1->Text = (ComboLower_1->Items->Values[(UNSIG)lower_tone]);
    ComboMBass_1->Text = (ComboMBass_1->Items->Values[(UNSIG)mbass_tone]);
    ComboMDrums_1->Text = (ComboMDrums_1->Items->Values[(UNSIG)mdrums_kit]);

    //recupera info para utilização normal
    ComboUP1_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboUP2_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboLower_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMBass_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMDrums_1->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumlist.dat");

    ScrollUP1Vol_1->Position        = up1_vol;
    ScrollUP2Vol_1->Position        = up2_vol;
    ScrollLowerVol_1->Position      = lower_vol;
    ScrollMBassVol_1->Position      = mbass_vol;

    ScrollUP1Oct_1->Position        = up1_oct;
    ScrollUP2Oct_1->Position        = up2_oct;
    ScrollLowerOct_1->Position      = lower_oct;

    ScrollSplitLower_1->Position    = lower_split;

    //verifica Upper 2 State:
    if(up2_state == UP2_DESATIVADO)     RadioUP2Desativado_1->Checked = true;
    else if(up2_state == UP2_MEL_INT)   RadioUP2MelInt_1->Checked = true;
    else                                RadioUP2Layer_1->Checked = true;

    CheckLowerInt_1->Checked        = lower_int;
    CheckLowerMem_1->Checked        = lower_mem;
}

// ------------------- Transfere dados para a tab USER PROGRAM_2 ------------------------

if(qual_uspr == USER_ALL || qual_uspr == USER_P_2)
{

    coleta_bytes(USPRL_2, &key_vel_on, &tempo, &transp_on, &transp_value,
                  &reverb_on, &reverb_value, &chorus_on, &chorus_value,
                  &up1_on, &up1_tone, &up1_vol, &up1_oct,
                  &up2_on, &up2_tone, &up2_vol, &up2_oct, &up2_state,
                  &lower_actv, &lower_tone, &lower_vol, &lower_oct,
                  &lower_split, &lower_int, &lower_mem,
                  &mbass_on, &mbass_tone, &mbass_vol,
                  &mdrums_on, &mdrums_kit);

    //passa variáveis para os objetos:

    CheckKey_2->Checked             = key_vel_on;
    EditTempo_2->Text               = IntToStr((UNSIG)tempo);
    CheckTransp_2->Checked          = transp_on;
    ScrollTransp_2->Position        = transp_value;
    CheckReverb_2->Checked          = reverb_on;
    ScrollReverb_2->Position        = reverb_value;
    CheckChorus_2->Checked          = chorus_on;
    ScrollChorus_2->Position        = chorus_value;

    CheckUP1_2->Checked             = up1_on;
    CheckUP2_2->Checked             = up2_on;
    CheckLower_2->Checked           = lower_actv;
    CheckMBass_2->Checked           = mbass_on;
    CheckMDrums_2->Checked          = mdrums_on;

    //procedimento para carregar os nomes dos Tones para às ComboBoxes  ---inicio---

    //carrega arquivo com as values no formato: 0=A11 Pian...
    ComboUP1_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboUP2_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboLower_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMBass_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMDrums_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumvalues.dat");

    ComboUP1_2->Text = (ComboUP1_2->Items->Values[(UNSIG)up1_tone]);
    ComboUP2_2->Text = (ComboUP2_2->Items->Values[(UNSIG)up2_tone]);
    ComboLower_2->Text = (ComboLower_2->Items->Values[(UNSIG)lower_tone]);
    ComboMBass_2->Text = (ComboMBass_2->Items->Values[(UNSIG)mbass_tone]);
    ComboMDrums_2->Text = (ComboMDrums_2->Items->Values[(UNSIG)mdrums_kit]);

    //recupera info para utilização normal
    ComboUP1_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboUP2_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboLower_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMBass_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMDrums_2->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumlist.dat");

    ScrollUP1Vol_2->Position        = up1_vol;
    ScrollUP2Vol_2->Position        = up2_vol;
    ScrollLowerVol_2->Position      = lower_vol;
    ScrollMBassVol_2->Position      = mbass_vol;

    ScrollUP1Oct_2->Position        = up1_oct;
    ScrollUP2Oct_2->Position        = up2_oct;
    ScrollLowerOct_2->Position      = lower_oct;

    ScrollSplitLower_2->Position    = lower_split;

    //verifica Upper 2 State:
    if(up2_state == UP2_DESATIVADO)     RadioUP2Desativado_2->Checked = true;
    else if(up2_state == UP2_MEL_INT)   RadioUP2MelInt_2->Checked = true;
    else                                RadioUP2Layer_2->Checked = true;

    CheckLowerInt_2->Checked        = lower_int;
    CheckLowerMem_2->Checked        = lower_mem;
}

// ------------------- Transfere dados para a tab USER PROGRAM_3 ------------------------

if(qual_uspr == USER_ALL || qual_uspr == USER_P_3)
{

    coleta_bytes(USPRL_3, &key_vel_on, &tempo, &transp_on, &transp_value,
                  &reverb_on, &reverb_value, &chorus_on, &chorus_value,
                  &up1_on, &up1_tone, &up1_vol, &up1_oct,
                  &up2_on, &up2_tone, &up2_vol, &up2_oct, &up2_state,
                  &lower_actv, &lower_tone, &lower_vol, &lower_oct,
                  &lower_split, &lower_int, &lower_mem,
                  &mbass_on, &mbass_tone, &mbass_vol,
                  &mdrums_on, &mdrums_kit);

    //passa variáveis para os objetos:

    CheckKey_3->Checked             = key_vel_on;
    EditTempo_3->Text               = IntToStr((UNSIG)tempo);
    CheckTransp_3->Checked          = transp_on;
    ScrollTransp_3->Position        = transp_value;
    CheckReverb_3->Checked          = reverb_on;
    ScrollReverb_3->Position        = reverb_value;
    CheckChorus_3->Checked          = chorus_on;
    ScrollChorus_3->Position        = chorus_value;

    CheckUP1_3->Checked             = up1_on;
    CheckUP2_3->Checked             = up2_on;
    CheckLower_3->Checked           = lower_actv;
    CheckMBass_3->Checked           = mbass_on;
    CheckMDrums_3->Checked          = mdrums_on;

    //procedimento para carregar os nomes dos Tones para às ComboBoxes  ---inicio---

    //carrega arquivo com as values no formato: 0=A11 Pian...
    ComboUP1_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboUP2_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboLower_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMBass_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMDrums_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumvalues.dat");

    ComboUP1_3->Text = (ComboUP1_3->Items->Values[(UNSIG)up1_tone]);
    ComboUP2_3->Text = (ComboUP2_3->Items->Values[(UNSIG)up2_tone]);
    ComboLower_3->Text = (ComboLower_3->Items->Values[(UNSIG)lower_tone]);
    ComboMBass_3->Text = (ComboMBass_3->Items->Values[(UNSIG)mbass_tone]);
    ComboMDrums_3->Text = (ComboMDrums_3->Items->Values[(UNSIG)mdrums_kit]);

    //recupera info para utilização normal
    ComboUP1_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboUP2_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboLower_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMBass_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMDrums_3->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumlist.dat");

    ScrollUP1Vol_3->Position        = up1_vol;
    ScrollUP2Vol_3->Position        = up2_vol;
    ScrollLowerVol_3->Position      = lower_vol;
    ScrollMBassVol_3->Position      = mbass_vol;

    ScrollUP1Oct_3->Position        = up1_oct;
    ScrollUP2Oct_3->Position        = up2_oct;
    ScrollLowerOct_3->Position      = lower_oct;

    ScrollSplitLower_3->Position    = lower_split;

    //verifica Upper 2 State:
    if(up2_state == UP2_DESATIVADO)     RadioUP2Desativado_3->Checked = true;
    else if(up2_state == UP2_MEL_INT)   RadioUP2MelInt_3->Checked = true;
    else                                RadioUP2Layer_3->Checked = true;

    CheckLowerInt_3->Checked        = lower_int;
    CheckLowerMem_3->Checked        = lower_mem;
}

// ------------------- Transfere dados para a tab USER PROGRAM_4 ------------------------

if(qual_uspr == USER_ALL || qual_uspr == USER_P_4)
{

    coleta_bytes(USPRL_4, &key_vel_on, &tempo, &transp_on, &transp_value,
                  &reverb_on, &reverb_value, &chorus_on, &chorus_value,
                  &up1_on, &up1_tone, &up1_vol, &up1_oct,
                  &up2_on, &up2_tone, &up2_vol, &up2_oct, &up2_state,
                  &lower_actv, &lower_tone, &lower_vol, &lower_oct,
                  &lower_split, &lower_int, &lower_mem,
                  &mbass_on, &mbass_tone, &mbass_vol,
                  &mdrums_on, &mdrums_kit);

    //passa variáveis para os objetos:

    CheckKey_4->Checked             = key_vel_on;
    EditTempo_4->Text               = IntToStr((UNSIG)tempo);
    CheckTransp_4->Checked          = transp_on;
    ScrollTransp_4->Position        = transp_value;
    CheckReverb_4->Checked          = reverb_on;
    ScrollReverb_4->Position        = reverb_value;
    CheckChorus_4->Checked          = chorus_on;
    ScrollChorus_4->Position        = chorus_value;

    CheckUP1_4->Checked             = up1_on;
    CheckUP2_4->Checked             = up2_on;
    CheckLower_4->Checked           = lower_actv;
    CheckMBass_4->Checked           = mbass_on;
    CheckMDrums_4->Checked          = mdrums_on;

    //procedimento para carregar os nomes dos Tones para às ComboBoxes  ---inicio---

    //carrega arquivo com as values no formato: 0=A11 Pian...
    ComboUP1_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboUP2_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboLower_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMBass_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMDrums_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumvalues.dat");

    ComboUP1_4->Text = (ComboUP1_4->Items->Values[(UNSIG)up1_tone]);
    ComboUP2_4->Text = (ComboUP2_4->Items->Values[(UNSIG)up2_tone]);
    ComboLower_4->Text = (ComboLower_4->Items->Values[(UNSIG)lower_tone]);
    ComboMBass_4->Text = (ComboMBass_4->Items->Values[(UNSIG)mbass_tone]);
    ComboMDrums_4->Text = (ComboMDrums_4->Items->Values[(UNSIG)mdrums_kit]);

    //recupera info para utilização normal
    ComboUP1_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboUP2_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboLower_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMBass_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMDrums_4->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumlist.dat");

    ScrollUP1Vol_4->Position        = up1_vol;
    ScrollUP2Vol_4->Position        = up2_vol;
    ScrollLowerVol_4->Position      = lower_vol;
    ScrollMBassVol_4->Position      = mbass_vol;

    ScrollUP1Oct_4->Position        = up1_oct;
    ScrollUP2Oct_4->Position        = up2_oct;
    ScrollLowerOct_4->Position      = lower_oct;

    ScrollSplitLower_4->Position    = lower_split;

    //verifica Upper 2 State:
    if(up2_state == UP2_DESATIVADO)     RadioUP2Desativado_4->Checked = true;
    else if(up2_state == UP2_MEL_INT)   RadioUP2MelInt_4->Checked = true;
    else                                RadioUP2Layer_4->Checked = true;

    CheckLowerInt_4->Checked        = lower_int;
    CheckLowerMem_4->Checked        = lower_mem;
}

// ------------------- Transfere dados para a tab USER PROGRAM_5 ------------------------

if(qual_uspr == USER_ALL || qual_uspr == USER_P_5)
{

    coleta_bytes(USPRL_5, &key_vel_on, &tempo, &transp_on, &transp_value,
                  &reverb_on, &reverb_value, &chorus_on, &chorus_value,
                  &up1_on, &up1_tone, &up1_vol, &up1_oct,
                  &up2_on, &up2_tone, &up2_vol, &up2_oct, &up2_state,
                  &lower_actv, &lower_tone, &lower_vol, &lower_oct,
                  &lower_split, &lower_int, &lower_mem,
                  &mbass_on, &mbass_tone, &mbass_vol,
                  &mdrums_on, &mdrums_kit);

    //passa variáveis para os objetos:

    CheckKey_5->Checked             = key_vel_on;
    EditTempo_5->Text               = IntToStr((UNSIG)tempo);
    CheckTransp_5->Checked          = transp_on;
    ScrollTransp_5->Position        = transp_value;
    CheckReverb_5->Checked          = reverb_on;
    ScrollReverb_5->Position        = reverb_value;
    CheckChorus_5->Checked          = chorus_on;
    ScrollChorus_5->Position        = chorus_value;

    CheckUP1_5->Checked             = up1_on;
    CheckUP2_5->Checked             = up2_on;
    CheckLower_5->Checked           = lower_actv;
    CheckMBass_5->Checked           = mbass_on;
    CheckMDrums_5->Checked          = mdrums_on;

    //procedimento para carregar os nomes dos Tones para às ComboBoxes  ---inicio---

    //carrega arquivo com as values no formato: 0=A11 Pian...
    ComboUP1_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboUP2_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboLower_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMBass_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMDrums_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumvalues.dat");

    ComboUP1_5->Text = (ComboUP1_5->Items->Values[(UNSIG)up1_tone]);
    ComboUP2_5->Text = (ComboUP2_5->Items->Values[(UNSIG)up2_tone]);
    ComboLower_5->Text = (ComboLower_5->Items->Values[(UNSIG)lower_tone]);
    ComboMBass_5->Text = (ComboMBass_5->Items->Values[(UNSIG)mbass_tone]);
    ComboMDrums_5->Text = (ComboMDrums_5->Items->Values[(UNSIG)mdrums_kit]);

    //recupera info para utilização normal
    ComboUP1_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboUP2_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboLower_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMBass_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMDrums_5->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumlist.dat");

    ScrollUP1Vol_5->Position        = up1_vol;
    ScrollUP2Vol_5->Position        = up2_vol;
    ScrollLowerVol_5->Position      = lower_vol;
    ScrollMBassVol_5->Position      = mbass_vol;

    ScrollUP1Oct_5->Position        = up1_oct;
    ScrollUP2Oct_5->Position        = up2_oct;
    ScrollLowerOct_5->Position      = lower_oct;

    ScrollSplitLower_5->Position    = lower_split;

    //verifica Upper 2 State:
    if(up2_state == UP2_DESATIVADO)     RadioUP2Desativado_5->Checked = true;
    else if(up2_state == UP2_MEL_INT)   RadioUP2MelInt_5->Checked = true;
    else                                RadioUP2Layer_5->Checked = true;

    CheckLowerInt_5->Checked        = lower_int;
    CheckLowerMem_5->Checked        = lower_mem;
}

// ------------------- Transfere dados para a tab USER PROGRAM_6 ------------------------

if(qual_uspr == USER_ALL || qual_uspr == USER_P_6)
{

    coleta_bytes(USPRL_6, &key_vel_on, &tempo, &transp_on, &transp_value,
                  &reverb_on, &reverb_value, &chorus_on, &chorus_value,
                  &up1_on, &up1_tone, &up1_vol, &up1_oct,
                  &up2_on, &up2_tone, &up2_vol, &up2_oct, &up2_state,
                  &lower_actv, &lower_tone, &lower_vol, &lower_oct,
                  &lower_split, &lower_int, &lower_mem,
                  &mbass_on, &mbass_tone, &mbass_vol,
                  &mdrums_on, &mdrums_kit);

    //passa variáveis para os objetos:

    CheckKey_6->Checked             = key_vel_on;
    EditTempo_6->Text               = IntToStr((UNSIG)tempo);
    CheckTransp_6->Checked          = transp_on;
    ScrollTransp_6->Position        = transp_value;
    CheckReverb_6->Checked          = reverb_on;
    ScrollReverb_6->Position        = reverb_value;
    CheckChorus_6->Checked          = chorus_on;
    ScrollChorus_6->Position        = chorus_value;

    CheckUP1_6->Checked             = up1_on;
    CheckUP2_6->Checked             = up2_on;
    CheckLower_6->Checked           = lower_actv;
    CheckMBass_6->Checked           = mbass_on;
    CheckMDrums_6->Checked          = mdrums_on;

    //procedimento para carregar os nomes dos Tones para às ComboBoxes  ---inicio---

    //carrega arquivo com as values no formato: 0=A11 Pian...
    ComboUP1_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboUP2_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboLower_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMBass_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMDrums_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumvalues.dat");

    ComboUP1_6->Text = (ComboUP1_6->Items->Values[(UNSIG)up1_tone]);
    ComboUP2_6->Text = (ComboUP2_6->Items->Values[(UNSIG)up2_tone]);
    ComboLower_6->Text = (ComboLower_6->Items->Values[(UNSIG)lower_tone]);
    ComboMBass_6->Text = (ComboMBass_6->Items->Values[(UNSIG)mbass_tone]);
    ComboMDrums_6->Text = (ComboMDrums_6->Items->Values[(UNSIG)mdrums_kit]);

    //recupera info para utilização normal
    ComboUP1_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboUP2_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboLower_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMBass_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMDrums_6->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumlist.dat");

    ScrollUP1Vol_6->Position        = up1_vol;
    ScrollUP2Vol_6->Position        = up2_vol;
    ScrollLowerVol_6->Position      = lower_vol;
    ScrollMBassVol_6->Position      = mbass_vol;

    ScrollUP1Oct_6->Position        = up1_oct;
    ScrollUP2Oct_6->Position        = up2_oct;
    ScrollLowerOct_6->Position      = lower_oct;

    ScrollSplitLower_6->Position    = lower_split;

    //verifica Upper 2 State:
    if(up2_state == UP2_DESATIVADO)     RadioUP2Desativado_6->Checked = true;
    else if(up2_state == UP2_MEL_INT)   RadioUP2MelInt_6->Checked = true;
    else                                RadioUP2Layer_6->Checked = true;

    CheckLowerInt_6->Checked        = lower_int;
    CheckLowerMem_6->Checked        = lower_mem;
}

// ------------------- Transfere dados para a tab USER PROGRAM_7 ------------------------

if(qual_uspr == USER_ALL || qual_uspr == USER_P_7)
{

    coleta_bytes(USPRL_7, &key_vel_on, &tempo, &transp_on, &transp_value,
                  &reverb_on, &reverb_value, &chorus_on, &chorus_value,
                  &up1_on, &up1_tone, &up1_vol, &up1_oct,
                  &up2_on, &up2_tone, &up2_vol, &up2_oct, &up2_state,
                  &lower_actv, &lower_tone, &lower_vol, &lower_oct,
                  &lower_split, &lower_int, &lower_mem,
                  &mbass_on, &mbass_tone, &mbass_vol,
                  &mdrums_on, &mdrums_kit);

    //passa variáveis para os objetos:

    CheckKey_7->Checked             = key_vel_on;
    EditTempo_7->Text               = IntToStr((UNSIG)tempo);
    CheckTransp_7->Checked          = transp_on;
    ScrollTransp_7->Position        = transp_value;
    CheckReverb_7->Checked          = reverb_on;
    ScrollReverb_7->Position        = reverb_value;
    CheckChorus_7->Checked          = chorus_on;
    ScrollChorus_7->Position        = chorus_value;

    CheckUP1_7->Checked             = up1_on;
    CheckUP2_7->Checked             = up2_on;
    CheckLower_7->Checked           = lower_actv;
    CheckMBass_7->Checked           = mbass_on;
    CheckMDrums_7->Checked          = mdrums_on;

    //procedimento para carregar os nomes dos Tones para às ComboBoxes  ---inicio---

    //carrega arquivo com as values no formato: 0=A11 Pian...
    ComboUP1_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboUP2_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboLower_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMBass_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMDrums_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumvalues.dat");

    ComboUP1_7->Text = (ComboUP1_7->Items->Values[(UNSIG)up1_tone]);
    ComboUP2_7->Text = (ComboUP2_7->Items->Values[(UNSIG)up2_tone]);
    ComboLower_7->Text = (ComboLower_7->Items->Values[(UNSIG)lower_tone]);
    ComboMBass_7->Text = (ComboMBass_7->Items->Values[(UNSIG)mbass_tone]);
    ComboMDrums_7->Text = (ComboMDrums_7->Items->Values[(UNSIG)mdrums_kit]);

    //recupera info para utilização normal
    ComboUP1_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboUP2_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboLower_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMBass_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMDrums_7->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumlist.dat");

    ScrollUP1Vol_7->Position        = up1_vol;
    ScrollUP2Vol_7->Position        = up2_vol;
    ScrollLowerVol_7->Position      = lower_vol;
    ScrollMBassVol_7->Position      = mbass_vol;

    ScrollUP1Oct_7->Position        = up1_oct;
    ScrollUP2Oct_7->Position        = up2_oct;
    ScrollLowerOct_7->Position      = lower_oct;

    ScrollSplitLower_7->Position    = lower_split;

    //verifica Upper 2 State:
    if(up2_state == UP2_DESATIVADO)     RadioUP2Desativado_7->Checked = true;
    else if(up2_state == UP2_MEL_INT)   RadioUP2MelInt_7->Checked = true;
    else                                RadioUP2Layer_7->Checked = true;

    CheckLowerInt_7->Checked        = lower_int;
    CheckLowerMem_7->Checked        = lower_mem;
}

// ------------------- Transfere dados para a tab USER PROGRAM_8 ------------------------

if(qual_uspr == USER_ALL || qual_uspr == USER_P_8)
{

    coleta_bytes(USPRL_8, &key_vel_on, &tempo, &transp_on, &transp_value,
                  &reverb_on, &reverb_value, &chorus_on, &chorus_value,
                  &up1_on, &up1_tone, &up1_vol, &up1_oct,
                  &up2_on, &up2_tone, &up2_vol, &up2_oct, &up2_state,
                  &lower_actv, &lower_tone, &lower_vol, &lower_oct,
                  &lower_split, &lower_int, &lower_mem,
                  &mbass_on, &mbass_tone, &mbass_vol,
                  &mdrums_on, &mdrums_kit);

    //passa variáveis para os objetos:

    CheckKey_8->Checked             = key_vel_on;
    EditTempo_8->Text               = IntToStr((UNSIG)tempo);
    CheckTransp_8->Checked          = transp_on;
    ScrollTransp_8->Position        = transp_value;
    CheckReverb_8->Checked          = reverb_on;
    ScrollReverb_8->Position        = reverb_value;
    CheckChorus_8->Checked          = chorus_on;
    ScrollChorus_8->Position        = chorus_value;

    CheckUP1_8->Checked             = up1_on;
    CheckUP2_8->Checked             = up2_on;
    CheckLower_8->Checked           = lower_actv;
    CheckMBass_8->Checked           = mbass_on;
    CheckMDrums_8->Checked          = mdrums_on;

    //procedimento para carregar os nomes dos Tones para às ComboBoxes  ---inicio---

    //carrega arquivo com as values no formato: 0=A11 Pian...
    ComboUP1_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboUP2_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboLower_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMBass_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonevalues.dat");
    ComboMDrums_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumvalues.dat");

    ComboUP1_8->Text = (ComboUP1_8->Items->Values[(UNSIG)up1_tone]);
    ComboUP2_8->Text = (ComboUP2_8->Items->Values[(UNSIG)up2_tone]);
    ComboLower_8->Text = (ComboLower_8->Items->Values[(UNSIG)lower_tone]);
    ComboMBass_8->Text = (ComboMBass_8->Items->Values[(UNSIG)mbass_tone]);
    ComboMDrums_8->Text = (ComboMDrums_8->Items->Values[(UNSIG)mdrums_kit]);

    //recupera info para utilização normal
    ComboUP1_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboUP2_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboLower_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMBass_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_tonelist.dat");
    ComboMDrums_8->Items->LoadFromFile(ExtractFilePath(Application->ExeName) + "_drumlist.dat");

    ScrollUP1Vol_8->Position        = up1_vol;
    ScrollUP2Vol_8->Position        = up2_vol;
    ScrollLowerVol_8->Position      = lower_vol;
    ScrollMBassVol_8->Position      = mbass_vol;

    ScrollUP1Oct_8->Position        = up1_oct;
    ScrollUP2Oct_8->Position        = up2_oct;
    ScrollLowerOct_8->Position      = lower_oct;

    ScrollSplitLower_8->Position    = lower_split;

    //verifica Upper 2 State:
    if(up2_state == UP2_DESATIVADO)     RadioUP2Desativado_8->Checked = true;
    else if(up2_state == UP2_MEL_INT)   RadioUP2MelInt_8->Checked = true;
    else                                RadioUP2Layer_8->Checked = true;

    CheckLowerInt_8->Checked        = lower_int;
    CheckLowerMem_8->Checked        = lower_mem;
}
    return;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuNewClick(TObject *Sender)
{
    if (MessageBox(NULL, msg_novo.c_str(),"New User Program", MB_OKCANCEL) == IDCANCEL)
        return;

    /* se continuar a criar o novo arquivo, apaga todos os USPRs inserindo  /
    /                                                    os valores padrão */
    for(int i=0;i<80;i++)
    {
        USPRL_1[i] = USPR_NEW[i];
        USPRL_2[i] = USPR_NEW[i];
        USPRL_3[i] = USPR_NEW[i];
        USPRL_4[i] = USPR_NEW[i];
        USPRL_5[i] = USPR_NEW[i];
        USPRL_6[i] = USPR_NEW[i];
        USPRL_7[i] = USPR_NEW[i];
        USPRL_8[i] = USPR_NEW[i];
    }
    matriz_para_uspr(USER_ALL); //coloca os novos valores no FormPrincipal


    Caminho_Salvar = ""; // Apaga o caminho de qualquer arquivo para save
                         //Para evitar de apagar o último arquivo aberto
    //coloca foco no User Program 1
    PagePrincipal->ActivePage = TabUSPR_1;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuCopyUSPRClick(TObject *Sender)
{
    //DEPOIS, encaixar aqui uma função para verificar conteudo do tempo, e combo boxes
    // para evitar valores invalidos como "NULL" ou outros valores inválidos ou tempo<20 e >250


    //verifica por tempos inválidos e corrige
    CorrigeTempoTranspose();


    // garante que USPR[x] vai conter o valor atual apresentado na tela
    if(PagePrincipal->ActivePage != NULL) PagePrincipalChanging(Sender, NULL);

    if(tabfocus == 1)
    {
        for(int i=0;i<80;i++)
            USPR_MEM[i] = USPR_1[i]; //copia valores na tela para a memória
    }

    else if(tabfocus == 2)
    {
        for(int i=0;i<80;i++)
            USPR_MEM[i] = USPR_2[i]; //copia valores na tela para a memória
    }
    else if(tabfocus == 3)
    {
        for(int i=0;i<80;i++)
            USPR_MEM[i] = USPR_3[i]; //copia valores na tela para a memória
    }
    else if(tabfocus == 4)
    {
        for(int i=0;i<80;i++)
            USPR_MEM[i] = USPR_4[i]; //copia valores na tela para a memória
    }
    else if(tabfocus == 5)
    {
        for(int i=0;i<80;i++)
            USPR_MEM[i] = USPR_5[i]; //copia valores na tela para a memória
    }
    else if(tabfocus == 6)
    {
        for(int i=0;i<80;i++)
            USPR_MEM[i] = USPR_6[i]; //copia valores na tela para a memória
    }
    else if(tabfocus == 7)
    {
        for(int i=0;i<80;i++)
            USPR_MEM[i] = USPR_7[i]; //copia valores na tela para a memória
    }
    else if(tabfocus == 8)
    {
        for(int i=0;i<80;i++)
            USPR_MEM[i] = USPR_8[i]; //copia valores na tela para a memória
    }

    //como a memória de transição tem algum valor, agora sim habilita o "Colar"
    // no caso de ser a primeira vez a usar o "Copiar"
    if(MenuPasteUSPR->Enabled == false) MenuPasteUSPR->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuPasteUSPRClick(TObject *Sender)
{
    //verifica a tab ativada, e usa variável de load (USPRL_X) para a transição
    if(tabfocus == 1)
    {
        for(int i=0;i<80;i++)
            USPRL_1[i] = USPR_MEM[i];

        matriz_para_uspr(USER_P_1); //coloca os novos valores na tela
    }

    else if(tabfocus == 2)
    {
        for(int i=0;i<80;i++)
            USPRL_2[i] = USPR_MEM[i];

        matriz_para_uspr(USER_P_2); //coloca os novos valores na tela
    }
    else if(tabfocus == 3)
    {
        for(int i=0;i<80;i++)
            USPRL_3[i] = USPR_MEM[i];

        matriz_para_uspr(USER_P_3); //coloca os novos valores na tela
    }
    else if(tabfocus == 4)
    {
        for(int i=0;i<80;i++)
            USPRL_4[i] = USPR_MEM[i];

        matriz_para_uspr(USER_P_4); //coloca os novos valores na tela
    }
    else if(tabfocus == 5)
    {
        for(int i=0;i<80;i++)
            USPRL_5[i] = USPR_MEM[i];

        matriz_para_uspr(USER_P_5); //coloca os novos valores na tela
    }
    else if(tabfocus == 6)
    {
        for(int i=0;i<80;i++)
            USPRL_6[i] = USPR_MEM[i];

        matriz_para_uspr(USER_P_6); //coloca os novos valores na tela
    }
    else if(tabfocus == 7)
    {
        for(int i=0;i<80;i++)
            USPRL_7[i] = USPR_MEM[i];

        matriz_para_uspr(USER_P_7); //coloca os novos valores na tela
    }
    else if(tabfocus == 8)
    {
        for(int i=0;i<80;i++)
            USPRL_8[i] = USPR_MEM[i];

        matriz_para_uspr(USER_P_8); //coloca os novos valores na tela
    }
}
//---------------------------------------------------------------------------





void __fastcall TFormPrincipal::English1Click(TObject *Sender)
{
    MenuFile->Caption = "&File";
        MenuNew->Caption = "&New";
        MenuOpen->Caption = "&Open";
        MenuSave->Caption = "&Save";
        MenuSaveAs->Caption = "Sa&ve As";
        MenuClose->Caption = "&Close";

    MenuEdit->Caption = "&Edit";
        MenuCopyUSPR->Caption = "&Copy current User Program to memory";
        MenuPasteUSPR->Caption = "&Paste on current User Program from memory";

     MenuOptions->Caption = "&Options";
        MenuLanguage->Caption = "&Language";

    MenuAbout0->Caption = "&About";
        MenuAbout->Caption = "&About";
        MenuWhereStyles->Caption = "&Where is the Style settings?";

    //alem dos nomes dos menus criar variáveis para avisos em caixas de texto
    //e modificar nestas funções
    msg_sair    = MSG_SAIR_ENG;
    msg_transp  = MSG_TRANSP_ENG;
    msg_novo    = MSG_NOVO_ENG;
    msg_about   = MSG_ABOUT_ENG;
    msg_open_err = MSG_OPEN_ENG;
    msg_sobreescrever = MSG_SOBREESCREVER_ENG;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::Portugues1Click(TObject *Sender)
{
    MenuFile->Caption = "&Arquivo";
        MenuNew->Caption = "&Novo";
        MenuOpen->Caption = "Abri&r";
        MenuSave->Caption = "&Salvar";
        MenuSaveAs->Caption = "Sal&var Como";
        MenuClose->Caption = "&Fechar";

    MenuEdit->Caption = "&Editar";
        MenuCopyUSPR->Caption = "&Copiar User Program atual para a memória";
        MenuPasteUSPR->Caption = "Co&lar User Program que está na memória";

     MenuOptions->Caption = "&Opções";
        MenuLanguage->Caption = "&Linguagem";

    MenuAbout0->Caption = "&Sobre";
        MenuAbout->Caption = "&Sobre";
        MenuWhereStyles->Caption = "Onde está a configuração de dos rítmos (Styles)?";


    //no FormCreate ou Show, verificar tag em arquivo e executar esta função
    // para alterar a linguagem logo no início
    msg_sair    = MSG_SAIR_POR;
    msg_transp  = MSG_TRANSP_POR;
    msg_novo    = MSG_NOVO_POR;
    msg_about   = MSG_ABOUT_POR;
    msg_open_err = MSG_OPEN_POR;
    msg_sobreescrever = MSG_SOBREESCREVER_POR;
}
//---------------------------------------------------------------------------

//faz execuções de EditTempoExit() e   ScrollTransp_1Exit
//para corrigir a função de Cópia de USPR
void __fastcall  TFormPrincipal::CorrigeTempoTranspose()
{
    if(tabfocus == 1)      {EditTempo_1Exit(NULL); ScrollTransp_1Exit(NULL);}
    else if(tabfocus == 2) {EditTempo_2Exit(NULL); ScrollTransp_2Exit(NULL);}
    else if(tabfocus == 3) {EditTempo_3Exit(NULL); ScrollTransp_3Exit(NULL);}
    else if(tabfocus == 4) {EditTempo_4Exit(NULL); ScrollTransp_4Exit(NULL);}
    else if(tabfocus == 5) {EditTempo_5Exit(NULL); ScrollTransp_5Exit(NULL);}
    else if(tabfocus == 6) {EditTempo_6Exit(NULL); ScrollTransp_6Exit(NULL);}
    else if(tabfocus == 7) {EditTempo_7Exit(NULL); ScrollTransp_7Exit(NULL);}
    else if(tabfocus == 8) {EditTempo_8Exit(NULL); ScrollTransp_8Exit(NULL);}
}

void __fastcall TFormPrincipal::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
    if (MessageDlg(msg_sair,
                 mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel,0) == mrCancel)

        CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::MenuAboutClick(TObject *Sender)
{
    ShowMessage(msg_about);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuWhereStylesClick(TObject *Sender)
{
    //apenas verifica se está em ingles (através do caption),
    //se não, abre o arquivo em português
    if(MenuWhereStyles->Caption == "&Where is the Style settings?")
        WinExec("Notepad.exe no_styles_eng.txt",SW_SHOW);
    else
        WinExec("Notepad.exe no_styles_por.txt",SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::MenuImprimirClick(TObject *Sender)
{
    //variaveis para uso local nesta função

    String key_prt; // Key Velocity Print
    String tmp_prt; // Tempo Value
    String tr_prt;  // Transpose
    String trv_prt; // Transpose Value
    String rvt_prt; // Reverb Type
    String rvv_prt; // Reverb Value
    String cht_prt; // Chorus Type
    String chv_prt; // Chorus Value

    // (...)


    // inserir MsgBox pedindo para inserir o nome da música
    RichEditImprimir->Lines->Add("NOME DA MÚSICA");

    RichEditImprimir->Lines->Add("\nUSER PROGRAM [1]\n");

    if(CheckKey_1->Checked) key_prt = "ON"; else key_prt = "OFF";
    RichEditImprimir->Lines->Add("Key Velocity: " + key_prt);

    tmp_prt = EditTempo_1->Text;
    RichEditImprimir->Lines->Add("Tempo: " + tmp_prt);

    trv_prt = LabelTransp_1->Caption;

    if(CheckTransp_1->Checked) tr_prt = "ON"; else tr_prt = "OFF";
    RichEditImprimir->Lines->Add("Transpose: " + tr_prt);
    RichEditImprimir->Lines->Add("Transpose Value: " + trv_prt);



    ShowMessage(RichEditImprimir->Text);// DEBUG

    //perguntar se deseja imprimir pela impressora ou imprimir em arquivo com SaveDialog2;


    /*Envia o Text do RichEditImprimir para a impressora imprimeir*/
    // if (PrintDialog1->Execute()) RichEditImprimir->Print(RichEditImprimir->Text);
    // else ShowMessage("Erro ao imprimir");

    //no final de cada solocitação da função Print do Menu, apagar os dados em RichEdit Imprimir
    RichEditImprimir->Text = "";
}
//---------------------------------------------------------------------------

