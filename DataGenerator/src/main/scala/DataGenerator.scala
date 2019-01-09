import java.io.{File, PrintWriter}

import scala.util.Random

object DataGenerator {

  def main(args: Array[String]) : Unit = {
    val writer = new PrintWriter(new File(args(0)))
    val builder = new StringBuilder();
    var count = 0;
    val times = args(1).toInt
    for( i <- 1 to times) {

      builder.append(Random.alphanumeric.filter(_.isLetter).take(10).mkString)
      builder.append(",")
      builder.append(Random.nextLong())
      builder.append(",")
      builder.append(Random.alphanumeric.filter(_.isLetter).take(10).mkString)
      builder.append("\r\n")
      count += 1

      if(count == 10000) {
        count = 0
        writer.write(builder.toString)
        builder.clear()
      }

    }
    writer.close()
  }

}
