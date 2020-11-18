public class Cart
{
   Plan currentPlan;
   PhoneModel currentPhoneModel;
   ExtraOptions options;
   
   public Cart()
   {
      currentPlan = new Plan(1);
      currentPhoneModel = new PhoneModel(1);
      options = new ExtraOptions();
   }
   
   public void setPlan(int planNum)
   {
      currentPlan.setPlan(planNum);
   }
   
   public void setPhoneModel(int phoneModelNum)
   {
      currentPhoneModel.setPhoneModel(phoneModelNum);
   }
   
   public void setHasHotspot(boolean hotspot)
   {
      options.setHasHotspot(hotspot);
   }
   
   public void setHasInsurance(boolean insurance)
   {
      options.setHasInsurance(insurance);
   }
   
   public double getInitialCost()
   {
      return currentPhoneModel.getCost();
   }
   
   public double getMonthlyCost()
   {
      return currentPlan.getCost() + options.getCost();
   }
   
   public double getTotalCost()
   {
      return getInitialCost() + getMonthlyCost();
   }
}