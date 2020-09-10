import java.io.*;

public class TestScoreSerializer
{
   FileOutputStream outputStream;
   ObjectOutputStream outputFile;
   
   public TestScoreSerializer(String filename) throws Exception
   {
      outputStream = new FileOutputStream(filename);
      outputFile = new ObjectOutputStream(outputStream);
   }
   
   public void serializeTestScores(TestScores scores) throws Exception
   {
      outputFile.writeObject(scores);
   }
   
   public void closeSerializer() throws Exception
   {
      outputFile.close();
   }
}