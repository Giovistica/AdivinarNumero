#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include<windows.h>
#include <stdio.h>
using namespace std;

int generar_numero_aleatorio_fidel ();
bool comprobacion_numero_fidel (int num);
int generar_numero_fidel();
int darNumeroFidel ();
bool verificarNumeroAgustin (int numeroAgustin);
int darNumeroAgustin(int & semilla);
void digitosDeJulia (int numero,int& confirmacion);
int comprobacionDeJulia (int numero,int& confirmacion);
int darNumeroJulia();
int generarNumeroSecreto(char numeroDeOponente, int & semilla);
void elegirOponente(char & numeroDeOponente);
void darDigitos(int numero, int &digito1, int & digito2, int & digito3, int & digito4);
void comprobarMateOpepa( int digito1, int digito2, int digito3, int digito4, int digitoJ1, int digitoJ2, int digitoJ3, int digitoJ4,int& respuesta1, int &respuesta2, int & respuesta3, int & respuesta4);
void probarPista (int numeroDelJugador,int numeroSecreto, int& respuesta1, int &respuesta2, int & respuesta3, int & respuesta4);
bool comprobarSiSonIguales (int numeroDelJugador, int numeroSecreto );
void pedirNumero (int &numeroDelJugador, int numeroDeIntentos);
void darPista(int respuesta1, int respuesta2, int  respuesta3, int  respuesta4);
void pantallaBloqueada();
void decirResultado(bool partidaGanada, int numeroSecreto);
void analizarResultado (int numeroDelJugador,int numeroSecreto, bool &partidaGanada);
void intentoDeAdivinar(int numeroSecreto, bool & partidaGanada);
int unaPartida(int & semilla);
void calcularPuntajesParciales(int ganador, int & puntajeFidel, int & puntajeAgustin,int& puntajeJulia,int & puntajeJugador);
void mostrarPuntajesParciales(int puntajeFidel, int puntajeAgustin, int puntajeJulia, int puntajeJugador);
void jugarMatePepaAlfajor(int &puntajeFidel, int &puntajeAgustin, int &puntajeJulia, int &puntajeJugador,  int & semilla);
void menuMatePepa(int &puntajeFidel, int &puntajeAgustin, int &puntajeJulia, int &puntajeJugador,int & semilla);
void matePePaAlfajor(int & puntajeFidel, int &puntajeAgustin, int & puntajeJulia, int & puntajeJugador, int & semilla);
void pantalla_carga ();
void bienvenido ();
void colorea();
void gotoxy(short x, short y);
void menu();
void JuegosJuegos ();
void instrucciones();

	



int main(int argc, char *argv[]) {

	pantalla_carga();
	bienvenido ();
	menu();
	return 0;
}
//FUNCIONES //

int generar_numero_aleatorio_fidel (){
	
	int numero= 1000 + rand()% (10000-1000);
	return numero;
}
bool comprobacion_numero_fidel (int num){
		
			
	int cantidad_de_ceros=0;
	bool comprobado=true;
	do{
		if(num%2==0)cantidad_de_ceros++;
		else cantidad_de_ceros=0;
		if(cantidad_de_ceros>2) comprobado=false;
		num/=2;
	} while(num>1 and comprobado==true);
	
	return comprobado;	
	
}
int generar_numero_fidel(){

	int dig1,dig2,dig3,dig4,numero_fidel;
	bool numero_comprobado=false;
		
	do{
		numero_fidel=generar_numero_aleatorio_fidel();	
		darDigitos(numero_fidel, dig1, dig2, dig3, dig4);
			
		if(dig1!=dig2 and dig1!=dig3 and dig1!=dig4 and dig2!=dig3 and dig2!=dig4 and dig3!=dig4){
		numero_comprobado=comprobacion_numero_fidel(numero_fidel);
				
		}		
	} while((numero_comprobado!=true));

	return numero_fidel;
		
}	
int darNumeroFidel (){

	int numero_fidel;
	srand(time(NULL));
	numero_fidel=generar_numero_fidel();
		
	return numero_fidel;
}
	
bool verificarNumeroAgustin (int numeroAgustin){
	// verifica que los numeros tengaN cifras distintas y cumplan los lineaminetos del numero de agustin
    
    int primerCifra, segundaCifra, tercerCifra, cuartaCifra;
	bool exito = false;
    
    darDigitos(numeroAgustin,primerCifra, segundaCifra, tercerCifra, cuartaCifra);
		
	if ( numeroAgustin > 1022 and numeroAgustin < 9877){
			
	    if(primerCifra != segundaCifra and primerCifra != tercerCifra and primerCifra != cuartaCifra){
				
		    if( segundaCifra != tercerCifra and segundaCifra != cuartaCifra and cuartaCifra!= tercerCifra){
					
			    exito = true;
			}
		}	
    }
		
	return exito;
}
		

			
			
