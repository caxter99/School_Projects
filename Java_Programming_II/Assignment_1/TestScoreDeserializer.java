import java.io.*;

public class TestScoreDeserializer
{
   FileInputStream inputStream;
   ObjectInputStream inputFile;
   
   public TestScoreDeserializer(String filename) throws Exception
   {
      inputStream = new FileInputStream(filename);
      inputFile = new ObjectInputStream(inputStream);
   }
   
   public TestScores[] deserializeAllTestScores(int numberOfTestScoreObjects) throws Exception
   {
      TestScores[] scores = new TestScores[numberOfTestScoreObjects];
      for (int x = 0; x < scores.length; x++)
      {
         scores[x] = (TestScores)inputFile.readObject();
      }
      
      return scores;
   }
   
   public void closeDeserializer() throws Exception
   {
      inputFile.close();
   }
}