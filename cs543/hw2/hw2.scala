import org.apache.spark.rdd.RDD
import org.apache.spark.mllib.linalg.Vectors
import org.apache.spark.mllib.regression.LabeledPoint
import org.apache.spark.mllib.evaluation.{RankingMetrics, RegressionMetrics}
import breeze.linalg.DenseVector
import org.apache.spark.ml.regression.LinearRegression
import org.apache.spark.ml.linalg.{Vectors => MLVectors}
import org.apache.spark.ml.feature.{LabeledPoint => MLabeledPoint}
import scala.math
import org.apache.spark.ml.feature.PolynomialExpansion
import org.apache.spark.ml.Pipeline
import org.apache.spark.ml.evaluation.RegressionEvaluator

//1.1

val baseRdd = sc.textFile("/spare/csd3618/spark-3.0.2-bin-hadoop2.7/dataset.csv")

//1.2.1

baseRdd.count

//1.2.2

baseRdd.take(5).foreach(println)

//1.3.1

def getLabeledPoint(s:String): LabeledPoint = {
	val list = s.split(",").toList
	LabeledPoint(list(0).toDouble,Vectors.dense(list(1).toDouble,list(2).toDouble,list(3).toDouble,list(4).toDouble,list(5).toDouble,list(6).toDouble,
	list(7).toDouble,list(8).toDouble,list(9).toDouble,list(10).toDouble,list(11).toDouble,list(12).toDouble))
}

//1.3.2

val parsedPointsRdd = baseRdd.map(str => getLabeledPoint(str))

//1.3.3

val labelRdd = parsedPointsRdd.map(x => x.label)
labelRdd.take(1).foreach(println)

//1.3.4

val featuresRdd = parsedPointsRdd.map(x => x.features)
featuresRdd.take(1).foreach(println)

//1.3.5

println(parsedPointsRdd.take(1)(0).features.size)

//1.3.6

val minLabel = labelRdd.min
val maxLabel = labelRdd.max

//1.4.1

val shiftedPointsRdd = parsedPointsRdd.map(x => LabeledPoint(x.label-minLabel, x.features))

//1.4.2

val shiftedLabelsRdd = shiftedPointsRdd.map(x => x.label)
val minSLabel = shiftedLabelsRdd.min
val maxSLabel = shiftedLabelsRdd.max

//1.5.1

val weights = Array(.8, .1, .1)
val seed = 42
val Array(trainData, valData, testData) = shiftedPointsRdd.randomSplit(weights,seed)

//1.5.2

trainData.cache
valData.cache
testData.cache

//1.5.3

println(trainData.count)
println(valData.count)
println(testData.count) 
println(trainData.count+valData.count+testData.count == shiftedPointsRdd.count)

//2.1.1
val trainLabelsRdd = trainData.map(x => x.label)
val sumLabels = trainLabelsRdd.reduce((x,y) => x + y)
val average = sumLabels/trainLabelsRdd.count*/

//2.1.2

def baseLineModel(lp:LabeledPoint):Double = {
	average
}

//2.2

def calcRmse(rddDD: RDD[(Double,Double)]): Double = {
	val regressionMetrics = new RegressionMetrics(rddDD)
	regressionMetrics.rootMeanSquaredError
}

val spRddPredictions = shiftedPointsRdd.map(x => (baseLineModel(x), x.label))
calcRmse(spRddPredictions)

//2.3.1

val predsNLabelsTrain = trainData.map(x => (baseLineModel(x), x.label))
val predsNLabelsVal = valData.map(x => (baseLineModel(x), x.label))
val predsNLabelsTest = testData.map(x => (baseLineModel(x), x.label))

//2.3.2

println(calcRmse(predsNLabelsTrain))
println(calcRmse(predsNLabelsVal))
println(calcRmse(predsNLabelsTest))

//3.1

def gradientSummand(weights: DenseVector[Double], lp: LabeledPoint) : DenseVector[Double]= {
	val a : Array[Double] = lp.features.toArray
	val dlp = DenseVector(a)
	
	val gs =  (weights.dot(dlp) - lp.label) * dlp

	gs
}

val example_w = DenseVector(1.0, 1.0, 1.0)
val example_lp = LabeledPoint(2.0, Vectors.dense(3, 1, 4))
gradientSummand(example_w, example_lp)

val example_w = DenseVector(.24, 1.2, -1.4)
val example_lp = LabeledPoint(3.0, Vectors.dense(-1.4, 4.2, 2.1))
gradientSummand(example_w, example_lp)