int darNumeroAgustin(int & semilla){
				
	// gnerera el numero apto y lo devuelve reiniciando la semilla cada 20 intentos
	int numeroAgustin, contador=0;
	bool exito= false;

	if(semilla==0){
        semilla = time(0)%21473;
    }		
	while(!exito){

        contador +=1;
        if(contador-1%20==0){
			semilla = time(0)%21473;
		}
		numeroAgustin = 49273*semilla % 21473;
		semilla = numeroAgustin;
		exito = verificarNumeroAgustin(numeroAgustin);    
	}
	return numeroAgustin;				
}
				
				
				
				
void digitosDeJulia (int numero,int& confirmacion){
	/*Se evalua el numero generado, separando cada uno de sus digitos. Una vez
	idenficados los digitos, se comparan entre ellos dependiendo de las condiciones
	propuestas por Julia. */

	int dig1, dig2, dig3, dig4;

	darDigitos (numero, dig1, dig2, dig3, dig4);

	if (dig1%2!=0 and (dig2%2==0 and dig2!=dig1) and (dig3%2==0 and dig3!=dig1 and dig3!=dig2)){
		if (dig4%2!=0 and dig4!=dig1 and dig4!=dig2 and dig4!=dig3 and (dig4*10+dig3)>(dig2*10+dig1)){

			confirmacion=1;

        }else confirmacion=0;
    }else confirmacion=0;
}
int darNumeroJulia(){
							
    /* En la funcion  generamos un do-while donde invocamos numeros ramdom
	para su analisis en la funcion comprobacion, en caso que el numero cumpla 
	con los requisitos pedidos, el while cierra.*/
							
	int num, confirmacion=0;
							
	srand(time(NULL));
	do {
		num=rand() % 9999 + 1000;
		digitosDeJulia (num, confirmacion);
	} while(confirmacion==0);
							
	return num;
}
				
int generarNumeroSecreto(char numeroDeOponente, int & semilla){
	//Esto genera el numero secreto de acuerdo a la dificultad elegida,
	int numeroSecreto;
	
	if(numeroDeOponente == '1') {
	    numeroSecreto = darNumeroFidel();
    }else if(numeroDeOponente == '2'){
	    numeroSecreto = darNumeroAgustin(semilla);
    }else{	
	    numeroSecreto = darNumeroJulia();
    }
    return numeroSecreto;	
}
void elegirOponente(char & numeroDeOponente){

	bool oponenteValido = false;
	unsigned char a=238, c=95, f=186;
	do{
		gotoxy(25,3);
		cout << "Ingrese el numero que corresponda al oponente elegido y presion ENTER"	<< endl;
		for (int b=25; b<95; b++){
			gotoxy (b,4);
			cout << a << endl; 
		}
		for (int e=6; e<=11; e++){
			gotoxy (54,e);
			cout << f << endl; 
			gotoxy (65,e);
			cout << f << endl; 
		}
		gotoxy (56,6);
		cout << "1-FIDEL" << endl;
		gotoxy (56,8);
		cout << "2-AGUSTIN"<< endl;
		gotoxy (56,10);
		cout << "3-JULIA"<< endl;
		gotoxy (59,13);
		cout << c << endl;
		gotoxy (60,13);
		cout << c << endl;
		gotoxy (61,13);
		cout << c << endl;
		
		gotoxy (60,13);
		cin >> numeroDeOponente;
		
		
		if( (numeroDeOponente == '1') || (numeroDeOponente == '2') || (numeroDeOponente == '3') ) {
			
			oponenteValido = true;
			
			
			gotoxy(45,15);
			cout << "Tu oponente es ... Docente ... de aedd CUIDADO!" << endl;
			Sleep(7000);
			system("cls");
			
		}
		else {
			
			oponenteValido = false;
			gotoxy(25,18);
			cout << "El valor ingresado " << numeroDeOponente << " no es correcto. "
				<< "Por favor ingrese otro valor" <<endl;
		}
	}while(oponenteValido == false);
}
void darDigitos(int numero, int &digito1, int & digito2, int & digito3, int & digito4){
		
	digito1 = numero/1000;
	digito2 = numero/100%10;
	digito3 = numero/10%10;
	digito4 = numero%10;
		
}
		
void comprobarMateOPepa( int digito1, int digito2, int digito3, int digito4, int digitoJ1, int digitoJ2, int digitoJ3, int digitoJ4,int& respuesta1, int &respuesta2, int & respuesta3, int & respuesta4){
		
    if(
			
		digito1 == digitoJ1 ) {
			respuesta1=1;
	}else if(
		digito1==digitoJ2 or
		digito1==digitoJ3 or
		digito1==digitoJ4 ){

			respuesta1=2;}
	if (digito2 == digitoJ2 ) {
        respuesta2=1;
	}else if(
		digito2==digitoJ1 or
		digito2==digitoJ3 or
		digito2==digitoJ4 ){

			respuesta2=2;}
        
	if (digito3 == digitoJ3 ) {
			respuesta3=1;
	}else if(
		digito3==digitoJ1 or
		digito3==digitoJ2 or
		digito3==digitoJ4 ){

			respuesta3=2;
        }								
	if(digito4 == digitoJ4 ) {
		respuesta4=1;
	}else if(
			digito4==digitoJ1 or
			digito4==digitoJ2 or
			digito4==digitoJ3 ){

				respuesta4=2;
    }		
}				
void probarPista (int numeroDelJugador,int numeroSecreto, int& respuesta1, int &respuesta2, int & respuesta3, int & respuesta4){

        

	int digito1, digito2, digito3, digito4;
	int digitoJ1, digitoJ2, digitoJ3, digitoJ4;
					
	darDigitos(numeroSecreto, digito1, digito2, digito3, digito4);
	darDigitos(numeroDelJugador, digitoJ1, digitoJ2, digitoJ3, digitoJ4);				
	comprobarMateOPepa( digito1, digito2, digito3, digito4,digitoJ1, digitoJ2, digitoJ3, digitoJ4, respuesta1, respuesta2, respuesta3, respuesta4);
					
}
						
						
bool comprobarSiSonIguales (int numeroDelJugador, int numeroSecreto ){

    
	return numeroDelJugador == numeroSecreto;							
								
}
							
