public class PhoneModel
{
   double cost;
   final double TAX_RATE = 0.06;
   
   public PhoneModel(int phoneModelNum)
   {
      setPhoneModel(phoneModelNum);
   }
   
   public void setPhoneModel(int phoneModelNum)
   {
      if (phoneModelNum == 1)
      {
         cost = 299.95;
      }
      else if (phoneModelNum == 2)
      {
         cost = 399.95;
      }
      else
      {
         cost = 499.95;
      }
   }
   
   public double getCost()
   {
      return cost + (cost * TAX_RATE);
   }
   
   public double getPhoneCost()
   {
      return cost;
   }
   
   public double getTax()
   {
      return cost * TAX_RATE;
   }
}