#include <iostream>
#include <fstream>
#include <vector>
#include "huffman.h"

#define NIL 0


using namespace std;

/*
 =======================================================================================================================
    CONTENUTO DEL FILE HUFFMAN.CPP
 =======================================================================================================================
 */

 
/*
 =======================================================================================================================
    Dichiaro le variabili statiche globali e le inizializzo a 0
	N.B:una variabile si dice globale quando è dichiarata all'esterno di ogni blocco di programma,
	cioè fuori dal main e fuori dalle funzioni.
 =======================================================================================================================
 */
int  File_Data::Numero_Caratteri=0;
int  File_Data::Caratteri_Diversi=0;
int* File_Data::Vettore_Caratteri=0;
int* File_Data::Vettore_Frequenze=0;


/*
 =======================================================================================================================
    Metodo Node che costruisce un nuovo nodo foglia
 =======================================================================================================================
 */
Node::Node(int Value,Node* Parent){


	/*Inizializzo i dati membro*/
	Frequence=0;
	value=Value;
	parent=Parent;
	Child_Left=NIL;
	Child_Right=NIL;
}
/*
 =======================================================================================================================
    Metodo Node che crea un nuovo nodo interno che sarà la somma delle frequenze dei sottoalberi destro e sinistro
 =======================================================================================================================
 */
Node::Node(Node* ChildLeft,Node* ChildRight){


	value=-1;/*il nodo interno non è associato ad alcun codice*/
	parent=NIL;
	Child_Left=ChildLeft;
	Child_Right=ChildRight;
	
/*nel caso in cui l'oggetto Node ha un figlio destro ,il puntatore del
parent(genitore) dell'oggetto sarà inizializzato con l'indirizzo dell'oggetto stesso(this)*/
	if(Child_Left!=NIL)  Child_Left->parent=this;
	/*la stessa cosa succede per quello sinistro*/
	if(Child_Right!=NIL) Child_Right->parent=this;
/*il nodo interno viene creato effettuando la somma delle frequenze dei sottoalberi destro e sinistro*/
	Frequence=*ChildLeft+*ChildRight;
}


/*
 =======================================================================================================================
     Metodo Min_Heap.Simula una coda di Min-priority. Utilizzo un TRY-CATCH per gestire l'eccezione.
	 L'intenzione di catturare e gestire l'eventuale eccezione viene segnalata al compilatore utilizzando un blocco try
	 mentre la vera e propria gestione dell'eccezione viene specificata con un blocco catch (detto exception handler), 
	 che viene chiamato al verificarsi dell'errore
 =======================================================================================================================
 */

Min_Heap::Min_Heap(int Max_n_Node){

    N_Node_Corrente=0; /*Inizializzo a 0 il numero dei nodi correnti*/
	Max_Num_Node=Max_n_Node;
	
	/*Alloco dinamicamente un array di nodi,puntatori a Node*/
	try{
	    min_heap=new Node*[Max_Num_Node];
	    if(min_heap==NULL) throw bad_alloc();
	}
        catch (int errore){
              cout << "min_heap non allocato" << endl;
              system("pause");
              exit(-1);
              }
}

/*
 =======================================================================================================================
    Metodo Insert
 =======================================================================================================================
 */

void Min_Heap::Insert(Node* h_Node){

int i,j;

	/*Inserisco l'elemento nell'ultima posizione dell'heap*/
	min_heap[N_Node_Corrente]=h_Node;

	/*ripristino la proprietà del Min_Heap*/
	for (i=N_Node_Corrente,j=(i+1)/2-1; j>=0; i=j,j=(i+1)/2-1){
	
		if (Compare(i,j)==i){  
		
			/*Scambio min_heap[i] con il più piccolo dei figli*/	
			Node* Temp=min_heap[i];
			min_heap[i]=min_heap[j];
			min_heap[j]=Temp;
	}
	
		else  break;
	}
	N_Node_Corrente++; /*incremento il numero di nodi presenti*/
}

/*
 =======================================================================================================================
    Metodo Extract_min, serve per estrarre il minimo
 =======================================================================================================================
 */

