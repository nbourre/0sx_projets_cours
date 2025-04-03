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
        -g, --graph: Nombre des dernières valeurs à afficher sur le graphique.
        
Returns:
    _type_: _description_
"""

import argparse
import serial
import csv
import time
from datetime import datetime
import signal
import matplotlib.pyplot as plt
import numpy as np


# Fonction pour gérer la sortie propre du script
def handle_exit(sig, frame):
    print("\nInterruption détectée. Fermeture du port et du fichier.")
    if ser:
        ser.close()
    if file:
        file.close()
    plt.close('all')
    exit(0)
    
# Enregistrement du gestionnaire de signal pour une sortie propre
signal.signal(signal.SIGINT, handle_exit)

def read_serial_data(port, baudrate, output_file, frequency, last_values):
    global ser, file
    ser = None
    file = None
    try:
        ser = serial.Serial(port, baudrate, timeout=1)
        print(f"Connexion établie sur {port} à {baudrate} bauds.")
        time.sleep(2)  # Délai pour établir la connexion série
        
        # Préparation pour le graphique en direct
        plt.ion()
        fig, ax = plt.subplots(figsize=(10, 6))
        data_lines = [np.zeros(last_values) for _ in range(3)]  # 4 types de données restantes après retrait de valMin et valMax
        labels = ["Luminosité (%)", "Température", "Humidité (%)"]
        lines = [ax.plot(np.arange(-last_values, 0), line, label=label)[0] for line, label in zip(data_lines, labels)]
        ax.legend(loc="upper left")
        ax.set_ylim(0, 100)  # Adapter cette échelle selon vos données réelles

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
                        error_state, data = parse_data(line)
                        
                        if error_state == 1 and data:
                            # Ajouter le timestamp actuel au début des données
                            timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                            writer.writerow([timestamp] + data)
                            print([timestamp] + data)  # Affiche les données pour vérification
                            
                            start_time = time.time()
                            
                            # Mise à jour du graphique avec les 4 données
                            for i, line in enumerate(lines):
                                line.set_ydata(np.roll(line.get_ydata(), -1))
                                line.set_ydata(np.append(line.get_ydata()[:-1], data[i]))
                            plt.pause(0.001)
                        elif error_state == 0:
                            print(line)  # Afficher les commentaires
                        elif error_state == -1:
                            print("Données invalides. Veuillez vérifier le format.")
                            print(line)  # Afficher les données invalides
                    else:
                        ser.readline()  # Vider le buffer série
                    
    except serial.SerialException as e:
        print(f"Erreur lors de la connexion au port série : {e}")
    except KeyboardInterrupt:
        print("Arrêt du script.")
    finally:
        if ser:
            ser.close()
        else:
            print("Port série non disponible")
        print(f"Les données ont été enregistrées dans {output_file}")


def parse_data(line):
    """_summary_
    Cette fonction analyse une ligne de données de l'Arduino et renvoie un tuple (errorState, tableau de données)

    Args:
        line (_type_): _description_

    Returns:
        int: état d'erreur (-1 si erreur, 0 si commentaire, 1 si données valides)
        list: tableau de données       
        
    """
    try:
        # Si line débute par '//', c'est un commentaire et on ignore la ligne
        if line.startswith('//'):
            return 0, [0] * 4
        # Adapter ici pour ignorer valMin et valMax dans votre format de données
        parts = line.split(',')
        # Exemple: Lum:valLum,Dist:dist,T:temp,H:hum
        # Nous supposons ici l'ordre Lum, Dist, Temp, Hum pour correspondre à l'exemple
        valLum = float(parts[0].split(':')[1])
        temp = float(parts[4].split(':')[1])
        hum = float(parts[5].split(':')[1])
        return 1, [valLum, temp, hum]
    except Exception as e:
        print(f"Erreur lors du parsing des données : {e}")
        return -1, [0] * 4  # Retourner une liste de zéros si erreur

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Lire les données d'Arduino et les enregistrer dans un fichier CSV.")
    parser.add_argument("-o", "--output", type=str, help="Chemin du fichier de sortie en format CSV.")
    parser.add_argument("-p", "--port", required=True, type=str, help="Port de communication avec l'Arduino.")
    parser.add_argument("-f", "--frequency", type=float, default=1.0, help="Fréquence de sauvegarde dans le fichier CSV (en secondes).")
    parser.add_argument("-b", "--baudrate", type=int, default=9600, help="Vitesse de transmission en bauds.")
    parser.add_argument("-g", "--graph", type=int, default=10, help="Nombre des dernières valeurs à afficher sur le graphique.")


    args = parser.parse_args()
    
    if not args.port:
        parser.print_help()
    else:
        # Générer le nom du fichier de sortie basé sur le timestamp si non spécifié
        output_file = args.output if args.output else f"{datetime.now().strftime('%Y-%m-%d_%H-%M-%S')}.csv"

        # Appeler la fonction de lecture des données
        read_serial_data(port=args.port, baudrate=args.baudrate, output_file=output_file, frequency=args.frequency, last_values=args.graph)
