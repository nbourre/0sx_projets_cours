import pandas as pd
import matplotlib.pyplot as plt

chemin_fichier = 'D:\\temp\\eclipse\\ton_fichier.csv'
ignore_first_x_rows = 0 # Pour netttoyer les données
ignore_last_x_rows = 0 # Pour netttoyer les données
separator = ',' # ',' ou ';'
encoding = 'ISO-8859-1' # 'utf-8'

# Charger les données à partir du fichier CSV
# Pas d'accent dans le fichier CSV
#data = pd.read_csv(chemin_fichier)

# Avec accent dans le fichier CSV
data = pd.read_csv(chemin_fichier, encoding=encoding, sep=separator)

if ignore_first_x_rows > 0:
    data = data.iloc[ignore_first_x_rows:]

if ignore_last_x_rows > 0:
    data = data.iloc[:-ignore_last_x_rows]

# Convertir la colonne 'Timestamp' en format datetime
data['Timestamp'] = pd.to_datetime(data['Timestamp'])

# Créer le graphique
plt.figure(figsize=(10, 6))
plt.plot(data['Timestamp'], data['Luminosité (%)'])
plt.title('Luminosité au fil du temps')
plt.xlabel('Temps')
plt.ylabel('Luminosité (%)')
plt.grid(True)
plt.xticks(rotation=45)
plt.tight_layout()

# Afficher le graphique
plt.show()