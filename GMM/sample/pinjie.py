# _*_ coding=utf-8 _*_
__date__ = '11/14/2018 14:10'

from pydub import AudioSegment
from pydub.silence import split_on_silence
import  random

if __name__ =="__main__":
    #要拼接的文件如下
    filesNameList=['A对话.wav','B对话.wav', 'C对话.wav', 'D对话.wav']

    #添加1s的空白
    jointOfList=None
    audiosegmentList=[]
    for fileName in filesNameList:
        oneWave=AudioSegment.from_wav(fileName)
        audiosegmentList.append(oneWave)
    #8段语音大概两分钟
    for a in [1, 2]:
        sequenceList=[]
        i=0
        while i<4:
            tmp=random.randint(0,3)
            if tmp not in sequenceList:
                sequenceList.append(tmp)
                i+=1
        for ind in sequenceList:
            oneWave=audiosegmentList[ind]
            slientPart=AudioSegment.silent(duration=1500)
            oneWave=oneWave+slientPart
            if jointOfList==None:
                jointOfList=oneWave
                continue
            jointOfList=jointOfList+oneWave

        #chunks = split_on_silence(oneWave,
        #    # must be silent for at least 2 seconds or 2000 ms
        #    min_silence_len=2000,
        #    # consider it silent if quieter than -16 dBFS
        #    #Adjust this per requirement
        #    silence_thresh=-19
        #)
    jointOfList.export( "dialog.wav", format="wav")

