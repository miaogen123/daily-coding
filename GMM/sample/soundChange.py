# _*_ coding=utf-8 _*_
#改变声音的音量
__date__ = '11/18/2018 15:02'
from pydub import AudioSegment

fileName="fangtan_part1.wav"
oneWave=AudioSegment.from_wav(fileName)
oneWave=oneWave.apply_gain(+10.5)
#oneWave+=20
oneWave.export("fangtan_part1.wav",format="wav")