//3.2

def getLabeledPrediction(weights: DenseVector[Double], lp: LabeledPoint) : (Double, Double)= {
	val a : Array[Double] = lp.features.toArray
	val dlp = DenseVector(a)
	
	(weights.dot(dlp), lp.label)
}

//3.3.1

/*Unfinished implementation of lrgd. The function takes as input an
RDD of LabeledPoints and the number of Iterations and returns the model
parameters, and the list of rmse for each iteration. Fill with code the 
question marks (?) and debug.
*/
import scala.collection.mutable.ListBuffer
def lrgd(trData: RDD[LabeledPoint], numIter: Int): (DenseVector[Double], List[Double]) = {
  val n = trData.count
  val d = trData.first.features.size
  val alpha = 0.0000000001
	println(alpha)
  val errorTrain = new ListBuffer[Double] 
  var weights = new DenseVector(Array.fill[Double](d)(0.0))
  for (i <- 0 until numIter){ 
    val gradient = trData.map(x => gradientSummand(weights, x)).reduce((x,y) => x + y)
    val alpha_i = alpha / (n * Math.sqrt(i+1))
    weights = weights - alpha_i * gradient
    //update errorTrain
    val predsNLabelsTrain = trData.map(x => getLabeledPrediction(weights, x)) //convert the training set into an RDD of (predictions, labels)
    errorTrain += calcRmse(predsNLabelsTrain)
  }
  (weights, errorTrain.toList)
}

//3.3.2

/*********   test lrgd *********/
val exampleN = 4
val exampleD = 3
val exampleData = sc.parallelize(trainData.take(exampleN)).map(lp => LabeledPoint(lp.label, Vectors.dense(lp.features.toArray.slice(0, exampleD))))
val exampleNumIters = 50
val (exampleWeights, exampleErrorTrain) = lrgd(exampleData, exampleNumIters)
println(exampleNumIters)
println(exampleWeights)
println(exampleErrorTrain)
/*******************************/



//4.1.1

val trainDataDF = trainData.map(lp => MLabeledPoint(lp.label, MLVectors.dense(lp.features.toArray))).toDF
val valDataDF = valData.map(lp => MLabeledPoint(lp.label, MLVectors.dense(lp.features.toArray))).toDF
val testDataDF = testData.map(lp => MLabeledPoint(lp.label, MLVectors.dense(lp.features.toArray))).toDF

val lr=new LinearRegression().setMaxIter(50).setRegParam(0.1).setFitIntercept(true)
val lrModel = lr.fit(trainDataDF)
println(s"Coefficients: ${lrModel.coefficients} Intercept: ${lrModel.intercept}")

//4.1.2

println(lrModel.evaluate(valDataDF).rootMeanSquaredError)

//4.1.3

val valPredictions = lrModel.transform(valDataDF)
valPredictions.select("prediction").show(10)

//4.2

val lr2=new LinearRegression().setMaxIter(50).setRegParam(1e-10).setFitIntercept(true)
val lr2Model = lr2.fit(trainDataDF)
lr2Model.evaluate(valDataDF).rootMeanSquaredError

val lr3=new LinearRegression().setMaxIter(50).setRegParam(1e-5).setFitIntercept(true)
val lr3Model = lr3.fit(trainDataDF)
lr3Model.evaluate(valDataDF).rootMeanSquaredError

val lr4=new LinearRegression().setMaxIter(50).setRegParam(1).setFitIntercept(true)
val lr4Model = lr4.fit(trainDataDF)
lr4Model.evaluate(valDataDF).rootMeanSquaredError

/*val lr5=new LinearRegression().setMaxIter(50).setRegParam(1000).setFitIntercept(true)
val lr5Model = lr5.fit(trainDataDF)
lr5Model.evaluate(valDataDF).rootMeanSquaredError

val lr5=new LinearRegression().setMaxIter(50).setRegParam(10000).setFitIntercept(true)
val lr5Model = lr5.fit(trainDataDF)
lr5Model.evaluate(valDataDF).rootMeanSquaredError

val lr5=new LinearRegression().setMaxIter(50).setRegParam(100).setFitIntercept(true)
val lr5Model = lr5.fit(trainDataDF)
lr5Model.evaluate(valDataDF).rootMeanSquaredError

val lr5=new LinearRegression().setMaxIter(50).setRegParam(10).setFitIntercept(true)
val lr5Model = lr5.fit(trainDataDF)
lr5Model.evaluate(valDataDF).rootMeanSquaredError

val lr5=new LinearRegression().setMaxIter(50).setRegParam(5).setFitIntercept(true)
val lr5Model = lr5.fit(trainDataDF)
lr5Model.evaluate(valDataDF).rootMeanSquaredError

val lr5=new LinearRegression().setMaxIter(50).setRegParam(0.001).setFitIntercept(true)
val lr5Model = lr5.fit(trainDataDF)
lr5Model.evaluate(valDataDF).rootMeanSquaredError*/