void pedirNumero (int &numeroDelJugador, int intentosDeAdivinar){
	
    unsigned char a,b,c,d;
	int aceptado=0;
	// acÃ¡ van verificaciones del numero del jugadr, que sea un int que enga cuatro cifras etc....
								
	do {
									
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),8);
		gotoxy (44,3);
		cout<< "ADIVINA EL NUMERO SECRETO!"<< endl;
		gotoxy (48,5);
		cout<<"Tenes "; 
		gotoxy (55,5);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
		cout<< 15-intentosDeAdivinar; 
		gotoxy (57,5);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),8);
		cout<<" intentos" <<endl;
		gotoxy (53,7);
		cout<< "SUERTE ! "<< endl;
									
										
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),11);
		gotoxy (42,9);
		cout <<"Ingrese un numero de 4 digitos"<< endl;
		gotoxy (54,11);
		cin >> a; 
		gotoxy (55,11);
		cin >> b;
		gotoxy (56,11);
		cin >> c; 
		gotoxy (57,11);
		cin >> d;
		if (isalpha(a) or isalpha(b) or isalpha(c) or isalpha(d)){
			gotoxy (48,13);
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),12);
			cout << "VALOR NO ACEPTADO" << endl;
			gotoxy (40,14);
			cout << "Ingrese un NUMERO de cuatro cifras" << endl;
			Sleep(2000);
			system("cls");
		}
		else{
			gotoxy (40,16);
			aceptado=1;
			numeroDelJugador = (a-48)*1000+(b-48)*100 + (c-48)*10 +(d-48);
			}
	}while((aceptado==0) or numeroDelJugador > 10000);

	gotoxy (49,13);
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),10);
	cout << "NUMERO ACEPTADO"<< endl;
	Sleep(1000);
								
}
void darPista(int respuesta1, int respuesta2, int  respuesta3, int  respuesta4){
									
	system("cls");

    if (respuesta1 ==0 && respuesta2 ==0 && respuesta3 ==0 && respuesta4 ==0){
		cout << "ALFAJOR ";
	}
																	
	else {
        
        if(respuesta1 == 1){
		    cout << "MATE ";
		}else if (respuesta1==2){
		    cout << "PEPA ";
		}
        if(respuesta2 == 1){
		    cout << "MATE ";
		}else if (respuesta2 ==2){
		    cout << "PEPA ";
		}
        if(respuesta3 == 1){
		    cout << "MATE ";
		}else if (respuesta3 ==2){
		    cout << "PEPA ";
		}
        if(respuesta4 == 1){
		    cout << "MATE ";
		}else if (respuesta4 ==2){
		    cout << "PEPA ";
		}	
    }    
	cout << endl;
	Sleep(900);
}	

void pantallaBloqueada(){
	
	system("cls");
	gotoxy (45,5);
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),12);
	cout << "FALLASTE 3 INTENTOS" << endl;
    gotoxy (47,6);
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),3);
	cout << "ESTAS BLOQUEADO" << endl;
	Sleep(10000);
	system("cls");
		
}	
void decirResultado(bool partidaGanada, int numeroSecreto){

	if (partidaGanada == false){
		gotoxy (50,5);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
		cout <<"Oh no!"<< endl;
		gotoxy (59,5);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),12);
		cout << "PERDISTE" << endl;
		gotoxy (44,6);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
		cout << "El numero correcto era: ";
		gotoxy (69,6);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),10);
		cout << numeroSecreto << endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
		Sleep(900);
		gotoxy (46,8);
		cout << "QUEDASTE LIBRE EN AEDD" << endl;
		Sleep(900);
		gotoxy (48,9);
		cout << "(y recien es Junio)" << endl;
		gotoxy (38,10);
		cout << "ESTA MANIOBRA TE COSTARA  UN Anio  DE CARRERA" << endl;
		Sleep(4000);
	}
	else{
		gotoxy (44,5);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),10);
		cout << "FELICIDADES USTED HA GANADO" << endl;
		gotoxy (49,7);
		cout << "Suma 25 puntos!!!" << endl;
	}
		Sleep(1000);
		system("cls");
}		
void analizarResultado (int numeroDelJugador,int numeroSecreto, bool &partidaGanada){
    
	int respuesta1=0, respuesta2=0, respuesta3=0, respuesta4=0;
				
	partidaGanada = comprobarSiSonIguales(numeroDelJugador,numeroSecreto);
	probarPista(numeroDelJugador, numeroSecreto,respuesta1, respuesta2, respuesta3, respuesta4);
	darPista(respuesta1, respuesta2, respuesta3, respuesta4);
				
				
}	
	
