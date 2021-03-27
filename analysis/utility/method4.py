import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math
import argparse


def method4(numOfThreads):
    df1=pd.read_csv("../data/data4/dataM4N"+str(numOfThreads)+"T1.csv")
    filename="../data/data4/dataM4N"+str(numOfThreads)+".csv"
    df=df1.copy()
    for i in range(2,numOfThreads+1):
        df_tobe_added=pd.read_csv("../data/data4/dataM4N"+str(numOfThreads)+"T"+str(i)+".csv")
        df["QueueDensity"]+=df_tobe_added["QueueDensity"]
        df["DynamicDensity"]+=df_tobe_added["DynamicDensity"]
    df.to_csv(filename,index=False)


if __name__=='__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument("--n",help="Number Of Threads used in method 4")
    opt=parser.parse_args()
    numOfThreads=4
    if opt.n is not None:
        numOfThreads=int(opt.n)
    method4(numOfThreads)