/*val lr5=new LinearRegression().setMaxIter(50).setRegParam(0.5).setFitIntercept(true)
val lr5Model = lr5.fit(trainDataDF)
lr5Model.evaluate(valDataDF).rootMeanSquaredError*/

val lr6=new LinearRegression().setMaxIter(50).setRegParam(0.4).setFitIntercept(true)
val lr6Model = lr6.fit(trainDataDF)
lr6Model.evaluate(valDataDF).rootMeanSquaredError

/*val lr7=new LinearRegression().setMaxIter(50).setRegParam(0.3).setFitIntercept(true)
val lr7Model = lr7.fit(trainDataDF)
lr7Model.evaluate(valDataDF).rootMeanSquaredError

val lr8=new LinearRegression().setMaxIter(50).setRegParam(0.2).setFitIntercept(true)
val lr8Model = lr8.fit(trainDataDF)
lr8Model.evaluate(valDataDF).rootMeanSquaredError*/

/*val lr6=new LinearRegression().setMaxIter(50).setRegParam(0.45).setFitIntercept(true)
val lr6Model = lr6.fit(trainDataDF)
lr6Model.evaluate(valDataDF).rootMeanSquaredError*/



/***** Quadratic Feature extraction for 5.1 ********/
implicit class Crossable[X](xs: Traversable[X]) {
  def cross[Y](ys: Traversable[Y]) = for { x <- xs; y <- ys } yield (x, y)
}

def quadFeatures(lp: LabeledPoint) = {
  val crossFeatures = lp.features.toArray.toList cross lp.features.toArray.toList
  val sqFeatures = crossFeatures.map(x => x._1 * x._2).toArray
  LabeledPoint(lp.label, Vectors.dense(sqFeatures))
}
val crossTrainDataRDD = trainData.map(lp => quadFeatures(lp))

val crossTrainDataRDDDFQ = crossTrainDataRDD.map(lp => MLabeledPoint(lp.label, MLVectors.dense(lp.features.toArray))).toDF

val crossValDataRDD = valData.map(lp => quadFeatures(lp))

val crossValDataRDDDFQ = crossValDataRDD.map(lp => MLabeledPoint(lp.label, MLVectors.dense(lp.features.toArray))).toDF

val crossTestDataRDD = testData.map(lp => quadFeatures(lp))

val crossTestDataRDDDFQ = crossTestDataRDD.map(lp => MLabeledPoint(lp.label, MLVectors.dense(lp.features.toArray))).toDF
/*****************************************************/



//5.2
val numIters = 500
val reg = 1e-10
val alpha = .2
val useIntercept = true
val lr3 = new LinearRegression()

lr3.setMaxIter(numIters).setRegParam(reg).setFitIntercept(useIntercept)
val lr3Model = lr3.fit(crossTrainDataRDDDFQ)

//5.3

lr3Model.evaluate(crossValDataRDDDFQ).rootMeanSquaredError

//5.4.1

println(lr3Model.evaluate(crossTestDataRDDDFQ).rootMeanSquaredError)

println(lr4Model.evaluate(testDataDF).rootMeanSquaredError)

//5.4.2

val crossTestDataPredictions = lr3Model.transform(crossTestDataRDDDFQ)
crossTestDataPredictions.select("prediction").show(50)

//5.5

val polynomial_expansion = (new PolynomialExpansion).setInputCol("features").setOutputCol("polyFeatures").setDegree(2)
val pipeline = new Pipeline()
pipeline.setStages(Array(polynomial_expansion, lr3)) //there are two stages here that you have to set.

val model = pipeline.fit(crossTrainDataRDDDFQ) //need to fit. Use the train Dataframe
val predictionsDF = model.transform(crossTestDataRDDDFQ) //Produce predictions on the test set. Use method transform.
val evaluator = new RegressionEvaluator()
evaluator.setMetricName("rmse")
val rmseTestPipeline = evaluator.evaluate(predictionsDF)
println(rmseTestPipeline)
