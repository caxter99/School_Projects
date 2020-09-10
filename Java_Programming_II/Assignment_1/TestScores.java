import java.util.stream.*;

public class TestScores
{
   final int MAX_SCORE = 100;
   final int MIN_SCORE = 0;
   int[] testScores;
      
   public TestScores(int[] testScoresInit)
   {
      if (containsValidScores(testScoresInit)) {
         testScores = testScoresInit;
      }
      else {
         testScores = new int[0];
      }
   }
   
   private boolean containsValidScores(int[] scores)
   {
      for (int x = 0; x < scores.length; x++)
      {
         if (scores[x] < MIN_SCORE)
         {
            throw new IllegalArgumentException("Error: Scores cannot be less than " + MIN_SCORE);
         }
         else if (scores[x] > MAX_SCORE) {
            throw new IllegalArgumentException("Error: Scores cannot be greater than " + MAX_SCORE);
         }
      }
      
      return true;
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
         }
      }
      System.out.println();
   }
   
   public static void main(String[] args) throws Exception
   {
      GenerateTestScores testScoreGenerator = new GenerateTestScores();
      
      int[] validTestScores = testScoreGenerator.generateValidTestScores(10);
      TestScores validScores = new TestScores(validTestScores);
      
      validScores.displayTestScores();
      System.out.println("The average of the valid test scores is: " + validScores.getAverageTestScore());
      
      int[] invalidTestScores = testScoreGenerator.generateInvalidTestScores(10);
      TestScores invalidScores = new TestScores(invalidTestScores);
   }
}