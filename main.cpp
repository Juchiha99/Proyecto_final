#include <iostream>
#include <stdlib.h>
#include <mysql.h>

using namespace std;

void menuConsultar();
void insertarFinal();
void insertarNodo();
void buscarAl();
void mostrarLista();
void updateAl();
void eliminarAl();
void saveData();
void exitData();

char serverdb[] = "localhost";
char userdb[] = "umg";
char passworddb[] = "Umg$2019";
char database[] = "proyectoiii";


//Para simula contro z & y
struct Cambio{
	string clave;
	string nombre;
	string correo;
	string nacimiento;
	string telefono;
	string direccion;
	Cambio *siguiente;
};

Cambio *cimaDeshacer = NULL, *cimaRehacer = NULL;

//lista enlazada
struct Alumno{
	string clave;
	string nombre;
	string correo;
	string nacimiento;
	string telefono;
	string direccion;
	Alumno *siguiente;
};

Alumno *inicio = NULL;



int main() {
	int opc;
	char opcion;
	MYSQL * connection;
	connection = mysql_init(0);
	if (connection){
		cout<<"La biblioteca Mysql se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection){
			
			cout<<"Conexion exitosa a la base de datos"<<endl;
			cout<<"\nInformacion de la base de datos"<<endl;
			
			menuConsultar();
			cout<<"\n";
			
			do{
				
				cout<<"\tMENU"<<endl;
				cout<<"\n";
				cout<<"1. Agregar alumno"<<endl;
				cout<<"2. Buscar alumno"<<endl;
				cout<<"3. Modificar los datos del alumno"<<endl;
				cout<<"4. Lista de los alumnos en memoria"<<endl;
				cout<<"5. Eliminar alumno"<<endl;
				cout<<"6. Deshacer ultimo cambio"<<endl;
				cout<<"7. Rehacer cambios"<<endl;
				cout<<"8. Guardar"<<endl;
				cout<<"9. Guardar y salir"<<endl;
				cout<<"Ingrese la opcion: ";
				cin>>opc;
				
				switch(opc){
				case 1:
					insertarNodo();
					break;
					
				case 2:
					buscarAl();
					break;
					
				case 3:
					updateAl();
					break;
					
				case 4:
					mostrarLista();
					break;
					
				case 5:
					eliminarAl();
					break;
					
				case 6:
					break;
					
				case 7:
					break;
					
				case 8:
					saveData();
					break;
					
				case 9:
					
					cout<<"\nQuieres guardar los cambios S/N: ";
					cin>>opcion;
					if(opcion == 's'){
						
						exitData();
					}
					else{
						cout<<"No se guardaron los datos en la base de datos"<<endl;
					}
					cout<<"Salio del programa"<<endl;
					break;
				}
			}while(opc !=9);
			
			
		}
		else{
			cout<<"No se pudo conectar a la base de datos: "<<mysql_error(connection)<<endl;
		}
		
	}
	else{
		
		cout<<"No es posible iniciar la biblioteca de Mysql"<<endl;
	}
	cout<<"\n";
	
	system("PAUSE");
	return 0;
}

void menuConsultar(){
	
	
	MYSQL* connection;
	string sql;
	int result;
	MYSQL_ROW row;
	MYSQL_RES* data;
	const char* query;
	connection = mysql_init(0);
	if (connection){
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection){
			
			sql = "SELECT * FROM alumno";
				query = sql.c_str();
				result = mysql_query(connection, query);
				if (result == 0){
					cout<<"Busqueda exitosa"<<endl;
					data = mysql_store_result(connection);
					int countColumns = mysql_num_fields(data);
					while(row = mysql_fetch_row(data)){
						for(int i = 0; i < countColumns; i++ ){
							cout<<row[i]<<"\t";
						}
						cout<<endl;
					}
				}
				else{
					cout<<"Busqueda sin exito"<<endl;
				}
	

		}
		else{
			cout<<"No se pudo conectar a la base de datos: "<<mysql_error(connection)<<endl;
		}
		
	}
	else{
		
		cout<<"No es posible iniciar la biblioteca de Mysql"<<endl;
	}
}

//pertenece a lista enlazada
void insertarFinal(){
	Alumno *alumno = new Alumno();
	cout<<"\nIngrese la clave del alumno: ";
	cin>>alumno->clave;
	cin.ignore();
	cout<<"Ingrese el nombre: ";
	getline(cin, alumno->nombre);
	cout<<"Ingrese el correo: ";
	getline(cin, alumno->correo);
	cout<<"Ingrese la fecha de nacimiento 'dd/mm/aaaa': ";
	getline(cin, alumno->nacimiento);
	cout<<"Ingrese el numero de telefono: ";
	cin>>alumno->telefono;
	cin.ignore();
	cout<<"Ingrese la direccion: ";
	getline(cin, alumno->direccion);
	alumno->siguiente = NULL;
	
	if(inicio == NULL){
		inicio = alumno;
		return;
	}
	Alumno *aux = inicio;
	while(aux->siguiente){
		aux = aux->siguiente;
	}
	aux->siguiente = alumno;
}

