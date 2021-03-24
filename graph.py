import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt

df = pd.read_csv("dataM5.csv")
df=df.dropna()
#print(df.head())
fig,ax=plt.subplots()
ax.plot(df["Frame"], df["QueueDensity"],label="Queue")
ax.set_xlabel("Frame Number")
ax.set_ylabel("Density")
ax.plot(df["Frame"], df["DynamicDensity"],label="Dynamic")
ax.legend(loc='upper left', bbox_to_anchor=(0.0, 1.00), shadow=True, ncol=1)
plt.show()