void intentoDeAdivinar(int numeroSecreto, bool & partidaGanada){

	int numeroDelJugador, numeroDeIntentos=0;
		
	while(!partidaGanada && numeroDeIntentos<15){
        
		if((numeroDeIntentos+3)%3 == 0 && numeroDeIntentos!=0 ){
			
			pantallaBloqueada();			
		}
		pedirNumero(numeroDelJugador, numeroDeIntentos);
		analizarResultado(numeroDelJugador,numeroSecreto,partidaGanada);
		
        numeroDeIntentos +=1;
		
		
				
	Sleep(1000);
    system("cls");
				
	}
}	
		
		
int unaPartida(int & semilla){
	system("cls");
	
	int  numeroSecreto, ganador;
	bool partidaGanada=false;
	char numeroDeOponente;
		
		
	elegirOponente(numeroDeOponente);
		
	numeroSecreto = generarNumeroSecreto(numeroDeOponente,semilla);
		
	intentoDeAdivinar(numeroSecreto,partidaGanada);
		
	decirResultado(partidaGanada,numeroSecreto);
		
		
	if (partidaGanada){ 
        ganador = 4;
	}
	else{
		ganador = int (numeroDeOponente)-48;
		}
	return ganador;
}	
		
		

void calcularPuntajesParciales(int ganador, int & puntajeFidel, int & puntajeAgustin,int& puntajeJulia,int & puntajeJugador){

	
	
	// no usamos string y repetimos codigo. 
	
	switch(ganador){
	
	case 1 : 
        puntajeFidel+=25;
        gotoxy (50,3);
	    cout << "FIDEL" << " suma 25 puntos !" <<endl;
	    gotoxy (39,4);
	    cout << "Su puntaje en esta sesion acumula:    " << puntajeFidel <<"  puntos "  << endl;
	    gotoxy (43,5);
	    break;
	
	case 2 : 
        puntajeAgustin+=25;
	    gotoxy (50,3);
	    cout << "AGUSTIN" << " suma 25 puntos !" <<endl;
	    gotoxy (39,4);
	    cout << "Su puntaje en esta sesion acumula:    " << puntajeAgustin <<"  puntos "  << endl;
	    gotoxy (43,5);
	    break;
	
	case 3 : 
        puntajeJulia+=25;
	    gotoxy (50,3);
	    cout << "JULIA" << " suma 25 puntos !" <<endl;
	    gotoxy (39,4);
	    cout << "Su puntaje en esta sesion acumula:    " << puntajeJulia <<"  puntos "  << endl;
	    gotoxy (43,5);
	    break;
	
	default: 
        puntajeJugador+=25;
	    gotoxy (50,3);
	    cout << "JUGADOR" << " suma 25 puntos !" <<endl;
	    gotoxy (39,4);
	    cout << "Su puntaje en esta sesion acumula:    " << puntajeJugador <<"  puntos "  << endl;
	    gotoxy (43,5);
    }
	
	system("pause");
}
void mostrarPuntajesParciales(int puntajeFidel, int puntajeAgustin, int puntajeJulia, int puntajeJugador){

	int aux,  numero1, numero2, numero3, numero4,x,y;
	int auxnombre, nombre1, nombre2, nombre3, nombre4;
	unsigned char a=205,b=186,c=187,d=188,e=200,f=201;

	if(puntajeFidel > puntajeAgustin){
		
		numero1 = puntajeFidel;
		nombre1 = 1;
		numero2 = puntajeAgustin;
		nombre2 = 2;
	}else{
		
		numero2 = puntajeFidel;
		nombre2 = 1;
		numero1 = puntajeAgustin;
		nombre1 = 2;
	}
	if(puntajeJulia > puntajeJugador){
		
		numero3 = puntajeJulia;
		nombre3 = 3;
		numero4 = puntajeJugador;
		nombre4 = 4;
		
	}else{
		
		numero4 = puntajeJulia;
		nombre4 = 3;
		numero3 = puntajeJugador;
		nombre3 = 4;
	}	

	if(numero3 > numero1){
		aux = numero1;
		auxnombre = nombre1;
		numero1 = numero3;
		nombre1 = nombre3;
		numero3 = aux;
		nombre3 = auxnombre;
	}
	
	if(numero4 > numero2){
		aux = numero2;
		auxnombre = nombre2;
		numero2 = numero4;
		nombre2 = nombre4;
		numero4 = aux;
		nombre4 = auxnombre;
	}
	if(numero3 > numero2){
		aux = numero2;
		auxnombre = nombre2;
		numero2 = numero3;
		nombre2 = nombre3;
		numero3 = aux;
		nombre3 = auxnombre;
	}

	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),11);
	for (x=42; x<=84; x++){
		for (y=18; y<=25; y++){
			if ((y==18 or y==25) and (x!=42 and x!=84)){
				gotoxy (x,y);
				cout << a << endl;
			}
			if ((y!=18 and y!=25) and (x==42 or x==84)){
				gotoxy (x,y);
				cout << b << endl;
			}
			if (y==18 and x==84){
				gotoxy (x,y);
				cout << c << endl;
			}
			if (y==25 and x==84){
				gotoxy (x,y);
				cout << d << endl;
			}
			if (y==25 and x==42){
				gotoxy (x,y);
				cout << e << endl;
			}
			if (y==18 and x==42){
				gotoxy (x,y);
				cout << f << endl;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),8);
	
	// no usamos string y repetimos mucho codigo.
	
	switch(nombre1){
	    case 1:
			gotoxy (44,20);
	        cout << " El puntaje de FIDEL   es :    " << numero1 << endl;
			break;
	    case 2:
			gotoxy (44,21);
	        cout << " El puntaje de AGUSTIN   es :    " << numero1 << endl;
	        break;
		case 3:
	        gotoxy (44,22);
	        cout << " El puntaje de JULIA   es :    " << numero1 << endl;
	        break;
	    case 4:	 
			gotoxy (44,23);
		    cout << " El puntaje de JUGADOR   es :    " << numero1 << endl;
		    break;
	}
	switch(nombre2){
		case 1:
	       gotoxy (44,20);
	       cout << " El puntaje de FIDEL   es :    " << numero2 << endl;
	       break;
	    case 2:
	       gotoxy (44,21);
	       cout << " El puntaje de AGUSTIN   es :    " << numero2 << endl;
	       break;
	    case 3:
	       gotoxy (44,22);
	       cout << " El puntaje de JULIA   es :    " << numero2 << endl;
	      break;
	    case 4:	 
		   gotoxy (44,23);
		   cout << " El puntaje de JUGADOR   es :    " << numero2 << endl;
		break;
	}	
	switch(nombre3){
		case 1:
	         gotoxy (44,20);
	         cout << " El puntaje de FIDEL   es :    " << numero3 << endl;
	         break;
	    case 2:
	        gotoxy (44,21);
	         cout << " El puntaje de AGUSTIN   es :    " << numero3 << endl;
	         break;
	    case 3:
	         gotoxy (44,22);
	         cout << " El puntaje de JULIA   es :    " << numero3 << endl;
	         break;
	    case 4:	 
		     gotoxy (44,23);
		     cout << " El puntaje de JUGADOR   es :    " << numero3 << endl;
		     break;
	}
	switch(nombre4){
		case 1:
	        gotoxy (44,20);
	        cout << " El puntaje de FIDEL   es :    " << numero4 << endl;
	        break;
		case 2:
	        gotoxy (44,21);
	        cout << " El puntaje de AGUSTIN   es :    " << numero4 << endl;
		    break;
	    case 3:
	        gotoxy (44,22);
	        cout << " El puntaje de JULIA   es :    " << numero4 << endl;
	    break;
	    case 4:	 
			gotoxy (44,23);
		    cout << " El puntaje de JUGADOR   es :    " << numero4 << endl;
		    break;
	}
	
	cin.get();
	if (cin.get()){
		Sleep(0);
	}
	
}	
void jugarMatePepaAlfajor(int &puntajeFidel, int &puntajeAgustin, int &puntajeJulia, int &puntajeJugador,  int & semilla){

	int ganador;
	ganador = unaPartida(semilla);
	// tambien anuncia al ganador
	calcularPuntajesParciales( ganador,puntajeFidel, puntajeAgustin, puntajeJulia, puntajeJugador);

}
void menuMatePepa(int &puntajeFidel, int &puntajeAgustin, int &puntajeJulia, int &puntajeJugador,int & semilla){
	
	bool opcionValida = true;
	char numeroDeOpcion;
	unsigned char a=186, b=95;
	
	
	do {
	    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
	    gotoxy (30,3);
	    cout << "Ingrese el numero correspondiente a la opcion elegida y presione ENTER"	<< endl;
	    gotoxy (50,6);
	    cout << "1-INICIAR PARTIDA" << endl;
	    gotoxy (50,8);
	    cout << "2-VER PUNTAJES PARCIALES"<< endl;
	    gotoxy (50,10);	
	    cout << "3-VOLVER AL MENU PRINCIPAL"<< endl;
	    for (int y=6; y<=11; y++){
		    gotoxy (48,y);
		    cout << a << endl;
		    gotoxy(77,y);
		    cout << a << endl;
	    }
	    gotoxy(60,16);
	    cout << b << endl;
	    gotoxy(62,16);
	    cout << b << endl;
	    gotoxy(61,16);
	    cout << b << endl;
	    gotoxy(61,16);
	    cin >> numeroDeOpcion;

	    if( numeroDeOpcion == '1') {
		
		    jugarMatePepaAlfajor(puntajeFidel, puntajeAgustin, puntajeJulia, puntajeJugador,  semilla);
		
	    } 
	    else if (numeroDeOpcion == '2'){
		
		    mostrarPuntajesParciales(puntajeFidel, puntajeAgustin, puntajeJulia, puntajeJugador);
	    }
	
	    else if(numeroDeOpcion == '3')  {
		    system("cls");
		    opcionValida=false;
	    }
	    else {
		
		    gotoxy (30,20);
		    cout << "El valor ingresado  no es correcto. "
			<< "Por favor ingrese otro valor" <<endl;
		    Sleep(900);
	    }
	
	     system("cls");

	} while(opcionValida == true );
}
void matePePaAlfajor(int & puntajeFidel, int &puntajeAgustin, int & puntajeJulia, int & puntajeJugador, int & semilla){

	instrucciones();
	menuMatePepa(puntajeFidel, puntajeAgustin, puntajeJulia, puntajeJugador, semilla);
}	

