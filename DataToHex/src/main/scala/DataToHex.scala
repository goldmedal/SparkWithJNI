
import java.io.{File, PrintWriter}

import org.apache.spark.sql.SparkSession
import org.apache.spark.sql.types.{LongType, StringType, StructField, StructType}

class Data2Hex() {

  @native def data2Hex(d1: String, d2: Long, d3: String): String
  def doStuff(d1: String, d2: Long, d3: String): String = {
    data2Hex(d1, d2, d3)
  }

}

object DataToHex {

  val mySchema = StructType(Array(
    StructField("_c0", StringType, true),
    StructField("_c1", LongType, true),
    StructField("_c2", StringType, true)
  ))

  def main(args: Array[String]): Unit = {
    System.loadLibrary("Data2Hex")

    val spark = SparkSession
        .builder
        .appName("DataToHex")
        .getOrCreate()

    val df = spark.read.format("csv").option("header", "false").schema(mySchema).load(args(0))
    val result1 = df.rdd.repartition(10).mapPartitions( x => {
      System.loadLibrary("Data2Hex")
      val conv = new Data2Hex()
      x.map( data => conv.data2Hex(data(0).asInstanceOf[String], data(1).asInstanceOf[Long], data(2).asInstanceOf[String]))
    }).collect
    val writer = new PrintWriter(new File("/home/jax/workspace/result.txt"))
    var builder = new StringBuilder
    var count = 0

    result1.foreach(data => {
      builder.append(data)
      builder.append("\r\n")
      count += 1
      if(count == 1000) {
        writer.write(builder.toString())
        builder.clear()
        count = 0
      }
    })

    writer.close()

  }

}