import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt

df = pd.read_csv("data.csv")
df=df.dropna()
#print(df.head())

plt.plot(df["Frame"], df["QueueDensity"])
plt.show()
