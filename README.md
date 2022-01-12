# myled_shinpei　
raspi3とブレッドボードを用いてledを発光させ、ユニークな表現をします(2021y ロボットシステム学課題１)

# 製作内容
・0,1,3,4の値をデバイスファイルに入力すると、3つのledが以下の通りに点灯する

 0=all off 　"すべてのledが消灯"

 1=all on　"すべてのledが点灯"

 3=wave   　"波のように順番に点灯"

 4=Brake lamp 5time Sign of love　"ledをブレーキランプのように五回点滅させ、dmesg上に「ア,イ,シ,テ,ル」の文字を表示させる"

 ※4の動作は有名な曲の歌詞にあるもので、ドライブデートをした後にブレーキランプで愛を伝えるという、カップルの間で昔に流行った行為です

# 実験器具
・Raspberry pi3 modelB+

・ブレッドボード

・led(黄)×3,抵抗200Ω×３

 ピンの割り当ては以下のとおりである
![S__4202498](https://user-images.githubusercontent.com/97512094/148928081-f8ed5f7a-3182-412f-9068-c2737d1d4c4d.jpg)
![D68F3A62-92DB-46A8-AF5C-536EB00DD630](https://user-images.githubusercontent.com/97512094/149068936-eb923208-2dee-45aa-b282-df5d7be5cbd6.jpg)

# 実験動画
https://youtu.be/pJsVPyUdBnE


# 実行方法

・プログラムの実行にはubuntuターミナルを用いて以下の手順を行ってください

・プログラム起動
```bash

git clone https://github.com/shinpei00kobayashi/myled_shinpei.git

cd myled_shinpei

make

sudo insmod myled.ko

sudo chmod 666 /dev/myled0
```

・all off　(消灯)
```bash
echo 0 > /dev/myled0
```

・all on　(全灯)
```bash
echo 1 > /dev/myled0
```

・weve　　(波)
```bash
echo 3 > /dev/myled0
```

・Brake lamp 5time Sign of love　(ブレーキランプ五回点滅アイシテルのサイン)
```bash
echo 4 > /dev/myled0
```