void pantalla_carga (){
	int x,y,i;
	unsigned char k;
	k=219;
	gotoxy (53,10); 
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
	cout << "CARGANDO..." << endl;
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),5);
	for (i=15; i<105;i++){
		gotoxy (i,13);
		cout << k;
		if (i==35 or i==50 or i==95)
			Sleep(900);
		for (x=50; x<70; x++){
			for (y=1; y<70; y++){
				gotoxy(y,24);
				}
			}
		}
		Sleep(3000);
		system ("cls");
	}
void colorea(){
	gotoxy (41,10); 
	cout << "Este juego no se encuentra disponible aun" << endl;
	Sleep(3000);
	system ("cls");
		
	}
void gotoxy(short x, short y){
	COORD cp = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
	}
void menu(){
		//int opcion;
		time_t comienzo, final;
		comienzo = time( NULL );
		char opcion, opcion2, a=95; 
		bool jugar=true;
        int semilla = 0;
	    int  puntajeFidel=0, puntajeAgustin=0, puntajeJulia=0, puntajeJugador=0;
		
		while(jugar){
	
			JuegosJuegos();
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),8);
			gotoxy(50,10);
			cout << "1.- Mate-Pepas-Alfajores " << endl;
			gotoxy(50,13);
			cout << "2.- Colorea " << endl;
			gotoxy(50,16);
			cout << "3.- Cerrar aplicacion " << endl;
			gotoxy(35,21);
			cout << "Ingrese el numero de opcion elegida y presione ENTER" << endl;
			gotoxy(60,22);
			cout << a << endl;
			gotoxy(59,22);
			cout << a << endl;
			gotoxy(61,22);
			cout << a << endl;
			gotoxy(60,22);
			cin >> opcion;
			if ((opcion!='1') and (opcion!='2') and (opcion!='3')){
				system ("cls");
				gotoxy(28,14);
				cout << "Opcion invalida, por favor esciba otro valor" << endl;
				Sleep(3000);
				system ("cls");
				 
			}
			else {
				switch(opcion){
				case '1':
					system ("cls");
					matePePaAlfajor(puntajeFidel, puntajeAgustin, puntajeJulia, puntajeJugador, semilla);
					break;
				case '2':
					system ("cls");
					colorea();
					break;
				case '3':
					unsigned char k=205,b=186,c=187,d=188,e=200,f=201;
					int x,y;
					
					system ("cls");
					for (x=42; x<=84; x++){
						for (y=3; y<=7; y++){
							if ((y==3 or y==7) and (x!=42 and x!=84)){
								gotoxy (x,y);
								cout << k << endl;
							}
							if ((y!=3 and y!=7) and (x==42 or x==84)){
								gotoxy (x,y);
								cout << b << endl;
							}
							if (y==3 and x==84){
								gotoxy (x,y);
								cout << c << endl;
							}
							if (y==7 and x==84){
								gotoxy (x,y);
								cout << d << endl;
							}
							if (y==7 and x==42){
								gotoxy (x,y);
								cout << e << endl;
							}
							if (y==3 and x==42){
								gotoxy (x,y);
								cout << f << endl;
							}
						}
					}
					gotoxy(44,4);
					cout << "Esta seguro de querer salir del juego?" << endl;
					gotoxy(44,6);
					cout << "1. SI ";
					gotoxy(78,6);
					cout << "2. NO ";
					gotoxy(62,8);
					cin >> opcion2;
					system ("cls");
					if (opcion2=='1'){
						for (x=42; x<=84; x++){
							for (y=11; y<=15; y++){
								if ((y==11 or y==15) and (x!=42 and x!=84)){
									gotoxy (x,y);
									cout << k << endl;
								}
								if ((y!=11 and y!=15) and (x==42 or x==84)){
									gotoxy (x,y);
									cout << b << endl;
								}
								if (y==11 and x==84){
									gotoxy (x,y);
									cout << c << endl;
								}
								if (y==15 and x==84){
									gotoxy (x,y);
									cout << d << endl;
								}
								if (y==15 and x==42){
									gotoxy (x,y);
									cout << e << endl;
								}
								if (y==11 and x==42){
									gotoxy (x,y);
									cout << f << endl;
								}
							}
						}
						final = time( NULL );
						gotoxy (44,13);
						cout << "El tiempo de sesion fue de: " <<difftime(final, comienzo)<< " SEGUNDOS"<< endl;
						gotoxy (44,17);
						cout << "Su puntaje durante la sesion fue de:" << endl;
						mostrarPuntajesParciales(puntajeFidel, puntajeAgustin, puntajeJulia, puntajeJugador);
						system ("cls");
						gotoxy(50,14);
						cout << "Gracias por su visita!"<< endl;
						gotoxy(56,15);
						cout << "Saludos!" << endl;
						Sleep(3000);
						system ("cls");
						jugar=false;
						
						
						
					}
					if (opcion2=='2'){
						system ("cls");
						
					}
				}
			}
			
		}
		
	}