bool Min_Heap::Extract_min(Node** h_Node){

int i,j;

if (N_Node_Corrente<1) return 0;
		
	/*decremento il numero di nodi nell'heap*/
	N_Node_Corrente--;
	/*restituisco come parametro di output il primo elemento dell'array*/
	*h_Node=min_heap[0];
	/*pongo l'ultimo elemento al primo posto*/
	min_heap[0]=min_heap[N_Node_Corrente];

	/*Min-Heapify: ripristina la proprietà del Min_Heap*/
	for (i=0,j=(i+1)*2-1; j<N_Node_Corrente; i=j,j=(i+1)*2-1){
	
			     if (j+1<N_Node_Corrente)   j=Compare(j,j+1);
			     if (Compare(i,j)==j){   
		
/*Scambio min_heap[i] con il più piccolo dei figli*/
		Node* Temp=min_heap[i];
	    min_heap[i]=min_heap[j];
	    min_heap[j]=Temp;
		
		}
		else  break;
		
	}
	return 1;
}


/*
 =======================================================================================================================
    Metodo Compare, serve per confrontare due elementi
 =======================================================================================================================
 */
int Min_Heap::Compare(int i,int j){

	if(*min_heap[i]<*min_heap[j])  return i;
	else  return j;
}

/*
 =======================================================================================================================
     Metodo Tree.L'albero viene generato partendo dall'array di nodi foglia e 
	 attraverso l'heap effettua gli inserimenti le estrazioni e le fusioni.
	 Utilizzo un TRY-CATCH per gestire l'eccezione nell'allocazione dinamica dell array di nodi foglia.
 =======================================================================================================================
 */

Tree::Tree(){

File_Data hData;/*oggetto della classe File_Data*/
int i;

	Min_Heap m_Heap(hData.caratteri_diversi()); /*istanzio l'oggetto m_Heap*/
	Node* ChildRight;
	Node* ChildLeft;
	
     /*metodi ereditati da File_Data*/
	int* vettore_caratteri=hData.vettore_caratteri();
	int* vettore_frequenze=hData.vettore_frequenze();

	/*alloco dinamicamente un array di nodi foglia*/
	try{
	     Vettore_Foglie=new Node*[256];
	     if(Vettore_Foglie==NULL) throw bad_alloc();
	}
        catch (int errore)
        {
              cout << "Vettore Foglie non allocato" << endl;
              system("pause");
              exit(-1);
              }
	
	for (i=0; i<hData.caratteri_diversi(); i++)
	{
		/*pongo nell'array i nodi con codice ASCII*/
		Vettore_Foglie[vettore_caratteri[i]]=new Node(vettore_caratteri[i],0);
		/*per assegnare la frequenza faccio un cast a int*/
		(int&)(*Vettore_Foglie[vettore_caratteri[i]])=vettore_frequenze[i];
		m_Heap.Insert(Vettore_Foglie[vettore_caratteri[i]]);
	}

	/*Costruisco l'albero partendo dalle foglie utilizzando l'Heap*/
	for (i=0; i<hData.caratteri_diversi()-1; i++){
	
						/*estraggo il minimo dal figlio sinistro e figlio destro*/
							m_Heap.Extract_min(&ChildLeft);
							m_Heap.Extract_min(&ChildRight);
							m_Heap.Insert(new Node(ChildLeft,ChildRight));/*un inserimento con fusione*/
	}
	/*la radice è l'ultimo elemento rimasto nella coda*/
	m_Heap.Extract_min(&root);
}

/*
 =======================================================================================================================
    Metodo Read_File, serve per aprire il file in lettura.tutte le operazioni 
    sono incluse in un blocco TRY-CATCH-THROW
 =======================================================================================================================
 */

Read_File::Read_File(char* File_name){

try{
	 /*apre il file in modalità binary*/
	 Finput.open(File_name, ios::binary);
	 if(!Finput) throw bad_alloc();
    }
    catch (int errore){
        cout << "Impossibile accedere al file(lettura)" << endl;
        system("pause");    
        exit(-1);
    }
	/*Azzero le variabili che vengono usate da Read_Bit()*/
	Bit_File_Sequence=0; 
	Size_Sequence=0;
}

/*
 =======================================================================================================================
    Metodo Read_Bit, serve per leggere i bit del file
 =======================================================================================================================
 */

