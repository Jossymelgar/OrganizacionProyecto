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