#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <cstring>
#include <locale.h>

using namespace std;

struct Dados
{
    string nome,id,idd,x,y;
    int inicio, fim; // inicio e fim do automato


};

Dados maqui1[100]; //dados da máquina, q0, q1, q2
Dados staIni [100]; //pegar os dados do inicio, para fazer a união
Dados maqui2[100];


struct transicoes
{
    string de, para, ler;

};

transicoes transi1[1000], transi2[1000], traIn[1000]; //pegar os dados das transições, ex: do estado 0 para o estado 1 lendo 0
int main()
{
    setlocale(LC_ALL, "Portuguese");

    string lerArqui, perc; // perc, fazer o percurso, ler o arquivo . LerAqui - ler enquanto o arquivo for doferente de /automatos

    fstream Maquina1("teste 1.jff");
    fstream Maquina2 ("teste 2.jff"); // arquivos para fazer as operações de uni�o e concatenação
    fstream buscaIn ("importar inic.jff"); //importar o arquivo para pegar o estado inicial para a união

    int contMD1id = 0,contMD1id2 = 0, contMD1na = 0,
        contMD1x = 0, contMD1y = 0, contIn = 0,
        contFi = 0, contS1 = 0, op; //contadores para os dados

    int contTde = 0, contTpr = 0,
        contTr = 0, conT = 0,cont = 0; //contadores das transições


    //SALVANDO DADOS DA PRIMEIRA MAQUINA
    while (getline(Maquina1,lerArqui)) //percorrer todo o arquivo
    {
        if (lerArqui == "\t\t<!--The list of states.-->&#13;") //se o arquivo for igual a essa condição, ele percorrer a partir dai
        {
            getline(Maquina1,perc); //lê a linha que está abaixo de "ler arquivo"
            do
            {


                for (int i = 0 ; i < perc.size(); i++) //percorrer linhas do arquivo
                {

                    if (perc[i] == '<' && perc[i+1] =='i') //quando achar o estado que é inicial
                        maqui1[contMD1id - 1].inicio = 1; //[contMD1id - 1] para pegar o estado inicial

                    if (perc[i] == '<' && perc[i+1] =='f')
                        maqui1[contMD1id - 1].fim = 1;

                    if (perc[i] == '<' && perc[i+1] == 's' )
                    {
                        if (perc.substr(15,1) == "n")  //pega os caracteres dos estados
                            maqui1[contMD1id].id = perc.substr(12,5);
                        else
                            maqui1[contMD1id].id = perc.substr(12,4);
                        maqui1[contMD1id].idd = perc.substr(13,1);  //substr copia os caracteres que está no arquivo
                        contMD1id ++;

                    }

                }


                for (int i = 0; i < perc.size(); i++) // vai pegar o id dos automatos
                {
                    if (perc[i] == 'n' && perc[i+1] == 'a' && perc[i+2] == 'm')
                    {
                        if (perc.substr(21,1) == "=")
                            maqui1[contMD1na].nome = perc.substr(22,5);
                        else
                        maqui1[contMD1na].nome = perc.substr(21,4);
                        contMD1na++;

                    }
                }
                for (int i = 0; i < perc.size(); i++) //pega a posição x e y
                {
                    if (perc[i] == '<' && perc[i+1] == 'x')
                    {
                        if (perc.substr(8,1) == ".")
                            maqui1[contMD1x].x= perc.substr(6,4);
                        else
                            maqui1[contMD1x].x = perc.substr(6,5);
                        contMD1x++;
                    }
                }


                for (int i = 0; i < perc.size(); i++)
                {
                    if (perc[i] == '<' && perc[i+1] == 'y')
                    {
                        if (perc.substr(8,1) == ".")
                            maqui1[contMD1y].y = perc.substr(6,4);
                        else
                            maqui1[contMD1y].y = perc.substr(6,5);
                        contMD1y++;
                    }
                }

                getline(Maquina1,perc);
            }
            while (perc != "\t\t<!--The list of transitions.-->&#13;"); // percorrer enquanto perc for diferente da condição

            if (lerArqui == "\t\t<!--The list of transitions.-->&#13;") // faz o mesmo que o if do início, só que agora com transições
                ;
            {
                getline(Maquina1,perc);

                do
                {
                    for(int i = 0; i < perc.size(); i++)
                    {
                        if (perc[i] == '<' && perc[i+1] == 'f')
                        {
                            if (perc.substr(11,1) == "<")
                                transi1[contTde].de = perc.substr(9,2);
                            else
                                transi1[contTde].de = perc.substr(9,1);
                            contTde++;
                        }
                    }

                    for (int i = 0; i < perc.size(); i++)
                    {
                        if (perc[i] == '<' && perc[i+1] == 't' && perc[i+2] == 'o')
                        {
                            if (perc.substr(9,1) == "<")
                                transi1[contTpr].para = perc.substr(7,2);
                            else
                            transi1[contTpr].para = perc.substr(7,1);

                            contTpr++;}
                    }

                    for (int i = 0; i < perc.size(); i++)
                    {
                        if (perc[i] == '<' && perc[i+1] == 'r')
                        {
                            if (perc.substr(8,1) == "/" )
                                transi1[contTr].ler = perc.substr(8,1);
                            else
                                transi1[contTr].ler = perc.substr(9,1);
                            contTr++;
                        }
                    }


                    getline(Maquina1,perc);
                }
                while(perc != "\t</automaton>&#13;");

            }
        }
    }


    contMD1id = 0;
    contMD1na = 0;
    contMD1x = 0;
    contMD1y = 0;
    contTde = 0;
    contTpr = 0;
    contTr = 0;



    while (getline(Maquina2,lerArqui))
    {

        if (lerArqui == "\t\t<!--The list of states.-->&#13;")
        {
            getline(Maquina2,perc);
            do
            {
                for (int i = 0 ; i < perc.size(); i++)
                {

                    if (perc[i] == '<' && perc[i+1] =='i')
                        maqui2[contMD1id - 1].inicio = 1;

                    if (perc[i] == '<' && perc[i+1] =='f')
                        maqui2[contMD1id - 1].fim = 1;

                    if (perc[i] == '<' && perc[i+1] == 's' )
                    {
                        if (perc.substr(17,1) == "n" )
                            maqui2[contMD1id].id = perc.substr(12,5);
                        else
                            maqui2[contMD1id].id = perc.substr(12,4);
                        maqui2[contMD1id].idd = perc.substr(13,1);

                        contMD1id ++;
                    }

                }


                for (int i = 0; i < perc.size(); i++)
                {
                    if (perc[i] == 'n' && perc[i+1] == 'a' && perc[i+2] == 'm')
                    {
                        if (perc.substr(21,1) == "=")
                            maqui2[contMD1na].nome = perc.substr(22,5);
                        else
                        maqui2[contMD1na].nome = perc.substr(21,4);
                        contMD1na++;
                    }
                }
                for (int i = 0; i < perc.size(); i++)
                {
                    if (perc[i] == '<' && perc[i+1] == 'x')
                    {
                        if (perc.substr(8,1) == ".")
                            maqui2[contMD1x].x= perc.substr(6,4);
                        else
                            maqui2[contMD1x].x= perc.substr(6,5);

                        contMD1x++;
                    }
                }


                for (int i = 0; i < perc.size(); i++)
                {
                    if (perc[i] == '<' && perc[i+1] == 'y')
                    {
                        if (perc.substr(8,1) == ".")
                            maqui2[contMD1y].y = perc.substr(6,4);
                        else
                            maqui2[contMD1y].y = perc.substr(6,5);
                        contMD1y++;
                    }
                }

                getline(Maquina2,perc);
            }
            while (perc != "\t\t<!--The list of transitions.-->&#13;");

            if (lerArqui == "\t\t<!--The list of transitions.-->&#13;")
                ;
            {


                do
                {
                    getline(Maquina2,perc);
                    for(int i = 0; i < perc.size(); i++)
                    {
                        if (perc[i] == '<' && perc[i+1] == 'f')
                        {
                            if (perc.substr(11,1) == "<")
                                transi2[contTde].de = perc.substr(9,2);
                            else
                            transi2[contTde].de = perc.substr(9,1);
                            contTde++;
                        }
                    }

                    for (int i = 0; i < perc.size(); i++)
                    {
                        if (perc[i] == '<' && perc[i+1] == 't' && perc[i+2] == 'o')
                        {
                            if (perc.substr(9,1) == "<")
                                transi2[contTpr].para = perc.substr(7,2);
                            else
                            transi2[contTpr].para = perc.substr(7,1);

                            contTpr++;
                        }
                    }

                    for (int i = 0; i < perc.size(); i++)
                    {
                        if (perc[i] == '<' && perc[i+1] == 'r')
                        {
                            if (perc.substr(8,1) == "/" )
                                transi2[contTr].ler = perc.substr(8,1);
                                else
                                    transi2[contTr].ler = perc.substr(9,1);
                            contTr++;

                        }
                    }



                }
                while(perc != "\t</automaton>&#13;");

            }
        }
    }

    while (getline(buscaIn, lerArqui))
    {

        if (lerArqui == "\t\t<!--The list of states.-->&#13;")

            getline(buscaIn, perc);
        do
        {

            for (int i = 0 ; i < perc.size(); i++)
            {

                if (perc[i] == '<' && perc[i+1] =='i')
                    staIni[0].inicio = 1;

                if (perc[i] == '<' && perc[i+1] =='f')
                    staIni[0].fim = 1;

                if (perc[i] == '<' && perc[i+1] == 's' )
                {
                    staIni[0].id = perc.substr(12,6);
                    traIn[0].de = perc.substr(13,3);

                }

            }


            for (int i = 0; i < perc.size(); i++)
            {
                if (perc[i] == 'n' && perc[i+1] == 'a' && perc[i+2] == 'm')
                {

                    staIni[0].nome = perc.substr(23,4);
                    contMD1na++;
                }
            }
            for (int i = 0; i < perc.size(); i++)
            {
                if (perc[i] == '<' && perc[i+1] == 'x')
                {
                    if (perc.substr(8,1) == ".")
                        staIni[0].x= perc.substr(6,4);
                    else
                        staIni[0].x = perc.substr(6,5);

                }
            }


            for (int i = 0; i < perc.size(); i++)
            {
                if (perc[i] == '<' && perc[i+1] == 'y')
                {
                    if (perc.substr(8,1) == ".")
                        staIni[0].y = perc.substr(6,4);
                    else
                        staIni[0].y = perc.substr(6,5);

                }
            }
            getline(buscaIn,perc);
        }
        while(perc != "\t</automaton>&#13;");





    }

    char* arquivoN = "jflep.jff";



    fstream exem;


    do
    {
        cout << "====== OPERAÇÕES REGULARES =====" << endl;
        cout << "\n1 - União " << endl;
        cout << "2 - Concatenação" << endl;
        cout << "3 - Visualizar o autamato 1"<<endl;
        cout << "4 - Visualizar o autamato 2\n"<<endl;
        cout <<"================================\n";
        cout <<"\nEscolha a operação ou digite 0 para sair: " << endl;
        cin >> op;
        cout << endl;

        switch (op)
        {
        case 1:
            exem.open(arquivoN,ios::out | ios :: trunc); //(União) salvar tudo no arquivo - Se cria um estado inicial, pegando suas coordenadas
            exem <<"<?xml version="<<'"'<<"1.0"<<'"'<<" encoding="<<'"'<<"UTF-8"<<'"'<<" standalone="<<'"'<<"no"<<'"'<<
                 "?><!--Created with JFLAP 6.4.--><structure>&#13;" <<endl;
            exem << "\t<type>fa</type>&#13;" << endl;
            exem << "\t<automaton>&#13;"<<endl;
            exem << "\t\t<!--The list of states.-->&#13;"<< endl;
            exem << "\t\t<state id="<< staIni[0].id <<"name="<< staIni[0].nome <<">&#13;"<<endl;
            exem << "\t\t\t<x>"<< staIni[0].x <<"</x>&#13;"<< endl;
            exem << "\t\t\t<y>"<< staIni[0].y <<"</y>&#13;"<<endl;
            exem << "\t\t\t<initial/>&#13;"<<endl;
            exem << "\t\t</state>&#13;"<<endl;

            for (int i = 0; i < 20; i++) //salvar os dados que foram pegos anteriormente  da máquina 1
            {
                if (maqui1[i].id == "")
                    break;
                else
                {
                    exem << "\t\t<state id="<< maqui1[i].id <<"name="<< maqui1[i].nome <<">&#13;"<<endl;
                    exem << "\t\t\t<x>"<< maqui1[i].x <<"</x>&#13;"<< endl;
                    exem << "\t\t\t<y>"<< maqui1[i].y <<"</y>&#13;"<<endl;
                    if (maqui1[i].fim == 1) //verifica se o estado é final. Caso ele não seja, ele fecha o estado
                        exem << "\t\t\t<final/>&#13;"<<endl;
                    exem << "\t\t</state>&#13;"<<endl;
                }

            }

            for (int i = 0; i < 20; i++)
            {
                if (maqui2[i].id == "")
                    break;
                else
                {
                    exem << "\t\t<state id="<< maqui2[i].id <<"name="<< maqui2[i].nome <<">&#13;"<<endl;
                    exem << "\t\t\t<x>"<< maqui2[i].x <<"</x>&#13;"<< endl;
                    exem << "\t\t\t<y>"<< maqui2[i].y <<"</y>&#13;"<<endl;
                    if (maqui2[i].fim == 1)
                        exem << "\t\t\t<final/>&#13;"<<endl;
                    exem << "\t\t</state>&#13;"<<endl;
                }

            }


            while (conT < 10)
            {
                if (maqui1[conT].inicio == 1) //verifica se o estado é inicial, para poder fazer a transição do novo estado inicial para os antigos estados iniciais
                {
                    exem << "\t\t<!--The list of transitions.-->&#13;"<<endl;
                    exem << "\t\t<transition>&#13;"<<endl;
                    exem << "\t\t\t<from>"<<traIn[0].de <<"</from>&#13;"<<endl;
                    exem << "\t\t\t<to>"<<maqui1[conT].idd<<"</to>&#13;"<<endl;
                    exem << "\t\t\t<read/>&#13;"<<endl;
                    exem << "\t\t</transition>&#13;"<<endl;
                }

                conT++;
            }
            conT = 0;
            while (conT < 10)
            {

                if (maqui2[conT].inicio == 1)
                {
                    exem << "\t\t<transition>&#13;"<<endl;
                    exem << "\t\t\t<from>"<<traIn[0].de <<"</from>&#13;"<<endl;
                    exem << "\t\t\t<to>"<<maqui2[conT].idd<<"</to>&#13;"<<endl;
                    exem << "\t\t\t<read/>&#13;"<<endl;
                    exem << "\t\t</transition>&#13;"<<endl;
                }
                conT ++;
            }


            for (int i = 0; i < 100; i++) //fazer as transições
            {
                if (transi1[i].de == "")  // garantir que ele não fique lendo vazio
                    break;
                else
                {
                    exem << "\t\t<transition>&#13;"<<endl;
                    exem << "\t\t\t<from>"<<transi1[i].de<<"</from>&#13;"<<endl;
                    exem << "\t\t\t<to>"<<transi1[i].para<<"</to>&#13;"<<endl;
                    if (transi1[i].ler == "/") // o barra faz a ligação por epsilon e, caso não faz a ligação pelos outros simbolos
                        exem << "\t\t\t<read/>&#13;"<<endl;
                    else
                        exem << "\t\t\t<read>"<<transi1[i].ler<<"</read>&#13;"<<endl;
                    exem << "\t\t</transition>&#13;"<<endl;
                }
            }
            for (int i = 0; i < 100; i++)
            {
                if (transi2[i].de == "")
                    break;
                else
                {
                    exem << "\t\t<transition>&#13;"<<endl;
                    exem << "\t\t\t<from>"<<transi2[i].de<<"</from>&#13;"<<endl;
                    exem << "\t\t\t<to>"<<transi2[i].para<<"</to>&#13;"<<endl;
                    if (transi2[i].ler == "/")
                        exem << "\t\t\t<read/>&#13;"<<endl;
                    else
                    exem << "\t\t\t<read>"<<transi2[i].ler<<"</read>&#13;"<<endl;
                    exem << "\t\t</transition>&#13;"<<endl;
                }
            }
            exem << "\t</automaton>&#13;"<<endl;
            exem << "</structure>" <<endl;
            exem.close(); //fecha o arquivo

            system("pause");
            system("cls");

            break;

        case 2:
            exem.open(arquivoN,ios::out | ios :: trunc);
            exem <<"<?xml version="<<'"'<<"1.0"<<'"'<<" encoding="<<'"'<<"UTF-8"<<'"'<<" standalone="<<'"'<<"no"<<'"'<<
                 "?><!--Created with JFLAP 6.4.--><structure>&#13;" <<endl;
            exem << "\t<type>fa</type>&#13;" << endl;
            exem << "\t<automaton>&#13;"<<endl;
            exem << "\t\t<!--The list of states.-->&#13;"<< endl;
            cont = 0;
            for (int i = 0; i < 10; i++)
            {
                if (maqui1[i].id == "")
                    break;
                else
                {
                    if (maqui1[i].inicio == 1)
                    {
                        exem << "\t\t<state id="<< maqui1[i].id <<"name="<< maqui1[cont].nome <<">&#13;"<<endl;
                        exem << "\t\t\t<x>"<< maqui1[i].x <<"</x>&#13;"<< endl;
                        exem << "\t\t\t<y>"<< maqui1[i].y <<"</y>&#13;"<<endl;
                        exem << "\t\t\t<initial/>&#13;"<<endl;
                        exem << "\t\t</state>&#13;"<<endl;
                        i++;
                    }
                    exem << "\t\t<state id="<< maqui1[i].id <<"name="<< maqui1[i].nome <<">&#13;"<<endl;
                    exem << "\t\t\t<x>"<< maqui1[i].x <<"</x>&#13;"<< endl;
                    exem << "\t\t\t<y>"<< maqui1[i].y <<"</y>&#13;"<<endl;
                    exem << "\t\t</state>&#13;"<<endl;
                }

            }

            for (int i = 0; i < 10; i++)
            {
                if (maqui2[i].id == "")
                    break;
                else
                {
                    exem << "\t\t<state id="<< maqui2[i].id <<"name="<< maqui2[i].nome <<">&#13;"<<endl;
                    exem << "\t\t\t<x>"<< maqui2[i].x <<"</x>&#13;"<< endl;
                    exem << "\t\t\t<y>"<< maqui2[i].y <<"</y>&#13;"<<endl;
                    if (maqui2[i].fim == 1)
                        exem << "\t\t\t<final/>&#13;"<<endl;
                    exem << "\t\t</state>&#13;"<<endl;
                }
            }
            exem << "\t\t<!--The list of transitions.-->&#13;"<<endl;
            for (int i = 0; i < 100; i++)
            {
                if (transi1[i].de == "")
                    break;
                else
                {   if (maqui1[i].fim == 1){
                    for (int j = 0; j < 10 ; j++){
                        if (maqui2[j].inicio == 1){
                    exem << "\t\t<transition>&#13;"<<endl;
                    exem << "\t\t\t<from>"<<maqui1[i].idd <<"</from>&#13;"<<endl;
                    exem << "\t\t\t<to>"<<maqui2[j].idd<<"</to>&#13;"<<endl;
                    exem << "\t\t\t<read/>&#13;"<<endl;
                    exem << "\t\t</transition>&#13;"<<endl;

                        }
                    }
                }
                    exem << "\t\t<transition>&#13;"<<endl;
                    exem << "\t\t\t<from>"<<transi1[i].de<<"</from>&#13;"<<endl;
                    exem << "\t\t\t<to>"<<transi1[i].para<<"</to>&#13;"<<endl;
                    if (transi1[i].ler == "/")
                        exem << "\t\t\t<read/>&#13;"<<endl;
                    else
                    exem << "\t\t\t<read>"<<transi1[i].ler<<"</read>&#13;"<<endl;
                    exem << "\t\t</transition>&#13;"<<endl;}

            }
                        for (int i = 0; i < 100; i++)
            {
                if (transi2[i].de == "")
                    break;
                else
                {
                    exem << "\t\t<transition>&#13;"<<endl;
                    exem << "\t\t\t<from>"<<transi2[i].de<<"</from>&#13;"<<endl;
                    exem << "\t\t\t<to>"<<transi2[i].para<<"</to>&#13;"<<endl;
                    if (transi2[i].ler == "/")
                        exem << "\t\t\t<read/>&#13;"<<endl;
                    else
                    exem << "\t\t\t<read>"<<transi2[i].ler<<"</read>&#13;"<<endl;
                    exem << "\t\t</transition>&#13;"<<endl;
                }
            }

            exem << "\t</automaton>&#13;"<<endl;
            exem << "</structure>" <<endl;
            exem.close();

            system("pause");
            system("cls");

            break;

        case 3:{
            ifstream automato1;
            string linhaAut1;
            automato1.open("teste 1.jff");

            if(automato1.is_open()){
                while(getline(automato1,linhaAut1)){
                    cout << linhaAut1 << endl;
                }
            }
            else {
                cout << "N�o foi poss�vel abrir o arquivo";
            }
            system("pause");
            system("cls");
            }break;

        case 4:{
            ifstream automato2;
            string linhaAut2;
            automato2.open("teste 2.jff");

            if(automato2.is_open()){
                while(getline(automato2,linhaAut2)){
                    cout << linhaAut2 << endl;
                }
            }
            else {
                cout << "N�o foi poss�vel abrir o arquivo";
            }

            system("pause");
            system("cls");

            }break;
        }
    }
    while(op != 0);

    return 0;
}
