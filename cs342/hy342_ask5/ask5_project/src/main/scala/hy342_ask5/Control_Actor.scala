package hy342_ask5

import akka.actor._
import akka.actor.Actor
import akka.actor.Props
import akka.actor.ActorSystem
import scala.io.StdIn

case class RegisterCtoT(t: Int, c: Int)
case class RegisterPtoT(t: Int, p: Int)
case class SendPAtoT(p:Int, t: Int, a: String)
case class ReadInputFromUser()

object Control_Actor_Object extends App{
  val system = ActorSystem("SimpleSystem")
  val server_actor = system.actorOf(Props[Server_Actor],"Server_Actor")

  //server actor
  class Server_Actor extends Actor{
    var AT:Map[Int,Array[String]] = Map()
    var PT:Map[Int,Array[Int]] = Map()
    var CT:Map[Int,Array[Int]] = Map()
    var CA:Map[Int,Array[String]] = Map()
    var R:Map[Int,Int] = Map()
    var p_counter = 1
    var c_counter = 1

    def receive = {
      //o server dexetai to aitima gia eggrafi tou producer se ena topic sto opoio thelei na stelnei arthra kai ton apothikeyei
      case RegisterPtoT(t, p) =>{
        if (!(PT contains p)) {
          PT += (p -> Array())
          println("Producer " + p + " registered to server")
          if ((PT contains p) && (t >= 1 && t <= 7)) {
            val A = PT(p) :+ t
            PT += (p -> A)
            println("Registered to " + newsTopics(t))
          }
          else println("topic " + t + " not inserted to producer " + p)
        }
        else {
          if ((PT contains p) && (t >= 1 && t <= 7)) {
            val A = PT(p) :+ t
            PT += (p -> A)
            println("Registered to " + newsTopics(t))
          }
          else println("topic " + t + " not inserted to producer " + p)
        }
        println()
    }

      //o server dexetai to aitima gia eggrafi tou consumer se ena topic sto opoio thelei na lamvanei arthra kai ton apothikeyei
      case RegisterCtoT(t, c) =>{
        if (!(CT contains c)) {
          CT += (c -> Array())
          println("Consumer " + c + " registered to server")
          if ((CT contains c) && (t >= 1 && t <= 7)) {
            val A = CT(c) :+ t
            CT += (c -> A)
            println("Registered to " + newsTopics(t))
          }
          else println("topic " + t + " not inserted to consumer " + c)
        }
        else {
          if ((CT contains c) && (t >= 1 && t <= 7)) {
            val A = CT(c) :+ t
            CT += (c -> A)
            println("Registered to " + newsTopics(t))
          }
          else println("topic " + t + " not inserted to consumer " + c)
        }
        println()
    }

      //o server paralambanei to arthro kai to dianemei stous consumers pou exoun eggrafei sto antistoixo topic
      case SendPAtoT(p, t, a) => {
        //o server elegxei ta topics ana producer
        if ((PT contains p) && (PT(p).contains(t))) {
          if (!(AT contains t)) {
            AT += (t -> Array())
            println("Topic " + t + " ready to include articles")

            if ((AT contains t) && (t >= 1 && t <= 7)) {
              val A = AT(t) :+ a
              AT += (t -> A)
              println("article '" + a + "' inserted to topic " + t)
              for ((k, v) <- CT) {
                if (v.contains(t)) {
                  CA += (k -> AT(t))
                  println("article '" + a + "' given to consumer " + k)
                  println("To arthro sou: "+a)
                }
              }
            }
            else println("article '" + a + "' not inserted to topic " + t)
          }
          else {
            if ((AT contains t) && (t >= 1 && t <= 7)) {
              val A = AT(t) :+ a
              AT += (t -> A)
              println("article '" + a + "' inserted to topic " + t)
              for ((k, v) <- CT) {
                if (v.contains(t)) {
                  CA += (k -> AT(t))
                  println("article '" + a + "' given to consumer " + k)
                  println("To arthro sou: "+a)
                }
              }
            }
            else println("article '" + a + "' not inserted to topic " + t)
          }
        }
        else {
          println("Error: Unregistered producer or producer does not have authority to write on this topic")
        }
        println()
      }

        case ReadInputFromUser()
        =>
        {
          println("Geia sou! Mporeis na epilekseis na diavaseis eidiseis anamesa sta epomena themata,")
          println("epelekse ton *arithmo tou topic sto opoio ")
          println("thes na eggrafeis apo to 1 mexri to 7 kai giayto to topic tha sou apostalei ena arthro, ")
          println("otan thes na stamatiseis dwse 0 kai gia kathe arithmo topic pou edwses tha sou epistrafei ena arthro: ")
          println()
          for ((k, v) <- newsTopics) {
            println("Topic: " + k + " -> " + v)
          }
          println()

          var x = 0

          x = StdIn.readInt()

          while (x != 0) {
            if (x >= 1 && x <= 7) {
              val producer = system.actorOf(Props[Producer], "Producer_" + p_counter)
              val consumer = system.actorOf(Props[Consumer], "Consumer_" + c_counter)
              producer ! RegisterPtoT(x, p_counter)
              consumer ! RegisterCtoT(x, c_counter)
              R += (p_counter -> x)
              p_counter += 1;
              c_counter += 1;
            }
            else {
              println("Topic number must be between 1 and 7 !")
            }
            x = StdIn.readInt()
          }

          for((k,v)<-R){
            server_actor ! SendPAtoT(k, v, "Arthro sxetiko me to topic " + newsTopics(v))
          }
        }
      }

    //epilogi thematwn eidisewn
    val newsTopics = Map(
      1 -> "Politics news",
      2 -> "Global news",
      3 -> "Sports news",
      4 -> "Weather news",
      5 -> "Church news",
      6 -> "Health news",
      7 -> "Army news"
    )
  }

  //producer-client actor
  class Producer extends Actor{
    def receive = {
      //o producer eggrafetai ston server
      case RegisterPtoT(t,p) => server_actor ! RegisterPtoT(t,p)
    }
  }

  //consumer-client actor
  class Consumer extends Actor{
    def receive = {
      //o consumer eggrafetai ston server
      case RegisterCtoT(t,c) => server_actor ! RegisterCtoT(t,c)
    }
  }

  server_actor ! ReadInputFromUser()

}



