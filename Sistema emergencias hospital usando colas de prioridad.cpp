#include <iostream>
using namespace std;

struct Nodo{
	
	string nombre;
	int edad;
	string sintomas;
	int gravedad;
		
	Nodo* siguiente;
	
};

int prioridad(int edad){
	
	int prioridad=0;
	
	if(edad<12){
		prioridad = 1;
	} else if(edad>65){
		prioridad =2;
	}else{
		prioridad = 4;
	}
	
	return prioridad;
}

void agregar(Nodo*& lista, string nombre, int edad, string sintomas, int gravedad){
	
	Nodo* nuevo_nodo = new Nodo();

	nuevo_nodo->nombre = nombre;
	nuevo_nodo->edad = edad;
	nuevo_nodo->sintomas = sintomas;
	nuevo_nodo->gravedad = gravedad;
	
	Nodo* actual = lista;
	Nodo* anterior = NULL;
	
	
	if(!lista){ //Si es el primer elemento de la cola
	
		lista = nuevo_nodo;
		
	}else{
		
		if(actual->siguiente){//Si hay más de un elemento en la cola
			
			//Este while lleva a "actual" a un nodo de mayor o igual gravedad que el que se está insertando, en caso de no haber un nodo de mayor gravedad llevará al final de la cola. 
			while(actual->gravedad < nuevo_nodo->gravedad && actual->siguiente){
				anterior = actual;
				actual = actual->siguiente;
			}
			
			
			//En caso de que actual sea el ultimo nodo de la lista puede tener una gravedad menor que el nuevo nodo, entonces se debe insertar el nuevo nodo despues de actual y no antes de actual como en el resto de casos.
			if(actual->gravedad < nuevo_nodo->gravedad){
				actual->siguiente = nuevo_nodo;
			}else{ 
				if(actual->gravedad == nuevo_nodo->gravedad){ //En caso de que el nodo actual tenga la misma gravedad que el nuevo nodo se debe insertar antes o despues dependiendo de la prioridad.
					if(prioridad(actual->edad) < prioridad(nuevo_nodo->edad)){//Si el nuevo nodo tiene una prioridad mayor debe agregarse despues
						while(prioridad(actual->edad) < prioridad(nuevo_nodo->edad) && actual->siguiente && actual->gravedad == nuevo_nodo->gravedad) {
							anterior = actual;
							actual = actual->siguiente;
						}
						if(prioridad(actual->edad) < prioridad(nuevo_nodo->edad)){//Si al llegar al final de los de la misma la prioridad el nuevo nodo sigue siendo mayor 
							Nodo* aux = actual->siguiente;
							actual->siguiente = nuevo_nodo;
							nuevo_nodo->siguiente = aux;
						}else{
							if(anterior){
								anterior->siguiente = nuevo_nodo;
							}else{
								lista = nuevo_nodo;
							}
							nuevo_nodo->siguiente = actual;	
						}
					}else{//Si el nuevo nodo tiene una prioridad menor se agrega inmediatamente antes del nodo actual 
					
						if(anterior){
							anterior->siguiente = nuevo_nodo;
						}else{
							lista = nuevo_nodo;
						}
						nuevo_nodo->siguiente = actual;	
					}
				}else{//si no tienen la misma gravedad y el nuevo nodo es menor se agrega antes del nodo actual
					if(anterior){
						anterior->siguiente = nuevo_nodo;
					}else{//Si el nuevo nodo era menor que el primer elemento en cola se agrega como incio de la lista
						lista = nuevo_nodo;
					}
					nuevo_nodo->siguiente = actual;
				}	
			}	
		}else{//Si solo hay un elemento en la cola
			
			if(actual->gravedad>nuevo_nodo->gravedad){//Si el nuevo nodo es menor se agrega al incio de la lista
				lista = nuevo_nodo;
				nuevo_nodo->siguiente = actual;
			}else if(actual->gravedad == nuevo_nodo->gravedad){
				if(prioridad(actual->edad) > prioridad(nuevo_nodo->edad)){//Si tienen la misma gravedad y prioridad del nuevo nodo es menor, el nuevo nodo se agrega al incio de la lista
					lista = nuevo_nodo;
					nuevo_nodo->siguiente = actual;
				}
			}else{ //En cualquier otro caso se agrega despues del elemento en la cola
				actual->siguiente = nuevo_nodo;
			}
		}
	}
}

void pasarPaciente(Nodo*& lista){
		
	cout << "\nSiguiente paciente:\n\n Nombre: " << lista->nombre << "\n Edad: " << lista->edad << "\n Sintomas: " << lista->sintomas << "\n Gravedad: " << lista->gravedad << "\n";
	
	Nodo* actual = lista;
	Nodo* aux = actual->siguiente;
	delete actual;
	lista = aux;

}

void print(Nodo*& lista) {

    cout << "[ ";
    if(lista){
	    Nodo* actual = lista;
	    while (actual->siguiente) {
	        cout << actual->nombre << ", ";
	        actual = actual->siguiente;
	    }
	    cout << actual->nombre;
	}
	cout << " ]";
}


int main (){
	
	int opcion;
	string nombre;
	int edad;
	string sintomas;
	int gravedad;
	bool continuar = true;
	Nodo* cola = NULL;
	
	while(continuar){
	cout << "\nSistema de urgencias\n\nMenu:\n 1.Ingresar Paciente:\n 2.Pasar paciente\n 3.Mostrar cola\n 4.Salir\n\n";
	do{
		cout << "Ingrese una opcion ->";
		cin >> opcion;
	}while(opcion>4 || !opcion);
	
	switch(opcion){
		case 1 :
			
			cout << "Nombre del paciente ->";
			cin.ignore();
			getline(cin, nombre);
			
			cout << "Edad del paciente ->";
			cin  >> edad;
			
			cout << "Sintomas del paciente ->";
			cin.ignore();
			getline(cin, sintomas);
			
			cout << "Gravedad del paciente ->";
			cin  >> gravedad;
			
			agregar(cola, nombre, edad, sintomas, gravedad);
			
			cout << "**Paciente agregado**\n";
			break;
		
		
		case 2:
			
			if(cola){
				
			pasarPaciente(cola);
			
			}else{
			
			cout << "\nNO hay pacientes en cola esperando ser atendidos.";
				
			}
			cout << "\nIngrese un numero cualquiera para volver al menu ->";
			cin >> nombre;
			break;
			
		case 3:
			
			print(cola);
			cout << "\n";
			break;
			
		case 4:
			continuar = false;
			cout << "\nPrograma terminado";
			break;

	}
	}
}