int Read_File::Read_Bit(){
	/*Viene prelevato un byte se la sequenza di bit è lunga 0*/
	if (Size_Sequence==0){
				/*get legge un byte alla volta*/
				Bit_File_Sequence=Finput.get();
				Size_Sequence=8;
	}
	
	/*sequanza posta in and bit a bit con la maschera 128*/
	int Bit=(Bit_File_Sequence&128)>>7;
	Bit_File_Sequence<<=1;
	Size_Sequence--;
	return Bit;
}
/*
 =======================================================================================================================
    Metodo Read_Carat, serve per raccogliere informazioni per la costruzione dell'albero
	uso la funzione get della classe fstream
 =======================================================================================================================
 */
int Read_File::Read_Carat(){ return Finput.get(); }

/*
 =======================================================================================================================
    Metodo Read_Source_File, legge dal file sorgente.
	Attraverso le funzioni seekg e tellg viene letto un carattere per volta.
	In un vettore viene salvata la frequenza di ogni carattere e in altro il numero di caratteri.
	Uso un blocco TRY-CATCH per gestire eventuali eccezioni durante l'allocazione dinamica del Vettore_Caratteri
	e Vettore_Frequenze
 =======================================================================================================================
 */

void Read_File::Read_Source_File(){

int i;
	
/*A ogni file aperto è associato un puntatore alla posizione corrente nel file. Questa è la posizione nel file da 
cui si comincerà a leggere alla prossima operazione di input. Per spostare il puntatore si usa seekg 
*/
	Finput.seekg (0, ios::end);/* per spostarsi in modo relativo rispetto alla fine del file.Posizionamento alla fine di Finput*/
	Numero_Caratteri = Finput.tellg();/*posizione corrente del cursore*/
	Finput.seekg (0, ios::beg);/*per spostarsi in modo relativo rispetto all'inizio del file .Posizionamento all'inizio di Finput*/

	/*memorizzo le frequenze di tutti i caratteri ASCII*/
	vector <int> count;
	for (i=0; i<256; i++)
	
	/*push_back permette di inserire, in coda nel vettore, un nuovo elemento. 
	L'elemento va specificato come parametro fra parentesi e deve essere 
	del tipo previsto nella dichiarazione del vettore*/
	count.push_back(0); 
	
	int Carattere;
	Caratteri_Diversi=0;

	for (i=0; i<Numero_Caratteri; i++){
	
		Carattere=Finput.get();/*legge il carattere(spazi inclusi). uso la funzione get della classe fstream*/
		
		/*se il carattere viene incontrato per la prima volta incrementa il numero di Caratteri_Diversi*/
		if (count[Carattere]==0)
			Caratteri_Diversi++;
		/*in ogni caso incremento la sua frequenza*/
		count[Carattere]++;
	}
	Finput.seekg (0, ios::beg); /*per spostarsi in modo relativo rispetto all'inizio del file */

	/*allocazione dinamica del Vettore_Caratteri*/
	try{
	     Vettore_Caratteri=new int[Caratteri_Diversi];
	     if(Vettore_Caratteri==NULL) throw bad_alloc();
	}
        catch (int errore)
        {
              cout << "Vettore caratteri non allocato" << endl;
              system("pause");
              exit(-1);
              }
			  
			  
		/*allocazione dinamica del Vettore_Frequenze*/
	try{
	     Vettore_Frequenze=new int[Caratteri_Diversi];
	     if(Vettore_Frequenze==NULL) throw bad_alloc();
	}
        catch (int errore)
        {
              cout << "Vettore frequenze non allocato" << endl;
              system("pause");
              exit(-1);
              }
	

	/* i caratteri e le frequenze vengono posti dinamicamente in due
	array diversi, la memorizzazione avviene in maniera consecutiva*/
	int increase=0;
	for (i=0; i<256; i++){
	
					if (count[i]!=0){
					
						Vettore_Caratteri[increase]=i;
						Vettore_Frequenze[increase]=count[i];
						increase++;
            }
       }
}

/*
 =======================================================================================================================
    Metodo Write_File, scrive sul file.tutte le operazioni 
 sono incluse in un blocco TRY-CATCH-THROW
 =======================================================================================================================
 */

Write_File::Write_File(char* File_name){

 try{
      /*apro il file in modalità binaria*/
	  Foutput.open(File_name, ios::binary);
	
	  if(!Foutput) throw bad_alloc();
    }
    catch (int errore){
        cout << "Impossibile accedere al file(scrittura)" << endl;
        system("pause");    
        exit(-1);
    }
	
	/*azzero le variabili usate da Write_Bit()*/
	Bit_File_Sequence=0; 
	Size_Sequence=0;
}