void JuegosJuegos (){
	int x,y;
	unsigned char k, l, m, n, v, j, f;
	k=186;
	l=205;
	m=200;
	n=188;
	v=204;
	j=201;
	f=187;
	for (x=1; x<200; x++){
		for (y=1; y<20; y++){
			gotoxy (x,y);
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
			if (x==6 and (y==5 or y==4 or y==3 or y==2 or y==1))
				cout << k << endl;
			if (y==5 and x==1)
				cout << k << endl;
			if (y==6 and (x==3 or x==4 or x==5 or x==2))
				cout << l << endl;
			if (y==6 and x==1)
				cout << m << endl;
			if (y==6 and x==6)
				cout << n << endl;
			if (x==10 and (y==5 or y==4 or y==3 or y==2 or y==1))
				cout << k << endl;
			if (y==6 and x==10)
				cout << m << endl;
			if (y==6 and (x==11 or x==12 or x==13 or x==14))
				cout << l << endl;
			if (x==15 and (y==5 or y==4 or y==3 or y==2 or y==1))
				cout << k << endl;
			if (x==15 and y==6)
				cout << n << endl;
			if (y==1 and x==19)
				cout << j << endl;
			if (y==1 and (x==20 or x==21 or x==22 or x==23 or x==24))
				cout << l << endl;
			if (y==6 and x==19)
				cout << m << endl;
			if (y==3 and x==19)
				cout << v << endl;
			if ((y==2 or y==4 or y==5) and x==19)
				cout << k << endl;
			if (y==3 and (x==20 or x==21 or x==22 or x==23 or x==24))
				cout << l << endl;
			if (y==6 and (x==20 or x==21 or x==22 or x==23 or x==24))
				cout << l << endl;
			if (y==1 and x==28)
				cout << j << endl;
			if (y==1 and (x==29 or x==30 or x==31 or x==32 or x==33))
				cout << l << endl;
			if (y==6 and x==28)
				cout << m << endl;
			if ((y==2 or y==3 or y==4 or y==5) and x==28)
				cout << k << endl;
			if (y==6 and (x==29 or x==30 or x==31 or x==32 or x==33))
				cout << l << endl;
			if (y==6 and x==34)
				cout << n << endl;
			if (y==5 and x==34)
				cout << k << endl;
			if (y==4 and x==34)
				cout << f << endl;
			if (y==4 and (x==32 or x==33))
				cout << l << endl;
			if (y==1 and x==37)
				cout << j << endl;
			if (y==1 and x==43)
				cout << f << endl;
			if (y==6 and x==37)
				cout << m << endl;
			if (y==6 and x==43)
				cout << n << endl;
			if (y==1 and (x==38 or x==39 or x==40 or x==41 or x==42))
				cout << l << endl;
			if (y==6 and (x==38 or x==39 or x==40 or x==41 or x==42))
				cout << l << endl;
			if ((y==2 or y==3 or y==4 or y==5) and x==37)
				cout << k << endl;
			if ((y==2 or y==3 or y==4 or y==5) and x==43)
				cout << k << endl;
			if (y==1 and x==47)
				cout << j << endl;
			if (y==1 and (x==48 or x==49 or x==50 or x==51 or x==52))
				cout << l << endl;
			if (y==2 and x==47)
				cout << k << endl;
			if (y==3 and x==47)
				cout << m << endl;
			if (y==3 and (x==48 or x==49 or x==50 or x==51))
				cout << l << endl;
			if (y==3 and x==52)
				cout << f << endl;
			if ((y==4 or y==5) and x==52)
				cout << k << endl;
			if (y==6 and x==52)
				cout << n << endl;
			if (y==6 and (x==47 or x==48 or x==49 or x==50 or x==51))
				cout << l << endl;
			////
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),9);
			if (x==66 and (y==5 or y==4 or y==3 or y==2 or y==1))
				cout << k << endl;
			if (y==5 and x==61)
				cout << k << endl;
			if (y==6 and (x==63 or x==64 or x==65 or x==62))
				cout << l << endl;
			if (y==6 and x==61)
				cout << m << endl;
			if (y==6 and x==66)
				cout << n << endl;
			if (x==70 and (y==5 or y==4 or y==3 or y==2 or y==1))
				cout << k << endl;
			if (y==6 and x==70)
				cout << m << endl;
			if (y==6 and (x==71 or x==72 or x==73 or x==74))
				cout << l << endl;
			if (x==75 and (y==5 or y==4 or y==3 or y==2 or y==1))
				cout << k << endl;
			if (x==75 and y==6)
				cout << n << endl;
			if (y==1 and x==79)
				cout << j << endl;
			if (y==1 and (x==80 or x==81 or x==82 or x==83 or x==84))
				cout << l << endl;
			if (y==6 and x==79)
				cout << m << endl;
			if (y==3 and x==79)
				cout << v << endl;
			if ((y==2 or y==4 or y==5) and x==79)
				cout << k << endl;
			if (y==3 and (x==80 or x==81 or x==82 or x==83 or x==84))
				cout << l << endl;
			if (y==6 and (x==80 or x==81 or x==82 or x==83 or x==84))
				cout << l << endl;
			if (y==1 and x==88)
				cout << j << endl;
			if (y==1 and (x==89 or x==90 or x==91 or x==92 or x==93))
				cout << l << endl;
			if (y==6 and x==88)
				cout << m << endl;
			if ((y==2 or y==3 or y==4 or y==5) and x==88)
				cout << k << endl;
			if (y==6 and (x==89 or x==90 or x==91 or x==92 or x==93))
				cout << l << endl;
			if (y==6 and x==94)
				cout << n << endl;
			if (y==5 and x==94)
				cout << k << endl;
			if (y==4 and x==94)
				cout << f << endl;
			if (y==4 and (x==92 or x==93))
				cout << l << endl;
			if (y==1 and x==97)
				cout << j << endl;
			if (y==1 and x==103)
				cout << f << endl;
			if (y==6 and x==97)
				cout << m << endl;
			if (y==6 and x==103)
				cout << n << endl;
			if (y==1 and (x==98 or x==99 or x==100 or x==101 or x==102))
				cout << l << endl;
			if (y==6 and (x==98 or x==99 or x==100 or x==101 or x==102))
				cout << l << endl;
			if ((y==2 or y==3 or y==4 or y==5) and x==97)
				cout << k << endl;
			if ((y==2 or y==3 or y==4 or y==5) and x==103)
				cout << k << endl;
			if (y==1 and x==107)
				cout << j << endl;
			if (y==1 and (x==108 or x==109 or x==110 or x==111 or x==112))
				cout << l << endl;
			if (y==2 and x==107)
				cout << k << endl;
			if (y==3 and x==107)
				cout << m << endl;
			if (y==3 and (x==108 or x==109 or x==110 or x==111))
				cout << l << endl;
			if (y==3 and x==112)
				cout << f << endl;
			if ((y==4 or y==5) and x==112)
				cout << k << endl;
			if (y==6 and x==112)
				cout << n << endl;
			if (y==6 and (x==107 or x==108 or x==109 or x==110 or x==111))
				cout << l << endl;
			SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),8);
			if ((y==8 or y==9 or y==10 or y==11 or y==12 or y==13 or y==14 or y==15 or y==16 or y==17 or y==18) and (x==48 or x==76))
				cout << k << endl;		}
	}
}
	void instrucciones(){
		unsigned char a=174, b=175;
		//Los acentos en los cout rompen el juego, al abrirlo entre VS y zinjai despues no compila
		gotoxy (37,3);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),6);
		cout << "HAS INGRESADO A MATES-PEPAS-ALFAJORES" << endl;
		gotoxy (48,5);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),6);
		cout << "¿COMO SE JUEGA?" << endl;
		gotoxy (10,7);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
		cout << "En este desafio pods elegir entre 3 oponentes " << endl; gotoxy (10,8); cout << "que esconden un numero secreto de 4 cifras y el cual debes adivinar" << endl;
		gotoxy (38,10);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),6);
		cout << "COMO ENCUENTRO EL NUMERO DE 4 CIFRAS?" << endl;
		gotoxy (10,12);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
		cout << "Cuando empiezes, tendras 15 oportunidades para encontrar el numero." << endl; gotoxy (10,13); cout << "Luego de cada intento el oponente te dara ALGUNAS pistas para que puedas adivinarlo. " << endl;
		gotoxy (13,15);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),4);
		cout << "MATE: ";
		gotoxy (19,15);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
		cout << "Signfica que el nmero ingresado en el intento tiene un dgito que esta bien y en el lugar correcto." << endl;
		gotoxy (13,17);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),9);
		cout << "PEPA: ";
		gotoxy (21,17);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
		cout << "Significa que el nmero ingresado en el intento tiene un dito que esta bien," << endl; gotoxy (13,18); cout << "pero dicho digito no se encuentra en el lugar correcto." << endl;
		gotoxy (13,20);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),2);
		cout << "ALFAJORES: ";
		gotoxy (25,20);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
		cout << "Ninguno de los dgitos ingresados forma parte del nmero secreto." << endl;
		gotoxy (13,22);
		cout << "En caso de ganar el juego se te otorgar 25 puntos" << endl; gotoxy(13,23); cout << "pasados los 15 intentos ganara el oponente." << endl;
		gotoxy (13,25);
		cout << "Suerte en tu travesia por el juego!" << endl;
		gotoxy (13,29);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),8);
		cout << "PRESIONA ENTER PARA CONTINUAR!" << endl;
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),7);
		for (int i=17; i <48; i++){
			gotoxy (i,5);
			cout << a << endl;
			gotoxy (i+46,5);
			cout << b << endl;
			gotoxy (i-10,10);
			cout << a << endl;
			gotoxy (i+59,10);
			cout << b << endl;
		}
		cin.get();
		if (cin.get()){
			system ("cls");
			
		}
	}
