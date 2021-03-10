import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt

df = pd.read_csv("data.csv")
df=df.dropna()
#print(df.head())
fig,ax=plt.subplots()
ax.plot(df["Frame"], df["QueueDensity"],label="QueueDensity")
ax.set_xlabel("Time (in seconds)")
ax.set_ylabel("Density")
ax.plot(df["Frame"], df["DynamicDensity"],label="DynamicDensity")
ax.legend(loc='upper left', bbox_to_anchor=(0.0, 1.00), shadow=True, ncol=1)
plt.show()
