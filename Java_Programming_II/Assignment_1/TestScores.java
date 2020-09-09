import java.util.stream.*;

public class TestScores
{
   int[] testScores;
      
   public TestScores(int[] testScoresInit)
   {
      testScores = testScoresInit;
   }
   
   public double getAverageTestScore()
   {
      return (float)IntStream.of(testScores).sum() / testScores.length;
   }
   
   public void displayTestScores()
   {
      System.out.print("The test scores are: ");
      for (int x = 0; x < testScores.length; x++)
      {
         System.out.print(testScores[x]);
         if (x < testScores.length - 1)
         {
            System.out.print(", ");
         } else {
            System.out.println();
         }
      }
      System.out.println();
   }
   
   public static void main(String[] args) throws Exception
   {
      GenerateTestScores testScoreGenerator = new GenerateTestScores();
      
      int[] validTestScores = testScoreGenerator.generateValidTestScores(10);
      TestScores validScores = new TestScores(validTestScores);
      // test
      validScores.displayTestScores();
      System.out.println("The average of the valid test scores is: " + validScores.getAverageTestScore());
   }
}