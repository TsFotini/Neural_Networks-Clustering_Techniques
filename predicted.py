import numpy as np
import pandas as pd
import sys
import csv
from keras.models import load_model
from sklearn.metrics import mean_absolute_error
from sklearn.metrics import mean_squared_error 
from keras import optimizers, losses, metrics

def mape_vectorized(a, b): 
    mask = a != 0
    return (np.fabs(a - b)/a)[mask].mean()

def mape_(mape):
    sum = 0
    for i in mape:
        sum = sum + i
    sum = sum / 7 * 100
    return sum

def write_to_file(result,temp):
    for i in range(len(result)):
        f.write(str(temp[i]))
        f.write(" ")
        count = 0
        for x in result[i]:
            data = x
            f.write(str(data))
            f.write(" |")
            count = count + 1
            f.write(str(count))
            f.write(" ")
        f.write("\n")

def write_to_file_csv(temp,result):
    lst = []
    for i in range(len(temp)):
        lst_inside = []
        lst_inside.append(str(temp[i]))
        for j in range(len(result[i])):
            lst_inside.append(str(result[i][j]))
        lst.append(lst_inside)
    with open('predict.csv', 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(lst)

csv_file = sys.argv[2]
data = pd.read_csv(csv_file) 
temp = data 
data = data.drop(data.columns[0],axis=1)
temp = temp.iloc[:, 0]
temp = temp.values
data2 = pd.read_csv("actual.csv") 
data2 = data2.drop(data2.columns[0],axis=1)
model = load_model('WindDenseNN.h5',compile=True)
model.compile(optimizer=optimizers.RMSprop(0.01),loss=losses.CategoricalCrossentropy(),metrics=[metrics.CategoricalAccuracy()])
result = model.predict(data, batch_size=32)
print(result.shape)
mape = mape_vectorized(data2, result)
mape = mape.to_numpy()
mape = mape_(mape)
print(mape)
mae = mean_absolute_error(data2, result)
print(mae)
mse = mean_squared_error(data2,result)
print(mse)
f= open("predicted.csv","w+")
f.write("MAE: %f" % mae )
f.write(" MAPE: %f" %mape)
f.write( " MSE: %f" %mse)
f.write("\n")
write_to_file(result,temp)
f.close()
write_to_file_csv(temp,result)