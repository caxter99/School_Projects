import java.util.stream.*;
import java.io.*;

public class EmployeeDemonstration implements Serializable
{
   // final int MAX_SCORE = 100;
//    final int MIN_SCORE = 0;
//    int[] testScores;
//       
//    public TestScores(int[] testScoresInit)
//    {
//       if (containsValidScores(testScoresInit)) {
//          testScores = testScoresInit;
//       }
//       else {
//          testScores = new int[0];
//       }
//    }
//    
//    private boolean containsValidScores(int[] scores)
//    {
//       for (int x = 0; x < scores.length; x++)
//       {
//          if (scores[x] < MIN_SCORE)
//          {
//             throw new IllegalArgumentException("Error: Scores cannot be less than " + MIN_SCORE);
//          }
//          else if (scores[x] > MAX_SCORE) {
//             throw new IllegalArgumentException("Error: Scores cannot be greater than " + MAX_SCORE);
//          }
//       }
//       
//       return true;
//    }
//    
//    public double getAverageTestScore()
//    {
//       return (float)IntStream.of(testScores).sum() / testScores.length;
//    }
//    
//    public void displayTestScores()
//    {
//       System.out.print("The test scores are: ");
//       for (int x = 0; x < testScores.length; x++)
//       {
//          System.out.print(testScores[x]);
//          if (x < testScores.length - 1)
//          {
//             System.out.print(", ");
//          }
//       }
//       System.out.println();
//    }
//    
//    public static void main(String[] args) throws Exception
//    {
//       final int NUM_OF_TEST_SCORES_OBJECTS = 6;
//       final String SERIALIZED_FILENAME = "serializedTestScores.ser";
//       
//       GenerateTestScores testScoreGenerator = new GenerateTestScores();
//       
//       TestScores[] validScores = new TestScores[NUM_OF_TEST_SCORES_OBJECTS];
//       for (int x = 0; x < validScores.length; x++)
//       {
//          validScores[x] = new TestScores(testScoreGenerator.generateValidTestScores((x + 1) * 2));
//       }
//       
//       System.out.println("Displaying all of the scores and their averages in each TestScores object:");
//       for (int x = 0; x < validScores.length; x++)
//       {
//          validScores[x].displayTestScores();
//          System.out.println("The average of the valid test scores is: " + validScores[x].getAverageTestScore());
//          System.out.println();
//       }
//       
//       System.out.println("Serializing the TestScores objects...");
//       
//       TestScoreSerializer testScoreSerializer = new TestScoreSerializer(SERIALIZED_FILENAME);
//       
//       for (int x = 0; x < validScores.length; x++)
//       {
//          testScoreSerializer.serializeTestScores(validScores[x]);
//       }
//       
//       testScoreSerializer.closeSerializer();
//       
//       System.out.println("Finished serializing the TestScores objects.");
//       
//       TestScoreDeserializer testScoreDeserializer = new TestScoreDeserializer(SERIALIZED_FILENAME);
//       
//       System.out.println("Deserializing those TestScores objects...");
//       
//       validScores = testScoreDeserializer.deserializeAllTestScores(validScores.length);
//       
//       System.out.println("Finished deserializing the TestScores objects.");
//       
//       System.out.println("Displaying all of the scores and their averages in each TestScores object after being deserialized:");
//       for (int x = 0; x < validScores.length; x++)
//       {
//          validScores[x].displayTestScores();
//          System.out.println("The average of the valid test scores is: " + validScores[x].getAverageTestScore());
//          System.out.println();
//       }
//       
//       int[] invalidTestScores = testScoreGenerator.generateInvalidTestScores(10);
//       TestScores invalidScores = new TestScores(invalidTestScores);
//    }
   
   public static void main(String[] args) throws Exception
   {
      // start here
   }
}