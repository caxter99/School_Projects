import java.util.concurrent.ThreadLocalRandom;

public class GenerateTestScores
{
   private static final int MAX_VALID_INT = 100;
   private static final int MIN_VALID_INT = 0;
   
   private int getRandomInt()
   {
      return ThreadLocalRandom.current().nextInt(MIN_VALID_INT, MAX_VALID_INT + 1);
   }
   
   public int[] generateValidTestScores(int size)
   {
      int[] testScores = new int[size];
      
      for (int x = 0; x < size; x++)
      {
         testScores[x] = getRandomInt();
      }
      
      return testScores;
   }
}