#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
 =======================================================================================================================
    CONTENUTO DEL FILE HUFFMAN.H
 =======================================================================================================================
 */


/*
 =======================================================================================================================
 La classe File_Data contieni gli attributi utilizzati da altre classi.
 Questa classe serve per rendere disponibili informazioni ricavate dall'analisi del file da comprimere.
 Per questo motivo gli attributi sono stati dichiarati protected per essere disponibili ad altre classi.
 
 N.B.: una classe rappresenta un tipo di dato astratto che puo' contenere elementi in stretta relazione tra loro
    che condividono gli stessi attributi ;
 =======================================================================================================================
 */

class File_Data
{  
 
public:

      /*
     ===========================================================================
      Costruttore della classe File_Data
     ===========================================================================
     */
	File_Data()   { };
	
	
	 /*
     ===========================================================================
       Distruttore della classe File_Data
     ===========================================================================
     */
	
	~File_Data()  { };
	
	/*
======================================================================================================================
    COSTRUTTORE: e' una funzione membro utile per inizializzare le variabili della classe. Ha sempre lo stesso nome
    della classe a cui appartiene, puo' accettare argomenti.Ogni volta ceh viene creato un oggetto viene sempre
    eseguito prima il costruttore, se non viene dichiarato esplicitamente viene generato automaticamente dal
    compilatore.
    DISTRUTTORE: e' anche esso una funzione membro di una classe, ha lo stesso nome della classe in
    oggetto ma anticipato dal simbolo (tilde), la sua funzione e' quella di restituire al sistema la memoria allocata
    dall'oggetto. Non puo' accettare argomenti, anceh esso se non viene dichiarato esplicitamente viene creato
    automaticamente dal compilatore.
======================================================================================================================
 */
	
	/*====================================================================================================================
	Attributi dichiarati static in una classe sono condivisi da tutti gli oggetti di quella classe
	Attiributi statici possono essere usati e modificati soltanto da metodi statici
	=======================================================================================================================*/

	static int numero_caratteri  ()  { return Numero_Caratteri;  };
	static int caratteri_diversi ()  { return Caratteri_Diversi; };
	static int* vettore_caratteri()  { return Vettore_Caratteri; };
	static int* vettore_frequenze()  { return Vettore_Frequenze; };
	
	/*====================================================================================================================
     protected: accessibili alle funzioni membro appartenenti alla stessa classe e alle classi da questa derivate.
	=======================================================================================================================*/
	
protected:
	static int Numero_Caratteri; /* indica quanti caratteri sono presenti nel file */
	static int Caratteri_Diversi; /* contiene il numero di caratteri diversi */
	static int* Vettore_Caratteri; /* vettore che contiene i caratteri */
	static int* Vettore_Frequenze; /* vettore che contiene le frequenze dei corrispondenti caratteri */
};
 /*
 =======================================================================================================================
    Dichiaro una classe Node. Crea due tipi di nodo che formano l'albero.
	Attraverso l'overloading sono stati creati quindi due costruttori, uno per il nodo foglia e l'altro per il
	nodo interno.
	L'operatore cast verrà utilizzato per trattare gli oggetti Node come int rispetto alle loro frequenze

 
    Overloading:Questa funzionalità permette di poter utilizzare lo stesso nome per una funzione più volte all’interno 
	dello stesso programma, a patto però che gli argomenti forniti siano differenti. In maniera automatica, 
	il programma eseguirà la funzione appropriata a seconda del tipo di argomenti passati.
 =======================================================================================================================
 */
 
class Node
{
  /*
     ===========================================================================
      public: accessibili da ogni parte del programma entro il campo di validità
	  della classe in oggetto
     ===========================================================================
     */
public:

     /*
     ===========================================================================
      Costruttore della classe Node foglia
     ===========================================================================
     */
	Node(int,Node*); 
	
	
	/*
     ===========================================================================
      Costruttore della classe Node interno
     ===========================================================================
     */
	Node(Node*, Node*);	
	
