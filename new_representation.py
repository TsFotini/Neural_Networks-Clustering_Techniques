import csv
import numpy as np
import pandas as pd
import sys
import keras
from keras.models import load_model
from keras import layers, optimizers, losses, metrics

def write_to_file_csv(temp,result):
    lst = []
    for i in range(len(temp)):
        lst_inside = []
        lst_inside.append(str(temp[i]))
        for j in range(len(result[i])):
            lst_inside.append(str(result[i][j]))
        lst.append(lst_inside)
    with open('new_representations.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(lst)
    
            
csv_file = sys.argv[2]
data = pd.read_csv(csv_file)
temp = data
data = data.drop(data.columns[0],axis=1)  
temp = temp.iloc[:, 0]
temp = temp.values
model = load_model('WindDenseNN.h5',compile=True)
model.compile(optimizer=optimizers.RMSprop(0.01),loss=losses.CategoricalCrossentropy(),metrics=[metrics.CategoricalAccuracy()])
new_model = keras.Sequential()
new_model.add(model.layers[0])
result = new_model.predict(data, batch_size=32)
print(result.shape)
print(result[7][9])
print(temp.shape)
write_to_file_csv(temp,result)
