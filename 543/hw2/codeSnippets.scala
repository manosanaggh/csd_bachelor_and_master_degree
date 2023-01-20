import org.apache.spark.mllib.linalg.{Vector, Vectors}
import org.apache.spark.mllib.regression.LabeledPoint
import org.apache.spark.mllib.evaluation.RegressionMetrics
import breeze.linalg.DenseVector
import org.apache.spark.rdd.RDD

/****Test gradientSummand
val example_w = DenseVector(1.0, 1.0, 1.0)
val example_lp = LabeledPoint(2.0, Vectors.dense(3, 1, 4))
gradientSummand(example_w, example_lp)

val example_w = DenseVector(.24, 1.2, -1.4)
val example_lp = LabeledPoint(3.0, Vectors.dense(-1.4, 4.2, 2.1))
gradientSummand(example_w, example_lp)
*****/


/*Unfinished implementation of lrgd. The function takes as input an
RDD of LabeledPoints and the number of Iterations and returns the model
parameters, and the list of rmse for each iteration. Fill with code the 
question marks (?) and debug.
*/
import scala.collection.mutable.ListBuffer
def lrgd(trData: RDD[LabeledPoint], numIter: Int): (DenseVector[Double], List[Double]) = {
  val n = trData.count
  val d = trData.first.features.size
  val alpha = 2
  val errorTrain = new ListBuffer[Double] 
  var weights = new DenseVector(Array.fill[Double](d)(0.0))
  for (i <- 0 until numIter){ 
    val gradient = ?
    val alpha_i = alpha / (n * Math.sqrt(i+1))
    weights = ?
    //update errorTrain
    val predsNLabelsTrain = ? //convert the training set into an RDD of (predictions, labels)
    errorTrain += calcRmse(predsNLabelsTrain)
  }
  (weights, errorTrain.toList)
}

/*********   test lrgd *********/
val exampleN = 4
val exampleD = 3
val exampleData = sc.parallelize(trainData.take(exampleN)).map(lp => LabeledPoint(lp.label, Vectors.dense(lp.features.toArray.slice(0, exampleD))))
val exampleNumIters = 50
val (exampleWeights, exampleErrorTrain) = lrgd(exampleData, exampleNumIters)
println(exampleWeights)
println(exampleErrorTrain)
/*******************************/

/********** MLLib + grid search*****************************/
import org.apache.spark.ml.regression.LinearRegression
import org.apache.spark.ml.linalg.{Vectors => MLVectors}
import org.apache.spark.ml.feature.{LabeledPoint => MLabeledPoint}

/*********************RDD conversion to Dataframe*****************/
val trainDataDF = trainData.map(lp => MLabeledPoint(lp.label, MLVectors.dense(lp.features.toArray))).toDF
val valDataDF = valData.map(lp => MLabeledPoint(lp.label, MLVectors.dense(lp.features.toArray))).toDF
val testDataDF = testData.map(lp => MLabeledPoint(lp.label, MLVectors.dense(lp.features.toArray))).toDF
/*******************************************************************/

/******Linear Regression Demo*********/
val lr=new LinearRegression().setMaxIter(50).setRegParam(0.1).setFitIntercept(true)
val lrModel = lr.fit(trainDataDF)
lrModel.evaluate(valDataDF).rootMeanSquaredError
/***************************************/


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
/*****************************************************/


/**** Use of pipelines ******************************/
import org.apache.spark.ml.feature.PolynomialExpansion
import org.apache.spark.ml.Pipeline
import org.apache.spark.ml.evaluation.RegressionEvaluator

val numIters = 500
val reg = 1e-10
val alpha = .2
val useIntercept = true
val polynomial_expansion = (new PolynomialExpansion).setInputCol("features").setOutputCol("polyFeatures").setDegree(?)
val lr3 = new LinearRegression()
lr3.setMaxIter(?).setRegParam(?).setElasticNetParam(?).setFitIntercept(?).setFeaturesCol("polyFeatures")

val pipeline = new Pipeline()
pipeline.setStages(?) //there are two stages here that you have to set.

val model=? //need to fit. Use the train Dataframe
val predictionsDF=? //Produce predictions on the test set. Use method transform.
val evaluator = new RegressionEvaluator()
evaluator.setMetricName("rmse")
val rmseTestPipeline = evaluator.evaluate(predictionsDF)
println(rmseTestPipeline)