	 /*
     ===========================================================================
       Distruttore della classe Node
     ===========================================================================
     */
	~Node(){}; 
	
	
	/*metodi get inline*/
	int Value        ()      { return value; }; 
	Node* Parent     ()      { return parent; };
	Node* ChildLeft  ()      { return Child_Left; };
	Node* ChildRight ()      { return Child_Right; };
	
	 /*
     ===================================================================================
      se dichiariamo un operator int() dentro una classe, 
	  saremo in grado di convertire un oggetto di questa classe in un valore intero. 
	 ===================================================================================
     */
	
	operator int&    ()       { return Frequence; };	/*operatore di cast*/
	
	 /*
 =======================================================================================================================
    Modificatore Private: utilizzabili solo all'interno dalla classe stessa
 =======================================================================================================================
 */
private:
	int Frequence;
	int value;
	Node* parent;	     /*puntatore al genitore*/
	
	Node* Child_Left;	/*puntatore al figlio sinisto*/
	Node* Child_Right;	/*puntatore al figlio destro*/
};

 /*
 =======================================================================================================================
    Dichiaro una classe Min_Heap. Simula una coda di Min-priority,i metodi utilizzati sono quelli di
	inserimento ed estrazione
 =======================================================================================================================
 */
class Min_Heap
{
public:

     /*
     ===========================================================================
      Costruttore della classe Min_Heap contenente il numero max di nodi
     ===========================================================================
     */
	Min_Heap(int Max_n_Node);
	
	
	 /*
     ===========================================================================
       Distruttore della classe Min_Heap
     ===========================================================================
     */
	~Min_Heap(){ delete[] min_heap; }; /*libera tutta la memoria allocata*/


	void Insert(Node*); /*Metodo Insert che prende in input un puntatore a Node*/
	bool Extract_min(Node**); /*Metodo che restituisce l'indirizzo del puntatore a Node*/


private:

	int  Compare(int i,int j);

	int    Max_Num_Node;
	int    N_Node_Corrente;
	Node** min_heap; /*Array di puntatori a Node*/
	
};
 /*
 =======================================================================================================================
    Dichiaro una classe Tree.È formata dalle altre tre classi,Node,Min_Heap e File_Data.
	Appena sono state raccolte le informazioni del file inserito viene chiamato il costruttore.
	Quando viene creato l'oggetto il costruttore di default genera l'albero iniziando da un array di nodi foglia
	e attraverso l'heap effettua gli inserimenti le estrazioni e le fusioni.
	I metodi get di Tree restituiscono le foglie che servono alla codifica e la radice che servirà alla decodifica.
 =======================================================================================================================
 */

class Tree
{
public:

     /*
     ===========================================================================
      Costruttore della classe Tree
     ===========================================================================
     */
	Tree();
	
	 /*
     ===========================================================================
       Distruttore della classe Tree
     ===========================================================================
     */
	~Tree()              { delete [] Vettore_Foglie; };/*dealloca la memoria*/

	Node** get_Foglie()  { return Vettore_Foglie; };
	Node*  get_Root()    { return root; };


private:
	Node** Vettore_Foglie; /*contiene i nodi con valori e frequenze*/
	Node* root;
};

 /*
 =======================================================================================================================
    Dichiaro una classe Read_File che legge il file in input.
	Ci sono due modalità di lettura, per il file sorgente vi è una lettura byte per byte,
	per il file codificato una lettura bit per bit.
	Il metodo Read_Source_File raccoglie le informazioni per la costruzione dell'albero
 =======================================================================================================================
 */

class Read_File : public File_Data /*classe derivata*/
{
public:

     /*
     ===========================================================================
      Costruttore della classe Read_File contenente il nome del file 
	  da leggere
     ===========================================================================
     */
	Read_File(char*);
	
	 /*
     ===========================================================================
       Distruttore della classe Read_File(chiude il file)
	   deallocando la memoria
     ===========================================================================
     */

	~Read_File             ()  {  Finput.close(); };



	int Read_Bit           ();              /*legge i bit*/
	int Read_Carat         ();           /*legge gli elementi del file*/
	void Read_Source_File  ();   /*legge dal file sorgente*/
	
	
private:

	ifstream Finput;         /* dichiarazione del file input */
	int Bit_File_Sequence;  /* definisco la variabile che conterra' la sequenza in bit del corrispondente  file */
	int Size_Sequence;     /* definisco la variabile che conterra' la grandezza della sequenza sopracitata */
};

 /*
 =======================================================================================================================
    dichiaro una classe Write_File che scrive sul file.
	I metodi dichiarati servono per scrivere sul file codificato e decodificato
 =======================================================================================================================
 */

class Write_File : public File_Data /*classe derivata*/
{
public:

     /*
     ===========================================================================
      Costruttore della classe Write_File contenente il nome del file
	  da scrivere
     ===========================================================================
     */
	Write_File(char*);
	
	 /*
     ===========================================================================
       Distruttore della classe Write_File
     ===========================================================================
     */
	~Write_File();


	/*per la scrittura del bit passato come parametro int*/
	void Write_Bit(int);
	/*per la scrittura del byte passato sempre come int*/
	void Write_Carat(int Carattere){ Foutput.put(Carattere); };


private:

	ofstream Foutput;/* dichiarazione del file che verra' scritto */
	int Bit_File_Sequence;/* definisco la variabile che conterra' la sequenza in bit del corrispondente file */
	int Size_Sequence;/* definisco la variabile che conterra' la grandezza della sequenza sopracitata */
};



 
 /*
 =======================================================================================================================
    dichiaro una classe Encoder che mi permettera' di codificare il file in ingresso ;
    
    Specificatori di Accesso: ricordo che PRIVATE rende accessibili gli attributi SOLO alle funzioni membro, 
	mentre PUBLIC rende gli attributi accessibili da ogni parte del programma
 =======================================================================================================================
 */

class Encoder
{
public:

    /*
     ===========================================================================
      Costruttore della classe Encoder
     ===========================================================================
     */
	Encoder   ()    { };
	
	 /*
     ===========================================================================
       Distruttore della classe Encoder
     ===========================================================================
     */
	~Encoder  ()   { }; 


/* dichiaro la procedura di codifica del file */
	void Encode(char* ,char* );



private:

	void Encode_Carat(Node* , Write_File*);
};


 /*
 =======================================================================================================================
    dichiaro una classe Decoder per decodificare il file codificato 
 =======================================================================================================================
 */

class Decoder
{
public:

/*
     ===========================================================================
      Costruttore della classe Decoder
     ===========================================================================
     */
	Decoder   ()  { };
	
	
	 /*
     ===========================================================================
       Distruttore della classe Decoder
     ===========================================================================
     */
	~Decoder  ()  { };


	/* dichiaro la procedura di decodifica del file */
	void Decode(char* ,char* );


private:

	int Decode_Carat(Node* ,Read_File* );
};

 /*
 =======================================================================================================================
    dichiaro una classe Valuta_Compressione che valuta il tasso di compressione(compression Rate) e il guadagno 
	di spazio dopo aver compresso il file
 =======================================================================================================================
 */

class Valuta_Compressione : public File_Data /*classe derivata*/
{
public:

/*
     ===========================================================================
      Costruttore della classe Valuta_Compressione
     ===========================================================================
     */
	Valuta_Compressione(char*, char*); 
	
	 /*
     ===========================================================================
       Distruttore della classe Valuta_Compressione
     ===========================================================================
     */

	~Valuta_Compressione          ();

    int Calcola_Dimensione_File   (); /*calcola la dimensione in byte del file*/
	float Compression_Rate        ();     /*calcola il rate(tasso) di compressione del file*/
	float Guadagno_Spazio         ();     /*calcola lo spazio guadagnato dopo la compressione del file in percentuale*/
	
	
private:

	ifstream Original_File,Compressed_File;

    float Dim_File_Origin;   /*variabile per la dimensione del file originale*/
	float Dim_File_Comp;    /*variabile per la dimensione del file compresso*/
};

#endif/* fine blocco ifndef */