void bienvenido (){
		unsigned char k, l, m, n, j, f;
		k=186;
		l=205;
		m=200;
		n=188;
		j=201;
		f=187;
		for (int x=49; x<=71; x++){
			for (int y=2; y<=4; y++){
				gotoxy (x,y);
				if ((x==49 or x==71) and (y!=2 and y!=4))
					cout << k << endl;
				if ((y==2 or y==4) and (x!=49 and x!=71))
					cout << l << endl;
				if (x==49 and y==4)
					cout << m << endl;
				if (x==71 and y==4)
					cout << n << endl;
				if (x==49 and y==2)
					cout << j << endl;
				if (x==71 and y==2)
					cout << f << endl;
			}
		}
		gotoxy (50,3);
		SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),11);
		cout << "B I E N V E N I D O !" << endl;  
		gotoxy (20,8);
		cout << "Creadores:" << endl;
		gotoxy (30,10);
		cout << "Mauricio Exequiel D'Amato - contacto: maurid2000@gmail.com" << endl;
		gotoxy (30,12);
		cout << "Giovana Cardo Cristofoli - contacto: giovi.cristofoli@gmail.com" << endl;
		gotoxy (30,14);
		cout << "Hector Dalla Fontana - contacto: agustindallafontana@iCloud.com" << endl; 
		gotoxy (20,17);
		cout << "Institucion: " << endl; 
		gotoxy (37,19);
		cout << "UTN Santa Fe - UTN Facultad Regional Santa Fe" << endl; 
		gotoxy (20,22);
		cout << "Grupo: " << endl;
		gotoxy (46,24);
		cout << "Intento de programadores" << endl; 
		time_t now=time(0);
		tm *ltm = localtime(&now);
		gotoxy (80,26);
		cout << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 2014 + ltm->tm_mday;
		gotoxy (80,27);
		cout <<"Hora: " << ltm->tm_hour << ":" << ltm->tm_min << endl;
		if (cin.get()){
			system ("cls");
			
		}
}
