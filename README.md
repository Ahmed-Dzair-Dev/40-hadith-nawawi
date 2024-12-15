# 40-hadith-nawawi

اولا انسخ المشروع : 
git clone https://github.com/Ahmed-Dzair-Dev/40-hadith-nawawi.git


حمل المكتبات اللازمة لعملية البناء :

sudo apt-get install libgtk-3-dev

sudo apt-get install libjson-c-dev

حمل الخطوط :

sudo apt-get install fonts-noto-core

sudo apt install fonts-hosny-amiri

ثم :

fc-cache -f -v

و من أجل عملية البناء :

cd hadith-viewer

mkdir build

cd build

cmake ..

make

و بعد ذلك تنتظر و تظهر رسالة نجاح البناء :

[ 50%] Linking C executable hadith-viewer
[100%] Built target hadith-viewer

انسخ البرنامج و ضعه في ملف src و شغل البرنامج