/*
 =======================================================================================================================
    Metodo Write_Bit, per la scrittura del bit
 =======================================================================================================================
 */

void Write_File::Write_Bit(int i_bit){

	if(i_bit==0) /*shiftiamo di 1 la sequenza se il bit è 0*/
		Bit_File_Sequence<<=1;
		
		/*altrimenti complementa shifta e ricomplementa*/
	else{
	    Bit_File_Sequence=~Bit_File_Sequence;
		Bit_File_Sequence<<=1;
		Bit_File_Sequence=~Bit_File_Sequence;
	}
	
	Size_Sequence++;
	
	/*Appena sono stati calcolati gli 8 bit viene scritto il byte*/
	if (Size_Sequence==8){
						Foutput.put(Bit_File_Sequence); /*put scrive un byte alla volta*/
						Size_Sequence=0;
	}
}

Write_File::~Write_File(){
		/*Pongo tutti 0 alla fine per riempire l'ultimo byte da scrivere*/
		while(Size_Sequence>0)
			Write_Bit(0);
			/*Chiudo il file aperto dal costruttore*/
		Foutput.close(); 
}

/*
 =======================================================================================================================
    funzione membro Encoder , per accedervi utilizziamo lo scope ::
	Il metodo utilizza due campi,il primo si riferisce al nome del file che deve essere codificato e che quindi
	viene aperto in lettura, il secondo campo si riferisce al nome del file codificato, chiamato Encoded_File.huf,
	dove huf indica Huffman File,e che quindi verrà aperto in scrittura.
	Questo metodo quindi oltre all'apertura del file da codificare in lettura e del file codificato in scrittura,
	prevede la lettura del file sorgente con prelievo di infomazioni,istanziamento di un albero,
	la codifica di un carattere per volta, scritta poi in codice del file compresso.
	L'albero viene poi percorso ricorsivamente in maniera Bottom-Up.
	
 =======================================================================================================================
 */

void Encoder::Encode(char* File_Sorgente,char* File_Compresso){

int i;

    cout<<endl;
	cout<<"Codificando il file sorgente,attendere..."<< endl;
	
	Read_File R_File(File_Sorgente); /*crea l'oggetto R_File*/
	Write_File W_File(File_Compresso); /*crea l'oggetto W_File*/
	R_File.Read_Source_File();
	Tree T; /*crea l'oggetto T*/

	
	/*parto dalle foglie*/
	Node** vettore_foglie=T.get_Foglie(); 
	int i_carattere;
	int i_num_carattere=R_File.numero_caratteri(); /*metodo ereditato da File_Data*/

	for (i=0;i<i_num_carattere;i++){
	
		i_carattere=R_File.Read_Carat(); /*legge il codice ascii (1byte con get)*/
		Encode_Carat(vettore_foglie[i_carattere], &W_File);
	}
	cout<<endl;
	cout<< " Il file e' stato codificato!" << endl;
	cout<<endl;
}

void Encoder::Encode_Carat(Node* N, Write_File* w_file){

/*la sequenza di bit incontrata nel percorso dalla foglia alla radice non corrisponde alla parola in codice,
 la sua inversa si.  grazie alla ricorsione questo ostacolo viene superato.*/
	Node* Parent=N->Parent();
	if (Parent!=0){
	
					int Bit;
					/*se è un figlio sinistro associa 0*/
						if (N==Parent->ChildLeft()) Bit=0;
		else Bit=1; /*altrimenti 1*/
		
/*w_file è un parametro che serve a mantenere la posizione del puntatore nel file che è stato aperto in scrittura*/
		Encode_Carat(Parent, w_file); //Risale ricorsivamente
		w_file->Write_Bit(Bit);
	}
}


/*
 =======================================================================================================================
 funzione membro Decoder , per accedervi utilizziamo lo scope::
 Il metodo Decode è formato da due campi, il primo è per il nome del file codificato e viene aperto in lettura,
 il secondo campo è per il nome del file decodificato e viene aperto in scrittura.
 Vengono quindi aperti i file, ricostruito l'albero, decodificate le parole in codice prelevando un bit alla volta
 percorrendo radice-foglia, viene scritto il carattere corrispondente nel file decodificato.
 L'albero viene percorso in modo ricorsivo Top-Down
 =======================================================================================================================
 */
