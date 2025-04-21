# 40-hadith-nawawi

# لم اتحقق من صحة كل الأحاديث لا تنقل نقل العميان ! 

اولا انسخ المشروع : 

بنسبة ل Debian و Ubuntu :
```
git clone https://github.com/Ahmed-Dzair-Dev/40-hadith-nawawi.git
```
بنسبة ل Fedora :
```
git clone https://github.com/Ahmed-Dzair-Dev/40-hadith-nawawi.git
```

حمل المكتبات اللازمة لعملية البناء :

بنسبة ل Debian و Ubuntu :

```
sudo apt-get install libgtk-3-dev
```

```
sudo apt-get install libjson-c-dev
```
بنسبة ل Fedora :

```
sudo dnf install gtk3-devel
```

```
sudo dnf install json-c-devel
```
حمل الخطوط :

بنسبة ل Debian و Ubuntu :

```
sudo apt-get install fonts-noto-core
```

```
sudo apt install fonts-hosny-amiri
```
بنسبة ل Fedora :
```
sudo dnf install google-noto-fonts
```

```
sudo dnf install amiri-fonts
```


ثم :

```

fc-cache -f -v

```

ما قبل البناء :

بنسبة ل Debian و Ubuntu :
```
sudo apt install cmake
```

```
sudo apt install gcc
```
بنسبة ل Fedora :

```
sudo dnf install cmake
```

```
sudo dnf install gcc
```


و من أجل عملية البناء :
```

cd hadith-viewer

mkdir build

cd build

cmake ..

make

```

و بعد ذلك تنتظر و تظهر رسالة نجاح البناء :

[ 50%] Linking C executable hadith-viewer
[100%] Built target hadith-viewer

انسخ البرنامج و ضعه في ملف src و شغل البرنامج
