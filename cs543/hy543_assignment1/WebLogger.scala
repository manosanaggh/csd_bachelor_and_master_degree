//2.1
import scala.util.matching.Regex
import org.apache.spark.rdd.RDD

//2.2
val baseRdd = sc.textFile("/spare/csd3618/spark-3.0.2-bin-hadoop2.7/NASA_access_log_Jul95")

case class Log (host: String, date: String, requestURI: String, status: Int, bytes: Int)

def getImprovedLogFields(str: String): Log = {
	val str2 = str.replaceAll("\"([^GETHEADPOST])[^HTTPimoMI](.*)\"","\"GET 0\"")
	//val str3 = str2.replaceAll("alyssa.prodigy.com","!!!!!")
	//val str4 = str3.replaceAll("alyssa.p","f - - [10/Jul/1995:16:45:50 -0400] \"GET 0\" 400 0")
	//val str5 = str4.replaceAll("!!!!!","alyssa.prodigy.com")
	val str6 = str2.replaceAll("-0400","@0400")
	val str7 = str6.replaceAll(" -"," 0")
	val str8 = str7.replaceAll("@0400","-0400")
	val str9 = str8.replaceAll(" 0 0 \\["," - - \\[")
	
	val patternHost = """^([^\s]+\s)""".r
	val patternTime = """^.*\[(\d\d/\w{3}/\d{4}:\d{2}:\d{2}:\d{2} -\d{4})]""".r
	val patternRequest = """^.*"\w+\s+([^\s]+)\s*.*"""".r
	val patternStatus = """^.*"\s+([^\s]+)""".r
	val patternBytes = """^.*\s+(\d+)$""".r

	Log (patternHost.findAllIn(str9).matchData.next().group(1), patternTime.findAllIn(str9).matchData.next().group(1), patternRequest.findAllIn(str9).matchData.next().group(1),
  patternStatus.findAllIn(str9).matchData.next().group(1).toInt, patternBytes.findAllIn(str9).matchData.next().group(1).toInt)
}

def convertToLog(base: RDD[String]): RDD[Log] = {
	base.map(str => getImprovedLogFields(str))
}

val cleanRdd = convertToLog(baseRdd)
cleanRdd.count
cleanRdd.persist

def printValues(splitRdd: RDD[Log]) = {
	//2.3.1
	val ecs = splitRdd.map(x => x.bytes)
	val ecs_min = ecs.min
	println(ecs_min)
	val ecs_max = ecs.max
	println(ecs_max)
	val ecs_sum = ecs.reduce((x,y) => x + y)
	println(ecs_sum / ecs.count)

	println("\n----------------------------------------------------------------------------------------------------------------------------------------------\n")

	//2.3.2
	val cbv = splitRdd.map(x => x.status)
	cbv.persist
	val cbv2 = cbv.countByValue
	val cbv3 = cbv2.map(x => x._2 -> x._1).toList
	val cbv4 = sc.parallelize(cbv3).top(100)
	cbv4.foreach(println)

	println("\n----------------------------------------------------------------------------------------------------------------------------------------------\n")

	//2.3.3
	val fh = splitRdd.map(x => x.host)
	val fh2 = fh.countByValue.toList
	val fh2p = sc.parallelize(fh2).persist
	val fh3 = fh2p.filter(_._2 > 10)
	fh3.take(10).foreach(println)

	println("\n----------------------------------------------------------------------------------------------------------------------------------------------\n")

	//2.3.4
	val ep = splitRdd.map(x => (x.requestURI, x.status))
	ep.persist
	val ep2 = ep.filter(_._2 != 200)
	val ep3 = ep2.map(x => x._1)
	val ep4 = ep3.countByValue
	val ep5 = ep4.map(x => x._2 -> x._1).toList
	val ep6 = sc.parallelize(ep5).top(10)
	ep6.foreach(println) 

	println("\n----------------------------------------------------------------------------------------------------------------------------------------------\n")
	
	//2.3.5
	val uh3 = fh2p.filter(_._2 == 1)
	println(uh3.count)

	println("\n----------------------------------------------------------------------------------------------------------------------------------------------\n")

	//2.3.6
	val rc404 = splitRdd.map(x => x.status)
	val rc2_404 = cbv.filter(_ == 404)
	println(rc2_404.count)

	println("\n----------------------------------------------------------------------------------------------------------------------------------------------\n")

	//2.3.7
	val d2_404 = ep.filter(_._2 == 404)
	val d3_404 = d2_404.map(x => x._1)
	val d4_404 = d3_404.countByValue.toList
	val d4_404p = sc.parallelize(d4_404).persist
	val d5_404 = d4_404p.filter(_._2 == 1)
	val d6_404 = d5_404.map(x => x._1)
	d6_404.take(40).foreach(println)

	println("\n----------------------------------------------------------------------------------------------------------------------------------------------\n")

	//2.3.8
	val g5_404 = d4_404p.map(x => x._2 -> x._1)
	val g6_404 = g5_404.top(20)
	val g7_404 = g6_404.map(x => x._2)
	g7_404.foreach(println)
}

printValues(cleanRdd)



