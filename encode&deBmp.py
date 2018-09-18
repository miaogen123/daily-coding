# _*_ coding=utf-8 _*_
__date__ = '9/18/2018 9:13 '
#用来向bmp中隐写数据


import cv2
import numpy
from bitarray import  bitarray


def encodeTobmp(img,strin,n, bitbase=1):
    if img.ndim !=3:
        raise RuntimeError("图像维数不为3")
    hei, width, channel=img.shape
    #bitsSet=bytes(strin,  encoding="utf-8")
    bitsSet=bytes(strin,  encoding="gbk")
    if bitbase>8:
        raise RuntimeError("写入的数据位太长")
    if n>width*hei:
        raise RuntimeError("起点位置超过了bmp像素点的个数")
    row=int(n/width)
    col=n-row*width
    count=0
    maxCount=len(bitsSet)*8
    base=2**bitbase-1
    bitset=bitarray()
    bitset.fromstring(strin)
    print(bitset.tostring())
    while(row<hei):
        while(col<width):
            last=numpy.uint8(img[row, col][2])
            last=last>>bitbase<<bitbase
            tmp=bitset[count:count+bitbase]
            offset="".join(tmp.to01())
            try:
                last=last+int(offset, 2)
            except ValueError:
                print ("转换错误")
                last=0
            img[row, col]=[img[row, col][0], img[row][col][1], last]
            count+=bitbase
            if count>=maxCount:
                return img
            col+=1
        col=0
        row+=1
    return img

def decode(s):
    return ''.join([chr(i) for i in [int(b, 2) for b in s.split(' ')]])

def decodeFrombmp(img,n, num,bitbase=1):
    if img.ndim !=3:
        raise RuntimeError("图像维数不为3")
    hei, width, channel=img.shape
    if bitbase>8:
        raise RuntimeError("读取的数据位太长")
    if n>width*hei:
        raise RuntimeError("起点位置超过了bmp像素点的个数")
    row=int(n/width)
    col=n-row*width
    count=0
    maxCount=num*8
    base=2**bitbase-1
    ret=""
    while(row<hei):
        while(col<width):
            last=img[row, col][2]
            last=last&numpy.uint8(base)
            str_format='{0:0'+str(bitbase)+'b}'
            eh=str_format.format(last)
            strin=decode(eh)
            ret+=(strin)
            count+=bitbase
            if count>=maxCount:
                return ret
            col+=1
        col=0
        row+=1
    return ret



if __name__ == '__main__':
    #TODO::文件名
    fn=input("输入写入的bmp文件路径及文件名")
    img=cv2.imread(fn)
    img2=img.copy()
    hei, wid, channel=img2.shape
    n=input("输入你开始的地址, 应当在0-"+str(hei*wid)+"之间")
    try:
        n=int(n)
    except:
        n=1
    strin=str()
    strin=input("输入你想要的字符串")
    bitbase=input("输入你想在每个像素的最后n(0-8)位写入")
    try:
        bitbase=int(bitbase)
    except:
        bitbase=1

    encodeTobmp(img2,strin, n, 8)
    cv2.imwrite("output.bmp",img2 )
    print("解码中")
    ret=decodeFrombmp(img2,  n, len(strin), 8)
    print(ret)

