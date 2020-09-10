import java.util.concurrent.ThreadLocalRandom;

public class GenerateTestScores
{
   private static final int MAX_VALID_INT = 100;
   private static final int MIN_VALID_INT = 0;
   
   private int getRandomInt(int min, int max)
   {
      return ThreadLocalRandom.current().nextInt(min, max + 1);
   }
   
   public int[] generateValidTestScores(int size)
   {
      int[] testScores = new int[size];
      
      for (int x = 0; x < size; x++)
      {
         testScores[x] = getRandomInt(MIN_VALID_INT, MAX_VALID_INT);
      }
      
      return testScores;
   }
   
   public int[] generateInvalidTestScores(int size)
   {
      if (size <= 1) {
         return new int[0];
      }
      
      int[] validTestScores = generateValidTestScores(size);
      
      int x = 0;
      int invalidValueLocation = getRandomInt(0, size - 1);
      int[] invalidTestScores = new int[size];
      while (x < size)
      {
         if (x != invalidValueLocation) {
            invalidTestScores[x] = validTestScores[x];
         } else {
            if (invalidValueLocation % 2 == 0) {
               invalidTestScores[x] = getRandomInt(-(MAX_VALID_INT + 1), MIN_VALID_INT - 1);
            } else {
               invalidTestScores[x] = getRandomInt(MIN_VALID_INT + MAX_VALID_INT, MAX_VALID_INT + MAX_VALID_INT);
            }
         }
         x++;
      }
      
      return invalidTestScores;
   }
}