import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from kd_tree import *

codigo_mapa = {'No Info':-1,'never':0,'former':1,'current':2,'not current':3,'ever':4}
codigo_mapa_2 = {'Male':1,'Female':0}
data = pd.read_csv('diabetes_prediction_dataset.csv')
data['smoking_history_num']=data['smoking_history'].map(codigo_mapa)
data['gender_num']=data['gender'].map(codigo_mapa_2)
data = data.drop('smoking_history',axis=1)
data = data.drop('gender',axis=1)
train_data, test_data = train_test_split(data, test_size=0.2, random_state=42)

X = train_data.drop('diabetes', axis=1).values.tolist()
C = train_data['diabetes'].values.tolist()
Y = test_data.drop('diabetes', axis=1).values.tolist()
D = test_data['diabetes'].values.tolist()

arbolknn = KDTreeClassifier(X,len(X[0]),C)

k = 5  # Número de vecinos más cercanos a considerar

predictions = []  # Lista para almacenar las predicciones

# Iterar a través de los puntos en Y y obtener las predicciones
for point in Y:
    clase_predicha = arbolknn.classify(point, k)
    predictions.append(clase_predicha)

resultado = pd.DataFrame({'Clase Real': D, 'Clase Predicha': predictions})
resultado.to_csv('resultado.csv', index=False)

#Metricas
cm = confusion_matrix(D,predictions)#Es una tabla que muestra el número de verdaderos positivos, verdaderos negativos, falsos positivos y falsos negativos. 
TN = cm[0][0]#Total verdaderos negativos
FP = cm[0][1]#Total falsos positivos
FN = cm[1][0]#Total falsos negativos
TP = cm[1][1]#Total verdaderos positivos
recall = TP / (TP + FN )#Mide la proporción de verdaderos positivos entre todos los casos positivos reales.
print("Recall= ",recall)
precision = TP / (TP + FP)#Mide la proporción de verdaderos positivos entre todas las predicciones positivas.
print("Precision=",precision)
specificity = TN / (TN +FP)#Mide la proporción de verdaderos negativos entre todos los casos negativos reales.
print("Specificity=",specificity)
accuracy = ( TP + TN ) / ( TP + TN + FP + FN) #Mide la proporción de predicciones correctas en relación con el total de prediccione
print("Accuracy =" , accuracy)
F1_Score = (2*precision * recall)/(precision + recall)
print("F1-Score =" , F1_Score)

