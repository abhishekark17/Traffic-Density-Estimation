import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import csv
import math

df_base = pd.read_csv("data.csv")
# df_M1=pd.read_csv("dataM1.csv")

# df_base_M1=pd.merge(df_base, df_M1, how ='inner', on ='Frame')

def main(methodNum):
    filename="dataM"+str(methodNum)+".csv"
    df=pd.read_csv(filename)
    df_base_M = pd.merge(df_base,df,how="inner", on="Frame")
    rms_base_q = math.sqrt((np.sum(df_base_M["QueueDensity_x"]**2)/len(df_base_M["Frame"])))
    rms_base_d = math.sqrt((np.sum(df_base_M["DynamicDensity_x"]**2)/len(df_base_M["Frame"])))
    rms_q = math.sqrt(np.sum((df_base_M["QueueDensity_x"]-df_base_M["QueueDensity_y"])**2)/len(df_base_M["Frame"]))
    rms_d = math.sqrt(np.sum((df_base_M["DynamicDensity_x"]-df_base_M["DynamicDensity_y"])**2)/len(df_base_M["Frame"]))
    return (rms_q/rms_base_q,rms_d/rms_base_d)

error_queue=[]
error_dynamic=[]
for i in range(1,6):
    error_q,error_d=main(i)
    error_queue.append(error_q)
    error_dynamic.append(error_d)
time=np.random.rand(5)
marker_q=['$1q$','$2q$','$3q$','$4q$','$5q$']
marker_d=['$1D$','$2D$','$3D$','$4D$','$5D$']

fig,ax=plt.subplots()
ax.scatter(error_queue,time,marker="$Q$",label="Queue")
ax.set_xlabel("Time")
ax.set_ylabel("Error")
ax.scatter(error_dynamic,time ,marker="$D$",label="Dynamic")
ax.legend(loc='upper left', bbox_to_anchor=(0.0, 1.00), shadow=True, ncol=1)
plt.show()


# filename="diff.csv"
# with open(filename,'w') as csvfile:
#     csvwriter=csv.writer(csvfile)
#     csvwriter.writerow(["Frame","Queue_base_M1","Dynamic_base_M1"])
#     for i in range(len(df_final["Frame"])):
#         queue_diff=abs(df_final["QueueDensity_x"][i]-df_final["QueueDensity_y"][i])
#         dynamic_diff=abs(df_final["DynamicDensity_x"][i]-df_final["DynamicDensity_y"][i])
#         csvwriter.writerow([df_final["Frame"][i],queue_diff,dynamic_diff])
