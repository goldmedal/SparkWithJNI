# SparkWithJNI
Practice how to use Spark invoke a native function implemented by C.

# How to build and run

1. `sbt clean package`
2. move all class files to project home path.
3. generate header file.
```shell
LIBS_HOME=/usr/local/Cellar/scala/2.12.4/libexec/lib
CP=$LIBS_HOME/scala-library.jar

javah -cp $CP:. Sample1
```
4. copy `jni.h` and `jni_md.h` to `/usr/include`
    - `jni.h` in $JAVA_HOME/include
    - `jni_md.h` in $JAVA_HOME/include/linux
5. Set `$JAVA_HOME` and run compile script
```shell
sh compile.sh
```
6. move `DataToHex-0.1.jar` to project home path.
7. modifiy the param in `run.sh`
8. run `run.sh`

