import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math
import argparse

def method5(numOfThreads):
    df1=pd.read_csv("../data/data5/dataM5N"+str(numOfThreads)+"T1.csv")
    filename="../data/data5/dataM5N"+str(numOfThreads)+".csv"
    df=df1.copy()
    for i in range(2,numOfThreads+1):
        df_to_concatenate=pd.read_csv("../data/data5/dataM5N"+str(numOfThreads)+"T"+ str(i)+".csv")
        df=pd.concat([df,df_to_concatenate])
    df.to_csv(filename,index=False)

if __name__=='__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument("--n",help="Number Of Threads used in method 4")
    opt=parser.parse_args()
    numOfThreads=4
    if opt.n is not None:
        numOfThreads=int(opt.n)
    method5(numOfThreads)