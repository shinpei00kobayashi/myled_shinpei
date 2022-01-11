# myled_shinpei　2021robosys
raspi3とブレッドボードを用いてledを発光させ、ユニークな表現をします

# 製作内容
・0～3の値をデバイスファイルに入力すると、3つのledが以下の通りに点灯する

0=all off 　"すべてのledが消灯"

1=all on　"すべてのledが点灯"

2=wave   　"波のように順番に点灯"

3=Brake lamp 5time Sign of love　"ledをブレーキランプのように五回点滅させ、dmesg上に「ア,イ,シ,テ,ル」の文字を表示させる"

※4の動作は有名な曲の歌詞にあるもので、ドライブデートをした後にブレーキランプで愛を伝えるという、カップルの間で昔に流行った行為

# 実験器具
・Raspberry pi3 modelB+

・ブレッドボード

・led(黄)×3,抵抗200Ω×３

ピンの割り当ては以下のとおりである
![S__4202498](https://user-images.githubusercontent.com/97512094/148928081-f8ed5f7a-3182-412f-9068-c2737d1d4c4d.jpg)
![EF8AFF13-6BC6-4C11-8036-9CC0B0D20851](https://user-images.githubusercontent.com/97512094/148929031-1c8dc758-c728-4a38-815a-cc81d3c17702.jpg)

# 実験動画
https://youtu.be/pJsVPyUdBnE


# 実行方法

・プログラム起動
```bash

git clone https://github.com/shinpei00kobayashi/myled_shinpei.git

cd myled_shinpei

make

sudo insmod myled.ko

sudo chmod 666 /dev/myled0
```

・all off
```bash
echo 0 > /dev/myled0
```

・all on
```bash
echo 1 > /dev/myled0
```

・weve
```bash
echo 2 > /dev/myled0
```

・Brake lamp 5time Sign of love
```bash
echo 3 > /dev/myled0
```
