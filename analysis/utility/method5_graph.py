import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math
import argparse

df_base = pd.read_csv("../data/data.csv")
time=[]
numOfThreads=[]
Normal_time=395
textfile=open("final_error.txt","a")
df_time=pd.read_csv("../data/time.csv")
for i in range(len(df_time["method"])):
    x=df_time["method"][i]
    t=df_time["time"][i]
    if(len(x)>5):
        if x[5]=="5":
            time.append(int(t))
            numOfThreads.append(x[7])

def main(numofthreads):
    filename="../data/data5/dataM5N"+str(numofthreads)+".csv"
    df=pd.read_csv(filename)
    df_base_M = pd.merge(df_base,df,how="inner", on="Frame")
    rms_base_q = math.sqrt((np.sum(df_base_M["QueueDensity_x"]**2)/len(df_base_M["Frame"])))
    rms_base_d = math.sqrt((np.sum(df_base_M["DynamicDensity_x"]**2)/len(df_base_M["Frame"])))
    rms_q = math.sqrt(np.sum((df_base_M["QueueDensity_x"]-df_base_M["QueueDensity_y"])**2)/len(df_base_M["Frame"]))
    rms_d = math.sqrt(np.sum((df_base_M["DynamicDensity_x"]-df_base_M["DynamicDensity_y"])**2)/len(df_base_M["Frame"]))
    return (rms_q/rms_base_q,rms_d/rms_base_d)

def graph_preprocess():
    error_queue=[]
    error_dynamic=[]
    for i in range(len(time)):
        error_q,error_d=main(numOfThreads[i])
        error_queue.append(error_q)
        error_dynamic.append(error_d)
    avg_error_q=sum(error_queue)/len(error_queue)
    avg_error_d=sum(error_dynamic)/len(error_dynamic)
    avg_time=sum(time)/len(time)
    textfile.write("method5 ")
    textfile.write(str(avg_error_q))
    textfile.write(" ")
    textfile.write(str(avg_error_d))
    textfile.write(" ")
    textfile.write(str(avg_time))
    textfile.write("\n")
    textfile.close()
    return(error_queue,error_dynamic)

def trade_off_graph(type_of_graph):
    error_queue,error_dynamic=graph_preprocess()
    marker_q=[]
    marker_d=[]

    for i in range(len(time)):
        marker_q.append("QN"+str(numOfThreads[i]))
        marker_d.append("DN"+str(numOfThreads[i]))

    fig,ax=plt.subplots()
    if type_of_graph=="queue": # only queue error
        ax.scatter(error_queue,time)
        fig.suptitle("Queue Density Error (Method 5)")
        ax.set_xlabel("Error")
        ax.set_ylabel("Time")
        #plt.xlim(0,max(error_queue)*1.2)
        #ax.annotate("Normal Time = "+str(Normal_time),(min(error_queue)*1.2,Normal_time))
        for i in range(len(marker_q)):
            ax.annotate(marker_q[i][1:],(error_queue[i],time[i]))
    elif type_of_graph=="dynamic": # only dynamic density
        ax.scatter(error_dynamic,time)
        fig.suptitle("Dynamic Density Error (Method 5)")
        ax.set_xlabel("Error")
        ax.set_ylabel("Time")
        #plt.xlim(0,max(error_dynamic)*1.2)
        #ax.annotate("Normal Time = "+str(Normal_time),(min(error_dynamic)*1.2,Normal_time))
        for i in range(len(marker_d)):
            ax.annotate(marker_d[i][1:],(error_dynamic[i],time[i]))
    else: # Both values in one graph (not recommended)
        ax.scatter(error_queue,time)
        fig.suptitle("Both Queue and Dynamic Density Error (Method 5)")
        ax.set_xlabel("Error")
        ax.set_ylabel("Time")
        #plt.xlim(0,max(error_dynamic)*1.2)
        #ax.annotate("Normal Time = "+str(Normal_time),(min(error_dynamic)*1.2,Normal_time))
        for i in range(len(marker_q)):
            ax.annotate(marker_q[i],(error_queue[i],time[i]))
        
        ax.scatter(error_dynamic,time)
        for i in range(len(marker_d)):
            ax.annotate(marker_d[i],(error_dynamic[i],time[i]))
    #ax.legend(loc='upper left', bbox_to_anchor=(0.0, 1.00), shadow=True, ncol=1)
    #plt.ylim(0,Normal_time+50)
    plt.savefig("../graphs/"+"method5_tradeoff_"+type_of_graph+".png")
    #plt.show()

if __name__=='__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument("--type",help="Give queue for queue_error, dynamic for dynamic_error or both for both errors. (By default assume dynamic)")
    opt=parser.parse_args()
    type_of_graph="queue"
    if(opt.type!=None):
        type_of_graph=str(opt.type)
    trade_off_graph(type_of_graph)