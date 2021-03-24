import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import csv
import math

df_base = pd.read_csv("data.csv")
df_M1=pd.read_csv("dataM1.csv")
#df_M3=pad.read_csv("dataM3.csv")
#df_M4=pad.read_csv("dataM4.csv")
#df_M5=pad.read_csv("dataM5.csv")

df_final=pd.merge(df_base, df_M1, how ='inner', on ='Frame')

filename="diff.csv"
with open(filename,'w') as csvfile:
    csvwriter=csv.writer(csvfile)
    csvwriter.writerow(["Frame","Queue_base_M1","Dynamic_base_M1"])
    for i in range(len(df_final["Frame"])):
        queue_diff=abs(df_final["QueueDensity_x"][i]-df_final["QueueDensity_y"][i])
        dynamic_diff=abs(df_final["DynamicDensity_x"][i]-df_final["DynamicDensity_y"][i])
        csvwriter.writerow([df_final["Frame"][i],queue_diff,dynamic_diff])

