#!/bin/zsh

#为对jni支持不好的android studio生成.h文件
#android studio 项目目录结构：
#<projectname>/app/src/main/java
#这个脚本要放到/app/src/main/java目录里。

if ! pwd | grep 'app/src/main/java'
then
  echo 这个脚本要放到/app/src/main/java目录里。
  exit 1
fi

#javah -cp $$CLASSPATH:Jpcap.jar -jni $(JSRC:.java=)
#javah  cool.couplet.study3.AdevHi
#javac -Xlint:unchecked -cp Jpcap.jar $<
#javah  cool.couplet.store.FenX
javah  cool.couplet.rtmvv.Aefh
mkdir -p ../jni
mv *.h ../jni

javac cool/couplet/rtmvv/Aefh.java

javap -s cool.couplet.rtmvv.Dirent
javap -s cool.couplet.rtmvv.DTType
#javap -v -p -c cool.couplet.rtmvv.DTType
find . -name "*.class" -exec rm -f {} \;
exit 0