#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
using namespace std;

struct Index{
	unsigned long llave;
	int rrn;
};

int menu();

//Listar
void L_CiudadBin();
void L_ClienteBin();
void L_LineaBin();
void L_LlamadaBin();

//herramientas de busqueda
int PosNuevoBinarySearch(vector<Index>, unsigned long);
int PosBinarySearch(vector<Index>, unsigned long);
bool binarySearch(vector<Index>, unsigned long, int,int);

//Buscar con indice
void BI_Ciudad();
void BI_Cliente();
void BI_Linea();

int main(int argc, char const *argv[]){

	
	return 0;
}

int menu(){
	int resp=0;
	while(true){
		cout<<"Menu\n"
		    <<"1. Crear\n"
		    <<"2. Listar\n"
		    <<"3. Agregar\n"
		    <<"4. Eliminar\n"
		    <<"5. Buscar\n"
		    <<"6. Modificar\n"
		    <<"7. Reindexar\n"
		    <<"8. Salir"<<endl;
		cin>>resp;
		if(resp>=1&&resp<=8){
			return resp;
		}else{
			cout<<"Ingrese un valor valido!"<<endl;
		}
	}
}


//Listar
void L_CiudadBin(){
	ifstream inFile("ciudad.bin",ios::binary);
	inFile.seekg(0);
	int avail;
	int cantRegistros;
	bool flag;
	inFile.read((char*)&avail, sizeof(int));
	inFile.read((char*)&cantRegistros, sizeof(int));
	inFile.read((char*)&flag, sizeof(bool));
	cout<<avail<<", "<<cantRegistros<<", "<<flag<<endl;
	int cont=0;
	while(cont<cantRegistros){
		char IdCiudad[5];
		char NombreCiudad[40];
		inFile.read((char*)IdCiudad, sizeof(IdCiudad));
		inFile.read((char*)NombreCiudad, sizeof(NombreCiudad));
		if (IdCiudad[0]!='*'){
			cout<<IdCiudad<<","<<NombreCiudad<<endl;
		}
		cont++;
	}
	inFile.close();
}
void L_ClienteBin(){
	ifstream inFile("cliente.bin",ios::binary);
	inFile.seekg(0);
	int avail;
	int cantRegistros;
	bool flag;
	inFile.read((char*)&avail, sizeof(int));
	inFile.read((char*)&cantRegistros, sizeof(int));
	inFile.read((char*)&flag, sizeof(bool));
	cout<<avail<<", "<<cantRegistros<<", "<<flag<<endl;
	int cont=0;
	while(cont<cantRegistros){
		char IdCliente[15];
		char NombreCliente[40];
		char Genero[2];
		char IdCiudad[5];
		inFile.read((char*)IdCliente, sizeof(IdCliente));
		inFile.read((char*)NombreCliente, sizeof(NombreCliente));
		inFile.read((char*)Genero, sizeof(Genero));
		inFile.read((char*)IdCiudad, sizeof(IdCiudad));
		cout <<IdCliente << "," << NombreCliente << "," << Genero << "," << IdCiudad <<endl;
		cont++;
	}
	inFile.close();
}
void L_LineaBin(){
	ifstream inFile("linea.bin",ios::binary);
	inFile.seekg(0);
	int avail;
	int cantRegistros;
	bool flag;
	inFile.read((char*)&avail, sizeof(int));
	inFile.read((char*)&cantRegistros, sizeof(int));
	inFile.read((char*)&flag, sizeof(bool));
	cout<<avail<<", "<<cantRegistros<<", "<<flag<<endl;
	int cont=0;
	while(cont<cantRegistros){
		char Numero[9];
		char Id[14];
		inFile.read((char*)Id, sizeof(Id));
		inFile.read((char*)Numero, sizeof(Numero));
		cout << Id << "," << Numero << endl;
		cont++;
	}
	inFile.close();
}
void L_LlamadaBin(){
	ifstream inFile("llamada.bin",ios::binary);
	inFile.seekg(0);
	int avail;
	int cantRegistros;
	bool flag;
	inFile.read((char*)&avail, sizeof(int));
	inFile.read((char*)&cantRegistros, sizeof(int));
	inFile.read((char*)&flag, sizeof(bool));
	cout<<avail<<", "<<cantRegistros<<", "<<flag<<endl;
	int cont=0;
	while(cont<cantRegistros){
		char Numero[9];
		char inic[20];
		char fin[20];
		char IdCiudad[4];
		inFile.read((char*)&Numero, sizeof(Numero));
		inFile.read((char*)&inic, sizeof(inic));
		inFile.read((char*)&fin, sizeof(fin));
		inFile.read((char*)&IdCiudad, sizeof(IdCiudad));
		cout <<Numero << "," << inic << "," << fin << "," << IdCiudad <<endl;
		cont++;
	}
	inFile.close();
}

