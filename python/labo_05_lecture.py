"""_summary_
    Script pour lire les données de l'Arduino et les enregistrer dans un fichier CSV.
    Le script utilise le module 'serial' pour lire les données de l'Arduino via le port série.
    Les données sont ensuite enregistrées dans un fichier CSV avec un timestamp pour chaque ligne.
    Le script utilise le module 'argparse' pour gérer les arguments en ligne de commande.
    
    Faire 'Ctrl+C' pour arrêter le script.

    Args:
        -p, --port: Port de communication avec l'Arduino.
        -f, --frequency: Fréquence de sauvegarde dans le fichier CSV (en secondes).
        -b, --baudrate: Vitesse de transmission en bauds.
        -o, --output: Chemin du fichier de sortie en format CSV.
        
Returns:
    _type_: _description_
"""

import argparse
import serial
import csv
import time
from datetime import datetime


def handle_exit(sig, frame):
    print("\nInterruption détectée. Fermeture du port et du fichier.")
    ser.close()
    file.close()
    exit(0)

def read_serial_data(port, baudrate, output_file, frequency):
    global ser, file
    ser = None
    file = None
    try:
        ser = serial.Serial(port, baudrate, timeout=1)
        print(f"Connexion établie sur {port} à {baudrate} bauds.")
        time.sleep(2)  # Délai pour établir la connexion série
        
        with open(output_file, 'w', newline='') as file:
            writer = csv.writer(file)
            # Écrire l'en-tête du fichier CSV
            writer.writerow(["Timestamp", "Luminosité (%)", "Min (0-1023)", "Max (0-1023)", "Distance (cm)", "Température", "Humidité (%)"])
            print("Enregistrement des données... Appuyez sur 'Ctrl+C' pour arrêter.")
            start_time = time.time()
            
            while True:
                if ser.in_waiting > 0:
                    current_time = time.time()
                    if current_time - start_time >= frequency:
                        line = ser.readline().decode('utf-8').rstrip()
                        data = parse_data(line)
                        if data:
                            # Ajouter le timestamp actuel au début des données
                            data.insert(0, datetime.now().strftime('%Y-%m-%d %H:%M:%S'))
                            writer.writerow(data)
                            print(data)  # Affiche les données pour vérification
                            start_time = time.time()
                    
    except serial.SerialException as e:
        print(f"Erreur lors de la connexion au port série : {e}")
    except KeyboardInterrupt:
        print("Arrêt du script.")
    finally:
        ser.close()
        print(f"Les données ont été enregistrées dans {output_file}")

def parse_data(line):
    try:
        parts = line.split(',')
        data = [part.split(':')[1] for part in parts]
        return data
    except Exception as e:
        print(f"Erreur lors du parsing des données : {e}")
        return None

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Lire les données d'Arduino et les enregistrer dans un fichier CSV.")
    parser.add_argument("-o", "--output", type=str, help="Chemin du fichier de sortie en format CSV.")
    parser.add_argument("-p", "--port", required=True, type=str, help="Port de communication avec l'Arduino.")
    parser.add_argument("-f", "--frequency", type=float, default=1.0, help="Fréquence de sauvegarde dans le fichier CSV (en secondes).")
    parser.add_argument("-b", "--baudrate", type=int, default=9600, help="Vitesse de transmission en bauds.")

    args = parser.parse_args()
    
    if not args.port:
        parser.print_help()
    else:
        # Générer le nom du fichier de sortie basé sur le timestamp si non spécifié
        output_file = args.output if args.output else f"{datetime.now().strftime('%Y-%m-%d_%H-%M-%S')}.csv"

        # Appeler la fonction de lecture des données
        read_serial_data(port=args.port, baudrate=args.baudrate, output_file=output_file, frequency=args.frequency)
