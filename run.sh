SPARK_HOME=~/download/spark-2.4.0-bin-hadoop2.7/bin
WORK_HOME=~/workspace
INPUT=data128M.csv

$SPARK_HOME/spark-submit \
    --master local[*] \
    --class DataToHex \
    --driver-class-path $WORK_HOME"/*.jar" \
    --files libData2Hex.so \
    --conf spark.driver.extraJavaOptions='-Djava.library.path='$WORK_HOME' -Dcom.sun.management.jmxremote.port=7091 -Dcom.sun.management.jmxremote.authenticate=false -Dcom.sun.management.jmxremote.ssl=false -XX:+UnlockCommercialFeatures -XX:+FlightRecorder -XX:FlightRecorderOptions=defaultrecording=true,dumponexit=true,dumponexitpath='$WORK_HOME'/log,stackdepth=2048' \  # enable Java Flight Recorder
    --conf spark.executor.extraJavaOptions='-Djava.library.path='$WORK_HOME' -Dcom.sun.management.jmxremote.port=7092 -Dcom.sun.management.jmxremote.authenticate=false -Dcom.sun.management.jmxremote.ssl=false -XX:+UnlockCommercialFeatures -XX:+FlightRecorder -XX:FlightRecorderOptions=defaultrecording=true,dumponexit=true,dumponexitpath='$WORK_HOME'/log,stackdepth=2048' \ # enable Java Flight Recorder
    DataToHex-0.1.jar $INPUT
