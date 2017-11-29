/* Projet Sam
	Controle de l'humdité dans le sol et création d'une pompe intéligente
	Programme developpé en C pour une machine de type "Raspberry Pi"
	Co developpé par Lebreton Jean Camille 
*/

// Definition des librairies nécessaires 
#include <stdio.h>		// Bilbiotheque standard pour les affichages et les controles des I/O (clavier ecran etc ...)
#include <stdlib.h>		// Bibliotheque standard pour la declaration des librairies standard
#include <pigpio.h> 	// Bibliotheque pour la gestion des GPIO de la rpi
#include <sys/time.h>	// Bilbiothque pour la gestion du temps 
#include <unistd.h> 	// Bibliotheque apportant la focntion "sleep"

//Declaration des variables 
// j'effectue la déclaration des varibles en globales pour le code soit plus compréhensible pour toi


//Déclaration des fonctions
// On déclarera une premiere fois le protype des fonctions ici pour les décrire 
void Initialisation (void);
void Launch_Pump(int secondes);

//Declaration des fonctions 
// ici on retrouvera le code des différentes fonctions
void Initialisation (void)
{
	// les 3 if suivant sont fait pour déclarer les différents IO dont nous aurons besoin
	if (gpioInitialise() < 0) // Initialisation des ports d'entrée sorties
		{
			fprintf(stderr, "pigpio initialisation échouée\n");// affichage sur la console d'un code d'erreur en case de défaut
			exit(1);
		}	
	if(gpioSetMode(18,PI_OUTPUT) !=0) // output du relay a l'état haut, on choisira de controller le moteur 
		{
			printf("erreur d'initialisation : reset sht OFF \n");// affichage sur la console d'un code d'erreur en case de défaut
		}
	if(gpioSetMode(23,PI_INPUT) !=0)	//input du sensor si il nous envoie un "1" on active la pompe
		{
			printf("erreur d'initialisation : Control Allumage OFF \n");// affichage sur la console d'un code d'erreur en case de défaut
		}
	
	// Essai pour verifier le bon fonctionnement
	gpioWrite(18,1); // on active le moteur
	sleep(1);
	gpioWrite(18,0); // on desactive le moteur
	if(gpioRead(23) !=1)
	{
		printf("Humidity in Soil not detected \n"); 	// <-- here you can change what s between the " but keep the \n it's usefull :)
	}
	else
	{
		printf("Humidity in Soil  detected \n");	// <-- here you can change what s between the " but keep the \n it's usefull :)
	}
}

void Launch_Pump(int secondes)
{
	// cette fonction fait tourner la pompe pendant X secondes. Cette variables X est le chiffre passé en paramètre dans la boucle main
	gpioWrite(18,1); //cette ligne permet de lancer la pompe
	sleep(secondes);
	gpioWrite(18,0); // cette ligne permet d'éteindre la pompe
}
//Debut du programme
int main(void)
{
	Initialisation();
	
	while(1) //on crée une boucle While(1) pour que le programme tourne a l'infini !
	{
		// A chaque boucle nous allons regarder si le capteur nous délivre un 0 ou un 1
		if(gpioRead(23) !=1)
		{
			Launch_Pump(30); 	// fonction que nous avons définis plus tot pour activer la pompe et donc permettre d'alimenter en eau la plante verte!
								// tu peux modifier le temps d'arrosage en modifiant la valeur a l'intérieur ( 30 = 30secondes 10= 10secondes etc etc ...)
		}	
		else
		{}
		sleep(1);// la fonction "sleep" nous sert ici a attendre 1 seconde. Ceci évite au code de tourner dans une boucle vide et utiliser toute la ressource processeur	
	
	}
}
