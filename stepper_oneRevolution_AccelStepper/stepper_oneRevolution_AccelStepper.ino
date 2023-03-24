#include <AccelStepper.h>

// Définir la constante de pas
#define MotorInterfaceType AccelStepper::FULL4WIRE

// Crée une instance
// Broches saisies dans la séquence IN1-IN3-IN2-IN4 pour une séquence de pas appropriée
AccelStepper myStepper(MotorInterfaceType, 8, 10, 9, 11);

void setup() {
// Définir la vitesse maximale, le facteur d'accélération,
// la vitesse initiale et la position cible
	myStepper.setMaxSpeed(2038.0);
	myStepper.setAcceleration(200.0);
	myStepper.setSpeed(200);
	myStepper.moveTo(2038);
}

void loop() {
	// Changer de direction une fois que le moteur atteint la position cible
	if (myStepper.distanceToGo() == 0) {
		myStepper.moveTo(-myStepper.currentPosition());
    // Question : Selon vous pourquoi est-ce que le moteur fait 2 révolutions?
    // Indice : Position de démarrage --> But --> -But
  }

	// Faire tourner le moteur d'un pas
  // Il faut appeler cette fonction dans le loop sinon le moteur ne tourne pas
	myStepper.run();
}