# -*- coding: utf-8 -*-
import xlwings as xw
# 读取result.txt中的计算结果
def loadDatadet(infile,k):
    f=open(infile,'r')
    sourceInLine=f.readlines()
    dataset=[]
    for line in sourceInLine:
        temp1=line.strip('\n')
        temp2=temp1.split('\t')
        dataset.append(temp2)
    for i in range(0,len(dataset)):
        for j in range(k):
            dataset[i].append(float(dataset[i][j]))
        del(dataset[i][0:k])
    return dataset
infile='result.txt'
k=6
infile=loadDatadet(infile,k)

app = xw.App(visible= True,add_book = False)
wb = xw.Book('chart.xlsx')
sht = wb.sheets[0]
# 调整单元格格式
sht.range('a1').column_width = 45
sht.range('b1:i1').column_width = 13
sht.range('a1').value = "数据汇总"

# 输入数据
sht.range('a2').options(transpose=True).value = ['堆芯出口温度为 °C','燃料棒表面平均热流密度 W/m2','燃料棒表面最大热流密度 W/m2','燃料棒平均线功率为 W/m','燃料棒最大线功率为 W/m','平均管流速 m/s','单元通道内流量 kg/s','单元通道面积 m^2']
sht.range('a12').options(transpose=True).value = [' ','控制体出口流温度 °C','控制体出口处的包壳外壁温 °C','控制体出口处的包壳内壁温均线功率为 °C','控制体出口处的UO2芯快外表面温度 °C','控制体出口处的UO2芯快内表面温度 °C','热管中的q_DNB_h x10^6  w/m^2 x10^6','DNBR']
sht.range('a22').options(transpose=True).value = [' ','单相流体摩擦压降 Pa','单相流体加速压降 Pa','单相流体提升压降 Pa','堆芯进口局部压降 Pa','堆芯出口局部压降 Pa','定位格架出口压降 Pa','总的压降 Pa']
n = 0
l = [1,2,3,4,5,6]
sht.range('b12').value = l

lis = ['b','c','d','e','f','g']

for i in range(2,10):
    sht.range('{}{}'.format('b',i)).value = infile[i-2][0]

for i in range(0,6):
    for j in range(13,20):
        sht.range('{}{}'.format(lis[i],j)).value = infile[8+n][0]
        n = n+1

for i in range(23,30):
    sht.range('{}{}'.format('b',i)).value = infile[49 + i -23][0]