

for i in range(0,6):
    for j in range(13,20):
        sht.range('{}{}'.format(lis[i],j)).value = infile[13+n][0]
        n = n+1