//pertenece a lista enlazada
void insertarNodo(){
	Alumno *alumno = new Alumno();	
	cin.ignore();
	cout<<"\nIngrese la clave del alumno: ";
	getline(cin, alumno->clave);
	cout<<"Ingrese el nombre: ";
	getline(cin, alumno->nombre);
	cout<<"Ingrese el correo: ";
	getline(cin, alumno->correo);
	cout<<"Ingrese la fecha de nacimiento 'dd/mm/aaaa': ";
	getline(cin, alumno->nacimiento);
	cout<<"Ingrese el numero de telefono: ";
	getline(cin, alumno->telefono);
	cout<<"Ingrese la direccion: ";
	getline(cin, alumno->direccion);
	alumno->siguiente = NULL;
	
	if(inicio == NULL){
		inicio = alumno;
		cout<<"Se agrego el registro a la memoria\n";
		return;
	}
	if (alumno->clave < inicio->clave){
		alumno->siguiente = inicio;
		inicio = alumno;
		cout<<"Se agrego el registro a la memoria\n";
		return;
	}
	Alumno *aux = inicio;
	Alumno *anterior;
	while(aux != NULL){
		if (alumno->clave == aux->clave){
			cout<<"Esta clave ya existe y no se agrego\n"<<endl;
			return;
		}
		if (alumno->clave < aux->clave){
			anterior->siguiente = alumno;
			alumno->siguiente = aux;
			cout<<"Se agrego el registro a la memoria\n";
			return;
		}
		anterior = aux;
		aux = aux->siguiente;
	}
	anterior->siguiente = alumno;

}

//pertenece a lista enlazada
void mostrarLista(){
	if (inicio == NULL){
		cout<<"No hay datos en esta lista"<<endl;
		return;
	}
	cout<< "\n Lista de alumnos\n";
	Alumno *aux = inicio;
	while(aux != NULL){
		cout<<"\n";
		cout<< "Clave: "<<aux->clave<< ", Nombre: "<<aux->nombre<< ", Correo: "<<aux->correo<< ", Fecha de nacimiento: "<<aux->nacimiento<< ", Numero de tel: "<<aux->telefono<< ", Direccion: "<<aux->direccion<<endl;
		aux = aux->siguiente;
	}
}

void saveData(){
	Alumno *aux = inicio;
	char opcion;
	MYSQL * connection;
	string sql;
	int result;
	const char* query;
	connection = mysql_init(0);
	if (connection){
		cout<<"La biblioteca Mysql se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection){
			
			cout<<"Conexion exitosa a la base de datos"<<endl;
			
			while(aux != NULL){
			sql = "INSERT INTO alumno(nombre_alumno, carne, correo_alumno, fecha_nacimiento, telefono_alumno, direccion_alumno) VALUES ('"+aux->nombre+"', '"+aux->clave+"', '"+aux->correo+"', '"+aux->nacimiento+"', '"+aux->telefono+"', '"+aux->direccion+"')";
				query = sql.c_str();
				result = mysql_query(connection, query);
				if (result == 0){
					cout<<"Registro guardado";
				}
				else{
					cout<<"No se agrego ningun registro"<<mysql_error(connection)<<endl;
				}
					aux = aux->siguiente;	
		}
			}
		else{
			cout<<"No se pudo conectar a la base de datos: "<<mysql_error(connection)<<endl;
		}
		
	}
	else{
		
		cout<<"No es posible iniciar la biblioteca de Mysql"<<endl;
	}
}

void exitData(){
	Alumno *aux = inicio;
	char opcion;
	MYSQL * connection;
	string sql;
	int result;
	const char* query;
	connection = mysql_init(0);
	if (connection){
		cout<<"La biblioteca Mysql se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection){
			
			cout<<"Conexion exitosa a la base de datos"<<endl;
			
			while (aux != NULL){
			sql = "INSERT INTO alumno(nombre_alumno, carne, correo_alumno, fecha_nacimiento, telefono_alumno, direccion_alumno) VALUES ('"+aux->nombre+"', '"+aux->clave+"', '"+aux->correo+"', '"+aux->nacimiento+"', '"+aux->telefono+"', '"+aux->direccion+"')";
				query = sql.c_str();
				result = mysql_query(connection, query);
				if (result == 0){
					cout<<"Registro guardado";
				}
				else{
					cout<<"No se agrego ningun registro"<<mysql_error(connection)<<endl;
				}
				aux = aux->siguiente;
			
		}
			}
		else{
			cout<<"No se pudo conectar a la base de datos: "<<mysql_error(connection)<<endl;
		}
		
	}
	else{
		
		cout<<"No es posible iniciar la biblioteca de Mysql"<<endl;
	}
}


