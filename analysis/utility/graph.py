import numpy as np 
import pandas as pd 
import matplotlib.pyplot as plt
import argparse

def graph(data):
    df = pd.read_csv("../data/"+data+".csv")
    df=df.dropna()
    #print(df.head())
    fig,ax=plt.subplots()
    ax.plot(df["Frame"], df["QueueDensity"],label="Queue")
    ax.set_xlabel("Frame Number")
    ax.set_ylabel("Density")
    ax.plot(df["Frame"], df["DynamicDensity"],label="Dynamic")
    ax.legend(loc='upper left', bbox_to_anchor=(0.0, 1.00), shadow=True, ncol=1)
    fig.suptitle(data)
    plt.savefig("../graphs/"+data+".png")
    #plt.show()

if __name__=='__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument("--file",help="Write the name of the file (only name without path or extension) for which you want the graph")
    opt=parser.parse_args()
    filename="data"
    if opt.file!=None:
        filename=str(opt.file)
    graph(filename)