void Decoder::Decode(char* File_Compresso,char* File_Destinatario){

int i;

    cout<<"================================"<< endl;
	cout<<"Decodifica in corso,attendere..."<< endl;
	Read_File R_File(File_Compresso);
	Write_File W_File(File_Destinatario);
	Tree T;
	/*parte dalla radice*/
	Node* Radice=T.get_Root(); 

	int Carattere;
	int numero_caratteri=R_File.numero_caratteri();

	for (i=0;i<numero_caratteri;i++){
	
		Carattere=Decode_Carat(Radice,&R_File);
		W_File.Write_Carat(Carattere);
	}
	cout<<"Il File e' stato decodificato!"<< endl;
}

int Decoder::Decode_Carat(Node* N,Read_File* R_File){

	Node* ChildLeft=N->ChildLeft();
	Node* ChildRight=N->ChildRight();
	/*se il nodo non è foglia*/
	if (ChildLeft!=0 && ChildRight!=0) {
	
		int Bit=R_File->Read_Bit(); /*legge il bit e scende ricorsivamente*/
		if (Bit==0) return Decode_Carat(ChildLeft,R_File);
		else return Decode_Carat(ChildRight,R_File);
	}
      /*quando giunge nella foglia restituisce il codice ASCII*/
	return N->Value();
}
/*
 =======================================================================================================================
Metodo Valuta_Compressione.ha due campi,il primo è per il file inserito in input,ovvero quello che deve essere
compresso, il secondo si riferisce al file codificato.
I due file vengono aperti e vengono calcolate le rispettive dimensioni in byte.
Vengono quindi calcolate attarverso delle formule il tasso di compressione e il guadagno dello spazio dopo
la compressione.
Uso un blocco TRY-CATCH per gestire eventuali eccezini durante il calcolo della dimensione dei file
 =======================================================================================================================
 */
Valuta_Compressione::Valuta_Compressione(char* File_Origin, char* File_Comp){

try{
	Original_File.open(File_Origin, ios::binary);/*apro il file originale*/
	
	if(!Original_File)
			       throw -1;
				   else{
	/*per calcolare lo spazio occupato in byte dal file originale*/
	          Original_File.seekg (0, ios::end); /* per spostarsi in modo relativo rispetto alla fine del file.Posizionamento alla fine di Original_File*/
	          Dim_File_Origin = Original_File.tellg();/*posizione corrente del cursore*/
	          Original_File.seekg (0, ios::beg);/*per spostarsi in modo relativo rispetto all'inizio del file .Posizionamento all'inizio di Original_File*/
			  
	}
	}
	catch (int errore){
        cout << "Errore durante il calcolo della dimensione del file originale!" << errore << endl;
		}
	
	try{
	Compressed_File.open(File_Comp, ios::binary);/*apro il file compresso*/
	
	if(!Compressed_File)
            throw -1;
        else{
	         
			  /*per calcolare lo spazio occupato in byte dal file compresso*/
			  Compressed_File.seekg (0, ios::end);/* per spostarsi in modo relativo rispetto alla fine del file.Posizionamento alla fine di Compressed_File*/
			  Dim_File_Comp = Compressed_File.tellg();/*posizione corrente del cursore*/
			  Compressed_File.seekg (0, ios::beg);/*per spostarsi in modo relativo rispetto all'inizio del file .Posizionamento all'inizio di Compressed_File*/
	         }
     }
  
  catch (int errore){
        cout << "Errore durante il calcolo della dimensione del file compresso!" << errore << endl;
    }
  }



Valuta_Compressione::~Valuta_Compressione(){
	Original_File.close(); /*chiudo il file originale*/
	Compressed_File.close();/*chiudo il file compresso*/
};

/* Metodo che ritorna la dimensione del file in modo da poterlo stampare in output durante l'esecuzione*/
int Valuta_Compressione::Calcola_Dimensione_File(){return Dim_File_Origin;}
/*Calcolo il tasso di compressione con la seguente formula
1-dimensione del file compresso/dimensione del file originale*/
float Valuta_Compressione::Compression_Rate(){ return (1-(Dim_File_Comp/Dim_File_Origin)); }
/*Calcolo lo spazio recuperato con la compressione del file con la seguente formula
1-dimensione del file compresso/dimensione file originale*100*/
float Valuta_Compressione::Guadagno_Spazio(){ return (1-(Dim_File_Comp/Dim_File_Origin))*100; }