void eliminarAl(){
	Alumno *alumno = new Alumno();
	char opcion;
	MYSQL * connection;
	string sql;
	int result;
	const char* query;
	connection = mysql_init(0);
	if (connection){
		cout<<"La biblioteca Mysql se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection){
			
			cout<<"Conexion exitosa a la base de datos"<<endl;
			cout<<"Ingrese el No. carne a eliminar: ";
			cin.ignore();
			getline(cin, alumno->clave);
			sql = "DELETE FROM alumno WHERE carne='"+alumno->clave+"'";
				query = sql.c_str();
				result = mysql_query(connection, query);
				if (result == 0){
					cout<<"Registro guardado";
				}
				else{
					cout<<"No se agrego ningun registro"<<mysql_error(connection)<<endl;
				}	
			}
		else{
			cout<<"No se pudo conectar a la base de datos: "<<mysql_error(connection)<<endl;
		}
		
	}
	else{
		
		cout<<"No es posible iniciar la biblioteca de Mysql"<<endl;
	}
}

void updateAl(){
	Alumno *alumno = new Alumno();
	char opcion;
	MYSQL * connection;
	string sql;
	int result;
	const char* query;
	connection = mysql_init(0);
	if (connection){
		cout<<"La biblioteca Mysql se ha iniciado correctamente"<<endl;
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection){
			
			cout<<"Conexion exitosa a la base de datos"<<endl;
			cin.ignore();
			cout<<"\nIngrese la clave a modificar: ";
			getline(cin, alumno->clave);
			cout<<"Ingrese el nombre: ";
			getline(cin, alumno->nombre);
			cout<<"Ingrese el correo: ";
			getline(cin, alumno->correo);
			cout<<"Ingrese la fecha de nacimiento 'dd/mm/aaaa': ";
			getline(cin, alumno->nacimiento);
			cout<<"Ingrese el numero de telefono: ";
			getline(cin, alumno->telefono);
			cout<<"Ingrese la direccion: ";
			getline(cin, alumno->direccion);
			sql = "UPDATE alumno SET nombre_alumno='"+alumno->nombre+"', correo_alumno='"+alumno->correo+"', fecha_nacimiento='"+alumno->nacimiento+"', telefono_alumno='"+alumno->telefono+"', direccion_alumno='"+alumno->direccion+"' WHERE carne='"+alumno->clave+"'";
				query = sql.c_str();
				result = mysql_query(connection, query);
				if (result == 0){
					cout<<"Registro guardado";
				}
				else{
					cout<<"No se agrego ningun registro"<<mysql_error(connection)<<endl;
				}	
			}
		else{
			cout<<"No se pudo conectar a la base de datos: "<<mysql_error(connection)<<endl;
		}
		
	}
	else{
		
		cout<<"No es posible iniciar la biblioteca de Mysql"<<endl;
	}
	
}

void buscarAl(){
	Alumno *alumno = new Alumno();
	MYSQL* connection;
	string sql;
	int result;
	MYSQL_ROW row;
	MYSQL_RES* data;
	const char* query;
	connection = mysql_init(0);
	if (connection){
		connection = mysql_real_connect(connection, serverdb, userdb, passworddb, database, 3306, NULL, 0);
		if (connection){
			cin.ignore();
			cout<<"Ingrese la clave del alumno: ";
			getline(cin, alumno->clave);
			sql = "SELECT * FROM alumno where carne='"+alumno->clave+"'";
				query = sql.c_str();
				result = mysql_query(connection, query);
				if (result == 0){
					cout<<"Busqueda exitosa"<<endl;
					data = mysql_store_result(connection);
					int countColumns = mysql_num_fields(data);
					while(row = mysql_fetch_row(data)){
						for(int i = 0; i < countColumns; i++ ){
							cout<<row[i]<<"\t";
						}
						cout<<endl;
					}
				}
				else{
					cout<<"Busqueda sin exito"<<endl;
				}
	

		}
		else{
			cout<<"No se pudo conectar a la base de datos: "<<mysql_error(connection)<<endl;
		}
		
	}
	else{
		
		cout<<"No es posible iniciar la biblioteca de Mysql"<<endl;
	}
}
