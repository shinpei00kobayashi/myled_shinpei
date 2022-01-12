# myled_shinpei　
raspi3とブレッドボードを用いてledを発光させ、ユニークな表現をします(2021y ロボットシステム学課題１)

# 製作内容
 0~4の値をデバイスファイルに入力すると、3つのledが以下の通りに点灯する

 0=all off 　　　  "すべてのledが消灯"

 1=all on　        "すべてのledが点灯"

 2=crouch start    "1秒ずつカウントを刻みLEDが順番に点灯する"

 3=wave   　       "波のように順番に点灯"

 4=Brake lamp 5time Sign of love　"ledをブレーキランプのように五回点滅させ、dmesg上に「ア,イ,シ,テ,ル」の文字を表示させる"

 ※4の動作は有名な曲の歌詞にあるもので、ドライブデートをした後にブレーキランプで愛を伝えるという、カップルの間で昔に流行った行為です

# 実験器具
・Raspberry pi3 modelB+

・ブレッドボード

・led(黄)×3,抵抗200Ω×３

 配線方法は以下のとおりである
![S__4202498](https://user-images.githubusercontent.com/97512094/148928081-f8ed5f7a-3182-412f-9068-c2737d1d4c4d.jpg)
![D68F3A62-92DB-46A8-AF5C-536EB00DD630](https://user-images.githubusercontent.com/97512094/149068936-eb923208-2dee-45aa-b282-df5d7be5cbd6.jpg)

# 実験動画
https://youtu.be/PcRT9q9oGfs


# 実行方法

・プログラムの実行にはubuntuターミナルを用いて以下の手順を行ってください

・プログラム起動
```bash
git clone https://github.com/shinpei00kobayashi/myled_shinpei.git
```

```bash
cd myled_shinpei
```

```bash
make
```

```bash
sudo insmod myled.ko
```

```bash
sudo chmod 666 /dev/myled0
```

・all off　(消灯)
```bash
echo 0 > /dev/myled0
```

```
if(c == '0'){ // all off
		gpio_base[10] = 1 << 25;
		gpio_base[10] = 1 << 15;
		gpio_base[10] = 1 << 10;
		}
  
/*! GPCLR0のgpio25,15,10に1を書き込みLEDを消灯させる*/

```


・all on　(全灯)
```bash
echo 1 > /dev/myled0
```
```
else if(c == '1'){ // all on
		gpio_base[7]  = 1 << 25;//gpiobase[7]=出力
		gpio_base[7]  = 1 << 15;
		gpio_base[7]  = 1 << 10;
		}
  
  /*! GPFSET0のgpio25,15,10に１を書き込みLEDを点灯させる*/
```


・crouch start
```bash
echo 2 > /dev/myled0
```

```
else if(c == '2'){ //crouch start

		t = 1;
		gpio_base[10] = 1 << 25;
		gpio_base[10] = 1 << 15;
		gpio_base[10] = 1 << 10;


		ssleep(t);
		gpio_base[7] = 1 << 25;
		
		ssleep(t);
		gpio_base[10]= 1 << 25;
		gpio_base[7] = 1 << 15;
		
		ssleep(t);
		gpio_base[10]= 1 << 15;
		gpio_base[7] = 1 << 10;
		
		ssleep(t);
		gpio_base[7] = 1 << 25;
		gpio_base[7] = 1 << 15;
		
		t = 3;
		ssleep(t);
		gpio_base[10]= 1 << 25;
		gpio_base[10]= 1 << 15;
		gpio_base[10]= 1 << 10;
		}
/*! ssleepで1秒間隔でLEDを順番に点灯させ、3秒後に全灯する*/

```




・wave　　(波)
```bash
echo 3 > /dev/myled0
```
```
else if(c == '3'){ //wave
		t = 200;
		gpio_base[10]= 1 << 25;
		gpio_base[10]= 1 << 15;
		gpio_base[10]= 1 << 10;

	for(i = 1; i <= 7; i++){
		
		gpio_base[7] = 1 << 25;
		msleep(t);
		gpio_base[10]= 1 << 25;
		gpio_base[7] = 1 << 15;
		msleep(t);
		gpio_base[10]= 1 << 15;
		gpio_base[7] = 1 << 10;
		msleep(t);
		gpio_base[10]= 1 << 10;
		gpio_base[7] = 1 << 15;
		msleep(t);
		gpio_base[10]= 1 << 15;
		gpio_base[7] = 1 << 25;
			
		}
		gpio_base[10]= 1 << 25;
		}
  
  /*! msleepで0.2秒間隔でLEDを順番に点灯させ、for文で1往復を七回する*/
  
  ```
・Brake lamp 5time Sign of love　(ブレーキランプ五回点滅アイシテルのサイン)
```bash
echo 4 > /dev/myled0
```

```
else if(c == '4'){ //ブレーキランプ５回愛してるのサイン
		
		t = 1;
		gpio_base[10]= 1 << 25;
		gpio_base[10]= 1 << 15;
		gpio_base[10]= 1 << 10;

	for(i = 1;i <= 5;i++){

		gpio_base[7]= 1 << 25;
		gpio_base[7]= 1 << 10;
 

		if(i == 1){
		printk(KERN_DEFAULT"ア\n");}
		else if(i == 2){
		printk(KERN_DEFAULT"イ\n");}
		else if(i == 3){
		printk(KERN_DEFAULT"シ\n");}
		else if(i == 4){
		printk(KERN_DEFAULT"テ\n");}
		else if(i == 5){
		printk(KERN_DEFAULT"ル\n");}

		ssleep(t);
		gpio_base[10]= 1 << 25;
		gpio_base[10]= 1 << 10;
		ssleep(t);
		}
	}
 
 /*! 両端のLEDをfor文で5回点滅させる。点滅するたびに指定の文字をprintkで出力*/
```
