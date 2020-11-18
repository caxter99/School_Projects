public class Plan
{
   double costPerMonth;
   
   public Plan(int planNum)
   {
      setPlan(planNum);
   }
   
   public void setPlan(int planNum)
   {
      if (planNum == 1)
      {
         costPerMonth = 45;
      }
      else if (planNum == 2)
      {
         costPerMonth = 65;
      }
      else
      {
         costPerMonth = 99;
      }
   }
   
   public double getCost()
   {
      return costPerMonth;
   }
}