import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt

df = pd.read_csv("diff.csv")
df=df.dropna()
#print(df.head())
fig,ax=plt.subplots()
ax.plot(df["Frame"], df["Queue_base_M1"],label="Queue")
ax.set_xlabel("Frame Number")
ax.set_ylabel("Density")
ax.plot(df["Frame"], df["Dynamic_base_M1"],label="Dynamic")
ax.legend(loc='upper left', bbox_to_anchor=(0.0, 1.00), shadow=True, ncol=1)
plt.show()
