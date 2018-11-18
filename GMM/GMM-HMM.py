# _*_ coding=utf-8 _*_

from scipy import signal
__date__ = '11/10/2018 9:12'

import pylab as pl
from sklearn.mixture import GaussianMixture
import os
import librosa
import numpy as np
import matplotlib.pyplot as plt
import wave
import time

from pydub import AudioSegment
from pydub.silence import split_on_silence

def match_target_amplitude(aChunk, target_dBFS):
    ''' Normalize given audio chunk '''
    change_in_dBFS = target_dBFS - aChunk.dBFS
    return aChunk.apply_gain(change_in_dBFS)

#对于语音信号除除静音
def excludeSilentReadWav(filename):
    song = AudioSegment.from_wav(filename)

    chunks = split_on_silence(song,
        # must be silent for at least 2 seconds or 2000 ms
        min_silence_len=1500,
        # consider it silent if quieter than -16 dBFS
        #Adjust this per requirement
        silence_thresh=-40
    )
    return chunks

    #Process each chunk per requirements and export
    #normalized_chunk=None
    #for i, chunk in enumerate(chunks):
    #    #chunk.export("chu{0}.wav".format(i), format="wav")
    #    if i==0:
    #        normalized_chunk=chunk
    #    else:
    #        normalized_chunk=normalized_chunk+chunk


def enframe(wave_data, nw, inc, winfunc):
    '''将音频信号转化为帧。
    参数含义：
    wave_data:原始音频型号
    nw:每一帧的长度(这里指采样点的长度，即采样频率乘以时间间隔)
    inc:相邻帧的间隔（同上定义）
    '''
    wlen=len(wave_data) #信号总长度
    if wlen<=nw: #若信号长度小于一个帧的长度，则帧数定义为1
        nf=1
    else: #否则，计算帧的总长度
        nf=int(np.ceil((1.0*wlen-nw+inc)/inc))
    pad_length=int((nf-1)*inc+nw) #所有帧加起来总的铺平后的长度
    zeros=np.zeros((pad_length-wlen,)) #不够的长度使用0填补，类似于FFT中的扩充数组操作
    pad_signal=np.concatenate((wave_data,zeros)) #填补后的信号记为pad_signal
    indices=np.tile(np.arange(0,nw),(nf,1))+np.tile(np.arange(0,nf*inc,inc),(nw,1)).T  #相当于对所有帧的时间点进行抽取，得到nf*nw长度的矩阵
    indices=np.array(indices,dtype=np.int32) #将indices转化为矩阵
    frames=pad_signal[indices] #得到帧信号
    win=np.tile(winfunc,(nf,1))  #window窗函数，这里默认取1
    return frames*win   #返回帧信号矩阵

def getWaveData(filename):
    fw = wave.open(filename,'rb')
    params = fw.getparams()
    #print(params)
    nchannels, sampwidth, framerate, nframes = params[:4]
    str_data = fw.readframes(nframes)
    wave_data = np.fromstring(str_data, dtype=np.int16)
    wave_data = wave_data * 1.0 / (max(abs(wave_data)))  # wave幅值归一化
    fw.close()
    return wave_data

def getGMM(filename):

    nw = 320  #对于16KHz的文件，20ms的采样点个数
    inc = 160
    wave_data=getWaveData(filename)
    winfunc = signal.hann(nw)
    X = enframe(wave_data, nw, inc, winfunc)
    frameNum = X.shape[0]  # 返回矩阵列数，获取帧数

    data=[]
    for oneframe in  X:
        tmpList=list()
        for a in librosa.feature.mfcc(y=oneframe, sr=16000, n_mfcc=24):
            tmpList.append(a[0])
        data.append(tmpList)
    data=np.array(data)


    gmm = GaussianMixture(7, covariance_type='full', random_state=0).fit(data)
    return gmm


if __name__=="__main__":
    start=time.clock()
    #生成训练过的模型
    names=['A', 'B', 'C', 'D' ]
    files=['./sample/A样本.wav', './sample/B样本_pre.wav', './sample/C样本.wav', './sample/D样本.wav']
    beTestFile="./sample/dialog.wav"
    #names=[ '易晟兵']
    #files=[ './sample/晟兵样本_pre.wav']
    GMMs=[]
    for file in files:
        GMMs.append(getGMM(file))
    timePointAfterGmm=time.clock()

    #对采样信号处理
    nw=320
    inc = 160
    winfunc = signal.hann(nw)
    fragmentListOfSample=excludeSilentReadWav(beTestFile)
    #fragmentListOfSample=excludeSilentReadWav("./sample/晟兵对话.wav")
    lenOffragment=len(fragmentListOfSample)
    for ind,fragment in enumerate(fragmentListOfSample):
        fragment.export("dialog{0}.wav".format(ind), format="wav", )
    for dialogNum in range(0,lenOffragment):
        testFrames=enframe(getWaveData("dialog{0}.wav".format(dialogNum)), nw, inc, winfunc)
        probilityList=[]
        sampleData=[]
        count=0
        sum_pro=0
        for oneframe in testFrames:
            tmpList=list()
            for a in librosa.feature.mfcc(y=oneframe, sr=16000 , n_mfcc=24):
                tmpList.append(a[0])
            sampleData.append(tmpList)
            count+=1
        maxPro=GMMs[0].score(sampleData)
        maxName= names[0]
        for index, GMM in enumerate(GMMs):
            probility=GMM.score(sampleData)
            print("dialog{0}.wav".format(dialogNum), "the score of model of {0}".format(names[index]), probility)
            if maxPro<probility:
                maxPro=probility
                maxName=names[index]
        print("the max probability :{0}, name :{1}".format(maxPro, maxName))
    end=time.clock()

    print("to train GMM model: ", timePointAfterGmm-start)
    print("total process: ", end-start, "seconds")
    #中间文件清理
    os.system("pause")
    for dialogNum in range(0, lenOffragment):
        fileName="dialog{0}.wav".format(dialogNum)
        try:
            os.remove(fileName)
        except :
            print("intermediate file delete faild : "+fileName)

