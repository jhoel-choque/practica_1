# -*- coding: utf-8 -*-
"""
Created on Fri Oct  2 17:49:29 2020

@author: Victor
"""
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import confusion_matrix
from collections import Counter

class KNN:
    def __init__(self, k=3):
        self.k = k
    
    def aprendizaje(self,X,C):
        self.X=X # matriz de vectores de caracteristicas
        self.c=C # clases asociadas a cada vector x(n)
        self.n_muestras=X.shape[0] # cantidad de muestras
    
    def clasificacion(self,Y):
        clases=[]
        for i in range(Y.shape[1]): # por cada vector y(n) a clasificar
            distancias=np.empty(self.n_muestras)
            for n in range(self.n_muestras): # por cada vector x(n) de caracteristicas
                distancias[n]=EUCLIDIANA(self.X[:,n],Y[:,i])
            
            # distancias mas cercanas
            k_distancias=np.argsort(distancias)
            # identificar las k distancias - clases
            k_etiqueta=self.c[k_distancias[:self.k]]
            print(k_etiqueta)
            # votacion
            c = Counter(k_etiqueta).most_common(1)#(5,0)
            clases.append(c[0][0]) # almacenamos la clase asignada al vector y(n)
        return clases
            

def EUCLIDIANA(x,y):
    return np.sqrt(np.sum((x-y)**2))

codigo_mapa = {'No Info':-1,'never':0,'former':1,'current':2,'not current':3,'ever':4}
data = pd.read_csv('diabetes_prediction_dataset.csv')
data['smoking_history_num']=data['smoking_history'].map(codigo_mapa)
data = data.drop('smoking_history',axis=1)
data = data.drop('gender',axis=1)
train_data, test_data = train_test_split(data, test_size=0.2, random_state=42)

X = train_data.drop('diabetes', axis=1).values
C = train_data['diabetes'].values
Y = test_data.drop('diabetes', axis=1).values

knn = KNN(k=3)
knn.aprendizaje(X, C)
clases_predichas = knn.clasificacion(Y)

#Metricas
cm = confusion_matrix(test_data['diabetes'],clases_predichas)#Es una tabla que muestra el número de verdaderos positivos, verdaderos negativos, falsos positivos y falsos negativos. 
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

resultado = pd.DataFrame({'Clase Real': test_data['diabetes'], 'Clase Predicha': clases_predichas})
resultado.to_csv('resultado.csv', index=False)
#print('clases de los puntos y(n): ',clases_predichas)
