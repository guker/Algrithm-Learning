#include <ctime>
#include <string>
#include "huffman.h"

using namespace std;


/*
=======================================================================================================================
MAIN PRINCIPALE DEL PROGETTO
=======================================================================================================================
*/

int main()
{
	/*====================*/
	char nome_file[50];   

	clock_t start,end;  
	double time;  
	char   mode;   
	/*====================*/
	cout << endl;
	cout << "=========================================================================" << endl;
	cout << "=======                                                           =======" << endl;
	cout << "======      Compresion Or Decompresion file(txt,wav,bmp and so on): ======" << endl;
	cout << "=====                    Huffmann encode and decode                =====" << endl;
	cout << "====                             hqwsky                            ====" << endl;
	cout << "=========================================================================" << endl;



	cout <<"Do you want to compress or decompress a  file?"<<endl;
	for(;;)
	{
		cout << "=========================================" << endl;
		cout << "** 1. Compress" << endl;
		cout << "** 2. Decompress" << endl;
		cout << "** 3. Exit" << endl;
		cout << "** ---> ";
		cin >> mode;
		cout << "=========================================" << endl;

		switch(mode)
		{
		case '1':
			{
				cout << endl;
				cout << "\t==========================================================" << endl;
				cout << endl;
				cout << "\t==                 Compression by Huffman code         ==" << endl;
				cout << endl;
				cout << "\t==========================================================" << endl;
				cout << endl;

				cout <<"input filename with extension "<<endl;
				cout <<"--->";
				cin >> nome_file;
				start = clock();
				ifstream File_da_comprimere(nome_file); 
				if(!File_da_comprimere) 
				{
					cout << "file not exist!\n";
					system("pause");
					return -1;
				}
				Encoder encode;
				encode.Encode(nome_file,"Encoded_File.huf");/*richiamo il metodo Encode che si occupa di comprimere il file*/
				Valuta_Compressione v_comp(nome_file,"Encoded_File.huf");/*richiamo il metodo Valuta_Compressione che si occupa 
																		 di calcolare il tasso di compressione */

				end = clock();/*fermo il tempo*/
				time = ((double)(end-start))/CLOCKS_PER_SEC; //calcola il tempo impiegato

				/*Stampo in output i risultati della compressione stampando:
				la dimensione in byte del file
				tasso di compressione
				guadagno di spazio dopo la compressione del file*/
				cout << "\t==========================================================" << endl;
				cout << "\t=====              Compression Result            =====" << endl;
				cout << "\t==========================================================" << endl;
				cout <<" file " << nome_file << " has " << v_comp.Calcola_Dimensione_File() << " byte" << endl;
				cout << " Compression Rate: "<< v_comp.Compression_Rate() << endl;
				cout << " save space : "<< v_comp.Guadagno_Spazio() << " %" << endl << endl;
				cout << " Compressed file : Encoded_File.huf" << endl;
				cout <<"----------------------------------------------------------"<<endl;
				cout << " duration :  " << time << "sec" << endl;
			}
		
			break;
		case '2':
			{
				cout << endl;
				cout << "\t============================================================" << endl;
				cout << endl;
				cout << "\t==             decomprssion by Huffman decode            ==" << endl;
				cout << endl;
				cout << "\t============================================================" << endl;
				cout << endl;

				/*viene chiesto di inserire il file da decomprimere*/
				cout <<"input decompressed file with extension "<<endl;
				cout<<"---->";
				cin >> nome_file;
				start = clock();/*faccio partire il tempo*/
				ifstream File_da_comprimere(nome_file); /* se il file non esiste stampo un errore a video */
				if(!File_da_comprimere) {
					cout << "file  not exist!\n";
					system("pause");
					return -1;
				}
				Decoder decode;
				decode.Decode("Encoded_File.huf","Decrypted_File.dhuf");/*richiamo la funzione decode che decomprime il file*/
				end = clock();/*fermo il tempo*/

				time = ((double)(start-end))/CLOCKS_PER_SEC; //calcola il tempo impiegato
				cout <<endl;
				cout << " decompressed file: Decrypted_File.dhuf " << endl;
				cout <<"----------------------------------------------------------"<<endl;
				cout << " duration: " << time << "sec" << endl;
			}

			break;
			/*la tereza scelta implica la chiusura del programma*/
		case '3':
			exit(0);

			/*nel caso in cui viene inserito un carattere errato viene stampata la seguente riga*/
		default:
			cout << " retry\n";
		}

	}

	system("pause");
	return 0;

}
