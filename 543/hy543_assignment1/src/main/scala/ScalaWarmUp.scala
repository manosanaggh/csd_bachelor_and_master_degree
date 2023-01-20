object ScalaWarmUp{

  def getSecondToLast(lst: List[Int]):Int = lst match{
    case Nil => -1
    case n :: rest =>
      if(rest.size == 1)
        n
      else
        getSecondToLast(rest)
  }
  
  def getSecondToLastZip(lst: List[Int]): Int = {
    val lstWithIndex = lst.zipWithIndex
    val result = lstWithIndex.filter(_._2 == lst.size-2)
    result.head._1
  }
  
  def filterUnique(l: List[String]): List[String] = {
    val res = l.distinct
    res
  }
  
  def getMostFrequentSubstring(lst: List[String], k: Int):String = {
    val subl = lst.map(x => x.inits.flatMap(_.tails.toList.init).toList)
    val subl2 = subl.map(x => x.filter(_.length == k))
    val subl3 = subl2.flatten
    val subl4 = subl3.zipWithIndex
    val subl5 = subl4.groupBy(_._1)
    val subl6 = subl5.map(x => x._2)
    val subl7 = subl6.map(x => (x,x.size))
    val subl8 = subl7.map(x => x._2)
    val max_size = subl8.reduce((a,b) => a max b)
    val subl9 = subl7.filter(_._2 == max_size)
    val subl10 = subl9.map(x => x._1)
    val subl11 = subl10.flatten
    val subl12 = subl11.map(x => x._1)
    val subl13 = subl12.toList.distinct
    subl13(0)
  }
  
  //balanced parentheses
  /*def checkBalancedParentheses(lst: List[String]): Boolean = {
  }*/


  def main(args: Array[String]): Unit = {
    val my_list = List(1,2,3,4,5,6,7,8,9,10)
    println(getSecondToLast(my_list))
    println(getSecondToLast(my_list) == my_list(my_list.size-2))
    println(getSecondToLastZip(my_list))
    println(getSecondToLastZip(my_list) == my_list(my_list.size-2))
    val my_list2 = List("a", "a", "b", "b", "c", "d", "d")
    println(filterUnique(my_list2))
    println(filterUnique(List("c", "c", "d", "e", "e", "a", "a")))
    println(filterUnique(List("a", "c", "b", "b", "a", "c")))
    val my_list3 = List("abcd", "xwyuzfs", "klmbco")
    println(getMostFrequentSubstring(my_list3,2))
  }
} 
