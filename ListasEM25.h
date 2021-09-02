#ifndef _LISTASEM25_H_
#define _LISTASEM25_H_


////////////////////////////////////////////////////////////////////////////////
// Função que converte o valor de número para o Nome do Tipo de Reverb Selecionado
////////////////////////////////////////////////////////////////////////////////
AnsiString ReverbName(int value)
{
    switch(value)
    {
        case 0: return "Room 1";
        case 1: return "Room 2";
        case 2: return "Room 3";
        case 3: return "Hall 1";
        case 4: return "Hall 2";
        case 5: return "Plate";
        case 6: return "Delay";
        case 7: return "Pan Delay";
    }

    return "Erro"; // Caso (impossível), de valor diferente, retorna erro

}


////////////////////////////////////////////////////////////////////////////////
// Função que converte o valor de número para o Nome do Tipo de Chorus Selecionado
////////////////////////////////////////////////////////////////////////////////
AnsiString ChorusName(int value)
{
    switch(value)
    {
        case 0: return "Chorus 1";
        case 1: return "Chorus 2";
        case 2: return "Chorus 3";
        case 3: return "Chorus 4";
        case 4: return "Flanger";
        case 5: return "FeedBack";
        case 6: return "Delay";
        case 7: return "Fdback Delay";
    }

    return "Erro"; // Caso (impossível), de valor diferente, retorna erro

}
////////////////////////////////////////////////////////////////////////////////
// Função que converte o valor de número para o Nome da Nota de Split Point
////////////////////////////////////////////////////////////////////////////////
AnsiString LowerSplitNote(int value)
{
    switch(value)
    {
        case 12: return "C2";
        case 13: return "C#2/Db2";
        case 14: return "D2";
        case 15: return "D#2/Eb2";
        case 16: return "E2";
        case 17: return "F2";
        case 18: return "F#2/Gb2";
        case 19: return "G2";
        case 20: return "G#2/Ab2";
        case 21: return "A2";
        case 22: return "A#2/Bb2";
        case 23: return "B2";

        case 24: return "C3";
        case 25: return "C#3/Db3";
        case 26: return "D3";
        case 27: return "D#3/Eb3";
        case 28: return "E3";
        case 29: return "F3";
        case 30: return "F#3/Gb3";
        case 31: return "G3";
        case 32: return "G#3/Ab3";
        case 33: return "A3";
        case 34: return "A#3/Bb3";
        case 35: return "B3";

        case 36: return "C4";
        case 37: return "C#4/Db4";
        case 38: return "D4";
        case 39: return "D#4/Eb4";
        case 40: return "E4";
        case 41: return "F4";
        case 42: return "F#4/Gb4";
        case 43: return "G4";
        case 44: return "G#4/Ab4";
        case 45: return "A4";
        case 46: return "A#4/Bb4";
        case 47: return "B4";
        
        case 48: return "C5";
    }

    return "Erro"; // Caso (impossível), de valor diferente, retorna erro
}

// Listas de mensagens do programa em inglês e português

const String MSG_SAIR_POR("Realmente deseja fechar o programa? Dados não salvos serão perdidos!");
const String MSG_SAIR_ENG("Sure you want to leave? Unsaved data will be lost!");

const String MSG_TRANSP_POR("O valor do Transpose não pode ser \"0\" \n Valor Padrão: \"1\"");
const String MSG_TRANSP_ENG("Transpose Value can't be \"0\" \n Default Value: \"1\"");

const String MSG_NOVO_POR("Deseja iniciar um novo arquivo? Dados não salvos serão perdidos!");
const String MSG_NOVO_ENG("Create new file? Unsaved data will be lost!");


const String MSG_ABOUT_POR("Criação e Edição de User Programs para o teclado musical Roland EM-25\n"
                           "Criado por Henrique L. Vilela\n\n"
                           "Versão: 0.9"
                          );
                                  //versão 0.9 devido a erros conhecidos "combobox"=NULL por exemplo;
const String MSG_ABOUT_ENG("Creating and Editing User Programs for musical keyboard Roland EM-25\n"
                            "Created by Henrique L. Vilela\n\n"
                            "Version: 0.9"
                          );

const String MSG_OPEN_POR("Arquivo não encontrado!");
const String MSG_OPEN_ENG("File not found!");

const String MSG_SOBREESCREVER_POR("Já existe um arquivo com esse nome. Deseja sobreescrevê-lo?");
const String MSG_SOBREESCREVER_ENG("There are another file using this name. Overwrite?");
#endif
