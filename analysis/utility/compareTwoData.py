import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math
import argparse


def comparing_two_data(data1,data2):
    filename1="../data/"+data1
    filename2="../data/"+data2
    df1=pd.read_csv(filename1)
    df2=pd.read_csv(filename2)
    df = pd.merge(df1,df2,how="inner", on="Frame")
    rms_1_q = math.sqrt((np.sum(df["QueueDensity_x"]**2)/len(df["Frame"])))
    rms_1_d = math.sqrt((np.sum(df["DynamicDensity_x"]**2)/len(df["Frame"])))
    rms_q = math.sqrt(np.sum((df["QueueDensity_x"]-df["QueueDensity_y"])**2)/len(df["Frame"]))
    rms_d = math.sqrt(np.sum((df["DynamicDensity_x"]-df["DynamicDensity_y"])**2)/len(df["Frame"]))
    print("RMS QueueDensity Error:")
    print(rms_q/rms_1_q)
    print("RMS DynamicDensity Error:")
    print(rms_d/rms_1_d)

if __name__=='__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument("--data1",help="first Data which is considered as base for comparison")
    parser.add_argument("--data2",help="Second Data which is to be compared")
    opt=parser.parse_args()
    data1="../data/data.csv"
    data2="../data/dataM1.csv"
    if opt.data1 is not None:
        data1=str(opt.data1)
    if opt.data2 is not None:
        data2=str(opt.data2)
    comparing_two_data(data1,data2)