import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math
import argparse

Normal_time=395
df_base = pd.read_csv("../data/data.csv")
time=[Normal_time]
df_time=pd.read_csv("../data/time.csv")

# This function collect all the data from all the threads of M4 and computes the total
# def data4(numOfThreads):
#     df1=pd.read_csv("../data/data4/dataM4N"+str(numOfThreads)+"T1.csv")
#     filename="../data/dataM4.csv"
#     df=df1.copy()
#     for i in range(2,numOfThreads+1):
#         df_tobe_added=pd.read_csv("../data/data4/dataM4N"+str(numOfThreads)+"T"+str(i)+".csv")
#         df["QueueDensity"]+=df_tobe_added["QueueDensity"]
#         df["DynamicDensity"]+=df_tobe_added["DynamicDensity"]
#     df.to_csv(filename,index=False)
        
# def data5(numOfThreads):
#     df1=pd.read_csv("../data/data5/dataM5N"+str(numOfThreads)+"T1.csv")
#     filename="../data/dataM5.csv"
#     df=df1.copy()
#     for i in range(2,numOfThreads+1):
#         df_to_concatenate=pd.read_csv("../data/data5/dataM5N"+str(numOfThreads)+"T"+ str(i)+".csv")
#         df=pd.concat([df,df_to_concatenate])
#     df.to_csv(filename,index=False)

# # This function calculates rms diff between base data and any method data
def method2():
    filename="../data/dataM2.csv"
    df=pd.read_csv(filename)
    df_base_M = pd.merge(df_base,df,how="inner", on="Frame")
    rms_base_q = math.sqrt((np.sum(df_base_M["QueueDensity_x"]**2)/len(df_base_M["Frame"])))
    rms_base_d = math.sqrt((np.sum(df_base_M["DynamicDensity_x"]**2)/len(df_base_M["Frame"])))
    rms_q = math.sqrt(np.sum((df_base_M["QueueDensity_x"]-df_base_M["QueueDensity_y"])**2)/len(df_base_M["Frame"]))
    rms_d = math.sqrt(np.sum((df_base_M["DynamicDensity_x"]-df_base_M["DynamicDensity_y"])**2)/len(df_base_M["Frame"]))
    return (rms_q/rms_base_q,rms_d/rms_base_d)

# # This function returns root mean square diff of two data. Arguments are strings like ("dataM1.csv" , "dataM2.csv")
# # def comparing_two_data(data1,data2):
# #     filename1="../data/"+data1
# #     filename2="../data/"+data2
# #     df1=pd.read_csv(filename1)
# #     df2=pd.read_csv(filename2)
# #     df = pd.merge(df1,df2,how="inner", on="Frame")
# #     rms_1_q = math.sqrt((np.sum(df["QueueDensity_x"]**2)/len(df["Frame"])))
# #     rms_1_d = math.sqrt((np.sum(df["DynamicDensity_x"]**2)/len(df["Frame"])))
# #     rms_q = math.sqrt(np.sum((df["QueueDensity_x"]-df["QueueDensity_y"])**2)/len(df["Frame"]))
# #     rms_d = math.sqrt(np.sum((df["DynamicDensity_x"]-df["DynamicDensity_y"])**2)/len(df["Frame"]))
# #     return (rms_q/rms_1_q,rms_d/rms_1_d)



def graph_preprocess():
    error_queue=[0]
    error_dynamic=[0]
    marker_q=["QNormal"]
    marker_d=["DNormal"]
    textfile=open("final_error.txt","r")
    for line in textfile.readlines():
        if line!="":
            s1,s2,s3,s4=map(str,line.split())
            error_queue.append(float(s2))
            error_dynamic.append(float(s3))
            time.append(float(s4))
            marker_q.append("QM"+s1[-1])
            marker_d.append("DM"+s1[-1])
    for i in range(len(df_time["method"])):
        x=df_time["method"][i]
        t=df_time["time"][i]
        if x=="dataM2":
            a,b=method2()
            error_queue.append(a)
            error_dynamic.append(b)
            time.append(t)
            marker_q.append("QM2")
            marker_d.append("DM2")
    
    return (error_queue,error_dynamic,marker_q,marker_d)


# This function draws the trade_off_graph (1 for queue_error, 2 for dynamic_error, 3 for both on same graph)
def trade_off_graph(type_of_graph):
    error_queue,error_dynamic,marker_q,marker_d=graph_preprocess()

    fig,ax=plt.subplots()
    if type_of_graph=="queue": # only queue error
        ax.scatter(error_queue,time)
        fig.suptitle("Queue Density Error")
        ax.set_xlabel("Error")
        ax.set_ylabel("Time")
        # plt.xlim(0,max(error_queue)*1.2)
        # ax.annotate("Normal Time = "+str(Normal_time),(min(error_queue)*1.2,Normal_time))
        for i in range(len(marker_q)):
            ax.annotate(marker_q[i][1:],(error_queue[i],time[i]))
    elif type_of_graph=="dynamic": # only dynamic density
        ax.scatter(error_dynamic,time)
        fig.suptitle("Dynamic Density Error")
        ax.set_xlabel("Error")
        ax.set_ylabel("Time")
        # plt.xlim(0,max(error_dynamic)*1.2)
        # ax.annotate("Normal Time = "+str(Normal_time),(min(error_dynamic)*1.2,Normal_time))
        for i in range(len(marker_d)):
            ax.annotate(marker_d[i][1:],(error_dynamic[i],time[i]))
    else: # Both values in one graph (not recommended)
        ax.scatter(error_queue,time)
        fig.suptitle("Both Queue and Dynamic Density Error")
        ax.set_xlabel("Error")
        ax.set_ylabel("Time")
        # plt.xlim(0,max(error_dynamic)*1.2)
        # ax.annotate("Normal Time = "+str(Normal_time),(min(error_dynamic)*1.2,Normal_time))
        for i in range(len(marker_q)):
            ax.annotate(marker_q[i],(error_queue[i],time[i]))
        
        ax.scatter(error_dynamic,time)
        for i in range(len(marker_d)):
            ax.annotate(marker_d[i],(error_dynamic[i],time[i]))
    #ax.legend(loc='upper left', bbox_to_anchor=(0.0, 1.00), shadow=True, ncol=1)
    #plt.ylim(0,Normal_time+50)
    plt.savefig("../graphs/"+"tradeoff_"+type_of_graph+".png")
    plt.show()


if __name__=='__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument("--type",help="Give queue for queue_error, dynamic for dynamic_error or both for both errors. (By default assume dynamic)")
    opt=parser.parse_args()
    type_of_graph="queue"
    if(opt.type!=None):
        type_of_graph=str(opt.type)
    trade_off_graph(type_of_graph)