//Herramientas de busqueda	
int PosNuevoBinarySearch(vector<Index> v,unsigned long key){
    int izquierda = 0;
    int derecha = v.size() - 1;
    int medio;
    bool fin = false;
    while(izquierda<derecha){   	
    	medio = (izquierda + derecha)/2;
    	if(key > v.at(medio).llave){
    		if(medio != v.size()-1){
    			if(key < v.at(medio+1).llave){
    				return medio+1;
    			}else{
    				if(fin && medio == v.size()-2){
    					return -1;
    				}
    				izquierda = medio;
    				fin = true;
    			}
    		}else{
    			if(key < v.at(medio).llave){
    				return medio;
    			}else{
    				return -1;
    			}
    		}
    	}else{
    		if(medio != 0){
    			if(key > v.at(medio-1).llave){
    				return medio;
    			}else{
    				derecha = medio;
    			}
    		}else{
    			if(key < v.at(medio).llave){
    				return medio;
    			}else{
    				return medio+1;
    			}
    		}
    	}
    }
    return -1;
}
int PosBinarySearch(vector<Index> v,unsigned long key){
	int tama = v.size();
	int inferior,superior,medio;
	inferior = 0;
	superior = tama;
	while(inferior <= superior){
		medio = (inferior+superior)/2;
		if(v.at(medio).llave==key){
			return medio;	
		}
		if(v.at(medio).llave>key){
			superior = medio;
			medio =(inferior+superior)/2;
		}
		if (v.at(medio).llave<key){
			inferior = medio;
			medio =(inferior+superior)/2;
		}
	}
}
bool binarySearch(vector<Index> v, unsigned long key, int start,int end){
    if(end < start)
        return false;
    else{
        int mid = (start + end)/2;
        if(v.at(mid).llave > key){
            return binarySearch(v, key, start, mid-1);
        }
        else if (v.at(mid).llave < key){
            return binarySearch(v, key, mid+1, end);
        }
        else{
            return true;
        }
    }
}

//Buscar con indice
void BI_Ciudad(){
	unsigned long key;
	cout<<"Ingrese ID Ciudad: ";
	cin>>key;
	if (binarySearch(l_indexCiudad,key,0,l_indexCiudad.size()-1)){
		ifstream inFile("ciudad.bin",ios::binary);
		int pos=PosBinarySearch(l_indexCiudad,key);
		char IdCiudad[5];
		char NombreCiudad[40];
		inFile.seekg(tamHeader+l_indexCiudad.at(pos).rrn*( sizeof(IdCiudad)+ sizeof(NombreCiudad)));
		inFile.read((char*)&IdCiudad, sizeof(IdCiudad));
		inFile.read((char*)&NombreCiudad, sizeof(NombreCiudad));
		inFile.close();
		cout<<IdCiudad<<","<<NombreCiudad<<endl;
	}else{
		cout<<"LLave invalido!"<<endl;
	}
}
void BI_Cliente(){
	unsigned long key;
	cout<<"Ingrese ID Cliente: ";
	cin>>key;
	if (binarySearch(l_indexCliente,key,0,l_indexCliente.size()-1)){
		ifstream inFile("cliente.bin",ios::binary);
		int pos=PosBinarySearch(l_indexCliente,key);
		char IdCliente[15];
		char NombreCliente[40];
		char Genero[2];
		char IdCiudad[5];
		inFile.seekg(tamHeader+l_indexCliente.at(pos).rrn*( sizeof(IdCliente)+ sizeof(NombreCliente)+ sizeof(Genero)+ sizeof(IdCiudad) ));
		inFile.read((char*)&IdCliente, sizeof(IdCliente));
		inFile.read((char*)&NombreCliente, sizeof(NombreCliente));
		inFile.read((char*)&Genero, sizeof(Genero));
		inFile.read((char*)&IdCiudad, sizeof(IdCiudad));
		inFile.close();
		cout <<IdCliente << "," << NombreCliente << "," << Genero << "," << IdCiudad <<endl;
	}else{
		cout<<"LLave invalido!"<<endl;
	}
}
void BI_Linea(){
	unsigned long key;
	cout<<"Ingrese ID Cliente: ";
	cin>>key;
	if (binarySearch(l_indexLinea,key,0,l_indexLinea.size()-1)){
		ifstream inFile("linea.bin",ios::binary);
		int pos=PosBinarySearch(l_indexLinea,key);
		char IdCliente[14];
		char Numero[9];
		inFile.seekg(tamHeader+ l_indexLinea.at(pos).rrn*( sizeof(IdCliente)+ sizeof(Numero)));
		inFile.read((char*)&IdCliente, sizeof(IdCliente));
		inFile.read((char*)&Numero, sizeof(Numero));
		inFile.close();
		cout<<IdCliente<<","<<Numero<<endl;
	}else{
		cout<<"LLave invalido!"<<endl;
	}
}